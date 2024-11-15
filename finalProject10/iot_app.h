#ifndef IOT_APP_H
#define IOT_APP_H

// include files
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <cjson/cJSON.h>

// shared variables
extern pthread_mutex_t data_cond_mutex;
extern pthread_cond_t data_cond;
extern const char SUBSCRIBE_TOPIC[];
extern int shared_value;

// function prototypes
void *rest_thr_fcn( void *ptr );
void *mqtt_thr_fcn( void *ptr );
void *publish_outcome_data(void *arg);  // โปรโตไทป์ฟังก์ชัน publish_outcome_data
void *fft_thr_fcn(void *ptr);      
void *insert_and_publish(void *arg);


#endif // IOT_APP_H