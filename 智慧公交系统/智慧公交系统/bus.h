#pragma once
#include <stdio.h>
#include <string.h>
#include "database.h"
#include "validation.h"

typedef struct {
    char bus_id[20];
    char bus_license[20];
    char bus_status[10];
    char bus_time[20];
    char bus_type[10];
}Bus;

Bus bus;


    void bus_input(Bus* bus) {
    printf("请输入车辆编号: ");
    scanf("%19s", bus->bus_id);

    while (true) {
        printf("请输入车牌号: ");
        scanf("%19s", bus->bus_license);

        if (is_valid_license(bus->bus_license)) {
            break;
        }
        else {
            printf("车牌号格式不正确，请重新输入。\n");
        }
    }

    printf("请输入车辆状态: ");
    scanf("%9s", bus->bus_status);

    printf("请输入始发时间 (格式: YYYY-MM-DD): ");
    scanf("%19s", bus->bus_time);

    printf("请输入车型: ");
    scanf("%9s", bus->bus_type);
}
    
    void bus_add(Bus *bus) {
        sprintf(sql, "INSERT INTO bus (bus_id, bus_license, bus_status, bus_time, bus_type) VALUES ('%s', '%s', '%s', '%s', '%s')",
            bus->bus_id, bus->bus_license, bus->bus_status, bus->bus_time, bus->bus_type);
        if (mysql_query(con, sql)) {
            fprintf(stderr, "车辆添加失败: %s\n", mysql_error(con));
        }
        else {
            printf("车辆添加成功\n");
        }
    }

    void bus_delete(const char *bus_id){
        sprintf(sql, "DELETE FROM bus WHERE bus_id = '%s'", bus_id);
        if (mysql_query(con, sql)) {
            fprintf(stderr, "车辆删除失败: %s\n", mysql_error(con));
        }
        else {
            printf("车辆删除成功\n");
        }
    }

    void bus_update(const char* bus_id) {
        Bus new_bus;
        strcpy(new_bus.bus_id, bus_id);

        printf("请输入车牌号: ");
        scanf("%19s", new_bus.bus_license);

        printf("请输入新的车辆状态: ");
        scanf("%9s", new_bus.bus_status);

        printf("请输入新的始发时间 (格式: YYYY-MM-DD): ");
        scanf("%19s", new_bus.bus_time);

        printf("请输入新的车型: ");
        scanf("%9s", new_bus.bus_type);

        sprintf(sql, "UPDATE bus SET bus_license = '%s', bus_status = '%s', bus_time = '%s', bus_type = '%s' WHERE bus_id = '%s'",
            new_bus.bus_license, new_bus.bus_status, new_bus.bus_time, new_bus.bus_type, new_bus.bus_id);

        if (mysql_query(con, sql)) {
            fprintf(stderr, "车辆信息修改失败: %s\n", mysql_error(con));
        }
        else {
            printf("车辆信息修改成功\n");
        }
    }

    void bus_print(MYSQL_RES* result) {
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

    void bus_query(const char* bus_id) {
        if (bus_id == NULL || strlen(bus_id) == 0) {
            // 查询整个表
            sprintf(sql, "SELECT * FROM bus");
        }
        else {
            // 查询特定车辆编号
            sprintf(sql, "SELECT * FROM bus WHERE bus_id = '%s'", bus_id);
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
        bus_print(result);

        // 释放结果集
        mysql_free_result(result);
    }