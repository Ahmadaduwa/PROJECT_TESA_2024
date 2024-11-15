#ifndef DB_HELPER_H
#define DB_HELPER_H

// include files
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

// ปรับโครงสร้าง OutcomeData ให้มีคอลัมน์ frequency1, frequency2, frequency3 และ event
typedef struct {
    char timestamp[20];
    float frequency1;
    float frequency2;
    float frequency3;
    int event;
} OutcomeData;

// function prototypes
void dbase_init_size(const char *db_name);             // ฟังก์ชันสร้าง size_table
void dbase_init_outcome(const char *db_name);          // ฟังก์ชันสร้าง outcome_table

int dbase_append_size(const char *db_name, int size);  // ฟังก์ชันเพิ่มข้อมูลลงใน size_table
int dbase_append_outcome(const char *db_name, float frequency1, float frequency2, float frequency3, int event_status); // ฟังก์ชันเพิ่มข้อมูลลงใน outcome_table

OutcomeData *dbase_query(const char *db_name, int *size); // ฟังก์ชันสำหรับ query ข้อมูลล่าสุดจาก outcome_table
int dbase_clear(const char *db_name, const char *table_name);             // ฟังก์ชันสำหรับลบข้อมูลใน outcome_table
OutcomeData *dbase_query_latest(const char *db_name); // ฟังก์ชันดึงข้อมูลล่าสุด
int dbase_delete_latest(const char *db_name);         // ฟังก์ชันลบข้อมูลล่าสุด

#endif // DB_HELPER_H
