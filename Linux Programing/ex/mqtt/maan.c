#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include"MQTTClient.h"

#define EXAMPLE_PRODUCT_KEY     "gx6ijQjFubS"
#define EXAMPLE_DEVICE_NAME     "mqtt_client"
#define EXAMPLE_DEVICE_SECRET   "a67ee613df2710db6da1d91af6d0839c"

extern int aiotMqttSign(const char *productKey, const char *deviceName, const char *deviceSecret,char clientId[150], char username[64], char password[65]);

int main(int argc, char**argv)
{
        int rc = 0;
        char *host=EXAMPLE_PRODUCT_KEY".iot-as-mqtt.cn-shanghai.aliyuncs.com";
        const char *subTopic = "/"EXAMPLE_PRODUCT_KEY"/"EXAMPLE_DEVICE_NAME"/user/get";
        const char *pubTopic = "/"EXAMPLE_PRODUCT_KEY"/"EXAMPLE_DEVICE_NAME"/user/update";

        char address[100] = {0};
        char clientId[150] = {0};
        char username[65] = {0};
        char password[65] = {0};

        char buf[1024];
        const int time_out=1000;
        int rv;
        int QOS=1;

        if ((rc = aiotMqttSign(EXAMPLE_PRODUCT_KEY, EXAMPLE_DEVICE_NAME, EXAMPLE_DEVICE_SECRET, clientId, username, password) < 0)) {
                printf("aiotMqttSign -%0x4x\n", -rc);
                return -1;
        }
        sprintf(address, "tcp://%s", host);
        printf("address %s\n", address);
        printf("clientid: %s\n", clientId);
        printf("username: %s\n", username);
        printf("password: %s\n", password);


        MQTTClient client;
        MQTTClient_connectOptions conn_opts=MQTTClient_connectOptions_initializer;
        MQTTClient_message publish_msg=MQTTClient_message_initializer;
        MQTTClient_deliveryToken token;

        conn_opts.keepAliveInterval=60;
        conn_opts.cleansession=1;
        conn_opts.username = username;
        conn_opts.password = password;

        MQTTClient_create(&client, address, clientId, MQTTCLIENT_PERSISTENCE_NONE, NULL);
        if((rv=MQTTClient_connect(client, &conn_opts))!=MQTTCLIENT_SUCCESS)
        {
                printf("MQTTClient_connect failure:%s\n",strerror(errno) );
                return 0;
        }
        publish_msg.qos=QOS;
        publish_msg.retained=0;
        while(1)
        {
                printf("enter the message you want to send:");
                fgets(buf,sizeof(buf), stdin);
                publish_msg.payload=(void *)buf;
                publish_msg.payloadlen=strlen(buf);
                MQTTClient_publishMessage(client, pubTopic, &publish_msg, &token);
                printf("waiting for %d seconds for publication of %s on topic %s for client with CLIENTD:%s\n",time_out/1000,buf,pubTopic, clientId);
                rv = MQTTClient_waitForCompletion(client, token, time_out);
                printf("Message with delivery token %d delivery\n",rv);
                printf("%s\n",buf);
                sleep(3);
        }
}

int aiotMqttSign(const char *productKey, const char *deviceName, const char *deviceSecret,
                     char clientId[150], char username[64], char password[65])
{
    char deviceId[PRODUCTKEY_MAXLEN + DEVICENAME_MAXLEN + 2] = {0};
    char macSrc[SIGN_SOURCE_MAXLEN] = {0};
    uint8_t macRes[32] = {0};
    int res;

    /* check parameters */
    if (productKey == NULL || deviceName == NULL || deviceSecret == NULL ||
        clientId == NULL || username == NULL || password == NULL) {
        return -1;
    }
    if ((strlen(productKey) > PRODUCTKEY_MAXLEN) || (strlen(deviceName) > DEVICENAME_MAXLEN) ||
        (strlen(deviceSecret) > DEVICESECRET_MAXLEN)) {
        return -1;
    }

    /* setup deviceId */
    memcpy(deviceId, deviceName, strlen(deviceName));
    memcpy(deviceId + strlen(deviceId), "&", strlen("&"));
    memcpy(deviceId + strlen(deviceId), productKey, strlen(productKey));

    /* setup clientid */
    memcpy(clientId, deviceId, strlen(deviceId));
    memcpy(clientId + strlen(deviceId), MQTT_CLINETID_KV, strlen(MQTT_CLINETID_KV));
    memset(clientId + strlen(deviceId) + strlen(MQTT_CLINETID_KV), 0, 1);

    /* setup username */
    memcpy(username, deviceId, strlen(deviceId));
    memset(username + strlen(deviceId), 0, 1);

    /* setup password */
    memcpy(macSrc, "clientId", strlen("clientId"));
    memcpy(macSrc + strlen(macSrc), deviceId, strlen(deviceId));
    memcpy(macSrc + strlen(macSrc), "deviceName", strlen("deviceName"));
    memcpy(macSrc + strlen(macSrc), deviceName, strlen(deviceName));
    memcpy(macSrc + strlen(macSrc), "productKey", strlen("productKey"));
    memcpy(macSrc + strlen(macSrc), productKey, strlen(productKey));
    memcpy(macSrc + strlen(macSrc), "timestamp", strlen("timestamp"));
    memcpy(macSrc + strlen(macSrc), TIMESTAMP_VALUE, strlen(TIMESTAMP_VALUE));

    utils_hmac_sha256((uint8_t *)macSrc, strlen(macSrc), (uint8_t *)deviceSecret,
                      strlen(deviceSecret), macRes);

    memset(password, 0, PASSWORD_MAXLEN);
    _hex2str(macRes, sizeof(macRes), password);
    return 0;
}