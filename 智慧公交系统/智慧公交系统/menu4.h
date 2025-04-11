#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include <stdio.h>
#include "include.h"

void menu4()
{
    int choice_1;
    do
    {
        printf("*信息修改列表*\n");
        printf("1.密码修改\n");
        printf("2.姓名修改\n");
        printf("3.手机号修改\n");
        printf("4.身份证修改\n");
        printf("5.驾龄修改\n");
        printf("6.返回上一级菜单\n");
        printf("请输入您的选择: ");
        scanf("%d", &choice_1);

        while (choice_1 < 1 || choice_1 > 6)
        {
            printf("输入错误，请重新输入: ");
            scanf("%d", &choice_1);
        }

        switch (choice_1)
        {
        case 1:
            system("cls");
            user_update_password();
            printf("按任意键继续...\n");
            _getch();
            system("cls");
            break;
        case 2:
            system("cls");
            user_update_name();
            printf("按任意键继续...\n");
            _getch();
            system("cls");
            break;
        case 3:
            system("cls");
            user_update_telephone();
            printf("按任意键继续...\n");
            _getch();
            system("cls");
            break;
        case 4:
            system("cls");
            user_update_id_card();
            printf("按任意键继续...\n");
            _getch();
            system("cls");
            break;
        case 5:
            system("cls");
            user_update_driving();
            printf("按任意键继续...\n");
            _getch();
            system("cls");

        case 6:
            system("cls");

            menu();
        }
    } while (choice_1 != 6);
}