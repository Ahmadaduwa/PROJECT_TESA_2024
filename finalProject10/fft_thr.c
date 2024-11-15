#include "sound_app.h"
#include "FFTImplementationCallback.h"
#include "abs.h"
#include "db_helper.h"
#include "predictSignal.h"
#include "sound_freq.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>
#include <sys/stat.h>
#include "shared.h"

// เพิ่มโปรโตไทป์ของฟังก์ชัน
void sound_freq(const double X[4096], double spectrum[2048]);

// database names
const char *db_size = "/home/wupi/Desktop/finalProject10/size_data.db";
const char *db_outcome = "/home/wupi/Desktop/finalProject10/outcome_data.db";

void *fft_thr_fcn(void *ptr) {
    static double tmp_buf[4096];
    static double freq_buf[2048];
    static double input_data[2048];
    static double output_data[2048];
    int event_status = 0;

    printf("FFT thread started\n");

    // เรียกใช้ฟังก์ชัน initialize จาก MATLAB
    predictSignal_initialize();

    while (is_fft_running) {
        pthread_testcancel();
        pthread_mutex_lock(&data_cond_mutex);

        // เตรียมข้อมูลจาก shared_buf
        for (int i = 0; i < 4096; i++) {
            tmp_buf[i] = (double)shared_buf[i] / SHRT_MAX;
        }

        // คำนวณ FFT
        sound_freq(tmp_buf, freq_buf);

        // เลือก Bin ที่สัมพันธ์กับความถี่เฉพาะ
        int bin_50hz = (int)(50.0 * (4096.0 / 48000.0));    // Bin สำหรับ 50 Hz
        int bin_1khz = (int)(1000.0 * (4096.0 / 48000.0));  // Bin สำหรับ 1 kHz
        int bin_2khz = (int)(2000.0 * (4096.0 / 48000.0));  // Bin สำหรับ 2 kHz

        // ตรวจสอบว่า Bin อยู่ในช่วงที่เหมาะสม
        if (bin_50hz < 0 || bin_50hz >= 2048 || bin_1khz < 0 || bin_1khz >= 2048 || bin_2khz < 0 || bin_2khz >= 2048) {
            fprintf(stderr, "Bin out of range. Check FFT_POINTS and SAMPLING_RATE.\n");
            pthread_mutex_unlock(&data_cond_mutex);
            continue;
        }

        // แปลง Bin เป็น Hz
        float freq1_hz = bin_50hz * (48000.0 / 4096.0);
        float freq2_hz = bin_1khz * (48000.0 / 4096.0);
        float freq3_hz = bin_2khz * (48000.0 / 4096.0);

        // หา Magnitude ของแต่ละ Bin
        float magnitude_50hz = freq_buf[bin_50hz];
        float magnitude_1khz = freq_buf[bin_1khz];
        float magnitude_2khz = freq_buf[bin_2khz];

        // ตรวจสอบเงื่อนไขและตั้งค่า event_status
        if (magnitude_1khz > 0.5 || magnitude_50hz > 0.5) {
            event_status = 1;
        } else {
            event_status = 0;
        }

        // แสดงข้อมูล
        printf("freq1=%.2f Hz (Magnitude=%.2f), freq2=%.2f Hz (Magnitude=%.2f), freq3=%.2f Hz (Magnitude=%.2f), status=%d\n",
               freq1_hz, magnitude_50hz,
               freq2_hz, magnitude_1khz,
               freq3_hz, magnitude_2khz,
               event_status);

        // บันทึกผลลัพธ์ลงฐานข้อมูล
        if (dbase_append_outcome(db_outcome, magnitude_50hz, magnitude_1khz, magnitude_2khz, event_status) != 0) {
            fprintf(stderr, "Failed to append data to outcome database\n");
        }

        pthread_mutex_unlock(&data_cond_mutex);

        // หน่วงเวลา 100 ms ก่อนการคำนวณครั้งถัดไป
        usleep(100000);
    }

    // เรียกใช้ฟังก์ชัน terminate จาก MATLAB
    predictSignal_terminate();

    printf("fft_thr_fcn has stopped.\n");
    return NULL;
}
