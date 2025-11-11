//
//  main.cpp
//  hw
//
//  Created by 姚晨 on 2025/11/10.
//
#include <iostream>
#include <stdio.h>
#include <string>
#include <algorithm>
using namespace std;
int excNumBit(int a,int excBit);
int main()
{
    int a;
    int b;
    long int c;
    cin >> a >> b;
    //add your code here
   int a_123 = excNumBit(a,3);
   int b_123 = excNumBit(b,3);
   if (a_123!=0 && b_123!=0) {
        c = a_123 * 1000 +b_123;
    }else {
        c = a_123+b_123;
    }

    printf("a=%d,b=%d,c=%ld\n", a, b, c);
}


/*
@spam 要包含<string>，只能在C++下运行
@int a 传入一个数字（至少两位）
@int excBit 标志要转换的位数（从右向左）
@return 返回已经转换的位数
*/

int excNumBit(int a, int excBit) {
    if (a == 0) return 0;
    
    bool isNegative = false;
    if (a < 0) {
        isNegative = true;
        a = -a;
    }
    
    // 计算实际位数
    int temp = a;
    int actualDigits = 0;
    while (temp > 0) {
        actualDigits++;
        temp /= 10;
    }
    
    int bitsToProcess = min(excBit, actualDigits);
    
    // 直接构建反转数字
    int reverseNum = 0;
    temp = a;
    for (int i = 0; i < bitsToProcess; i++) {
        reverseNum = reverseNum * 10 + (temp % 10);
        temp /= 10;
    }
    
    if (isNegative) {
        reverseNum = -reverseNum;
    }
    
    return reverseNum;
}

/*
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{  //add your code here
    int a,b;
    string a1;
    scanf("%d",&a);
    a1 = to_string(a);
    vector<char>A_arr;
    for(const char c :a1){
        A_arr.push_back(c);
    }
    reverse(A_arr.begin(),A_arr.end());
    for (int i=0; i < A_arr.size(); i++) {
        a1[i] = A_arr[i];
    }
    b = stoi(a1);
    printf("a=%d, b=%d\n", a, b);
}
*/
