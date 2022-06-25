#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/MQTTClient.h"
#include <unistd.h>



#define ADDRESS "gx6ijQjFubS.iot-as-mqtt.cn-shanghai.aliyuncs.com:1883" 
#define CLIENTID "mqtt_client|securemode=3,signmethod=hmacsha1|" 
#define TOPIC "/sys/gx6irHQ3rix/mqtt_client/thing/event/property/post"  
#define PAYLOAD "Hello man,can you see me?"
#define QOS 1
#define TIMEOUT 10000L


int main(int argc,char* argv[]){
    //声明
    MQTTClient client;
    char *username="mqtt_client&gx6ijQjFubS";
    char *password="63CECA34C34D81434FA1F3017B98C95B7B254CB4";

    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;

    int rc;

    if((rc=MQTTClient_create(&client,ADDRESS,CLIENTID,
                    MQTTCLIENT_PERSISTENCE_NONE,NULL))!=MQTTCLIENT_SUCCESS){
        printf("Failed to create client, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }

    conn_opts.keepAliveInterval=30;
    conn_opts.cleansession =1;
    conn_opts.username = username;
    conn_opts.password = password;

  /* <b>2</b>: Connection refused: Identifier rejected<br>*/
    if((rc=MQTTClient_connect(client,&conn_opts))!=MQTTCLIENT_SUCCESS) {
        printf("Failed to connect, return code %d\n",rc);
        exit(EXIT_FAILURE);
    }

    pubmsg.payload =PAYLOAD;
    pubmsg.payloadlen  = (int)strlen(PAYLOAD);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;

    while(1){
        if ((rc = MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token)) != MQTTCLIENT_SUCCESS)
        {
            printf("Failed to publish message, return code %d\n", rc);
            exit(EXIT_FAILURE);
        }

        printf("waiting for up to %d seconds for publication of %s\n"
                "on tapic %s for client with ClientID:%s\n",
                    (int)(TIMEOUT/1000,PAYLOAD,TOPIC,CLIENTID));
        rc = MQTTClient_waitForCompletion(client,token,TIMEOUT);
        printf("Message with delivery token %d delivered\n",token);
        sleep(5);
    }
/*    MQTTClient_disconnect(client,10000);
    MQTTClient_destroy(&client);
    return rc;*/
}