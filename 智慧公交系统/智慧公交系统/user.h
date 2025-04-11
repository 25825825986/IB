#pragma once
#include <stdio.h>
#include <string.h>
#include "gloabal.h"
#include "database.h"

typedef struct {
    char user_id[20];
    char user_name[20];
    char password[20];
    char name[20];
    char phone_number[20];
    char id_card[20];
    char driving[10];
    char user_status[3];
    char role_id[20];
} User;

User user;

void user_input(User* user) {
    printf("请输入用户编号: ");
    scanf("%19s", user->user_id);

    printf("请输入用户名: ");
    scanf("%19s", user->user_name);

    printf("请输入密码: ");
    scanf("%19s", user->password);

    printf("请输入姓名: ");
    scanf("%19s", user->name);

    printf("请输入电话: ");
    scanf("%19s", user->phone_number);

    printf("请输入身份证: ");
    scanf("%19s", user->id_card);

    printf("请输入驾龄: ");
    scanf("%9s", user->driving);

    printf("请输入用户状态: ");
    scanf("%2s", user->user_status);
}

void user_add(User* user) {
    sprintf(sql, "INSERT INTO user (user_id, user_name, password, name, telephone, id_card, driving, user_status, role_id) VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')",
        user->user_id, user->user_name, user->password, user->name, user->phone_number, user->id_card, user->driving, user->user_status, user->role_id);
    if (mysql_query(con, sql)) {
        fprintf(stderr, "用户添加失败: %s\n", mysql_error(con));
    }
    else {
        printf("用户添加成功\n");
    }
}

void user_delete(const char* user_id) {
    sprintf(sql, "DELETE FROM user WHERE user_id = '%s'", user_id);
    if (mysql_query(con, sql)) {
        fprintf(stderr, "用户删除失败: %s\n", mysql_error(con));
    }
    else {
        printf("用户删除成功\n");
    }
}


void user_update_name(){
    char new_name[20];
    printf("请输入新的姓名：");
    scanf("%19s", new_name);

    sprintf(sql, "UPDATE user SET name = '%s' WHERE user_name = '%s'", new_name, nowusername);

    if (mysql_query(con, sql)) {
        fprintf(stderr, "用户信息修改失败: %s\n", mysql_error(con));
    }
    else {
        printf("用户信息修改成功\n");
    }
}

void user_update_password(){
    char new_password[20];
    while (1) {
        printf("请输入新的密码: ");
        scanf("%19s", new_password);

        if (is_valid_password(new_password)) {
            break;
        }
        printf("密码至少包含一个大写字母，小写字母，数字。\n");
    }
    sprintf(sql, "UPDATE user SET password = '%s' WHERE user_name = '%s'", new_password, nowusername);

    if (mysql_query(con, sql)) {
        fprintf(stderr, "密码修改失败: %s\n", mysql_error(con));
    }
    else {
        printf("密码修改成功\n");
    }
}

void user_update_telephone() {
    char new_telephone[20];
    printf("请输入新的电话：");
    scanf("%19s", new_telephone);

    sprintf(sql, "UPDATE user SET telephone = '%s' WHERE user_name = '%s'", new_telephone, nowusername);

    if (mysql_query(con, sql)) {
        fprintf(stderr, "电话修改失败: %s\n", mysql_error(con));
    }
    else {
        printf("电话修改成功\n");
    }
}

void user_update_id_card(){
    char new_id_card[20];
    while (1) {
        printf("请输入新的身份证: ");
        scanf("%19s", new_id_card);

        if (is_valid_id(new_id_card)) {
            break;
        }
        printf("请输入有效的身份证！\n");
    }
    sprintf(sql, "UPDATE user SET id_card = '%s' WHERE user_name = '%s'", new_id_card, nowusername);

    if (mysql_query(con, sql)) {
        fprintf(stderr, "身份证修改失败: %s\n", mysql_error(con));
    }
    else {
        printf("身份证修改成功\n");
    }
}

void user_update_driving(){
    char new_driving[20];
    printf("请输入新的驾龄: ");
    scanf("%19s", new_driving);

    sprintf(sql, "UPDATE user SET driving = '%s' WHERE user_name = '%s'", new_driving, nowusername);

    if (mysql_query(con, sql)) {
        fprintf(stderr, "驾龄修改失败: %s\n", mysql_error(con));
    }
    else {
        printf("驾龄修改成功\n");
    }
}

void user_update() {
    User new_user;
    strcpy(new_user.user_name, nowusername);

    while (1) {
        printf("请输入新的密码: ");
        scanf("%19s", new_user.password);

        if (is_valid_password(new_user.password)) {
            break;
        }
        printf("密码至少包含一个大写字母，小写字母，数字。\n");
    }
    

    printf("请输入新的姓名: ");
    scanf("%19s", new_user.name);

    printf("请输入新的电话: ");
    scanf("%19s", new_user.phone_number);
    while (1) {
        printf("请输入新的身份证: ");
        scanf("%19s", new_user.id_card);
        if (is_valid_id(new_user.id_card)) {
            break;
        }
        printf("不要乱输身份证！\n");
    }
    
    printf("请输入新的驾龄: ");
    scanf("%9s", new_user.driving);

    sprintf(sql, "UPDATE user SET password = '%s', name = '%s', telephone = '%s', id_card = '%s', driving = '%s' WHERE user_name = '%s'",
        new_user.password, new_user.name, new_user.phone_number, new_user.id_card, new_user.driving, nowusername);

    if (mysql_query(con, sql)) {
        fprintf(stderr, "用户信息修改失败: %s\n", mysql_error(con));
    }
    else {
        printf("用户信息修改成功\n");
    }
}

void user_print(MYSQL_RES* result) {
    unsigned int num_fields = mysql_num_fields(result);
    MYSQL_FIELD* fields = mysql_fetch_fields(result);

    // 打印表头
    for (unsigned int i = 0; i < num_fields; i++) {
        printf("  %-10s", fields[i].name);
    }
    printf("\n");

    // 打印分隔符
    for (unsigned int i = 0; i < num_fields; i++) {
        printf("------------------");
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
}

void user_query(const char* user_id) {
    if (user_id == NULL || strlen(user_id) == 0) {
        // 查询整个表
        sprintf(sql, "SELECT * FROM user");
    }
    else {
        // 查询特定用户编号
        sprintf(sql, "SELECT * FROM user WHERE user_id = '%s'", user_id);
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
    user_print(result);

    // 释放结果集
    mysql_free_result(result);
}

void status_update(const char* user_id, const char* new_user_status) {
    snprintf(sql, sizeof(sql), "UPDATE user SET user_status = '%s' WHERE user_id = '%s'", new_user_status, user_id);

    // 执行查询
    if (mysql_query(con, sql)) {
        fprintf(stderr, "更新用户状态失败: %s\n", mysql_error(con));
        return;
    }

    if (mysql_affected_rows(con) > 0) {
        printf("用户状态更新成功\n");
    }
    else {
        printf("更新失败，可能是用户不存在\n");
    }
}
