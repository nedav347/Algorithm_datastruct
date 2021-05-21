/*
* Домашнее задание к уроку 4
* курса "Алгоритмы и структуры данных"
* автор Недокунев А.В.
* среда разработки Notepad++ /компилятор MinGW/
* codepage UTF-8
*/
#include <stdio.h>
#include <string.h>

#define sizeX 8
#define sizeY 8

/*Задание 1
Реализовать функцию перевода чисел из десятичной системы в двоичную, используя рекурсию.
*/
void dectobin(int n) {
	if (n >= 1) {
		dectobin (n/2);
		printf("%d", n%2);
	}
}


/*Задание 3
Реализовать функцию возведения числа [a] в степень [b]:
Рекурсивно.*/
int exponent(int a, int b) {
    if (b == 0) {
        return 1;
	}
    return exponent(a, b - 1) * a;
}

/*Задание 4
Реализовать функцию возведения числа [a] в степень [b]:
Рекурсивно, используя свойство чётности степени 
(то есть, если степень, в которую нужно возвести число, чётная, 
основание возводится в квадрат, а показатель делится на два, 
а если степень нечётная - результат умножается на основание, 
а показатель уменьшается на единицу)*/
int exponent_even(int a, int b) {
    int c;
	if (b == 0)
        return 1;
    c = exponent_even(a, b / 2);
    return ((b%2) ? a : 1) * c * c; //a^b = (a^(b/2))^2 * a^(b%2)
/*
если совсем по условию, то:
   if (b % 2 == 1)
        return exponent_even(a, b - 1) * a; //здесь глубина рекурсии в два раза больше... 
    else {
        c = exponent_even(a, b / 2);
        return c * c;
*/
}

/*Задание 5
Реализовать нахождение количества маршрутов шахматного короля с препятствиями 
(где единица - это наличие препятствия, а ноль - свободная для хода клетка)*/
int routes(int x, int y, int (*barrier)[sizeY]) {
    if (barrier[x][y] == 1){
		return 0;
	}
	if (x == 0 && y == 0){
        return 0;
	} else if (x == 0 ^ y == 0){
        return 1;
	} else {
        return routes(x, y - 1, barrier) + routes(x - 1, y, barrier);
	}
}

int main(){
	int number, a, b;
	printf("%s","Введите число: ");
	fflush(stdout);
	scanf("%d",&number);
	dectobin(number);
	printf("%s", "\n=======================================================\n");
	printf("%s","Введите значение основания: ");
	fflush(stdout);
	scanf("%d",&a);
	printf("%s","Введите значение степени: ");
	fflush(stdout);
	scanf("%d",&b);
	printf("exponent: %d\n", exponent(a, b));
	printf("exponent_even: %d\n", exponent_even(a, b));
	printf("%s", "=======================================================\n");

	int barrier[sizeX][sizeY] = {0};
	barrier[0][3] = 1;
	barrier[3][2] = 1;
	
    for (int y = 0; y < sizeY; ++y) {
        for (int x = 0; x < sizeX; ++x) {
            printf("%5d", routes(x, y, barrier));
        }
        printf("\n");
    }
	return 0;
}
