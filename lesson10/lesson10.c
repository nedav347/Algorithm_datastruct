/*
* Домашнее задание к уроку 10
* курса "Алгоритмы и структуры данных"
* автор Недокунев А.В.
* среда разработки VSCode /компилятор MinGW/
* codepage UTF-8
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define T char
#define true 1 == 1
#define false 1 != 1

typedef int boolean;

typedef struct Node {
	T dat;
	struct Node *next;
} Node;

typedef struct {
    Node *head;
    int size;
} Stack;

void init (Stack *stack) {
    stack->head = NULL;
    stack->size = 0;
}

boolean pushStack(Stack *stack, T value) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) {
        printf("%s \n", "Not enout memory");
        return false;
    }
    tmp->dat = value;
    tmp->next = stack->head;

    stack->head = tmp;
    stack->size++;
    return true;
}

T popStack(Stack *stack) {
    if (stack->size == 0) {
        printf("%s \n", "Stack is empty");
        return -1;
    }
    Node *tmp = stack->head;
    T data = stack->head->dat;
    stack->head = stack->head->next;
    free(tmp);
    stack->size--;
    return data;
}

T peekStack(Stack *stack) {
    if (stack->size == 0) {
        printf("%s \n", "Stack is empty");
        return -1;
    }
    T data = stack->head->dat;
    return data;
}

void printNode(Node *n) {
    if (n == NULL) {
        printf("[]");
        return;
    }
    printf("[%c]", n->dat);
}

void printStack(Stack *stack) {
    Node *current = stack->head;
    if (current == NULL) {
        printNode(current);
    } else {
        do {
            printNode(current);
            current = current->next;
        } while (current != NULL);
    }
    printf(" Size: %d \n", stack->size);
}

T invertchar(char symbol) {
    if (symbol == ')') return '(';
    if (symbol == ']') return '[';
    if (symbol == '}') return '{';
}


/*Задание 1
Написать программу, которая определяет, является ли введенная скобочная последовательность правильной. 
Примеры правильных скобочных выражений: (), ([])(), {}(), ([{}]), 
неправильных — )(, ())({), (, ])}), ([(]) для скобок [,(,{. 
Например: (2+(2*2)) или [2/{5*(4+7)}]
()({[]()}[]) // (([[{}]]))() // ((([[[[()[]]]{}]{}])))
*/

boolean checkBalance() {
    char *s;
    Stack *stchar = (Stack*) malloc(sizeof(Stack));
    init(stchar);
    int numchar = 0;
    s = (char*)malloc(1000);
    printf("%s \n", "Введите строку, например ()({[]()}[]) или [2/{5*(4+7)}] :");
    fflush(stdout);
    scanf("%s", s);
    while (s[numchar] != '\0'){
        if (s[numchar] == '(' || s[numchar] == '[' || s[numchar] == '{') { //кладем в стек открывающие скобки
            pushStack(stchar, s[numchar]);
        }
        if (s[numchar] == ')' || s[numchar] == ']' || s[numchar] == '}') {
            if (peekStack(stchar) != -1 && peekStack(stchar) == invertchar(s[numchar])) { //если закрывающая скобка не пара к предыдущей открывающей - все, последовательность не правильная, а уж если ее вообще нет...
//                if (popStack(stchar) == -1) { //не знаю, как такое может быть, ведь только что проверили...
//                    return false;
//                }
                popStack(stchar); //удаляем из стека парную открывающую
            } else {
                free(stchar);
                free(s);
                return false;
            }
        }
        numchar++;
    }
    free(s);
    if (stchar->size == 0) { //если ВСЕ скобки правильно закрылись - стек должен быть пустой 
        free(stchar);
        return true;
    } else {
        free(stchar);
        return false;
    }
}


/*Задание 2
Создать функцию, копирующую односвязный список (без удаления первого списка).
*/

void fillList(Stack *list) {
    char *s;
    int numchar = 0;
    s = (char*)malloc(1000);
    printf("%s \n", "Введите строку :");
    fflush(stdout);
    scanf("%s", s);
    while (s[numchar] != '\0'){
        pushStack(list, s[numchar++]);
    }
}

void copyList(Stack *orig, Stack *copy) { //промучавшись день, так и не смог "развернуть" список
    Node *current = orig->head;           //так что копируется список в обратном порядке...
    do {
        pushStack(copy, current->dat);
        current = current->next;
    } while (current != NULL);
}

/*Задание 3
Реализуйте алгоритм, который определяет, отсортирован ли связный список.
*/

boolean checkSort(Stack *list) { 
    Node *current = list->head;
    int countUp = 0;
    int countDown = 0;
    do {
        if (current->dat < current->next->dat) {
            if (countDown > 0) return false;
            countUp++;
        } else if (current->dat > current->next->dat) {
            if (countUp > 0) return false;
            countDown++;
        }
        current = current->next;
    } while (current != NULL); //если элементы одинаковые - ничего не делаем, на упорядоченность не влияет
    return true;
}


int main(const int argc, const char **argv){
    int num = 2;
    while (true)
    {
        printf("%s \n", "Введите номер задачи:");
        printf("%s \n", "1. проверка скобочной последовательности");
        printf("%s \n", "2. Копирование односвязного списка");
        printf("%s \n", "3. Проверка упорядоченности списка");
        printf("%s \n", "Любой другой символ для выхода");
        fflush(stdout);
        scanf("%d", &num);
        if (num == 1) printf("Последовательность %sправильная \n", checkBalance() ? "" : "НЕ"); 
        if (num == 2) {
            Stack *secList = (Stack*) malloc(sizeof(Stack)); //стек из первого задания на основе односвязного списка, его и используем
            Stack *origList = (Stack*) malloc(sizeof(Stack));
            init(origList);
            init(secList);
            fillList(origList);
            copyList(origList, secList);
            printStack(origList);
            printStack(secList);
        }
        if (num == 3) {
            Stack *sortList = (Stack*) malloc(sizeof(Stack));
            init(sortList);
            fillList(sortList);
            printf("Список %s отсортирован", checkSort(sortList) ? "" : "НЕ");
        }
        break;
    }
    return 0;
}