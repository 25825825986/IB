#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include <stdio.h>
#include "include.h"

void menu3_5()
{
    char schedule_id[20];
    int choice_3_5;
    do
    {
        printf("*排班管理列表*\n");
        printf("1.添加排班\n");
        printf("2.删除排班\n");
        printf("3.修改排班\n");
        printf("4.返回上一级菜单\n");
        printf("请输入您的选择: ");
        scanf("%d", &choice_3_5);

        while (choice_3_5 < 1 || choice_3_5 > 4)
        {
            printf("输入错误，请重新输入: ");
            scanf("%d", &choice_3_5);
        }

        switch (choice_3_5)
        {
        case 1:
            system("cls");
            schedule_input(&schedule);
            schedule_add(&schedule);
            printf("按任意键继续...\n");
            _getch();
            system("cls");
            break;
        case 2:
            system("cls");
            schedule_query(NULL);
            printf("请输入要删除的排班号：");
            scanf("%19s", schedule_id);
            schedule_delete(schedule_id);
            printf("按任意键继续...\n");
            _getch();
            system("cls");
            break;
        case 3:
            system("cls");
            schedule_query(NULL);
            printf("请输入要修改的排班号：");
            scanf("%19s", schedule_id);
            printf("按任意键继续...\n");
            schedule_update(schedule_id);
            _getch();
            system("cls");
            break;
        case 4:
            system("cls");
            menu3();
        }
    } while (choice_3_5 != 4);
}