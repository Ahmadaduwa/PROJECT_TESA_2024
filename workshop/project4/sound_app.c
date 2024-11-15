#include "sound_app.h"
#include "FFTImplementationCallback.h"
#include "abs.h"

pthread_mutex_t data_cond_mutex;
pthread_cond_t data_cond;
short shared_buf[9600];

int main(int argc, char *argv[]) {
    pthread_t alsa_thr, fft_thr;

    // prepare IPC objects
    pthread_mutex_init(&data_cond_mutex, NULL);
    pthread_cond_init(&data_cond, NULL);

    // initialize threads
    pthread_create(&alsa_thr, NULL, alsa_thr_fcn, argv[1]);  // ใช้ argv[1] สำหรับอุปกรณ์เสียง
    pthread_create(&fft_thr, NULL, fft_thr_fcn, NULL);

    // waiting for all threads to terminate
    pthread_join(alsa_thr, NULL);
    pthread_join(fft_thr, NULL); 
}
