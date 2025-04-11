#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include <stdio.h>
#include "include.h"

void menu3_2()
{
    char line_id[20];
    int choice_3_2;
    do
    {
        printf("*线路管理列表*\n");
        printf("1.添加线路\n");
        printf("2.删除线路\n");
        printf("3.修改线路\n");
        printf("4.返回上一级菜单\n");
        printf("请输入您的选择: ");
        scanf("%d", &choice_3_2);

        while (choice_3_2 < 1 || choice_3_2 > 4)
        {
            printf("输入错误，请重新输入: ");
            scanf("%d", &choice_3_2);
        }

        switch (choice_3_2)
        {
        case 1:
            system("cls");
            line_input(&line);
            line_add(&line);
            printf("按任意键继续...\n");
            _getch();
            system("cls");
            break;
        case 2:
            system("cls");
            line_query(NULL);
            printf("请输入要删除的线路编号：");
            scanf("%19s", line_id);
            line_delete(line_id);
            printf("按任意键继续...\n");
            _getch();
            system("cls");
            break;
        case 3:
            system("cls");
            line_query(NULL);
            printf("请输入要修改的线路编号：");
            scanf("%19s", line_id);
            line_update(line_id);
            printf("按任意键继续...\n");
            _getch();
            system("cls");
            break;
        case 4:
            system("cls");
            menu3();
        }
    } while (choice_3_2 != 4);
}