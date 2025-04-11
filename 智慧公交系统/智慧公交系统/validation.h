#pragma once
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


// 定义所有符合要求的汉字
const char valid_chars[] = "京津沪渝冀豫云辽黑湘皖鲁新苏浙赣鄂桂甘晋蒙陕吉闽贵粤青藏川宁琼";

// 检查汉字是否在有效汉字列表中
bool is_valid_first_char(char c) {
    for (int i = 0; i < strlen(valid_chars); i++) {
        if (c == valid_chars[i]) {
            return true;
        }
    }
    return false;
}

// 检查车牌号格式是否正确
bool is_valid_license(const char* license) {
    int length = strlen(license);
    if (length != 10 && length != 11) {
        return false;
    }

    // 第一个字符应为有效汉字
    if (!is_valid_first_char(license[0])) {
        return false;
    }

    // 第二个字符应为字母（A-Z）
    if (!isalpha(license[3]) || !isupper(license[3])) {
        return false;
    }

    if (license[4] != '-') {
        return false;
    }


    // 检查剩余部分（字母和数字的组合）
    for (int i = 5; i < length; i++) {
        if (!isalnum(license[i]) || islower(license[i])) {
            return false;
        }
    }

    return true;
}

// 检查身份证号格式是否正确
bool is_valid_id(const char* id_card) {
    // 身份证号一般是18位，最后一位可能是数字或X
    int len = strlen(id_card);
    if (len != 18) return false;

    // 前17位应该是数字，最后一位可能是数字或X
    for (int i = 0; i < 17; i++) {
        if (!isdigit(id_card[i])) return false;
    }

    if (!(isdigit(id_card[17]) || (id_card[17] == 'X'))) return false;

    return true;
}

// 检查密码格式是否正确
bool is_valid_password(const char* password) {
    int len = strlen(password);

    // 密码长度应在6到12位之间
    if (len < 6 || len > 12) return false;

    // 密码应该包含至少一个大写字母、一个小写字母和一个数字
    bool has_upper = false, has_lower = false, has_digit = false;

    for (int i = 0; i < len; i++) {
        if (isupper(password[i])) has_upper = true;
        if (islower(password[i])) has_lower = true;
        if (isdigit(password[i])) has_digit = true;
    }

    if (!has_upper || !has_lower || !has_digit) return false;

    return true;
}
