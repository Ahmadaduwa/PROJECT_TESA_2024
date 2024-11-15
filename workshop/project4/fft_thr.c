#include "sound_app.h"
#include "sound_freq.h"
#include <limits.h>
#include <unistd.h>
#include <time.h>
#include <math.h> 
#include <stdio.h> 

void *fft_thr_fcn(void *ptr)
{
    (void)ptr;  
    static double tmp_buf[4096];
    static double freq_buf[4096];

    int dtmf_count[10] = {0};
    int last_detected_digit = -1;  
    long elapsed_time; 

    printf("กด 'y' เพื่อเริ่มทำงาน: ");
    char start_char = getchar();
    if (start_char != 'y') {
        printf("ยกเลิกการทำงาน\n");
        return NULL;  
    }

    while (1)
    {

        for (int i = 0; i < 10; i++)
            dtmf_count[i] = 0;


        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);

        do {
            pthread_mutex_lock(&data_cond_mutex);

 
            for (int i = 0; i < 4096; i++)
            {
                tmp_buf[i] = (double)shared_buf[i] / SHRT_MAX;
            }
            sound_freq(tmp_buf, freq_buf);


            double low_freq = 0, high_freq = 0;
            int low_index = 0, high_index = 0;

            for (int i = 0; i < 4096; i++)
            {
                double freq = i * (48000.0 / 4096);
                if (freq >= 697.0 && freq <= 941.0 && freq_buf[i] > low_freq)
                {
                    low_freq = freq_buf[i];
                    low_index = i;
                }
                else if (freq >= 1209.0 && freq <= 1477.0 && freq_buf[i] > high_freq)
                {
                    high_freq = freq_buf[i];
                    high_index = i;
                }
            }

            double detected_low_freq = low_index * (48000.0 / 4096);
            double detected_high_freq = high_index * (48000.0 / 4096);

            if ((detected_low_freq > 600 && detected_low_freq < 1000) && (detected_high_freq > 1200 && detected_high_freq < 1500))
            {
                if (fabs(detected_low_freq - 703.125000) < 2 && fabs(detected_high_freq - 1218.750000) < 2)
                    dtmf_count[1]++;
                else if (fabs(detected_low_freq - 703.125000) < 2 && fabs(detected_high_freq - 1335.937500) < 2)
                    dtmf_count[2]++;
                else if (fabs(detected_low_freq - 703.125000) < 2 && fabs(detected_high_freq - 1476.562500) < 2)
                    dtmf_count[3]++;
                else if (fabs(detected_low_freq - 773.437500) < 2 && fabs(detected_high_freq - 1218.750000) < 2)
                    dtmf_count[4]++;
                else if (fabs(detected_low_freq - 773.437500) < 2 && fabs(detected_high_freq - 1335.937500) < 2)
                    dtmf_count[5]++;
                else if (fabs(detected_low_freq - 773.437500) < 2 && fabs(detected_high_freq - 1476.562500) < 2)
                    dtmf_count[6]++;
                else if (fabs(detected_low_freq - 855.468750) < 2 && fabs(detected_high_freq - 1218.750000) < 2)
                    dtmf_count[7]++;
                else if (fabs(detected_low_freq - 855.468750) < 2 && fabs(detected_high_freq - 1335.937500) < 2)
                    dtmf_count[8]++;
                else if (fabs(detected_low_freq - 855.468750) < 2 && fabs(detected_high_freq - 1476.562500) < 2)
                    dtmf_count[9]++;
                else if (fabs(detected_low_freq - 937.500000) < 2 && fabs(detected_high_freq - 1335.937500) < 2)
                    dtmf_count[0]++;
            }

            pthread_mutex_unlock(&data_cond_mutex);

            usleep(1000);  


            clock_gettime(CLOCK_MONOTONIC, &end);
            elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
        } while (elapsed_time < 125000); 

        int max_count = 0;
        int detected_digit = -1;
        for (int i = 0; i < 10; i++)
        {
            if (dtmf_count[i] > max_count)
            {
                max_count = dtmf_count[i];
                detected_digit = i;
            }
        }


        if (detected_digit != last_detected_digit && max_count > 0)
        {
            printf("%d\n", detected_digit);
            last_detected_digit = detected_digit;
        }
        else if (max_count == 0 && last_detected_digit != -1)
        {
            printf("ไม่ได้รับเสียงสัญญาณ\n");
            last_detected_digit = -1;
        }

        usleep(25000);
    }
}
