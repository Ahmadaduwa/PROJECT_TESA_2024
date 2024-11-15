#include "db_helper.h"
#include <stdio.h>
#include <sqlite3.h>
#include <pthread.h>

// ประกาศ mutex สำหรับการล็อกฐานข้อมูล
pthread_mutex_t db_mutex = PTHREAD_MUTEX_INITIALIZER;

// คำสั่ง SQL สำหรับการสร้างตาราง size_table
const char INIT_SIZE_DB_CMD[] = 
    "CREATE TABLE IF NOT EXISTS size_table ("
    "_id INTEGER PRIMARY KEY AUTOINCREMENT, "
    "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP, "
    "file_size INTEGER);";

const char INIT_OUTCOME_DB_CMD[] = 
    "CREATE TABLE IF NOT EXISTS outcome_table ("
    "_id INTEGER PRIMARY KEY AUTOINCREMENT, "
    "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP, "
    "frequency1 REAL, "
    "frequency2 REAL, "
    "frequency3 REAL, "
    "event_status INTEGER);";
  // เพิ่มคอลัมน์ event_statussq





// คำสั่งสำหรับเพิ่มข้อมูลลงใน data_table
const char APPEND_SQL_CMD[] = "INSERT INTO data_table (frequency, tm_sec) VALUES (?, ?);";


// คำสั่งสำหรับการดึงข้อมูลล่าสุดจาก data_table
const char QUERY_SQL_CMD[] = "SELECT * FROM data_table ORDER BY timestamp DESC LIMIT 1;";

