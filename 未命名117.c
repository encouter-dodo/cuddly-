#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 50

// 结构体用于存储单词及其出现次数
typedef struct WordCount {
    char word[MAX_WORD_LENGTH];
    int count;
} WordCount;

// 交换两个WordCount结构体的内容
void swap(WordCount *a, WordCount *b) {
    WordCount temp = *a;
    *a = *b;
    *b = temp;
}

// 对单词统计数组按照出现次数降序、字典序升序排序（冒泡排序实现简单示例，可替换更高效排序算法）
void sortWordCounts(WordCount word_counts[], int num_words) {
	int i,j;
    for (i= 0; i < num_words - 1; i++) {
        for (j = 0; j < num_words - i - 1; j++) {
            if ((word_counts[j].count < word_counts[j + 1].count) ||
                (word_counts[j].count == word_counts[j + 1].count && strcmp(word_counts[j].word, word_counts[j + 1].word) > 0)) {
                swap(&word_counts[j], &word_counts[j + 1]);
            }
        }
    }
}

int main() {
	int i,j;
    char text[10000];
    fgets(text, 10000, stdin);
    // 去除换行符（如果存在）
    if (text[strlen(text) - 1] == '\n') {
        text[strlen(text) - 1] = '\0';
    }
    char *words[MAX_WORDS];
    int num_words = 0;
    char *token = strtok(text, " ");
    while (token!= NULL && num_words < MAX_WORDS) {
        // 转换为小写
        for (size_t i = 0; i < strlen(token); i++) {
            token[i] = tolower(token[i]);
        }
        words[num_words] = strdup(token);
        num_words++;
        token = strtok(NULL, " ");
    }
    WordCount word_counts[MAX_WORDS];
    int unique_word_index = 0;
    for (i = 0; i < num_words; i++) {
        int found = 0;
        for (j = 0; j < unique_word_index; j++) {
            if (strcmp(words[i], word_counts[j].word) == 0) {
                word_counts[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(word_counts[unique_word_index].word, words[i]);
            word_counts[unique_word_index].count = 1;
            unique_word_index++;
        }
    }
    sortWordCounts(word_counts, unique_word_index);
    int num_to_print = unique_word_index < 10? unique_word_index : 10;
    for (i = 0; i < num_to_print; i++) {
        printf("%s:%d\n", word_counts[i].word, word_counts[i].count);
    }
    return 0;
}

