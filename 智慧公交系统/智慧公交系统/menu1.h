#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include <stdio.h>
#include "include.h"

void menu1()
{
    char line_id[20];
    char bus_id[20];
    char start[20];
    char end[20];
    int choice_1;
    do
    {
        printf("*信息查询列表*\n");
        printf("1.普通查询\n");
        printf("2.线路查询\n");
        printf("3.车辆编号查询\n");
        printf("4.起点站，终点站查询\n");
        printf("5.返回上一级菜单\n");
        printf("请输入您的选择: ");
        scanf("%d", &choice_1);

        while (choice_1 < 1 || choice_1 > 5)
        {
            printf("输入错误，请重新输入: ");
            scanf("%d", &choice_1);
        }

        switch (choice_1)
        {
        case 1:
            system("cls");
            schedule_query(NULL);
            printf("按任意键继续...\n");
            _getch();
            system("cls");
            break;
        case 2:
            system("cls");
            printf("请输入线路名:");
            scanf("%19s", line_id);
            schedule_query_byline(line_id);
            printf("按任意键继续...\n");
            _getch();
            system("cls");
            break;
        case 3:
            system("cls");
            printf("请输入车牌号:");
            scanf("%19s", bus_id);
            schedule_query_bybus(bus_id);
            printf("按任意键继续...\n");
            _getch();
            system("cls");
            break;
        case 4:
            system("cls");
            printf("请输入起点站(输入无查询终点站):");
            scanf("%19s", start);
            printf("请输入终点站(输入无查询起点站):");
            scanf("%19s", end);
            schedule_query_bystation(start, end);
            printf("按任意键继续...\n");
            _getch();
            system("cls");
            break;
        case 5:
            system("cls");
            menu();
        }
    } while (choice_1 != 5);
}