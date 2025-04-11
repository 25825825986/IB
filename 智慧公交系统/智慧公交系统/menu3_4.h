#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include <stdio.h>
#include "include.h"

void menu3_4()
{
    char station_id[20];
    int choice_3_4;
    do
    {
        printf("*站点管理列表*\n");
        printf("1.添加站点\n");
        printf("2.删除站点\n");
        printf("3.修改站点\n");
        printf("4.返回上一级菜单\n");
        printf("请输入您的选择: ");
        scanf("%d", &choice_3_4);

        while (choice_3_4 < 1 || choice_3_4 > 4)
        {
            printf("输入错误，请重新输入: ");
            scanf("%d", &choice_3_4);
        }

        switch (choice_3_4)
        {
        case 1:
            system("cls");
            station_input(&station);
            station_add(&station);
            printf("按任意键继续...\n");
            _getch();
            system("cls");
            break;
        case 2:
            system("cls");
            station_query(NULL);
            printf("请输入要删除的站点编号：");
            scanf("%19s", station_id);
            station_delete(station_id);
            printf("按任意键继续...\n");
            _getch();
            system("cls");
            break;
        case 3:
            system("cls");
            station_query(NULL);
            printf("请输入要修改的站点编号：");
            scanf("%19s", station_id);
            station_update(station_id);
            printf("按任意键继续...\n");
            _getch();
            system("cls");
            break;
        case 4:
            system("cls");
            menu3();
        }
    } while (choice_3_4 != 4);
}