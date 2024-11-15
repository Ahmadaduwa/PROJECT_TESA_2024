// shared.h
#ifndef SHARED_H
#define SHARED_H

#include <pthread.h>

// ประกาศตัวแปรสถานะที่ใช้ร่วมกัน
extern volatile int is_running;
extern volatile int is_fft_running;

// Mutex และ Condition Variable ที่ใช้ร่วมกัน
extern pthread_mutex_t data_cond_mutex;
extern pthread_cond_t data_cond;


#endif // SHARED_H
