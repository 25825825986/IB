#pragma once
#include <stdio.h>
#include "database.h"

typedef struct {
    char rels_id[20];
    char line_id[20];
    char station[20];
    char order[3];
    char direction[20];
} Rels;

Rels rels;

void rels_input(Rels* rels) {
    printf("请输入线站编号: ");
    scanf("%19s", rels->rels_id);

    printf("请输入线路编号: ");
    scanf("%19s", rels->line_id);

    printf("请输入站点编号: ");
    scanf("%19s", rels->station);

    printf("请输入线路顺序: ");
    scanf("%2s", rels->order);

    printf("请输入线路方向: ");
    scanf("%19s", rels->direction);
}

void rels_add(Rels* rels) {
    // 检查是否存在相同的线站关系
    sprintf(sql,
        "SELECT COUNT(*) FROM re_line_station WHERE line_id = '%s' AND station_id = '%s' AND line_station_order = '%s' AND direction = '%s'",
        rels->line_id, rels->station, rels->order, rels->direction);

    if (mysql_query(con, sql)) {
        fprintf(stderr, "检查线站关系是否存在失败: %s\n", mysql_error(con));
        return;
    }

    if (result == NULL) {
        fprintf(stderr, "获取检查结果失败: %s\n", mysql_error(con));
        return;
    }

    if (row && atoi(row[0]) > 0) {
        system("cls");
        printf("该线站关系已存在\n");
        mysql_free_result(result);
        return;
    }

    mysql_free_result(result);

    sprintf(sql, "INSERT INTO rels (rels_id, line_id, station, order, direction) VALUES ('%s', '%s', '%s', '%s', '%s')",
        rels->rels_id, rels->line_id, rels->station, rels->order, rels->direction);
    if (mysql_query(con, sql)) {
        fprintf(stderr, "线站添加失败: %s\n", mysql_error(con));
    }
    else {
        printf("线站添加成功\n");
    }
}

void rels_delete(const char* rels_id) {
    sprintf(sql, "DELETE FROM rels WHERE rels_id = '%s'", rels_id);
    if (mysql_query(con, sql)) {
        fprintf(stderr, "线站删除失败: %s\n", mysql_error(con));
    }
    else {
        printf("线站删除成功\n");
    }
}

void rels_update(const char* rels_id) {
    Rels new_rels;
    strcpy(new_rels.rels_id, rels_id);

    printf("请输入新的线路编号: ");
    scanf("%19s", new_rels.line_id);

    printf("请输入新的站点编号: ");
    scanf("%19s", new_rels.station);

    printf("请输入新的线路顺序: ");
    scanf("%2s", new_rels.order);

    printf("请输入新的线路方向: ");
    scanf("%19s", new_rels.direction);

    sprintf(sql,
        "SELECT COUNT(*) FROM re_line_station WHERE line_id = '%s' AND station_id = '%s' AND line_station_order = '%s' AND direction = '%s' AND rels_id != '%s'",
        new_rels.line_id, new_rels.station, new_rels.order, new_rels.direction, rels_id);

    if (mysql_query(con, sql)) {
        fprintf(stderr, "检查线站关系是否存在失败: %s\n", mysql_error(con));
        return;
    }

    if (result == NULL) {
        fprintf(stderr, "获取检查结果失败: %s\n", mysql_error(con));
        return;
    }

    if (row && atoi(row[0]) > 0) {
        printf("该线站关系已存在\n");
        mysql_free_result(result);
        return;
    }

    mysql_free_result(result);

    sprintf(sql, "UPDATE rels SET line_id = '%s', station = '%s', order = '%s', direction = '%s' WHERE rels_id = '%s'",
        new_rels.line_id, new_rels.station, new_rels.order, new_rels.direction, rels_id);

    if (mysql_query(con, sql)) {
        fprintf(stderr, "线站信息修改失败: %s\n", mysql_error(con));
    }
    else {
        printf("线站信息修改成功\n");
    }
}

void rels_print(MYSQL_RES* result) {
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

void rels_query(const char* rels_id) {
    if (rels_id == NULL || strlen(rels_id) == 0) {
        // 查询整个表
        sprintf(sql, "SELECT * FROM rels");
    }
    else {
        // 查询特定线站编号
        sprintf(sql, "SELECT * FROM rels WHERE rels_id = '%s'", rels_id);
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
    rels_print(result);

    // 释放结果集
    mysql_free_result(result);
}