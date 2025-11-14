//
//  basiHPC.cpp
//  HPA
//
//  Created by 姚晨 on 2025/11/13.
//
#include "basiHPC.h"
#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

string hp_mutip(string s1, string s2) {
    // 检查特殊情况
    if (s1 == "0" || s2 == "0") return "0";
    unsigned long len1 = s1.size(), len2 = s2.size();
    vector<int> a(len1), b(len2), c(len1 + len2, 0);
    
    // 将字符串转换为数字数组（逆序存储）
    for (int i = 0; i < len1; i++) {
        a[i] = s1[len1 - 1 - i] - '0';
    }
    for (int i = 0; i < len2; i++) {
        b[i] = s2[len2 - 1 - i] - '0';
    }
    
    // 进行乘法运算
    for (int i = 0; i < len1; i++) {
        for (int j = 0; j < len2; j++) {
            c[i + j] += a[i] * b[j];
        }
    }
    
    // 统一处理进位
    for (int i = 0; i < len1 + len2 - 1; i++) {
        if (c[i] >= 10) {
            c[i + 1] += c[i] / 10;
            c[i] %= 10;
        }
    }
    
    // 找到最高非零位
    unsigned long index = len1 + len2 - 1;
    while (index > 0 && c[index] == 0) {
        index--;
    }
    
    // 将结果转换为字符串
    string result = "";
    for (unsigned long i = index; i >= 0; i--) {
        result += to_string(c[i]);
    }
    
    return result;
}

string hp_plus( string s1,string s2) {
    string sum;
    s1[210];
    s2[210];
    int a1[210] = { 0 }, a2[210] = { 0 }, a3[210] = { 0 };
    unsigned long len1 = s1.size(), len2 = s2.size(),len=0;
    for (int i = 0; i <len1; i++) {
        a1[i] = s1[len1 - 1 - i]-'0';
    }
    for (int j = 0; j < len2; j++) {
        a2[j] = s2[len2 - 1 - j]-'0';
    }
    len = (len1 > len2) ? (len1) : (len2);
    for (int k = 0; k < len; k++) {
        a3[k] = a1[k] + a2[k];
    }
    for (int l = 0; l < len; l++) {
        if (a3[l] >= 10) {
            a3[l] -= 10;
            a3[l + 1]++;
        }
    }
    if (a3[len] != 0) {
        len++;
    }
    for (unsigned long m = len - 1; m >= 0; m--) {
        sum.push_back(a3[m]);
    }

    return sum;
}



#include <functional>
#include <stdexcept>

using namespace std;

// 移除前导零
string HighPrecisionDivider::removeLeadingZeros(const string& num) {
    size_t start = num.find_first_not_of('0');
    return (start == string::npos) ? "0" : num.substr(start);
}

// 比较两个大数的大小
int HighPrecisionDivider::compare(const string& a, const string& b) {
    string a_clean = removeLeadingZeros(a);
    string b_clean = removeLeadingZeros(b);
    
    if (a_clean.length() != b_clean.length()) {
        return a_clean.length() > b_clean.length() ? 1 : -1;
    }
    
    return a_clean.compare(b_clean);
}

// 大数减法 (a >= b)
string HighPrecisionDivider::subtract(const string& a, const string& b) {
    string result;
    int borrow = 0;
    int i = a.length() - 1;
    int j = b.length() - 1;
    
    while (i >= 0 || j >= 0) {
        int digit_a = (i >= 0) ? a[i--] - '0' : 0;
        int digit_b = (j >= 0) ? b[j--] - '0' : 0;
        
        int diff = digit_a - digit_b - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        result.push_back(diff + '0');
    }
    
    reverse(result.begin(), result.end());
    return removeLeadingZeros(result);
}

// 大数加法
string HighPrecisionDivider::add(const string& a, const string& b) {
    string result;
    int carry = 0;
    int i = a.length() - 1;
    int j = b.length() - 1;
    
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';
        
        result.push_back(sum % 10 + '0');
        carry = sum / 10;
    }
    
    reverse(result.begin(), result.end());
    return removeLeadingZeros(result);
}

// 大数乘以一位数
string HighPrecisionDivider::multiplyByDigit(const string& a, int digit) {
    if (digit == 0) return "0";
    
    string result;
    int carry = 0;
    
    for (int i = a.length() - 1; i >= 0; i--) {
        int product = (a[i] - '0') * digit + carry;
        result.push_back(product % 10 + '0');
        carry = product / 10;
    }
    
    if (carry) {
        result.push_back(carry + '0');
    }
    
    reverse(result.begin(), result.end());
    return removeLeadingZeros(result);
}

