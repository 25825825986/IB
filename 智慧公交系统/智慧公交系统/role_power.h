#pragma once
#include <stdio.h>

typedef struct {
    char rerp_id[20];
    char role_id[20];
    char power_id[20];
} Rerp;

void role_power_input(Rerp* role_power) {
    printf("请输入角色权限编号: ");
    scanf("%19s", role_power->rerp_id);

    printf("请输入角色编号: ");
    scanf("%19s", role_power->role_id);

    printf("请输入权限编号: ");
    scanf("%19s", role_power->power_id);

}

void role_power_add(Rerp* role_power) {
    sprintf(sql, "INSERT INTO role_power (role_power_id, role_id, power_id) VALUES ('%s', '%s', '%s')",
        role_power->rerp_id, role_power->role_id, role_power->power_id);
    if (mysql_query(con, sql)) {
        fprintf(stderr, "角色权限添加失败: %s\n", mysql_error(con));
    }
    else {
        printf("角色权限添加成功\n");
    }
}

void role_power_delete(const char* role_power_id) {
    sprintf(sql, "DELETE FROM role_power WHERE role_power_id = '%s'", role_power_id);
    if (mysql_query(con, sql)) {
        fprintf(stderr, "角色权限删除失败: %s\n", mysql_error(con));
    }
    else {
        printf("角色权限删除成功\n");
    }
}