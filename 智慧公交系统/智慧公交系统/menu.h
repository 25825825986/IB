#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include "include.h"
#include <stdio.h>

void menu1();
void menu2();
void menu3();
void menu4();

void menu()
{
    int choice;
    do
    {
        printf("*用户菜单列表*\n");
        printf("1.信息查询\n");
        printf("2.调度员系统\n");
        printf("3.管理员系统\n");
        printf("4.修改个人信息\n");
        printf("5.退出系统\n");
        printf("请输入您的选择: ");
        scanf("%d", &choice);

        while (choice < 1 || choice > 5)
        {
            printf("输入错误，请重新输入: ");
            scanf("%d", &choice);
        }

        switch (choice)
        {
        case 1:
            system("cls");
            menu1();
            break;
        case 2:
            if (strcmp(user_role_id, "2") == 0 || strcmp(user_role_id, "3") == 0) {
                system("cls");
                menu2();
            }
            else {
                system("cls");
                printf("权限不足，无法进入调度员系统。\n");
            }
            break;
        case 3:
            if (strcmp(user_role_id, "3") == 0) {
                system("cls");
                menu3();
            }
            else {
                system("cls");
                printf("权限不足，无法进入管理员系统。\n");
            }
            break;
        case 4:
            system("cls");
            menu4();
            /*user_update();
            printf("按任意键继续...\n");
            _getch();*/
            break;
        case 5:
            system("cls");
            printf("欢迎下次使用！\n");
            exit(0);
        }
    } while (choice != 5);
}

