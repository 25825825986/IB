#pragma once
#include <stdio.h>
#include <string.h>
#include "database.h"

typedef struct {
    char line_id[20];
    char line_name[20];
    char line_status[10];
    char line_time[20];
    char line_direction[20];
}Line;

Line line;

void line_input(Line* line) {
    printf("请输入线路编号: ");
    scanf("%19s", line->line_id);

    printf("请输入线路名: ");
    scanf("%19s", line->line_name);

    printf("请输入线路状态: ");
    scanf("%9s", line->line_status);

    printf("请输入开启时间 (格式: YYYY-MM-DD): ");
    scanf("%19s", line->line_time);

    printf("请输入线路方向: ");
    scanf("%19s", line->line_direction);
}

void line_add(Line* line) {
    sprintf(sql, "INSERT INTO line (line_id, line_name, line_status, line_time, line_direction) VALUES ('%s', '%s', '%s', '%s', '%s')",
        line->line_id, line->line_name, line->line_status, line->line_time, line->line_direction);
    if (mysql_query(con, sql)) {
        fprintf(stderr, "线路添加失败: %s\n", mysql_error(con));
    }
    else {
        printf("线路添加成功\n");
    }
}

void line_delete(const char* line_id) {
    sprintf(sql, "DELETE FROM line WHERE line_id = '%s'", line_id);
    if (mysql_query(con, sql)) {
        fprintf(stderr, "线路删除失败: %s\n", mysql_error(con));
    }
    else {
        printf("线路删除成功\n");
    }
}

void line_update(const char* line_id) {
    Line new_line;
    strcpy(new_line.line_id, line_id);

    printf("请输入新的线路名: ");
    scanf("%19s", new_line.line_name);

    printf("请输入新的线路状态: ");
    scanf("%9s", new_line.line_status);

    printf("请输入新的开启时间 (格式: YYYY-MM-DD): ");
    scanf("%19s", new_line.line_time);

    printf("请输入新的线路方向: ");
    scanf("%19s", new_line.line_direction);

    sprintf(sql, "UPDATE line SET line_name = '%s', line_status = '%s', line_time = '%s', line_direction = '%s' WHERE bus_id = '%s'",
        new_line.line_name, new_line.line_status, new_line.line_time, new_line.line_direction, new_line.line_id);

    if (mysql_query(con, sql)) {
        fprintf(stderr, "线路信息修改失败: %s\n", mysql_error(con));
    }
    else {
        printf("线路信息修改成功\n");
    }
}


void line_print(MYSQL_RES* result) {
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

void line_query(const char* line_id) {
    if (line_id == NULL || strlen(line_id) == 0) {
        // 查询整个表
        sprintf(sql, "SELECT * FROM line");
    }
    else {
        // 查询特定线路编号
        sprintf(sql, "SELECT * FROM line WHERE line_id = '%s'", line_id);
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
    line_print(result);

    // 释放结果集
    mysql_free_result(result);
}