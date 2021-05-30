/*
* Домашнее задание к уроку 9
* курса "Алгоритмы и структуры данных"
* автор Недокунев А.В.
* среда разработки VSCode /компилятор MinGW/
* codepage UTF-8
*/
#include <stdio.h>
#include <stdlib.h>

#define SIZE 32
#define T char
#define true 1 == 1
#define false 1 != 1

typedef struct
{
	int dat;
	int pri;
} Node;

Node* arr[SIZE];
int head, tail, items;

typedef int boolean;
int cursor = -1;
T Stack[SIZE];

/*Задание 1
Описать очередь с приоритетным исключением
*/
void initQueue() {
    for (int i = 0; i < SIZE; ++i) {
        arr[i] = NULL;
    }
    head = tail = items = 0;
}

void ins(int pr, int dat) {
    Node *node = (Node*) malloc(sizeof(Node));
    node->dat = dat;
    node->pri = pr;

    if (items == SIZE) {
        printf("%s \n", "Queue is full");
        return;
    } else {
        int idx = tail++ % SIZE;
	    arr[idx] = node;
		items++;
	}
}

Node* rem(int pr) {
    int i = 0;
    int idx = 0;
    Node *tmp;
    if (items == 0) { //если очередь пустая
        return NULL;
    } else {
        for (i = head; i < tail; i++) { //просматриваем от "головы" до хвоста
            idx = i % SIZE;
            if (arr[idx]->pri == pr) break; //приоритет найден
        }
        if (i == tail) return NULL; //нет такого приоритета
        tmp = arr[idx]; //сохраним найденное для выдачи
        arr[idx] = NULL; //обнулим для случая, если найденный приоритет был первым в очереди
        while (i > head) { //сдвигаем слева на освободившееся место
            idx = i % SIZE;
            arr[idx] = arr[idx - 1];
            i--;
        }
        arr[head] = NULL; //очищаем элемент, на который пока что указывает "голова"
        items--; //элементов же стало меньше
        head++; //смещаем "голову"
        return tmp;
    }
}

void printQueue(int ids) {
    printf("%d[ ", ids);
    for (int i = 0; i < SIZE; ++i) {
        if (arr[i] == NULL)
            printf("[*, *] ");
        else
            printf("[%d, %d] ", arr[i]->pri, arr[i]->dat);
    }
    printf(" ]\n");
}

/*Задание 2
Реализовать перевод из десятичной в двоичную систему счисления с использованием стека.
Стек у нас будет на основе массива, более сложные мы "не проходили"
*/
boolean pushStack(T data) {
    if (cursor < SIZE) {
        Stack[++cursor] = data;
        return true;
    } else {
        printf("%s \n", "Stack overflow");
        return false;
    }
}

T popStack() {
    if (cursor != -1) {
        return Stack[cursor--];
    } else {
        printf("%s \n", "Stack is empty");
        return -1;
    }
}

int Dec2Bin(int n) {
	int pos = 0;
	
	while (n >= 1){
		if (n % 2){//разложим число на степени двойки (получится двоичное представление, но в обратном порядке) и запихнем в стек
			if (!pushStack('1')) return -1;
		} else {
			if (!pushStack('0')) return -1;
		}
		n /= 2;
		pos++;//количество символов в двоичном представлении
	}

	for (int k = pos; k < SIZE; k++){
		if (!pushStack('0')) return -1; //добавляем символы нуля до 32 символов (для красоты)
        pos++;
	}
    return pos;
}


int main(const int argc, const char **argv){
    Node* n;
    initQueue();
    ins(1, 11);
    ins(3, 22);
    ins(4, 33);
    ins(2, 44);
    ins(3, 55);
    ins(4, 66);
    ins(5, 77);
    ins(1, 88);
    ins(2, 99);
    ins(6, 100);
    printQueue(10);
    for (int i = 0; i < 7; ++i) {
        n = rem(i);
        printQueue(15);
        if (n != NULL)
        printf("pri=%d, dat=%d, head=%d, tail=%d, items=%d \n", n->pri, n->dat, head, tail, items);
    }
    printQueue(20);

    ins(1, 110);
    ins(3, 120);
    ins(6, 130);
    printQueue(30);

    for (int i = 0; i < 5; ++i) {
        n = rem(i);
        printQueue(35);
        if (n != NULL)
        printf("pri=%d, dat=%d, head=%d, tail=%d, items=%d \n", n->pri, n->dat, head, tail, items);
    }
    printQueue(40);

	unsigned int number;
	printf("%s \n", "Введите целое положиетльное число: ");
	fflush(stdout);
    scanf("%d",&number);
	number = Dec2Bin(number);
    if (number == -1) return 1;
	for (int i = 0; i < number; i++)//выведем результат с разделителями и предваряющими нулями
	{
		if (i % 4 == 0) printf(" ");
		printf("%c", popStack());
	}

	return 0;
}