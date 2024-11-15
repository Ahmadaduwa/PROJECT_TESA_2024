#include "sound_app.h"
#include "sound_freq.h"
#include <limits.h>
#include <unistd.h>    // สำหรับ usleep
#include <time.h>      // สำหรับ clock_gettime

// กำหนดความถี่ DTMF ตามมาตรฐาน
#define LOW_FREQS {697.0, 770.0, 852.0, 941.0}
#define HIGH_FREQS {1209.0, 1336.0, 1477.0}

// ฟังก์ชันสำหรับตรวจจับ DTMF
void *fft_thr_fcn(void *ptr)
{
    static double tmp_buf[4096];
    static double freq_buf[4096];

    // ตัวนับผลลัพธ์ DTMF
    int dtmf_count[10] = {0};
    double low_freqs[] = LOW_FREQS;
    double high_freqs[] = HIGH_FREQS;

    struct timespec start, end;
    long elapsed_time;

    while (1)
    {
        // เริ่มจับเวลา
        clock_gettime(CLOCK_MONOTONIC, &start);

        // เคลียร์ตัวนับในช่วงเวลา 25 ms
        for (int i = 0; i < 10; i++) dtmf_count[i] = 0;

        // ตรวจจับ DTMF ภายใน 25 ms
        for (int count = 0; count < 5; count++) // รับข้อมูล 5 ครั้งต่อ 25 ms
        {
            pthread_mutex_lock(&data_cond_mutex);

            // แปลงข้อมูลเสียงและทำ FFT
            for (int i = 0; i < 4096; i++)
            {
                tmp_buf[i] = (double)shared_buf[i] / SHRT_MAX;
            }
            sound_freq(tmp_buf, freq_buf);

            // ค้นหาความถี่สูงสุดในแต่ละช่วง (ต่ำและสูง)
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

            // แปลงค่า index ไปเป็น Hz
            double detected_low_freq = low_index * (48000.0 / 4096);
            double detected_high_freq = high_index * (48000.0 / 4096);

            // ตรวจจับค่าของปุ่ม DTMF และบันทึกผลลัพธ์ลงในตัวนับ
            if ((detected_low_freq > 600 && detected_low_freq < 1000) && (detected_high_freq > 1200 && detected_high_freq < 1500))
            {
                if (fabs(detected_low_freq - 703.125000) < 10 && fabs(detected_high_freq - 1218.750000) < 10)
                    dtmf_count[1]++;
                else if (fabs(detected_low_freq - 703.125000) < 10 && fabs(detected_high_freq - 1335.937500) < 10)
                    dtmf_count[2]++;
                else if (fabs(detected_low_freq - 703.125000) < 10 && fabs(detected_high_freq - 1476.562500) < 10)
                    dtmf_count[3]++;
                else if (fabs(detected_low_freq - 773.437500) < 10 && fabs(detected_high_freq - 1218.750000) < 10)
                    dtmf_count[4]++;
                else if (fabs(detected_low_freq - 773.437500) < 10 && fabs(detected_high_freq - 1335.937500) < 10)
                    dtmf_count[5]++;
                else if (fabs(detected_low_freq - 773.437500) < 10 && fabs(detected_high_freq - 1476.562500) < 10)
                    dtmf_count[6]++;
                else if (fabs(detected_low_freq - 855.468750) < 10 && fabs(detected_high_freq - 1218.750000) < 10)
                    dtmf_count[7]++;
                else if (fabs(detected_low_freq - 855.468750) < 10 && fabs(detected_high_freq - 1335.937500) < 10)
                    dtmf_count[8]++;
                else if (fabs(detected_low_freq - 855.468750) < 10 && fabs(detected_high_freq - 1476.562500) < 10)
                    dtmf_count[9]++;
                else if (fabs(detected_low_freq - 937.500000) < 10 && fabs(detected_high_freq - 1335.937500) < 10)
                    dtmf_count[0]++;
            }

            pthread_mutex_unlock(&data_cond_mutex);
            usleep(5000); // หน่วงเวลาประมาณ 5 ms เพื่อทำซ้ำ 5 ครั้งใน 25 ms
        }

        // ค้นหาค่าที่นับได้มากที่สุดในช่วง 25 ms
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

        // แสดงผลลัพธ์
        if (max_count > 0)
            printf("%d\n", detected_digit);
        else
            printf("ไม่ได้รับเสียงสัญญาณ\n");

        // ตรวจสอบเวลาที่ใช้และรอจนกว่าจะครบ 25 ms ก่อนเริ่มรอบใหม่
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
        if (elapsed_time < 25000)
        {
            usleep(25000 - elapsed_time);
        }
    }
}
