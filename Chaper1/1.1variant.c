#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COLS 20
#define MAX_INPUT 1000

int read_column_numbers(int columns[], int max);
void rearrange(char *output, char const *input,
               int n_columns, int const columns[]);

int main(void)
{
    printf("程序已启动\n");
    int n_columns;
    int columns[MAX_COLS];
    char input[MAX_INPUT];
    char output[MAX_INPUT];

    n_columns = read_column_numbers(columns, MAX_COLS);

    // 使用安全的fgets代替gets
    while (fgets(input, sizeof(input), stdin) != NULL) {
        // 移除fgets读取的换行符
        input[strcspn(input, "\n")] = '\0';
        
        printf("Original input : %s\n", input);
        rearrange(output, input, n_columns, columns);
        printf("Rearranged line : %s\n", output);
    }
    return EXIT_SUCCESS;
}

int read_column_numbers(int columns[], int max)
{
    printf("请输入列号，以负数结束：\n");
    int num = 0;
    int ch;
    
    while (num < max && scanf("%d", &columns[num]) == 1
           && columns[num] >= 0) {
        num += 1;
    }

    // 修正拼写错误和退出码
    if (num % 2 != 0) {
        puts("Last column number is not paired.");
        exit(EXIT_FAILURE);  // 使用FAILURE表示错误退出
    }

    // 清除输入缓冲区
    while ((ch = getchar()) != EOF && ch != '\n')
        ;
      
    return num;
}

void rearrange(char *output, char const *input,
               int n_columns, int const columns[])
               
{   printf("正在处理字符串：%s\n", input);
    int col;
    int output_col = 0;
    int len = strlen(input);
    
    // 确保输出缓冲区初始为空
    output[0] = '\0';

    for (col = 0; col < n_columns; col += 2) {
        int start = columns[col];
        int end = columns[col + 1];
        int nchars;

        // 检查列号有效性
        if (start < 0 || end < 0) {
            fprintf(stderr, "Invalid column number: %d-%d\n", start, end);
            continue;
        }
        
        if (end < start) {
            // 交换顺序确保 start <= end
            int temp = start;
            start = end;
            end = temp;
        }

        // 调整列号范围
        if (start >= len) {
            continue;  // 起始位置超过字符串长度
        }
        
        if (end >= len) {
            end = len - 1;  // 调整结束位置
        }

        nchars = end - start + 1;

        // 检查输出缓冲区空间
        if (output_col >= MAX_INPUT - 1) break;
        
        if (output_col + nchars > MAX_INPUT - 1) {
            nchars = MAX_INPUT - output_col - 1;
        }

        // 安全复制
        strncpy(output + output_col, input + start, nchars);
        output_col += nchars;
        output[output_col] = '\0';  // 确保每次复制后字符串有效
    }

    // 确保字符串终止
    output[output_col] = '\0';
}