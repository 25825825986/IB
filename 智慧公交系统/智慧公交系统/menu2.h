#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include <stdio.h>
#include "include.h"

void menu2()
{
    char bus_id[20];
    char schedule_id[20];
    int choice_2;
    do
    {
        printf("*调度员管理系统*\n");
        printf("1.添加车辆\n");
        printf("2.删除车辆\n");
        printf("3.修改车辆\n");
        printf("4.添加排班\n");
        printf("5.删除排班\n");
        printf("6.修改排班\n");
        printf("7.返回上一级菜单\n");
        printf("请输入您的选择: ");
        scanf("%d", &choice_2);

        while (choice_2 < 1 || choice_2 > 7)
        {
            printf("输入错误，请重新输入: ");
            scanf("%d", &choice_2);
        }

        switch (choice_2)
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
            break;
        case 4:
            system("cls");
            schedule_input(&schedule);
            schedule_add(&schedule);
            printf("按任意键继续...\n");
            _getch();
            system("cls");
            break;
        case 5:
            system("cls");
            schedule_query(NULL);
            printf("请输入要删除的排班号：");
            scanf("%19s", schedule_id);
            schedule_delete(schedule_id);
            printf("按任意键继续...\n");
            _getch();
            system("cls");
            break;
        case 6:
            system("cls");
            schedule_query(NULL);
            printf("请输入要修改的排班号：");
            scanf("%19s", schedule_id);
            printf("按任意键继续...\n");
            _getch();
            system("cls");
            break;
        case 7:
            system("cls");
            menu();
        }
    } while (choice_2 != 7);
}