void dbase_init_size(const char *db_name) {
    sqlite3 *db;
    char *errmsg = NULL;

    if (sqlite3_open(db_name, &db) != SQLITE_OK) {
        fprintf(stderr, "Error opening database %s: %s\n", db_name, sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    if (sqlite3_exec(db, INIT_SIZE_DB_CMD, NULL, NULL, &errmsg) != SQLITE_OK) {
        fprintf(stderr, "Error creating size_table: %s\n", errmsg);
        sqlite3_free(errmsg);
        sqlite3_close(db);
        return;
    }

    //printf("Size table initialized successfully.\n");
    sqlite3_close(db);
}

void dbase_init_outcome(const char *db_name) {
    sqlite3 *db;
    char *errmsg = NULL;

    if (sqlite3_open(db_name, &db) != SQLITE_OK) {
        fprintf(stderr, "Error opening database %s: %s\n", db_name, sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    if (sqlite3_exec(db, INIT_OUTCOME_DB_CMD, NULL, NULL, &errmsg) != SQLITE_OK) {
        fprintf(stderr, "Error creating outcome_table: %s\n", errmsg);
        sqlite3_free(errmsg);
        sqlite3_close(db);
        return;
    }

    printf("Outcome table initialized successfully.\n");
    sqlite3_close(db);
}


int dbase_append_size(const char *db_name, int size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *APPEND_SIZE_SQL_CMD = "INSERT INTO size_table (file_size) VALUES (?);";

    // เปิดฐานข้อมูล size_data.db
    if (sqlite3_open(db_name, &db) != SQLITE_OK) {
        fprintf(stderr, "Error opening %s database\n", db_name);
        sqlite3_close(db);
        return -1;
    }

    // เตรียม statement สำหรับเพิ่มขนาดไฟล์ลงใน size_table
    if (sqlite3_prepare_v2(db, APPEND_SIZE_SQL_CMD, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Error preparing SQL statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    // Bind ขนาดไฟล์ที่ต้องการเข้าไปใน statement
    sqlite3_bind_int(stmt, 1, size);  // size

    // ดำเนินการ SQL statement
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Error executing SQL statement\n");
    } else {
        //printf("File size %d bytes inserted into size_table successfully.\n", size);
    }

    // ปิด statement และฐานข้อมูล
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}
int dbase_append_outcome(const char *db_name, float frequency1, float frequency2, float frequency3, int event_status) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *APPEND_OUTCOME_SQL_CMD = "INSERT INTO outcome_table (frequency1, frequency2, frequency3, event_status) VALUES (?, ?, ?, ?);";

    // ล็อก Mutex
    pthread_mutex_lock(&db_mutex);

    if (sqlite3_open(db_name, &db) != SQLITE_OK) {
        fprintf(stderr, "Error opening %s database\n", db_name);
        pthread_mutex_unlock(&db_mutex);  // ปลดล็อกก่อนออกจากฟังก์ชัน
        return -1;
    }

    if (sqlite3_prepare_v2(db, APPEND_OUTCOME_SQL_CMD, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Error preparing SQL statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        pthread_mutex_unlock(&db_mutex);
        return -1;
    }

    // Bind frequency1, frequency2, frequency3 และ event_status
    sqlite3_bind_double(stmt, 1, frequency1);
    sqlite3_bind_double(stmt, 2, frequency2);
    sqlite3_bind_double(stmt, 3, frequency3);
    sqlite3_bind_int(stmt, 4, event_status);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Error executing SQL statement\n");
    } else {
        printf("Data inserted into outcome_table successfully.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    // ปลดล็อก Mutex
    pthread_mutex_unlock(&db_mutex);
    return 0;
}

OutcomeData *dbase_query(const char *db_name, int *size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    OutcomeData *results = NULL;
    *size = 0;

    // ล็อก Mutex
    pthread_mutex_lock(&db_mutex);

    // เปิดการเชื่อมต่อกับฐานข้อมูลพร้อม retry
    int rc, retries = 5;
    while ((rc = sqlite3_open(db_name, &db)) == SQLITE_BUSY && retries > 0) {
        usleep(50000); // รอ 50 มิลลิวินาทีก่อน retry
        retries--;
    }
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error opening database %s: %s\n", db_name, sqlite3_errmsg(db));
        pthread_mutex_unlock(&db_mutex);
        return NULL;
    }

    // คำสั่ง SQL สำหรับดึงข้อมูลจาก outcome_table
    const char *sql = "SELECT timestamp, frequency1, frequency2, frequency3, event_status FROM outcome_table ORDER BY timestamp ASC;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error preparing SQL statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        pthread_mutex_unlock(&db_mutex);
        return NULL;
    }

    int capacity = 10;
    results = (OutcomeData *)malloc(capacity * sizeof(OutcomeData));

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        if (*size >= capacity) {
            capacity *= 2;
            results = (OutcomeData *)realloc(results, capacity * sizeof(OutcomeData));
        }
        const char *timestamp_text = (const char *)sqlite3_column_text(stmt, 0);
        if (timestamp_text) {
            strncpy(results[*size].timestamp, timestamp_text, sizeof(results[*size].timestamp) - 1);
            results[*size].timestamp[sizeof(results[*size].timestamp) - 1] = '\0';
        } else {
            strcpy(results[*size].timestamp, "");
        }
        results[*size].frequency1 = sqlite3_column_double(stmt, 1);
        results[*size].frequency2 = sqlite3_column_double(stmt, 2);
        results[*size].frequency3 = sqlite3_column_double(stmt, 3);
        results[*size].event = sqlite3_column_int(stmt, 4);
        (*size)++;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    // ปลดล็อก Mutex
    pthread_mutex_unlock(&db_mutex);

    return results;
}




int dbase_clear(const char *db_name, const char *table_name) {
    sqlite3 *db;
    char *errmsg = NULL;

    // สร้างคำสั่ง SQL แบบไดนามิกเพื่อให้ลบข้อมูลจากตารางที่ระบุ
    char clear_sql_cmd[256];
    snprintf(clear_sql_cmd, sizeof(clear_sql_cmd), "DELETE FROM %s;", table_name);

    // เปิดฐานข้อมูล
    if (sqlite3_open(db_name, &db) != SQLITE_OK) {
        fprintf(stderr, "Error opening database %s: %s\n", db_name, sqlite3_errmsg(db));
        return -1;
    }

    // ลบข้อมูลในตารางที่กำหนด
    if (sqlite3_exec(db, clear_sql_cmd, NULL, NULL, &errmsg) != SQLITE_OK) {
        fprintf(stderr, "Error clearing table %s in database %s: %s\n", table_name, db_name, errmsg);
        sqlite3_free(errmsg);
        sqlite3_close(db);
        return -1;
    }

    printf("Cleared table %s successfully in database %s.\n", table_name, db_name);
    sqlite3_close(db);
    return 0;
}

