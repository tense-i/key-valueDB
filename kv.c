
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "kv.h"

/**
 * 函数名 : WriteKeyValue
 * 函数功能描述 ：如果指定文件存在key就修改其value，如果不存在就在文件尾部追加key = value
 * 函数入参:   char *fileName 文件名,
 *            char *key 键名,
 *            char *value 值
 **/

/**
 * 函数功能描述 ：查找指定文件key对于的value 存在返回其value，不存在返回NULL
 * @param fileName     文件名
 * @param key       需要查询的值对应的键
 * @return
 */
char *ReadValue(char *fileName, char *key)
{
    char buf[ABUP_JSON_VALUE_SIZE] = " ";
    char *pval = NULL;
    char *val;
    int val_len = 0;
    FILE *fp;
    fp = fopen(fileName, "r");
    if (NULL == fp)
    {
        printf("文件不存在----\n");
        return NULL;
    }
    int i = 0;
    int isExits = 0;

    while (fgets(buf, ABUP_JSON_VALUE_SIZE, fp))
    {
        while (buf[i] == ' ')
            i++;
        if (strncmp(&buf[i], key, sizeof(key)) == 0)
        {
            isExits = 1;
            pval = strstr(&buf[i], "=") + 1;
            val_len = strlen(pval);
            val = (char *)malloc(val_len + 1);
            for (int j = 0; j != val_len - 1; j++)
            {
                val[j] = *pval;
                pval++;
            }
            val[val_len] = '\0';
            break;
        }
    }
    fclose(fp);
    if (isExits == 1)
        return val;
    else
        NULL;
}

/**
 * 函数功能描述 ：如果指定文件存在key就删除key及value
 * @param fileName    保存数据的文件名
 * @param key         需要删除的值对应的键
 */
void RemoveKeyValue(char *fileName, char *key)
{

    FILE *fp, *tempFp;
    fp = fopen(fileName, "r");
    if (NULL == fp)
    {
        printf("文件打开失败----\n");
        return;
    }
    tempFp = fopen("temp.txt", "w");
    if (NULL == tempFp)
    {
        printf("临时文件创建失败\n");
    }
    char buf[ABUP_JSON_VALUE_SIZE] = "";
    int i = 0;
    int isExists = 0;
    while (fgets(buf, ABUP_JSON_VALUE_SIZE, fp))
    {
        while (buf[i] == ' ')
            i++;
        if (strncmp(&buf[i], key, sizeof(key)) == 0)
        {
            isExists = 1;
            continue;
        }
        else
        {

            fputs(buf, tempFp);
        }
    }
    if (isExists == 0)
        return;
    fclose(fp);
    fclose(tempFp);
    remove(fileName);
    rename("temp.txt", fileName);
}