// Knuth 除法算法 - 核心高效算法
pair<string, string> HighPrecisionDivider::knuthDivide(const string& dividend, const string& divisor) {
    if (divisor == "0") return {"Error", "Division by zero"};
    
    string normalized_dividend = dividend;
    string normalized_divisor = divisor;
    
    // 预处理：确保除数足够大以避免除数为0的情况
    int n = normalized_divisor.length();
    int m = normalized_dividend.length() - n;
    
    if (m < 0) {
        return {"0", dividend}; // 被除数小于除数
    }
    
    // 归一化：使除数的第一位数字 >= 5
    int d = 10 / (normalized_divisor[0] - '0' + 1);
    if (d > 1) {
        normalized_dividend = multiplyByDigit(normalized_dividend, d);
        normalized_divisor = multiplyByDigit(normalized_divisor, d);
    }
    
    n = normalized_divisor.length();
    m = normalized_dividend.length() - n;
    
    vector<int> quotient(m + 1, 0);
    string remainder = normalized_dividend.substr(0, n);
    
    for (int j = 0; j <= m; j++) {
        // 估算商
        int r_length = remainder.length();
        string first_two = (r_length >= 2) ? remainder.substr(0, 2) :
                          (r_length == 1) ? remainder + "0" : "00";
        
        int q_hat = stoi(first_two) / (normalized_divisor[0] - '0');
        q_hat = min(q_hat, 9); // 确保商是一位数
        
        // 调整商
        while (compare(multiplyByDigit(normalized_divisor, q_hat), remainder) > 0) {
            q_hat--;
        }
        
        quotient[j] = q_hat;
        
        if (j < m) {
            string product = multiplyByDigit(normalized_divisor, q_hat);
            remainder = subtract(remainder, product);
            
            // 添加下一位数字
            if (n + j < normalized_dividend.length()) {
                remainder += normalized_dividend[n + j];
            } else {
                remainder += '0';
            }
            
            remainder = removeLeadingZeros(remainder);
        }
    }
    
    // 构建商字符串
    string quotient_str;
    for (int digit : quotient) {
        quotient_str += to_string(digit);
    }
    quotient_str = removeLeadingZeros(quotient_str);
    
    // 反归一化余数
    if (d > 1) {
        // 将余数除以d
        string temp_remainder = remainder;
        remainder = "";
        int carry = 0;
        
        for (char c : temp_remainder) {
            int current = carry * 10 + (c - '0');
            remainder += to_string(current / d);
            carry = current % d;
        }
        remainder = removeLeadingZeros(remainder);
    }
    
    return {quotient_str, remainder};
}

// 简单除法（用于小数字）
string HighPrecisionDivider::simpleDivide(long long a, long long b, int precision) {
    if (b == 0) return "Error: Division by zero";
    
    string result;
    bool negative = false;
    
    // 处理符号
    if ((a < 0 && b > 0) || (a > 0 && b < 0)) {
        negative = true;
    }
    
    a = llabs(a);
    b = llabs(b);
    
    // 整数部分
    long long integer_part = a / b;
    long long remainder = a % b;
    
    result = to_string(integer_part);
    
    // 小数部分
    if (precision > 0 && remainder != 0) {
        result += ".";
        
        for (int i = 0; i < precision; i++) {
            remainder *= 10;
            result += to_string(remainder / b);
            remainder %= b;
            
            if (remainder == 0) {
                // 补零
                for (int j = i + 1; j < precision; j++) {
                    result += "0";
                }
                break;
            }
        }
    } else if (precision > 0) {
        result += ".";
        for (int i = 0; i < precision; i++) {
            result += "0";
        }
    }
    
    if (negative && result != "0") {
        result = "-" + result;
    }
    
    return result;
}

// 完整的高精度除法函数
string HighPrecisionDivider::divide(const string& dividend, const string& divisor, int precision) {
    // 处理符号
    bool negative = false;
    string clean_dividend = dividend;
    string clean_divisor = divisor;
    
    if (dividend[0] == '-') {
        negative = !negative;
        clean_dividend = dividend.substr(1);
    }
    if (divisor[0] == '-') {
        negative = !negative;
        clean_divisor = divisor.substr(1);
    }
    
    // 移除前导零
    clean_dividend = removeLeadingZeros(clean_dividend);
    clean_divisor = removeLeadingZeros(clean_divisor);
    
    // 检查特殊情况
    if (clean_divisor == "0") {
        return "Error: Division by zero";
    }
    if (clean_dividend == "0") {
        return "0";
    }
    
    // 使用 Knuth 算法计算整数部分和余数
    auto [quotient, remainder] = knuthDivide(clean_dividend, clean_divisor);
    
    if (quotient == "Error") {
        return remainder; // 返回错误信息
    }
    
    // 处理小数部分
    string result = quotient;
    if (precision > 0 && remainder != "0") {
        result += ".";
        
        for (int i = 0; i < precision; i++) {
            if (remainder == "0") {
                result += "0";
                continue;
            }
            
            // 将余数乘以10
            remainder += "0";
            
            // 再次使用 Knuth 算法
            auto [decimal_quotient, new_remainder] = knuthDivide(remainder, clean_divisor);
            
            if (decimal_quotient.length() > 0) {
                result += decimal_quotient;
                remainder = new_remainder;
            } else {
                result += "0";
            }
            
            if (remainder == "0") {
                // 补零直到达到指定精度
                for (int j = i + 1; j < precision; j++) {
                    result += "0";
                }
                break;
            }
        }
    } else if (precision > 0) {
        result += ".";
        for (int i = 0; i < precision; i++) {
            result += "0";
        }
    }
    
    // 添加符号
    if (negative && result != "0") {
        result = "-" + result;
    }
    
    return result;
}

// 智能除法 - 自动选择算法
string HighPrecisionDivider::smartDivide(const string& dividend, const string& divisor, int precision) {
    // 对于小数字，使用简单算法；对于大数字，使用 Knuth 算法
    try {
        // 尝试转换为 long long
        long long num1 = stoll(dividend);
        long long num2 = stoll(divisor);
        
        // 检查是否在安全范围内
        if (num1 > -1e18 && num1 < 1e18 && num2 > -1e18 && num2 < 1e18) {
            return simpleDivide(num1, num2, precision);
        }
    } catch (const exception& e) {
        // 转换失败，使用高精度算法
    }
    
    return divide(dividend, divisor, precision);
}
