#pragma once
#include <stdio.h>
#include "database.h"

typedef struct {
    char role_id[20];
    char role_name[10];
    char role_describe[100];
} Role;

void role_input(Role* role) {
    printf("请输入角色编号: ");
    scanf("%19s", role->role_id);

    printf("请输入角色名称: ");
    scanf("%9s", role->role_name);

    printf("请输入角色描述: ");
    scanf("%99s", role->role_describe);
}

void role_add(Role* role) {
    sprintf(sql, "INSERT INTO role (role_id, role_name, role_describe) VALUES ('%s', '%s', '%s')",
        role->role_id, role->role_name, role->role_describe);


    if (mysql_query(con, sql)) {
        fprintf(stderr, "角色添加失败: %s\n", mysql_error(con));
    }
    else {
        printf("角色添加成功\n");
    }
}

void role_delete(const char* role_id) {
    sprintf(sql, "DELETE FROM role WHERE role_id = '%s'", role_id);
    if (mysql_query(con, sql)) {
        fprintf(stderr, "角色删除失败: %s\n", mysql_error(con));
    }
    else {
        printf("角色删除成功\n");
    }
}

void role_update(const char* username, const char* new_role_id) {
    snprintf(sql, sizeof(sql), "UPDATE user SET role_id = '%s' WHERE user_name = '%s'", new_role_id, username);

    // 执行查询
    if (mysql_query(con, sql)) {
        fprintf(stderr, "更新用户角色失败: %s\n", mysql_error(con));
        return;
    }

    if (mysql_affected_rows(con) > 0) {
        printf("用户角色更新成功\n");
    }
    else {
        printf("更新失败，可能是用户名不存在\n");
    }
}

void role_print(MYSQL_RES* result) {
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

void role_query(const char* role_id) {
    if (role_id == NULL || strlen(role_id) == 0) {
        // 查询整个表
        sprintf(sql, "SELECT * FROM role");
    }
    else {
        // 查询特定角色编号
        sprintf(sql, "SELECT * FROM role WHERE role_id = '%s'", role_id);
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
    role_print(result);

    // 释放结果集
    mysql_free_result(result);
}