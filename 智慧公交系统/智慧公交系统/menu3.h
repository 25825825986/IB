#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include <stdio.h>
#include "include.h"

void menu3_1();
void menu3_2();
void menu3_3();
void menu3_4();
void menu3_5();

void menu3()
{
    int choice_3;
    do
    {
        printf("*管理员管理系统*\n");
        printf("1.用户信息操作\n");
        printf("2.线路信息操作\n");
        printf("3.车辆信息操作\n");
        printf("4.站点信息操作\n");
        printf("5.排班信息操作\n");
        printf("6.返回上一级菜单\n");
        printf("请输入您的选择: ");
        scanf("%d", &choice_3);

        while (choice_3 < 1 || choice_3 > 6)
        {
            printf("输入错误，请重新输入: ");
            scanf("%d", &choice_3);
        }

        switch (choice_3)
        {
        case 1:
            system("cls");
            menu3_1();
            break;
        case 2:
            system("cls");
            menu3_2();
            break;
        case 3:
            system("cls");
            menu3_3();
            break;
        case 4:
            system("cls");
            menu3_4();
            break;
        case 5:
            system("cls");
            menu3_5();
            break;
        case 6:
            system("cls");
            menu();
        }
    } while (choice_3 != 6);
}