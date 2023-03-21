#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "MQTTClient.h"
#if !defined(WIN32)
#include <unistd.h>
#else
#include <windows.h>
#endif
#include "cJSON.h"

#include "timer.h"
#include "modbusmaster.h"

#define ADDRESS     "gx6iPJPKbW2.iot-as-mqtt.cn-shanghai.aliyuncs.com:1883"//更改此处地址
#define CLIENTID    "test|securemode=3,signmethod=hmacsha1|" //更改此处客户端ID
#define TOPIC       "/sys/gx6iPJPKbW2/test/thing/event/property/post" //更改发送的话题
#define TOPIC1      "/sys/gx6iPJPKbW2/test/thing/service/property/set"
#define PAYLOAD     "Hello Man, Can you see me ?!" //更改信息内容
#define QOS         1
#define TIMEOUT     10000L
MQTTClient client;
//char * PAYLOAD;
int main(int argc, char* argv[]){
    int rc;
    char *username =  "test&gx6iPJPKbW2";
    char *password = "C878249B6C7406FBD6EDB179B26A2AAE62F9CD0C";
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    conn_opts.keepAliveInterval = 30;
    conn_opts.cleansession = 1;
    conn_opts.username = username;
    conn_opts.password = password;

    MQTTClient_create(&client,ADDRESS,CLIENTID,MQTTCLIENT_PERSISTENCE_NONE,NULL);

    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS){
        printf("Failed to connect, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }
    pubmsg.payload =PAYLOAD;
    pubmsg.payloadlen = strlen(PAYLOAD);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;

    while(1){

        MQTTClient_publishMessage(client,TOPIC,&pubmsg,&token);
        printf("Waiting for up to %d seconds for publication of %s\n"
                "on topic %s for client with ClientID: %s\n",
                (int)(TIMEOUT/1000),PAYLOAD,TOPIC,CLIENTID);
        rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
        printf("Message with delivery token %d delivered\n", token);
        sleep(5);
    }
}
