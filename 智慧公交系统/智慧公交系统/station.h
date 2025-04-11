#pragma once
#include <stdio.h>
#include "database.h"

typedef struct {
	char station_id[20];
	char station_name[20];
	char logitude[10];
	char latitude[10];
	char area[10];
	char street[10];
} Station;

Station station;

void station_input(Station* station) {
    printf("请输入站点编号: ");
    scanf("%19s", station->station_id);

    printf("请输入站点名: ");
    scanf("%19s", station->station_name);

    printf("请输入经度: ");
    scanf("%9s", station->logitude);

    printf("请输入纬度: ");
    scanf("%9s", station->latitude);

    printf("请输入区域: ");
    scanf("%9s", station->area);

    printf("请输入街道: ");
    scanf("%9s", station->street);
}

void station_add(Station* station) {
    sprintf(sql, "INSERT INTO station (station_id, station_name, longitude, latitude, area, street) VALUES ('%s', '%s', '%s', '%s','%s','%s')",
        station->station_id, station->station_name, station->logitude, station->latitude, station->area, station->street);


    if (mysql_query(con, sql)) {
        fprintf(stderr, "站点添加失败: %s\n", mysql_error(con));
    }
    else {
        printf("站点添加成功\n");
    }
}

void station_delete(const char* station_id) {
    sprintf(sql, "DELETE FROM station WHERE station_id = '%s'", station_id);
    if (mysql_query(con, sql)) {
        fprintf(stderr, "站点删除失败: %s\n", mysql_error(con));
    }
    else {
        printf("站点删除成功\n");
    }
}

void station_update(const char* station_id) {
    Station new_station;
    strcpy(new_station.station_id, station_id);

    printf("请输入新的站点名: ");
    scanf("%19s", new_station.station_name);

    printf("请输入新的经度: ");
    scanf("%9s", new_station.logitude);

    printf("请输入新的纬度: ");
    scanf("%9s", new_station.latitude);

    printf("请输入新的区域: ");
    scanf("%9s", new_station.area);

    printf("请输入新的街道: ");
    scanf("%9s", new_station.street);

    sprintf(sql, "UPDATE station SET station_name = '%s', longitude = '%s', latitude = '%s', area = '%s', street = '%s' WHERE station_id = '%s'",
        new_station.station_name, new_station.logitude, new_station.latitude, new_station.area, new_station.street, station_id);

    if (mysql_query(con, sql)) {
        fprintf(stderr, "站点信息修改失败: %s\n", mysql_error(con));
    }
    else {
        printf("站点信息修改成功\n");
    }
}

void station_print(MYSQL_RES* result) {
    unsigned int num_fields = mysql_num_fields(result);
    MYSQL_FIELD* fields = mysql_fetch_fields(result);

    // 打印表头
    for (unsigned int i = 0; i < num_fields; i++) {
        printf("  %-20s", fields[i].name);
    }
    printf("\n");

    // 打印分隔符
    for (unsigned int i = 0; i < num_fields; i++) {
        printf("--------------------");
    }
    printf("\n");

    // 打印每一行数据
    while ((row = mysql_fetch_row(result))) {
        for (unsigned int i = 0; i < num_fields; i++) {
            printf("| %-20s", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }
}

void station_query(const char* station_id) {
    if (station_id == NULL || strlen(station_id) == 0) {
        // 查询整个表
        sprintf(sql, "SELECT * FROM station");
    }
    else {
        // 查询特定站点编号
        sprintf(sql, "SELECT * FROM station WHERE station_id = '%s'", station_id);
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
    station_print(result);

    // 释放结果集
    mysql_free_result(result);
}