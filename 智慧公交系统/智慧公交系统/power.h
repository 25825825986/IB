#pragma once
#include <stdio.h>
#include "database.h"

typedef struct {
    char power_id[20];
    char power_name[20];
    char power_description[100];
} Power;

Power power;


void power_input(Power* power) {
    printf("请输入权限编号: ");
    scanf("%19s", power->power_id);

    printf("请输入权限名称: ");
    scanf("%19s", power->power_name);

}

void power_add(Power* power) {
    sprintf(sql, "INSERT INTO power (power_id, power_name) VALUES ('%s', '%s')",
        power->power_id, power->power_name);
    if (mysql_query(con, sql)) {
        fprintf(stderr, "权限添加失败: %s\n", mysql_error(con));
    }
    else {
        printf("权限添加成功\n");
    }
}

void power_delete(const char* power_id) {
    sprintf(sql, "DELETE FROM power WHERE power_id = '%s'", power_id);
    if (mysql_query(con, sql)) {
        fprintf(stderr, "权限删除失败: %s\n", mysql_error(con));
    }
    else {
        printf("权限删除成功\n");
    }
}