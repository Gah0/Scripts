#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/MQTTClient.h"
#include <unistd.h>
#include "cJSON.h"



#define ADDRESS "gx6iJwqHb4C.iot-as-mqtt.cn-shanghai.aliyuncs.com:1883" 
#define CLIENTID "mqtt_client|securemode=3,signmethod=hmacsha1|" 
#define TOPIC "/sys/gx6iJwqHb4C/mqtt_client/thing/event/property/post"  
#define TOPIC1 "/sys/gx6iJwqHb4C/mqtt_client/thing/service/property/set"  
#define QOS 1
#define TIMEOUT 10000L
#define PAYLOAD "CAN YOU SEE ME?"
int g_iRunFlag = 1;


int main(int argc,char* argv[]){
    //声明
    MQTTClient client;


    int rc = 0;
    char *username="mqtt_client&gx6iJwqHb4C";
    char *password="90EAA627740BC99450FF628E11A7FC9ACDD3D07D";


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

    if(MQTTClient_connect(client,&conn_opts)!=MQTTCLIENT_SUCCESS) {
        printf("Failed to connect, return code %d\n",rc);
        exit(EXIT_FAILURE);
    }

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