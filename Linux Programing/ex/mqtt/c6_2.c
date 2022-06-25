#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/MQTTClient.h"
#include <unistd.h>
#include "cJSON.h"



#define ADDRESS "gx6ivaaC8f8.iot-as-mqtt.cn-shanghai.aliyuncs.com:1883" 
#define CLIENTID "mqtt_cjson|securemode=3,signmethod=hmacsha1|" 
#define TOPIC "/sys/gx6ivaaC8f8/mqtt_cjson/thing/event/property/post"  
#define TOPIC1 "/sys/gx6ivaaC8f8/mqtt_cjson/thing/service/property/set"  
#define QOS 1
#define TIMEOUT 10000L

int g_iRunFlag = 1;


int main(int argc,char* argv[]){
    //声明
    MQTTClient client;

    char *PAYLOAD=NULL;
    int rc = 0;
    char *username="mqtt_cjson&gx6ivaaC8f8";
    char *password="F23E8669D13EF686D18EEB85C58D0A6DC248D948";


    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;

    if((rc=MQTTClient_create(&client,ADDRESS,CLIENTID,
                    MQTTCLIENT_PERSISTENCE_NONE,NULL))!=MQTTCLIENT_SUCCESS){
        printf("Failed to create client, return code %d\n", rc);
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

    rc = MQTTClient_subscribe(client,TOPIC,QOS);
    if(rc != MQTTCLIENT_SUCCESS){
        printf("Failed to SUBSCRIBE, return code %d\n",rc);
        MQTTClient_destroy(&client);
        return -1;
    }

    cJSON *croot = cJSON_CreateObject();  
    cJSON *params = cJSON_CreateObject();
    cJSON *sys = cJSON_CreateObject();
    cJSON *Power = cJSON_CreateObject();
    cJSON *WF = cJSON_CreateObject();

    cJSON_AddItemToObject(sys, "ack", cJSON_CreateNumber(0));
    cJSON_AddItemToObject(Power, "value", cJSON_CreateString("on"));
    cJSON_AddItemToObject(Power, "time", cJSON_CreateNumber(1524448722000));
    cJSON_AddItemToObject(params, "Power",Power);
    cJSON_AddItemToObject(WF, "value", cJSON_CreateNumber(23.6));
    //cJSON_AddItemToObject(WF, "time", cJSON_CreateNumber(1524448722000));
    cJSON_AddItemToObject(params, "temperature",WF);
    //数组reputation

    cJSON_AddItemToObject(croot,"id",cJSON_CreateString("123"));
    cJSON_AddItemToObject(croot,"version",cJSON_CreateString("1.0"));
    cJSON_AddItemToObject(croot,"sys",sys);
    cJSON_AddItemToObject(croot,"params",params);
    cJSON_AddItemToObject(croot,"method",cJSON_CreateString("thing.event.property.post"));
    
    printf("%s\n",cJSON_Print(croot));
    PAYLOAD = cJSON_Print(croot);

    pubmsg.payload =PAYLOAD;
    pubmsg.payloadlen  = (int)strlen(PAYLOAD);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    while(1){
        MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);

        printf("waiting for up to %d seconds for publication of %s\n"
        "on topic %s\n for client with ClientID:%s\n",
        (int)(TIMEOUT/1000),PAYLOAD,TOPIC,CLIENTID);

        rc = MQTTClient_waitForCompletion(client,token,TIMEOUT);
        printf("Message with delivery token %d delivered\n",token);
        sleep(5);
    } 
/*    MQTTClient_disconnect(client,10000);
    MQTTClient_destroy(&client);
    return rc;*/
}