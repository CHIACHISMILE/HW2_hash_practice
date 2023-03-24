# HW2_hash_practice
醫工三 b812109032 許家齊 資料結構與演算法 HW2_hash_practice 雜湊練習

# Homework Instructions
資料「hw2_data.txt」是一份近千行的字串資料。每一行只有一個英文字，且文字重複率很高。請寫一隻程式讀進這個檔案，逐行讀進這些英文字，並統計出以下兩點：
 
1. 總共有多少個不重複的英文字
2. 每一個英文字出現次數為和
 
請將作業上傳到github。repository名稱請取為HW2_hash_practice。請以任何你喜歡的方式（WORD/PDF報告、Github Readme，或Jupyter notebook）告訴我程式執行結果。評分點為：
 
1. 是否有正確答出答案
2. 是否能夠清楚看出答案
3. 是否能夠清楚看到程式碼
追加4. 請使用hash or dictionary。我知道有其他更方便的功能，但麻煩請使用hash。
 
加分點：
1. 是否有加註解
2. 程式是否有結構化
3. 變數與function名稱是否清楚可辨識
4. 是否使用github的commit與push上傳程式碼
 
順帶說明一下這個檔案的格式是DOS/Windows，也就是CR+LF做每一行的結尾。雖然理論上不會影響到大部分同學的程式執行，但在Mac/Linux上寫C/C++的同學就需要特別注意一下了。

# Data path
The txt data "hw2_data.txt" must put in the same folder with your code.

# Code
[c](HW2_hash_practice.c)
```c
// Fundamental data structure & algorithm
// HW2_03_23_2023
// C language, Encoding = UTF-8
// written by 醫工三 b812109032 許家齊

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_TABLE_SIZE 100  // 定義hash表的大小

// 定義一個單字結構，用於存儲單字及其出現次數
typedef struct WordEntry {
    char* word;  // 單字字串
    int count;   // 出現次數
    struct WordEntry* next;  // 指向下一個單字結構的指針，用於解決hash碰撞
} WordEntry;

// 函數原型
unsigned int hash_function(char* key);
void insert(char* key, WordEntry** hash_table);
void display(WordEntry** hash_table);

// 主函數
int main() {
    FILE* file;
    char word[100];
    int unique_word_count = 0;
    WordEntry* hash_table[HASH_TABLE_SIZE] = { NULL };  // 初始化hash表為空指針

    file = fopen("hw2_data.txt", "r");  // 打開文本文件
    if (file == NULL) {  // 如果打開文件失敗，則輸出錯誤信息並退出程式
        printf("Error: Failed to open file.\n");
        return 1;
    }

    while (fscanf(file, "%s", word) != EOF) {  // 逐行讀取文件中的單字
        // printf("word = %s \n", word); // test
        if (strlen(word) > 0) {  // 如果單字不為空，則插入到hash表中
            insert(word, hash_table);
        }
    }

    fclose(file);  // 關閉文件

    display(hash_table);  // 顯示hash表中的所有單字及其出現次數

    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        WordEntry* entry = hash_table[i];
        while (entry != NULL) {
            unique_word_count++;
            entry = entry->next;
        }
    }

    printf("Unique word count: %d\n", unique_word_count); // 顯示hash表中的不同單字有幾個

    return 0;
}

// hash函數，將字串轉換成一個數字作為hash表的index值
unsigned int hash_function(char* key) {
    unsigned int hash_value = 0;
    while (*key != '\0') {
        hash_value = hash_value + *key; // 將 hash_value 加上 key 的 ASCII 編碼值
        // printf("hashvalue = %d and ",hash_value); // test
        // printf("*key = %d and ", *key); // test
        // printf("key = %s \n", key); // test
        // printf("hash_value / HASH_TABLE_SIZE remainder = %d\n", hash_value % HASH_TABLE_SIZE); // test
        key++;
    }
    return hash_value % HASH_TABLE_SIZE;  // 取模運算得到hash表的index
}

// 將單字插入到hash表中
void insert(char* key, WordEntry** hash_table) {
    unsigned int hash_index = hash_function(key);  // 得到hash表的index
    // printf("word =  %s , hashindex = %d \n", key, hash_index); // test

    // 在hash表的index處，查找是否已經存在該單字
    WordEntry* entry = hash_table[hash_index];
    while (entry != NULL) {
        if (strcmp(entry->word, key) == 0) {  // 如果已經存在該單字，則出現次數加 1，然後返回
            entry->count++;
            return;
        }
        entry = entry->next;  // 否則繼續查找下一個單字
    }

    // 如果沒有找到該單字，則創建一個新的單字結構，並插入到hash表中
    WordEntry* new_entry = (WordEntry*)malloc(sizeof(WordEntry));
    new_entry->word = (char*)malloc(strlen(key) + 1);  // 為單字字串動態分配內存空間
    strcpy(new_entry->word, key);  // 複製單字字串到單字結構中
    new_entry->count = 1;  // 初始出現次數為 1
    new_entry->next = hash_table[hash_index];  // 將新的單字結構插入到hash表中
    hash_table[hash_index] = new_entry;
}

// 顯示hash表中的所有單字及其出現次數
void display(WordEntry** hash_table) {
    printf("Word\t\tCount\n");
    printf("--------------------\n");
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {  // for loop 查看所有hash表中的index
        WordEntry* entry = hash_table[i];
        while (entry != NULL) {  
            printf("%-20s%d\n", entry->word, entry->count);  // 輸出單字及其出現次數
            entry = entry->next;  // 繼續查找下一個單字結構
        }
    }
}
```

# Result
```
Word            Count
--------------------
Steak               46
Fries               76
Burger              196
Pizza               83
Potato              3
Rib                 33
Coke                145
Cheese              234
Taco                57
Pho                 19
Unique word count: 10
```

# Questions
在將字串轉為hash編碼時，我是將文字的第一個字母轉成ASCII加上第二個字母轉成ASCII...將單字加總完成後再除以hash表的總長度取餘數當作其儲存在hash表中的index值。
神奇的是我有試過若只取第一個字母而已竟然也可以成功分配？！想請問老師可以為我解惑嗎？
