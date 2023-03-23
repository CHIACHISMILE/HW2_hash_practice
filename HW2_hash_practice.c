// Fundamental data structure & algorithm
// HW2_03_23_2023
// C language, Encoding = UTF-8
// written by 醫工三 b812109032 許家齊

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // 包含 isalpha 函數

#define HASH_TABLE_SIZE 100  // 定義hash表的大小

// 定義一個單字結構，用於存儲單字及其出現次數
typedef struct WordEntry {
    char* word;  // 單字字符串
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
        // 將單字轉換成小寫
        for (int i = 0; i < strlen(word); i++) {
            word[i] = tolower(word[i]);
        }
        // 只保留單字中的字母
        char* p = word;
        int i = 0;
        while (*p != '\0') {
            if (isalpha(*p)) {  // 如果是字母，則轉換成小寫
                word[i] = tolower(*p);
                i++;
            }
            p++;
        }
        word[i] = '\0';
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

// hash函數，將字符串轉換成一個數字作為hash表的下標
unsigned int hash_function(char* key) {
    unsigned int hash_value = 0;
    while (*key != '\0') {
        hash_value = (hash_value << 5) + *key;  // 將 hash_value 左移 5 位，然後加上 key 的 ASCII 码值
        key++;
    }
    return hash_value % HASH_TABLE_SIZE;  // 取模運算得到hash表的下標
}

// 將單字插入到hash表中
void insert(char* key, WordEntry** hash_table) {
    unsigned int hash_index = hash_function(key);  // 得到hash表的下標

    // 在hash表的下標處，查找是否已經存在該單字
    WordEntry* entry = hash_table[hash_index];
    while (entry != NULL) {
        if (strcmp(entry->word, key) == 0) {  // 如果已經存在該單字，則出現次數加 1，然後返回
            entry->count++;
            return;
        }
        entry = entry->next;  // 否則繼續查找下一個單字結構
    }

    // 如果沒有找到該單字，則創建一個新的單字結構，然後插入到hash表的下標處
    WordEntry* new_entry = (WordEntry*)malloc(sizeof(WordEntry));
    new_entry->word = (char*)malloc(strlen(key) + 1);  // 為單字字符串分配內存空間
    strcpy(new_entry->word, key);  // 複製單字字符串到單字結構中
    new_entry->count = 1;  // 初始出現次數為 1
    new_entry->next = hash_table[hash_index];  // 將新的單字結構插入到hash表中
    hash_table[hash_index] = new_entry;
}

// 顯示hash表中的所有單字及其出現次數
void display(WordEntry** hash_table) {
    printf("Word\t\tCount\n");
    printf("--------------------\n");
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {  // 遍歷hash表的每個下標
        WordEntry* entry = hash_table[i];
        while (entry != NULL) {  // 遍歷該下標處的所有單字結構
            printf("%-20s%d\n", entry->word, entry->count);  // 輸出單字及其出現次數
            entry = entry->next;  // 繼續查找下一個單字結構
        }
    }
}
