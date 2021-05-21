/*
* Домашнее задание к уроку 6
* курса "Алгоритмы и структуры данных"
* автор Недокунев А.В.
* среда разработки Notepad++ /компилятор MinGW/
* codepage UTF-8
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define SIZE_X 3
#define SIZE_Y 3

/*Задание 1
Реализовать пузырьковую сортировку двумерного массива например, 
массив 1,9,2 5,7,6 4,3,8 должен на выходе стать 1,2,3 4,5,6 7,8,9
*/
void fillArr(int (*arr)[SIZE_Y]){
	for (int i = 0; i < SIZE_X; ++i){
		for (int j = 0; j < SIZE_Y; ++j) {
			arr[i][j] = rand() % 100;
		}
	}
}

void printArr(int (*arr)[SIZE_Y]) {
	for (int i = 0; i < SIZE_X; ++i){
		for (int j = 0; j < SIZE_Y; ++j) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
}

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void bubble(int (*arr)[SIZE_Y]) {
	int tmp;
	for (int i = 0; i < SIZE_X; ++i) {
		for (int j = 0; j < SIZE_Y; ++j) {
			for (int k = 0; k < SIZE_X; ++k) {
				for (int m = 0; m < SIZE_Y; ++m) {
					if (arr[i][j] < arr[k][m]) {
						swap(&arr[i][j], &arr[k][m]);
					}
				}
			}
		}
	}
}


/*Задание 3
Реализовать алгоритм Трабба-Прадо-Кнута в коде на языке С
Алгоритм:
ask for 11 numbers to be read into a sequence S 
reverse sequence S 
for each item in sequence S 
	call a function to do an operation 
	if result overflows 
		alert user 
	else 
		print result
Функция:
f(x) = sqrt(|x|) + 5 * x ** 3
*/
double funcTPK(double number) {
	return sqrt(fabs(number)) + 5 * pow(number, 3);
}

void algTPK() {
	double S[11] = {0}, result;
	for (int i = 0; i < 11; i++) {
		printf("%s%d\n", "Введите элемент ", i);
		fflush(stdout);
		scanf("%lf", &S[i]);
	}
	for (int i = 10; i >= 0; i--){
		result = funcTPK(S[i]);
		if (result > 400.0) {
			printf("%d %s\n", i, "переполнение");
		 } else {
			printf("%d %f\n", i, result);
		 }
	}
}

int main(){
	int arr[SIZE_X][SIZE_Y]; // = {{1,9,2},{5,7,6},{4,3,8}};
	fillArr(arr);
	bubble(arr);
	printArr(arr);
	algTPK();
	return 0;
}
