#include "iot_app.h"
#include "db_helper.h"
#include <MQTTClient.h>
#include <cjson/cJSON.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "shared.h"
#include <stdbool.h>
#include <time.h>
#define BATCH_SIZE 10 // จำนวน JSON ต่อการส่ง

// ข้อมูล MQTT Broker และ Topic
const char MQTT_BROKER[] = "tcp://broker.emqx.io:1883";
const char MQTT_CLIENTID[] = "TGR2024_MQTT_CLIENT";
const char SUBSCRIBE_TOPIC[] = "******";
const char PUBLISH_TOPIC[] = "data/raspberry/prediction";
const char OPEN_TOPIC[] = "data/raspberry/open";   // topic สำหรับเปิด
const char CLOSE_TOPIC[] = "data/raspberry/close"; // topic สำหรับปิด
const char DB_OUTCOME_NAME[] = "/home/wupi/Desktop/finalProject10/outcome_data.db";

struct timespec start, end;
long elapsed_time_ms = 0;

// ประกาศตัวแปร thread
pthread_t fft_thread;
pthread_t publish_thread;

// ฟังก์ชัน FFT Thread สำหรับการประมวลผลสัญญาณ
extern void *fft_thr_fcn(void *arg);

typedef struct
{
    char *json_payload;
} PublishData;
void *pubsub_thr_fcn(void *ptr)
{
    int rc;

    printf("Starting MQTT pubsub thread\n");

    MQTTClient mqtt_client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_create(&mqtt_client, MQTT_BROKER, MQTT_CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    if ((rc = MQTTClient_connect(mqtt_client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }

    // สมัครรับคำสั่งจาก OPEN_TOPIC และ CLOSE_TOPIC
    MQTTClient_subscribe(mqtt_client, OPEN_TOPIC, 0);  // สมัครรับ OPEN_TOPIC
    MQTTClient_subscribe(mqtt_client, CLOSE_TOPIC, 0); // สมัครรับ CLOSE_TOPIC

    while (1)
    {
        char *topic = NULL;
        int message_len;
        MQTTClient_message *received_message = NULL;

        // รับคำสั่งจากทั้ง OPEN_TOPIC และ CLOSE_TOPIC
        if (MQTTClient_receive(mqtt_client, &topic, &message_len, &received_message, 1000) == MQTTCLIENT_SUCCESS && received_message != NULL)
        {
            printf("Received message from topic %s: %s\n", topic, (char *)received_message->payload);

            if (strcmp(topic, OPEN_TOPIC) == 0 && !is_running)
            {
                // เมื่อได้รับคำสั่งจาก OPEN_TOPIC ให้เริ่มส่งข้อมูล
                is_running = 1;
                printf("Start publishing outcome data\n");

                // ลบข้อมูลเก่าในฐานข้อมูล outcome
                if (dbase_clear(DB_OUTCOME_NAME, "outcome_table") != 0)
                {
                    fprintf(stderr, "Failed to clear outcome database\n");
                }
                else
                {
                    printf("Cleared outcome database\n");
                }
            }
            else if (strcmp(topic, CLOSE_TOPIC) == 0 && is_running)
            {
                // เมื่อได้รับคำสั่งจาก CLOSE_TOPIC ให้หยุดส่งข้อมูล
                is_running = 0;
                printf("Stopped publishing outcome data\n");
            }

            // เคลียร์ข้อมูล
            MQTTClient_freeMessage(&received_message);
            MQTTClient_free(topic);
        }

        if (is_running)
        {
            if (MQTTClient_receive(mqtt_client, &topic, &message_len, &received_message, 1000) == MQTTCLIENT_SUCCESS && received_message != NULL)
            {
                printf("Received message from topic %s: %s\n", topic, (char *)received_message->payload);

                if (strcmp(topic, OPEN_TOPIC) == 0 && !is_running)
                {
                    // เมื่อได้รับคำสั่งจาก OPEN_TOPIC ให้เริ่มส่งข้อมูล
                    is_running = 1;
                    printf("Start publishing outcome data\n");

                    // ลบข้อมูลเก่าในฐานข้อมูล outcome
                    if (dbase_clear(DB_OUTCOME_NAME, "outcome_table") != 0)
                    {
                        fprintf(stderr, "Failed to clear outcome database\n");
                    }
                    else
                    {
                        printf("Cleared outcome database\n");
                    }
                }
                else if (strcmp(topic, CLOSE_TOPIC) == 0 && is_running)
                {
                    // เมื่อได้รับคำสั่งจาก CLOSE_TOPIC ให้หยุดส่งข้อมูล
                    is_running = 0;
                    printf("Stopped publishing outcome data\n");
                }

                // เคลียร์ข้อมูล
                MQTTClient_freeMessage(&received_message);
                MQTTClient_free(topic);
            }
            int size;
            OutcomeData *data = dbase_query(DB_OUTCOME_NAME, &size); // ดึงข้อมูลทั้งหมดจาก database
            pthread_testcancel();

            if (data != NULL && size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    // สร้าง JSON Object สำหรับแต่ละ row
                    cJSON *json_data = cJSON_CreateObject();
                    const char *data_event = (data[i].event == 0) ? "0" : "1";
                    cJSON_AddStringToObject(json_data, "timestamp", data[i].timestamp);
                    cJSON_AddNumberToObject(json_data, "frequency1", data[i].frequency1);
                    cJSON_AddNumberToObject(json_data, "frequency2", data[i].frequency2);
                    cJSON_AddNumberToObject(json_data, "frequency3", data[i].frequency3);
                    cJSON_AddStringToObject(json_data, "outcome", data_event);

                    // แปลง JSON Object เป็น string
                    char *json_payload = cJSON_PrintUnformatted(json_data);
                    cJSON_Delete(json_data); // ลบ JSON Object หลังจากแปลงเป็น string แล้ว

                    // ส่ง JSON ผ่าน MQTT
                    MQTTClient_message pubmsg = MQTTClient_message_initializer;
                    pubmsg.payload = (void *)json_payload;
                    pubmsg.payloadlen = (int)strlen(json_payload);
                    pubmsg.qos = 1;
                    pubmsg.retained = 0;

                    MQTTClient_deliveryToken token;
                    MQTTClient_publishMessage(mqtt_client, PUBLISH_TOPIC, &pubmsg, &token);
                    MQTTClient_waitForCompletion(mqtt_client, token, 1000);

                    printf("Published JSON: %s\n", json_payload);

                    free(json_payload); // ล้างหน่วยความจำ
                }

                // ลบข้อมูลทั้งหมดในฐานข้อมูลหลังจากส่งเสร็จ
                if (dbase_clear(DB_OUTCOME_NAME, "outcome_table") != 0)
                {
                    fprintf(stderr, "Failed to clear outcome database\n");
                }
                else
                {
                    printf("Cleared outcome database\n");
                }
            }
            else
            {
                fprintf(stderr, "Failed to retrieve data from outcome database\n");
            }

            free(data);    // ล้างหน่วยความจำของข้อมูลที่ดึงมาจาก database
            usleep(25000); // รอ 25 ms ก่อนดึงข้อมูลและส่งใหม่
        }
    }

    MQTTClient_disconnect(mqtt_client, 1000);
    MQTTClient_destroy(&mqtt_client);
    return NULL;
}
