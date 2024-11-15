#include "shared.h"
#include "sound_app.h"
#include "FFTImplementationCallback.h"
#include "abs.h"
#include "iot_app.h"
#include "db_helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t data_cond_mutex;
pthread_cond_t data_cond;
short shared_buf[9600];

// กำหนดตัวแปรจริงที่ใช้ร่วมกัน
volatile int is_running = 0;
volatile int is_fft_running = 1; // ให้ fft_thr_fcn ทำงานทันที

// ประกาศ extern จากไฟล์อื่น
extern void *fft_thr_fcn(void *arg);
extern void *pubsub_thr_fcn(void *arg); // ฟังก์ชันจัดการ MQTT pub/sub

int main(int argc, char *argv[])
{


    pthread_t alsa_thr, pubsub_thread, fft_thread;

    // เริ่มต้นฐานข้อมูล outcome และ size
    // เริ่มต้นฐานข้อมูล outcome, size, และ event
    dbase_init_size("/home/wupi/Desktop/finalProject10/size_data.db");
    dbase_init_outcome("/home/wupi/Desktop/finalProject10/outcome_data.db");

    // เริ่มต้น Mutex และ Condition Variable
    pthread_mutex_init(&data_cond_mutex, NULL);
    pthread_cond_init(&data_cond, NULL);

    // สร้าง ALSA Thread
    if (pthread_create(&alsa_thr, NULL, alsa_thr_fcn, argv[1]) != 0)
    {
        perror("Failed to create alsa_thr");
        exit(EXIT_FAILURE);
    }

    // สร้าง MQTT Publish/Subscribe Thread
    if (pthread_create(&pubsub_thread, NULL, pubsub_thr_fcn, (void *)SUBSCRIBE_TOPIC) != 0)
    {
        perror("Failed to create pubsub_thr");
        exit(EXIT_FAILURE);
    }

    // เรียกใช้ FFT Thread ทันที
    if (pthread_create(&fft_thread, NULL, fft_thr_fcn, NULL) != 0)
    {
        perror("Failed to create fft_thr");
        exit(EXIT_FAILURE);
    }

    // รอให้ Thread สิ้นสุดการทำงาน
    pthread_join(alsa_thr, NULL);
    pthread_join(pubsub_thread, NULL);
    pthread_join(fft_thread, NULL);

    // ทำลาย Mutex และ Condition Variable
    pthread_mutex_destroy(&data_cond_mutex);
    pthread_cond_destroy(&data_cond);

    printf("Program finished successfully.\n");
    return 0;
}
