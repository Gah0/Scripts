#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "MQTTClient.h"
#include <unistd.h>

#include "cJSON.h"
#include "modbus.h"
#include "timer.h"
#include "modbusmaster.h"

#define ADDRESS     "gx6iPJPKbW2.iot-as-mqtt.cn-shanghai.aliyuncs.com:1883"
#define CLIENTID    "device1|securemode=3,signmethod=hmacsha1|"
#define TOPIC       "/sys/gx6iPJPKbW2/test/thing/event/property/post"
#define TOPIC1      "/sys/gx6iPJPKbW2/test/thing/service/property/set"
#define QOS         1
#define TIMEOUT     10000L


int g_iRunFlag = 1;
double temperature=0;
int temp;
char * PAYLOAD;
char *p;
extern int timerflag;
pthread_t modbus,mqtt;
cJSON * root;
MQTTClient client;
extern modbus_t *ctx;

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message){
    printf("Recieve a message: (topic)%s, (msg)%s\n", topicName, (char*)message->payload);
    cJSON *root=cJSON_Parse(message->payload);

    if (!root){
        printf("Error before: [%s]\n",cJSON_GetErrorPtr());
        return -1;
    }else{
        cJSON *item=cJSON_GetObjectItem(root,"params");
        if(item!=NULL){
            cJSON *item1=cJSON_GetObjectItem(item,"temperature");
            if(item1!=NULL) {
                printf("cJSON_GetObjectItem: type=%d, key is %s, value is %f\n",item1->type,item1->string,item1->valuedouble);
                temperature=item1->valuedouble;
                temp=temperature*10;
                modbus_write_register(ctx, 0,temp);
                printf("temperature is %f",temperature);
            }
            cJSON_Delete(root);
        }
    }
    MQTTClient_freeMessage(&message);
    return 1;
}





int Mqtt_init(void){
    int rc;
    char *username =  "test&gx6iPJPKbW2";
    char *password = "C878249B6C7406FBD6EDB179B26A2AAE62F9CD0C";
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;


    if((rc=MQTTClient_create(&client,ADDRESS,CLIENTID,
                    MQTTCLIENT_PERSISTENCE_NONE,NULL))!=MQTTCLIENT_SUCCESS){
        printf("Failed to create client, return code %d\n", rc);
        MQTTClient_destroy(&client);
        return -1;
    }

    if((rc = MQTTClient_setCallbacks(client, NULL, NULL, msgarrvd, NULL)) != MQTTCLIENT_SUCCESS){
        printf("Failed to set callbacks, return code %d n", rc);
        MQTTClient_destroy(&client);
        return -1;
    }

    conn_opts.keepAliveInterval = 30;
    conn_opts.cleansession = 1;
    conn_opts.username = username;
    conn_opts.password = password;

    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS){
        printf("Failed to connect, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }

    if ((rc = MQTTClient_subscribe(client, TOPIC1, QOS)) != MQTTCLIENT_SUCCESS){
        printf("Failed to subscribe, return code %d\n", rc);
        MQTTClient_destroy(&client);
        return -1;
    }
    return 1;
}

int Alink_pub(void){
        root = cJSON_CreateObject();
        cJSON *params = cJSON_CreateObject();
        cJSON *sys = cJSON_CreateObject();
        cJSON *Power = cJSON_CreateObject();
        cJSON *WF = cJSON_CreateObject();

        cJSON_AddItemToObject(sys,"ack",cJSON_CreateNumber(0));

        cJSON_AddItemToObject(Power,"value",cJSON_CreateString("on"));
        cJSON_AddItemToObject(Power,"time",cJSON_CreateNumber(1524448722000));
        cJSON_AddItemToObject(params,"power", Power);
        cJSON_AddItemToObject(WF,"value",cJSON_CreateNumber(temperature));
        cJSON_AddItemToObject(params,"temperature", WF);

        cJSON_AddItemToObject(root,"id",cJSON_CreateString("123"));
        cJSON_AddItemToObject(root,"version",cJSON_CreateString("1.0"));//根节点下添加第二个键
        cJSON_AddItemToObject(root,"sys",sys);
        cJSON_AddItemToObject(root,"params", params );
        cJSON_AddItemToObject(root,"method", cJSON_CreateString("thing.event.property.post"));
    //  printf("%s\n"， CJSON Print(root));
        PAYLOAD=cJSON_Print(root);
        return PAYLOAD;
}

pthread_mutex_t mutex= PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;//for timer
pthread_mutex_t mutex2 =PTHREAD_MUTEX_INITIALIZER;//for cjson lock
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;


void *modbuspth(void *arg){
    modbus_init();
    while(1){
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond,&mutex);
        pthread_mutex_lock(&mutex2);

        modbusmaster();

        pthread_mutex_unlock(&mutex2);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond2);

    }
}

void *mqttpth(void *arg){
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc;

    rc=Mqtt_init();
    if(rc==1){
        printf("success init, return code %d\n", rc);
    }

    while(1){

        pthread_mutex_lock(&mutex2);
        pthread_cond_wait(&cond2,&mutex2);
        p=Alink_pub();
        if(p){
            printf("sucess create JSON by Alink_pub()");
        }else{
            printf("create JSON failed");
            cJSON_Delete(root);
        }

        pthread_mutex_unlock(&mutex2);

        pubmsg.payload =p;
        pubmsg.payloadlen = strlen(p);
        pubmsg.qos = QOS;
        pubmsg.retained = 0;

        MQTTClient_publishMessage(client,TOPIC,&pubmsg,&token);
        printf("Waiting for up to %d seconds for publication of %s\n"
                "on topic %s for client with ClientID: %s\n",
                (int)(TIMEOUT/1000),PAYLOAD,TOPIC,CLIENTID);
        rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
        printf("Message with delivery token %d delivered\n", token);

        cJSON_Delete(root);
    }

    // sleep(5);
    MQTTClient_disconnect(client,10000);
    MQTTClient_destroy(&client);
    //return rc;
}

int main(int argc, char* argv[]){

    timer_init();

    pthread_create(&modbus,NULL,modbuspth,NULL);
    pthread_create(&mqtt,NULL,mqttpth,NULL);
    printf("p_create modbus and mqtt");
    pthread_join(mqtt,NULL);
    pthread_join(modbus,NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}
