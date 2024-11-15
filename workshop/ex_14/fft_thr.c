#include "sound_app.h"
#include "sound_freq.h"
#include <limits.h>

void *fft_thr_fcn(void *ptr) {
    // setup
    static double tmp_buf[4096];
    static double freq_buf[4096];

    while(1) {
        // lock and wait for data signal
        pthread_mutex_lock(&data_cond_mutex);
        pthread_cond_wait(&data_cond, &data_cond_mutex);
        printf("Start processing\n");

        for (int i = 0; i < 4096; i++) {
            tmp_buf[i] = (double)shared_buf[i] / SHRT_MAX;
        }

        // Perform FFT and store frequency amplitudes in freq_buf
        sound_freq(tmp_buf, freq_buf);

        // Find top 3 frequencies with the highest amplitudes
        double top_amplitudes[3] = {0.0, 0.0, 0.0};
        int top_indices[3] = {0, 0, 0};

        for (int i = 0; i < 4096; i++) {
            if (freq_buf[i] > top_amplitudes[0]) {
                top_amplitudes[2] = top_amplitudes[1];
                top_indices[2] = top_indices[1];
                
                top_amplitudes[1] = top_amplitudes[0];
                top_indices[1] = top_indices[0];
                
                top_amplitudes[0] = freq_buf[i];
                top_indices[0] = i;
            } else if (freq_buf[i] > top_amplitudes[1]) {
                top_amplitudes[2] = top_amplitudes[1];
                top_indices[2] = top_indices[1];
                
                top_amplitudes[1] = freq_buf[i];
                top_indices[1] = i;
            } else if (freq_buf[i] > top_amplitudes[2]) {
                top_amplitudes[2] = freq_buf[i];
                top_indices[2] = i;
            }
        }


        double sampling_rate = 48000.0;
        double freq_resolution = sampling_rate / 4096;

        printf("Top 3 frequencies with highest amplitude:\n");
        for (int j = 0; j < 3; j++) {
            double frequency = top_indices[j] * freq_resolution;
            printf("Frequency %d: %f Hz, Amplitude: %f\n Frequency %d: %f Hz", j + 1, frequency, top_amplitudes[j]);
        }

        pthread_mutex_unlock(&data_cond_mutex);
    }
}
