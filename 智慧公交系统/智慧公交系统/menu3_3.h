#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include <stdio.h>
#include "include.h"

void menu3_3()
{
    char bus_id[20];
    int choice_3_3;
    do
    {
        printf("*车辆管理列表*\n");
        printf("1.添加车辆\n");
        printf("2.删除车辆\n");
        printf("3.修改车辆\n");
        printf("4.返回上一级菜单\n");
        printf("请输入您的选择: ");
        scanf("%d", &choice_3_3);

        while (choice_3_3 < 1 || choice_3_3 > 4)
        {
            printf("输入错误，请重新输入: ");
            scanf("%d", &choice_3_3);
        }

        switch (choice_3_3)
        {
        case 1:
            system("cls");
            bus_input(&bus);
            bus_add(&bus);
            printf("按任意键继续...\n");
            _getch();
            system("cls");
            break;
        case 2:
            system("cls");
            bus_query(NULL);
            printf("请输入要删除的车辆编号：");
            scanf("%19s", bus_id);
            bus_delete(bus_id);
            printf("按任意键继续...\n");
            _getch();
            system("cls");
            break;
        case 3:
            system("cls");
            bus_query(NULL);
            printf("请输入要修改的车辆编号：");
            scanf("%19s", bus_id);
            bus_update(bus_id);
            printf("按任意键继续...\n");
            _getch();
            system("cls");
            break;
        case 4:
            system("cls");
            menu3();
        }
    } while (choice_3_3 != 4);
}