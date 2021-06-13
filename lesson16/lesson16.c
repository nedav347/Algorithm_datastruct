/*
* Домашнее задание к уроку 16
* курса "Алгоритмы и структуры данных"
* автор Недокунев А.В.
* среда разработки VSCode /компилятор MinGW/
* codepage UTF-8
*/
#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000
#define COUNT 5
#define true 1 == 1
#define false 1 != 1

/*
Задание 1
Реализовать шифрование и расшифровку цезаря с передаваемым в функцию сообщением и ключом
*/
void caesarReplace(char *str, int num, int key, int end, int len) {
    if ((int)str[num] < (end - key)) {
        str[num] = str[num] + key;
    } else {
        str[num] = str[num] - len + key;
    }
}

void caesarReplaceDecode(char *str, int num, int key, int start, int len) {
        if ((int)str[num] > (start + key)) {
            str[num] -= key;
        } else {
            str[num] = str[num] + len - key;
        }
}

void caesarEncode(char *str, int key) {
    int i = 0;
    while (str[i] != '\0'){
        //если это цифра
        if ((int)str[i] > 47 && (int)str[i] < 58) {
            caesarReplace(str, i, key, 58, 10);
        }
        //если заглавная буква
        if ((int)str[i] > 64 && (int)str[i] < 91) {
            caesarReplace(str, i, key, 91, 26);
        }
        //если строчная буква
        if ((int)str[i] > 96 && (int)str[i] < 123) {
            caesarReplace(str, i, key, 123, 26);
        }
        //что делать со знаками препинания и прочими служебными символами пока не ясно
        i++;
    }
}

void caesarDecode(char *str, int key) {
    int i = 0;
    while (str[i] != '\0'){
        //если это цифра
        if ((int)str[i] > 47 && (int)str[i] < 58) {
            caesarReplaceDecode(str, i, key, 47, 10);
        }
        //если заглавная буква
        if ((int)str[i] > 64 && (int)str[i] < 91) {
            caesarReplaceDecode(str, i, key, 64, 26);
        }
        //если строчная буква
        if ((int)str[i] > 96 && (int)str[i] < 123) {
            caesarReplaceDecode(str, i, key, 96, 26);
        }
        //что делать со знаками препинания и прочими служебными символами пока не ясно
        i++;
    }
}

/*
Задание 2
Реализовать шифрование и расшифровку перестановками с передаваемым в функцию сообщением и количеством столбцов
*/
char* permutationEncode(char *str, int col){
    char *s = malloc(sizeof(char) * 256);
    int num = 0, snum = 0;
    while(str[num] != '\0'){
        for (int i = 0; i < col; ++i) {
            if (str[num] == '\0') break;
            s[snum + (i * col)] = str[num];
            num++;
        }
        snum++;
    }
    s[num] = '\0';
    return s;
}

char* permutationDecode(char *str, int col){
    char *s = malloc(sizeof(char) * 256);
    int num = 0, snum = 0;
    while(str[num] != '\0'){
        for (int i = 0; i < col; ++i) {
            if (str[num] == '\0') break;
            s[snum + (i * col)] = str[num];
            num++;
        }
        snum++;
    }
    s[snum] = '\0';
    return s;
}


////////////////////////////////////////////////////////////////////////////////////////
int main(const int argc, const char **argv){
    char str[256] = "123456789";
    printf("%s\n", "Введите строку для кодирования: ");
    fflush(stdout);
    gets(str);
    caesarEncode(str, 3);
    printf("Шифр Цезаря: %s\n", str);
    printf("Шифр перестановками: %s\n", permutationEncode(str, 3));
    printf("%s\n", "Введите строку для декодирования: ");
    fflush(stdout);
    gets(str);
    caesarDecode(str, 3);
    printf("Шифр Цезаря: %s\n", str);
    printf("Шифр перестановками: %s\n", permutationEncode(str, 3));
    return 0;
}