#define _CRT_SECURE_NO_WARNINGS 1
#include "include.h"
#include "gloabal.h"
#include <stdio.h>
#include <mysql.h>
#include "database.h"

char nowusername[20];
char user_role_id[20];

int login(const char* password) {
    snprintf(sql, sizeof(sql), "SELECT * FROM user WHERE user_name = '%s'", nowusername);

    // 执行查询
    if (mysql_query(con, sql)) {
        fprintf(stderr, "查询失败: %s\n", mysql_error(con));
        return -1; // 查询失败
    }

    result = mysql_store_result(con);
    if (result == NULL) {
        fprintf(stderr, "存储结果集失败: %s\n", mysql_error(con));
        return -1; // 存储结果集失败
    }

    int login_status = 0;

    // 检查查询结果
    if ((row = mysql_fetch_row(result))) {
        // 用户名存在，检查用户状态
        if (strcmp(row[8], "禁用") == 0) { // 假设第9列是 user_status
            // 用户状态为禁用
            system("cls");
            printf("用户已被禁用，无法登录。\n");
            login_status = -3;
        }
        else {
            mysql_free_result(result); // 释放之前的结果集
            snprintf(sql, sizeof(sql), "SELECT * FROM user WHERE user_name = '%s' AND password = '%s'", nowusername, password);

            // 执行查询
            if (mysql_query(con, sql)) {
                fprintf(stderr, "查询失败: %s\n", mysql_error(con));
                return -1; // 查询失败
            }

            result = mysql_store_result(con);
            if (result == NULL) {
                fprintf(stderr, "存储结果集失败: %s\n", mysql_error(con));
                return -1; // 存储结果集失败
            }

            if ((row = mysql_fetch_row(result))) {
                // 成功登录
                strncpy(user_role_id, row[1], sizeof(user_role_id) - 1);
                user_role_id[sizeof(user_role_id) - 1] = '\0'; // 确保字符串结尾为 '\0'
                login_status = 1;
            }
        }
    }
    else {
        // 用户名不存在
        login_status = -2;
    }

    // 释放结果集
    mysql_free_result(result);

    return login_status;
}

int main() {
    char password[20];

    connectSQL();

    printf("欢迎使用智慧公交系统！\n");

    while (1) {
        printf("请输入用户名：");
        scanf("%19s", nowusername);
        printf("请输入密码：");

        int i = 0;
        char ch;
        while ((ch = getch()) != '\r' && i < 19) {
            if (ch == '\b' && i > 0) {
                printf("\b \b");
                i--;
                continue;
            }
            password[i++] = ch;
            printf("*"); // 显示星号代替实际字符
        }
        password[i] = '\0';

        int status = login(password);
        if (status == 1) {
            printf("登录成功！\n");
            break; // 登录成功，退出循环
        }
        else if (status == -2) {
            system("cls");
            printf("用户名不存在，请重新输入！\n");
        }
        else if (status == -3) {
            system("cls");
            printf("用户已被禁用，无法登录。\n");
        }
        else {
            system("cls");
            printf("密码错误，请重新输入！\n");
        }
    }

    system("cls");
    menu();
    mysql_close(con);

    return 0;
}


