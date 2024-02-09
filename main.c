#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "kv.h"

char *genRandomString(int length)
{ // 生成长度为length的随机字符串
    int flag, i;
    char *string;
    srand((unsigned)time(NULL));
    if ((string = (char *)malloc(length)) == NULL)
    {
        return NULL;
    }

    for (i = 0; i < length - 1; i++)
    {
        flag = rand() % 3;
        switch (flag)
        {
        case 0:
            string[i] = 'A' + rand() % 26;
            break;
        case 1:
            string[i] = 'a' + rand() % 26;
            break;
        case 2:
            string[i] = '0' + rand() % 10;
            break;
        default:
            string[i] = 'x';
            break;
        }
    }
    string[length - 1] = '\0';
    return string;
}
int main(int argc, char const *argv[])
{
    char fileName[50] = "test.txt"; // 保存数据的文件
    char *key1 = NULL;
    char *value1 = NULL;
    int i = 0;

    clock_t start, stop;
    start = clock();
    for (i = 0; i < 1000; i++)
    {
        key1 = genRandomString(4);

        value1 = genRandomString(10);
        WriteKeyValue(fileName, key1, value1);
    }
    stop = clock();
    // 计算以秒为单位的运行时间，（结束时间-开始时间）/CLK_TCK
    printf("Fun函数耗费时间为%f秒\n", ((double)(stop - start)) / CLK_TCK);

    return 0;
}
