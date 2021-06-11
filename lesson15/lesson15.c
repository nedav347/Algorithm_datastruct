/*
* Домашнее задание к уроку 15
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
Реализовать простейшую хеш-функцию. На вход функции подается строка, на выходе сумма кодов символов.
*/
int simpleHash(){
    char *s;
    int numchar = 0, result = 0;
    s = (char*)malloc(SIZE);
    printf("%s \n", "Введите строку :");
    fflush(stdout);
    gets(s);
    while (s[numchar] != '\0') {
        result += (int)s[numchar++];
    }
    return result;
}

/*
Задание 2
Имеются монеты номиналом 50, 10, 5, 2, 1 коп. 
Напишите функцию которая минимальным количеством монет наберет сумму 98 коп. 
Для решения задачи используйте “жадный” алгоритм.
*/
int sumCoins(int sum, int *coins) {
    int result = 0;
    printf("монеты :");
    for (int i = 0; i < COUNT; ++i) {
        while (sum >= coins[i]){
            printf(" %d,", coins[i]);
            sum -=coins[i];
            result++;
        }
    }
    return result;
}


////////////////////////////////////////////////////////////////////////////////////////
int main(const int argc, const char **argv){
    int num = 1;
    int coins[COUNT] = {50, 10, 5, 2, 1};
    const int sum = 98;
    while (true)
    {
        printf("%s \n", "Введите номер задачи:");
        printf("%s \n", "1. хэш-функция");
        printf("%s \n", "2. монеты");
        fflush(stdout);
        scanf("%d", &num);
        fflush(stdin);
        if (num == 1) printf("хэш = %d\n", simpleHash()); 
        if (num == 2) printf("\nдля суммы %d копеек требуется %d монет", sum, sumCoins(sum, coins));
        break;
    }
    return 0;
}