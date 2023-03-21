//解析阿里云下发的cjson_parse
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include "modbusmaster_2_setitimer.h"

#include "include/MQTTClient.h"
#include "cJSON.h"
#include "modbus.h"


#define ADDRESS "gx6ivaaC8f8.iot-as-mqtt.cn-shanghai.aliyuncs.com:1883"
#define CLIENTID "lichee_modbus|securemode=3,signmethod=hmacsha1|"
#define TOPIC "/sys/gx6ivaaC8f8/lichee_modbus/thing/event/property/post"
#define TOPIC1 "/sys/gx6ivaaC8f8/lichee_modbus/thing/service/property/set"
#define QOS 1
#define TIMEOUT 10000L

char *username="lichee_modbus&gx6ivaaC8f8";
char *password="1181A8F770B69C4A3AE776E3BD949CF5A7A7BD12";

pthread_mutex_t mutex= PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;//for timer
pthread_mutex_t mutex2 =PTHREAD_MUTEX_INITIALIZER;//for cjson lock
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;

extern modbus_t *ctx;//task.json ./modbusmaster.c

int g_iRunFlag = 1;
double temperature = 0;
int temp=0;
double t= 0;
int count=0;

int msgarrvd(void *context,char *topicName, int topicLen,MQTTClient_message *message){

    printf("Recieve a message:(topic)%s,(msg)%s\n",topicName, (char *)message->payload);
    cJSON *root = cJSON_Parse(message->payload);
    if (!root){
        printf("Error before: [%s]\n",cJSON_GetErrorPtr());
        return -1;
    }else{
        cJSON *item = cJSON_GetObjectItem(root,"params");
        if(item!=NULL){
            cJSON *item1= cJSON_GetObjectItem(item,"temperature");
            if(item1!= NULL){
                /*item1有数据，无法解析*/
                printf("cJSON_GetObjectItem: type=%d, key is %s, value is %f\n",item1->type,item1->string,item1->valuedouble);
                temperature=item1->valuedouble;
                t=temperature-(int)temperature;
                while(temperature>1){
                    t=temperature/10;
                    count++;
                }
                t=t*count*10;
                modbus_write_register(ctx, 0,temperature);
                modbus_write_register(ctx, 1,t);

                printf("temperature is %f,%f\n",temperature,t);
            }
            cJSON_Delete(root);
        }
    }
/*     if(0 == strcmp(message->payload,"quit")){
        g_iRunFlag = 0;
    } */
    MQTTClient_freeMessage(&message);
 //   MQTTClient_free(topicName);
//    return 0;
}

int main(int argc,char* argv[]){
    //声明
    MQTTClient client;

    char *PAYLOAD=NULL;
    int rc = 0;

    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;

    modbus_init();

    if((rc=MQTTClient_create(&client,ADDRESS,CLIENTID,
                    MQTTCLIENT_PERSISTENCE_NONE,NULL))!=MQTTCLIENT_SUCCESS){
        printf("Failed to create client, return code %d\n", rc);
        MQTTClient_destroy(&client);
        return -1;
    }

    if(MQTTClient_setCallbacks(client,NULL,NULL,msgarrvd,NULL) != MQTTCLIENT_SUCCESS){
        printf("Failed to set callbacks, return code %d\n",rc);
        MQTTClient_destroy(&client);
        return -1;
    }

    conn_opts.keepAliveInterval=30;
    conn_opts.cleansession =1;
    conn_opts.username = username;
    conn_opts.password = password;

    rc=MQTTClient_connect(client,&conn_opts);
    if(rc!=MQTTCLIENT_SUCCESS) {
        printf("Failed to connect, return code %d\n",rc);
        exit(EXIT_FAILURE);
    }

    //订阅主题，参数，句柄，主题，QOS质量
    rc = MQTTClient_subscribe(client,TOPIC1,QOS);
    if(rc != MQTTCLIENT_SUCCESS){
        printf("Failed to SUBSCRIBE, return code %d\n",rc);
        MQTTClient_destroy(&client);
        return -1;
    }
    while(1){
        modbusmaster();

        cJSON *croot = cJSON_CreateObject();
        cJSON *params = cJSON_CreateObject();
        cJSON *sys = cJSON_CreateObject();
        cJSON *Power = cJSON_CreateObject();
        cJSON *WF = cJSON_CreateObject();


        cJSON_AddItemToObject(sys, "ack", cJSON_CreateNumber(0));
        cJSON_AddItemToObject(Power, "value", cJSON_CreateString("on"));
        cJSON_AddItemToObject(Power, "time", cJSON_CreateNumber(1524448722000));
        cJSON_AddItemToObject(params, "Power",Power);
        cJSON_AddItemToObject(WF, "value", cJSON_CreateNumber(temperature));
        //cJSON_AddItemToObject(WF, "time", cJSON_CreateNumber(1524448722000));
        cJSON_AddItemToObject(params, "temperature",WF);
        //数组reputation

        cJSON_AddItemToObject(croot,"id",cJSON_CreateString("123"));
        cJSON_AddItemToObject(croot,"version",cJSON_CreateString("1.0"));
        cJSON_AddItemToObject(croot,"sys",sys);
        cJSON_AddItemToObject(croot,"params",params);
        cJSON_AddItemToObject(croot,"method",cJSON_CreateString("thing.event.property.post"));

        //printf("%s\n",cJSON_Print(croot));
        PAYLOAD = cJSON_Print(croot);

        pubmsg.payload =PAYLOAD;
        pubmsg.payloadlen  = (int)strlen(PAYLOAD);
        pubmsg.qos = QOS;
        pubmsg.retained = 0;

        MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);

        printf("waiting for up to %d seconds for publication of\n%s\n"
        "on topic %s\nfor client with ClientID:%s\n",
        (int)(TIMEOUT/1000),PAYLOAD,TOPIC,CLIENTID);

        rc = MQTTClient_waitForCompletion(client,token,TIMEOUT);
        printf("Message with delivery token %d delivered\n",token);

        cJSON_Delete(croot);
        sleep(10);
    }
    MQTTClient_disconnect(client,10000);
    MQTTClient_destroy(&client);
    return rc;
}
