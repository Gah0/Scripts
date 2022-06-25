#include <stdio.h>
#include "cJSON.h"

int main(){
    cJSON *croot = cJSON_CreateObject();  
    cJSON *album= cJSON_CreateObject();  
    cJSON *rep_itm=cJSON_CreateObject();  
    cJSON *rep_arr = cJSON_CreateArray();  

    cJSON_AddItemToObject(rep_itm, "song", cJSON_CreateString("READY FOR IT"));
    cJSON_AddItemToObject(rep_itm, "song", cJSON_CreateString("End GAME"));
    cJSON_AddItemToArray(rep_arr,rep_itm);
    //数组reputation

    cJSON_AddItemToObject(album,"1989",cJSON_CreateString("Style"));
        //album节点下第二个key - value
    cJSON_AddItemToObject(album,"Reputation",rep_arr);

    //album 节点下的最后一个key value
    cJSON_AddItemToObject(album,"Lover",cJSON_CreateString("Miss Americana & the heartbreak prince"));

    cJSON_AddItemToObject(croot,"name",cJSON_CreateString("Taylor Swift"));
    cJSON_AddItemToObject(croot,"age",cJSON_CreateNumber(31));
    cJSON_AddItemToObject(croot,"album",album);
    cJSON_AddItemToObject(croot,"address",cJSON_CreateString("Tennessee"));
    printf("%s\n",cJSON_Print(croot));
    return 0;
}
