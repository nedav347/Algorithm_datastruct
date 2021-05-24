/*
* Домашнее задание к уроку 7
* курса "Алгоритмы и структуры данных"
* автор Недокунев А.В.
* среда разработки VSCode /компилятор MinGW/
* codepage UTF-8
*/
#include <stdio.h>
#include <stdlib.h>

#define SIZE_X 30

void fillArr(int* arr){
	for (int i = 0; i < SIZE_X; ++i){
		arr[i] = rand() % 100;
	}
}

void printArr(int* arr) {
	for (int i = 0; i < SIZE_X; ++i){
			printf("%d ", arr[i]);
	}
	printf("\n");
}

/*Задание 1
Описать в коде улучшенный алгоритм быстрой сортировки
*/

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void sortins(int* arr, int start_index, int end_index) { // сортировка вставкой
	int temp, pos; //temp - для временного хранения перемещаемого элемента; pos - указатель на текущую позицию вставки перемещаемого элемента
	for (int i = start_index + 1; i < end_index; ++i) { // первый элемент отсортирован по умолчанию
		temp = arr[i]; //берем первое значение из неотсортированной части
		pos = i - 1;   //устанавливаем pos на последний элемент отсортированной части
		while (pos >= 0 && arr[pos] > temp) { //ищем в отсортированной части куда вставить взятый в temp элемент
			arr[pos + 1] = arr[pos]; //сдвигаем по одному элементу вправо
			pos--;
		}
		arr[pos + 1] = temp; // вставляем взятый в temp элемент в образовавшуюся "дырку"
	}
}

void qsortenhanced(int* arr, int start_index, int end_index) { //сортируем массив от start_index до end_index
	int left_index = start_index, right_index = end_index, pivot; //left_index и right_index - маркеры для обхода массива слева-направо и с право-налево, pivot - значение опорного элемента осртируемого массива
	if ((end_index - start_index) > 10) { //"улучшение" - если сортируемый массив 10 или менее элементов, то используем сортировку вставкой, иначе быструю сортировку
		if (((arr[start_index] - arr[(start_index + end_index)/2])*(arr[end_index] - arr[start_index])) >= 0) {
			swap(&arr[start_index], &arr[(start_index + end_index)/2]); //если медиана от начального, среднего и конечного элемента массива начальное значение - меняем начальный и средний элемент местами
		} else if ((arr[(start_index + end_index)/2] - arr[end_index])*(arr[end_index] - arr[start_index]) >= 0) {
			swap(&arr[end_index], &arr[(start_index + end_index)/2]); //если медиана от начального, среднего и конечного элемента массива конечное значение - меняем конечный и средний элемент местами
		}
		pivot = arr[(start_index + end_index)/2]; //знечение того самого опорного (он же средний) элемента 
		do {
			while (arr[left_index] < pivot) left_index++; //ищем слева-направо элемент больше опорного
			while (arr[right_index] > pivot) right_index--; //ищем справа-налево элемент меньше опорного 
			if (left_index <= right_index){
				swap(&arr[left_index], &arr[right_index]); //если больший слева от правого - меняем их местами
				left_index++;
				right_index--;
			}
		} while (left_index <= right_index); //повторяем поиск пока маркеры не пересекутся
		if (left_index < end_index) qsortenhanced(arr, start_index, left_index); //рекурсивно вызываем сортировку для "левой" части массива
		if (right_index > start_index) qsortenhanced(arr, right_index, end_index);  //рекурсивно вызываем сортировку для "правой" части массива
	} else {
		sortins(arr, start_index, end_index); //для подмассива из 10 и менее элементов вызываем сортировку вставкой
	}
}

/*Задание 2
Сортировать в массиве целых положительных чисел только чётные числа, 
нечётные оставив на своих местах при помощи алгоритма блочной сортировки, 
то есть массив вида [0 2 8 3 4 6 5 9 8 2 7 3] превратить в [0 2 2 3 4 4 5 9 8 8 7 3]
*/

void bucketsort(int* arr, int len) { //блочная сортировка
	const int max = len; //заводим константу для максимального значения элементов в корзинах
	const int b = 10; //заводим константу для колтичества корзин

	int buckets[b][max + 1]; //объявляем 10 корзин с количеством элементов, на 1 (для счетчика этих элементов) больше дляины исходного массива
	for (int i = 0; i < b; ++i) { //обнуляем счетчики элементов в корзинах
		buckets[i][max] = 0;
	}
	for (int dig = 1; dig < 1000000000; dig *= 10) { //проходим по разрядам числа
		for (int i = 0; i < max; ++i) { //проходим по всем элементам массива
			if (arr[i] % 2 == 0) { //если элемент четное число - кладем в соотвествующую корзину для сортировки
				int d = (arr[i] / dig) % b; //вычисляем номер корзины
				buckets[d][buckets[d][max]++] = arr[i];
			}
		}
		int idx = 0; //вспомогательный индех
		for (int i = 0; i < b; ++i) { //проходим по всем корзинам
			for (int j = 0; j < buckets[i][max]; ++j) { //проходим по всем элементам в корзине
				while (arr[idx] % 2 > 0) idx++; //ищем в массиве индексы четных элементов, нечетные не трогаем
				arr[idx++] = buckets[i][j]; //записываем в массив отсортированные нечетные элементы по индексам нечетных 
			}
			buckets[i][max] = 0; //обнуляем счетчики элементов в корзинах
		}
	}
}


int main(){
	int arr[SIZE_X];
	fillArr(arr);
	printArr(arr);
//	qsortenhanced(arr, 0, SIZE_X-1);
	bucketsort(arr, SIZE_X);
	printArr(arr);
	return 0;
}
