#pragma once
#include <mysql.h>
#include <stdio.h>
#include "gloabal.h"
// 数据库连接信息
const char* HOST = "localhost";
const char* USERNAME = "root"; 
const char* PASSWORD = "123456"; // 请根据实际情况修改密码
const char* DATABASE = "ib_sys"; // 请根据实际情况修改数据库名称

// 全局变量
MYSQL *con;
MYSQL_RES* res;
MYSQL_ROW row;
MYSQL_RES* result;
char sql[1024];

// 函数声明
void connectSQL();
// 连接数据库
void connectSQL() {
    con = mysql_init(NULL);
    if (mysql_set_character_set(con, "utf8mb4")) {
        fprintf(stderr, "设置字符集失败: %s\n", mysql_error(con));
    }
    if (!mysql_real_connect(con, HOST, USERNAME, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "连接数据库错误 %s\n", mysql_error(con));
    }
    else {
        printf("成功连接数据库!\n");
    }
}
