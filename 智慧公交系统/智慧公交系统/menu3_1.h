#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include <stdio.h>
#include "include.h"

void menu3_1()
{
    char user_id[20];
    char username[20];
    char new_role_id[20];
    char new_user_status[10];
    int choice_3_1;
    do
    {
        printf("*用户管理列表*\n");
        printf("1.添加用户角色\n");
        printf("2.删除用户\n");
        printf("3.修改用户状态\n");
        printf("4.返回上一级菜单\n");
        printf("请输入您的选择: ");
        scanf("%d", &choice_3_1);

        while (choice_3_1 < 1 || choice_3_1 > 4)
        {
            printf("输入错误，请重新输入: ");
            scanf("%d", &choice_3_1);
        }

        switch (choice_3_1)
        {
        case 1:
            system("cls");
            user_query(NULL);

            printf("请输入要修改角色的用户名：");
            scanf("%19s", username);
            printf("请输入新的角色编号：");
            scanf("%19s", new_role_id);
            role_update(username, new_role_id);
            printf("按任意键继续...\n");
            _getch();
            system("cls");
            break;
        case 2:
            system("cls");
            user_query(NULL);
            printf("请输入要删除的用户编号：");
            scanf("%19s", user_id);
            user_delete(user_id);
            printf("按任意键继续...\n");
            _getch();
            system("cls");
            break;
        case 3:
            system("cls");
            user_query(NULL);
            printf("请输入要修改的用户编号：");
            scanf("%19s", user_id);
            printf("请输入用户状态：");
            scanf("%19s", new_user_status);
            status_update(user_id, new_user_status);
            printf("按任意键继续...\n");
            _getch();
            system("cls");
            break;
        case 4:
            system("cls");
            menu3();
        }
    } while (choice_3_1 != 4);
}