#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

typedef struct {
    char schedule_id[20];
    char bus_id[20];
    char line_id[20];
    char user_id[20];
    char start[20];
    char end[20];
    char trips[10];
    char row_time[20];
} Schedule;

Schedule schedule;

void schedule_input(Schedule* schedule) {
    printf("请输入排班编号: ");
    scanf("%19s", schedule->schedule_id);

    printf("请输入车辆编号: ");
    scanf("%19s", schedule->bus_id);

    printf("请输入线路编号: ");
    scanf("%19s", schedule->line_id);

    printf("请输入司机编号: ");
    scanf("%19s", schedule->user_id);

    printf("请输入起点站编号: ");
    scanf("%19s", schedule->start);

    printf("请输入终点站编号: ");
    scanf("%19s", schedule->end);

    printf("请输入趟次: ");
    scanf("%9s", schedule->trips);

    printf("请输入发车时间(XXXX-XX-XX): ");
    scanf("%19s", schedule->row_time);
}

bool check_schedule_existence(Schedule* schedule) {
    sprintf(sql, "SELECT COUNT(*) FROM schedule WHERE user_id = '%s' AND trips = '%s' AND row_time = '%s'",
        schedule->user_id, schedule->trips, schedule->row_time);

    if (mysql_query(con, sql)) {
        fprintf(stderr, "检查排班是否存在失败: %s\n", mysql_error(con));
        return false;
    }

    MYSQL_RES* result = mysql_store_result(con);
    if (result == NULL) {
        fprintf(stderr, "获取检查结果失败: %s\n", mysql_error(con));
        return false;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    bool exists = row && atoi(row[0]) > 0;

    if (exists) {
        printf("该司机已有排班\n");
    }

    mysql_free_result(result);
    return exists;
}

void schedule_add(Schedule* schedule) {
    if (check_schedule_existence(schedule)) {
        return; // 如果司机已有排班，则直接返回
    }

    sprintf(sql, "INSERT INTO schedule (schedule_id, bus_id, line_id, user_id, start, end, trips, row_time) VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')",
        schedule->schedule_id, schedule->bus_id, schedule->line_id, schedule->user_id, schedule->start, schedule->end, schedule->trips, schedule->row_time);

    if (mysql_query(con, sql)) {
        fprintf(stderr, "排班添加失败: %s\n", mysql_error(con));
    }
    else {
        printf("排班添加成功\n");
    }
}

void schedule_delete(const char* schedule_id) {
    sprintf(sql, "DELETE FROM schedule WHERE schedule_id = '%s'", schedule_id);

    if (mysql_query(con, sql)) {
        fprintf(stderr, "排班删除失败: %s\n", mysql_error(con));
    }
    else {
        printf("排班删除成功\n");
    }
}

void schedule_update(const char* schedule_id) {
    Schedule new_schedule;
    strcpy(new_schedule.schedule_id, schedule_id);

    printf("请输入新的车辆编号: ");
    scanf("%19s", new_schedule.bus_id);

    printf("请输入新的线路编号: ");
    scanf("%19s", new_schedule.line_id);

    printf("请输入新的司机编号: ");
    scanf("%19s", new_schedule.user_id);

    printf("请输入新的起点站编号: ");
    scanf("%19s", new_schedule.start);

    printf("请输入新的终点站编号: ");
    scanf("%19s", new_schedule.end);

    printf("请输入新的趟次: ");
    scanf("%9s", new_schedule.trips);

    printf("请输入新的发车时间(XXXX-XX-XX): ");
    scanf("%19s", new_schedule.row_time);

    if (check_schedule_existence(&new_schedule)) {
        return; // 如果司机已有排班，则直接返回
    }

    sprintf(sql,
        "UPDATE schedule SET bus_id = '%s', line_id = '%s', user_id = '%s', start = '%s', end = '%s', trips = '%s', row_time = '%s' WHERE schedule_id = '%s'",
        new_schedule.bus_id, new_schedule.line_id, new_schedule.user_id, new_schedule.start, new_schedule.end, new_schedule.trips, new_schedule.row_time, schedule_id);

    if (mysql_query(con, sql)) {
        fprintf(stderr, "排班信息修改失败: %s\n", mysql_error(con));
    }
    else {
        printf("排班信息修改成功\n");
    }
}

void get_name_from_id(const char* field, const char* id, char* name, size_t size) {
    char sql[256];
    if (strcmp(field, "bus_id") == 0) {
        snprintf(sql, sizeof(sql), "SELECT bus_license FROM bus WHERE bus_id = '%s'", id);
    }
    else if (strcmp(field, "line_id") == 0) {
        snprintf(sql, sizeof(sql), "SELECT line_name FROM line WHERE line_id = '%s'", id);
    }
    else if (strcmp(field, "user_id") == 0) {
        snprintf(sql, sizeof(sql), "SELECT name FROM user WHERE user_id = '%s'", id);
    }
    else if (strcmp(field, "start") == 0) {
        snprintf(sql, sizeof(sql), "SELECT station_name FROM station WHERE station_id = '%s'", id);
    }
    else if (strcmp(field, "end") == 0) {
        snprintf(sql, sizeof(sql), "SELECT station_name FROM station WHERE station_id = '%s'", id);
    }
    else {
        snprintf(name, size, "UNKNOWN");
        return;
    }

    if (mysql_query(con, sql)) {
        fprintf(stderr, "查询名称失败: %s\n", mysql_error(con));
        snprintf(name, size, "ERROR");
        return;
    }

    MYSQL_RES* result = mysql_store_result(con);
    if (result == NULL) {
        fprintf(stderr, "获取名称结果失败: %s\n", mysql_error(con));
        snprintf(name, size, "ERROR");
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (row && row[0]) {
        snprintf(name, size, "%s", row[0]);
    }
    else {
        snprintf(name, size, "NOT FOUND");
    }

    mysql_free_result(result);
}

void schedule_print(MYSQL_RES* result) {
    unsigned int num_fields = mysql_num_fields(result);
    MYSQL_FIELD* fields = mysql_fetch_fields(result);

    // 打印表头
    for (unsigned int i = 0; i < num_fields; i++) {
        if (strcmp(fields[i].name, "bus_id") == 0) {
            printf(" %-12s", "bus license");
        }
        else if (strcmp(fields[i].name, "line_id") == 0) {
            printf(" %-12s", "line");
        }
        else if (strcmp(fields[i].name, "user_id") == 0) {
            printf(" %-12s", "driver");
        }
        else if (strcmp(fields[i].name, "start") == 0) {
            printf(" %-12s", "start");
        }
        else if (strcmp(fields[i].name, "end") == 0) {
            printf(" %-12s", "end");
        }
        else {
            printf(" %-12s", fields[i].name);
        }
    }
    printf("\n");

    // 打印分隔符
    for (unsigned int i = 0; i < num_fields; i++) {
        printf("---------------");
    }
    printf("\n");

    // 打印每一行数据
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        for (unsigned int i = 0; i < num_fields; i++) {
            if (strcmp(fields[i].name, "bus_id") == 0 || strcmp(fields[i].name, "line_id") == 0 ||
                strcmp(fields[i].name, "user_id") == 0 || strcmp(fields[i].name, "start") == 0 ||
                strcmp(fields[i].name, "end") == 0) {
                char name[50];
                get_name_from_id(fields[i].name, row[i], name, sizeof(name));
                printf("| %-12s", name);
            }
            else {
                printf("| %-12s", row[i] ? row[i] : "NULL");
            }
        }
        printf("\n");
    }
}

void schedule_query(const char* schedule_id) {
    if (schedule_id == NULL || strlen(schedule_id) == 0) {
        sprintf(sql, "SELECT * FROM schedule");
    }
    else {
        sprintf(sql, "SELECT * FROM schedule WHERE schedule_id = '%s'", schedule_id);
    }

    if (mysql_query(con, sql)) {
        fprintf(stderr, "查询失败: %s\n", mysql_error(con));
        return;
    }

    MYSQL_RES* result = mysql_store_result(con);
    if (result == NULL) {
        fprintf(stderr, "存储结果集失败: %s\n", mysql_error(con));
        return;
    }

    // 打印查询结果
    schedule_print(result);

    // 释放结果集
    mysql_free_result(result);
}

void schedule_query_byline(const char* line_name) {
    if (line_name == NULL || strlen(line_name) == 0) {
        // 查询整个表
        sprintf(sql, "SELECT * FROM schedule");
    }
    else {
        // 查询特定线路名的排班
        sprintf(sql, "SELECT * FROM schedule WHERE line_id IN (SELECT line_id FROM line WHERE line_name = '%s')", line_name);
    }

    if (mysql_query(con, sql)) {
        fprintf(stderr, "查询失败: %s\n", mysql_error(con));
        return;
    }

    MYSQL_RES* result = mysql_store_result(con);
    if (result == NULL) {
        fprintf(stderr, "存储结果集失败: %s\n", mysql_error(con));
        return;
    }

    // 打印查询结果
    schedule_print(result);

    // 释放结果集
    mysql_free_result(result);
}

void schedule_query_bybus(const char* bus_license) {
    if (bus_license == NULL || strlen(bus_license) == 0) {
        // 查询整个表
        sprintf(sql, "SELECT * FROM schedule");
    }
    else {
        // 查询特定车牌号的排班
        sprintf(sql, "SELECT * FROM schedule WHERE bus_id IN (SELECT bus_id FROM bus WHERE bus_license = '%s')", bus_license);
    }

    if (mysql_query(con, sql)) {
        fprintf(stderr, "查询失败: %s\n", mysql_error(con));
        return;
    }

    MYSQL_RES* result = mysql_store_result(con);
    if (result == NULL) {
        fprintf(stderr, "存储结果集失败: %s\n", mysql_error(con));
        return;
    }

    // 打印查询结果
    schedule_print(result);

    // 释放结果集
    mysql_free_result(result);
}

void schedule_query_bystation(const char* start, const char* end) {
    if ((start == NULL || strcmp(start, "无") == 0 || strlen(start) == 0) &&
        (end == NULL || strcmp(end, "无") == 0 || strlen(end) == 0)) {
        printf("请至少输入一个站！\n");
        return;
    }

    if (start == NULL || strcmp(start, "无") == 0 || strlen(start) == 0) {
        // 查询终点站
        sprintf(sql, "SELECT * FROM schedule WHERE end IN (SELECT station_id FROM station WHERE station_name = '%s')", end);
    }
    else if (end == NULL || strcmp(end, "无") == 0 || strlen(end) == 0) {
        // 查询起点站
        sprintf(sql, "SELECT * FROM schedule WHERE start IN (SELECT station_id FROM station WHERE station_name = '%s')", start);
    }
    else {
        // 查询起点站和终点站
        sprintf(sql, "SELECT * FROM schedule WHERE start IN (SELECT station_id FROM station WHERE station_name = '%s') AND end IN (SELECT station_id FROM station WHERE station_name = '%s')", start, end);
    }

    if (mysql_query(con, sql)) {
        fprintf(stderr, "查询失败: %s\n", mysql_error(con));
        return;
    }

    MYSQL_RES* result = mysql_store_result(con);
    if (result == NULL) {
        fprintf(stderr, "存储结果集失败: %s\n", mysql_error(con));
        return;
    }

    // 打印查询结果
    schedule_print(result);

    // 释放结果集
    mysql_free_result(result);
}

/*void schedule_print_ad(MYSQL_RES* result) {
    if (result == NULL) {
        return;
    }
    unsigned int num_fields = mysql_num_fields(result);
    MYSQL_FIELD* fields = mysql_fetch_fields(result);

    // 打印表头
    for (unsigned int i = 0; i < num_fields; i++) {
        printf("  %-10s", fields[i].name);
    }
    printf("\n");

    // 打印分隔符
    for (unsigned int i = 0; i < num_fields; i++) {
        printf("------------");
    }
    printf("\n");

    // 打印每一行数据
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        for (unsigned int i = 0; i < num_fields; i++) {
            printf("| %-10s", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }
}*/

