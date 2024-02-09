
#define ABUP_JSON_VALUE_SIZE 1024
#define ABUP_JSON_KEY_SIZE 128

/**
 * 函数功能描述 ：如果指定文件存在key就修改其value，如果不存在就在文件尾部追加key = value
 * @param fileName 文件名
 * @param key       保存的键名
 * @param value     保存的值
 */
void WriteKeyValue(char *fileName, char *key, char *value)
{
    // 键缓冲区
    char buf[ABUP_JSON_KEY_SIZE] = "";

    int isExist = 0;

    FILE *fp, *temp;
    // 读写打开、不清空
    fp = fopen(fileName, "r+"); // 以读写的模式打开要写入的文件

    // 数据库文件不存在
    if (NULL == fp)
    {
        // 以只写的方式打开、不存在即创建该文件
        fp = fopen(fileName, "w+");
        fprintf(fp, "%s = %s\n", key, value);
        fclose(fp);
        printf("-----写入成功-----\n");
        return;
    }
    // 存在
    else
    {
        // 创建一个临时文件、
        temp = fopen("temp.txt", "w+");
        int i = 0;
        while (fgets(buf, ABUP_JSON_VALUE_SIZE, fp))
        {
            // 略过空格
            while (buf[i] == ' ')
                i++;

            // 判断buf[i]开始的字符串与key是否相同
            if (strncmp(&buf[i], key, strlen(key)) == 0)
            {
                // 相同将键值对写入临时文件
                fprintf(temp, "%s = %s\n", key, value);
                isExist = 1;
            }
            else
            {
                // 将字符串buf写入temp文件中，即其它的数据也要写入temp 文件中
                fputs(buf, temp);
            } // 循环读取所有文件
        }

        fclose(temp);

        // 不存在直接追加到文件尾部
        if (isExist == 0)
        {
            fprintf(fp, "%s = %s\n", key, value);
            fclose(fp);
            remove("temp.txt");
        }
        // 存在的话直接将temp中保存的更新数据变为数据库文件
        else
        {
            fclose(fp);
            remove(fileName);
            // 将临时文件直接命名为数据文件
            rename("temp.txt", fileName);
        }
    }
    return;
}

/**
 * 函数功能描述 ：查找指定文件key对于的value 存在返回其value，不存在返回NULL
 * @param fileName     文件名
 * @param key       需要查询的值对应的键
 * @return
 */
char *ReadValue(char *fileName, char *key);

/**
 * 函数功能描述 ：如果指定文件存在key就删除key及value
 * @param fileName    保存数据的文件名
 * @param key         需要删除的值对应的键
 */
void RemoveKeyValue(char *fileName, char *key);
