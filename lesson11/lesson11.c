/*
* Домашнее задание к уроку 11
* курса "Алгоритмы и структуры данных"
* автор Недокунев А.В.
* среда разработки VSCode /компилятор MinGW/
* codepage UTF-8
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 10000
#define true 1 == 1
#define false 1 != 1
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
typedef int boolean;

typedef struct Node {
	int key;
	struct Node *left;
	struct Node *right;
} BinTree;

/*
Задание 1
Написать функцию проверяющую является ли переданное в неё бинарное дерево сбалансированным
*/
int heightTree(BinTree* tree) { //рекурсивное определение высоты дерева
    if (tree == NULL) return 0;
    return 1 + MAX(heightTree(tree->left), heightTree(tree->right));
}

/*
признак сбалансированности: левый и правый дочерние элементы должны быть сбалансированы по высоте, а высота левого дерева должна находится в пределах 1 от высоты правого дерева
*/
boolean checkBalance(BinTree* tree) {
    if (tree == NULL) return true; //пустое дерево является сбалансированным
    if (checkBalance(tree->left) && checkBalance(tree->right) && abs(heightTree(tree->left) - heightTree(tree->right)) <= 1) return true;
    return false;
}

/*
Задание 2
создаст [50] деревьев по [10000] узлов и заполнит узлы случайными целочисленными значениями;
Поскольку в задании не указано, какой вид бинарного дерева нужен, будем использовать бинарное дерево поиска,
Во-первых, нам как-то надо решить, куда вставлять новый узел,
во-вторых это удобно для других заданий...
*/
BinTree* buildTree(BinTree* tree, int count) {
//  int value[31] = {16, 8, 24, 4, 12, 20, 28, 2, 6, 10, 14, 18, 22, 26, 30, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31};
//  int idx = 0;
    for (count; count > 0; count--) { //создаем узлы в цикле 
        BinTree* new = (BinTree*) malloc(sizeof(BinTree));
        if (new == NULL) {
            printf("%s\n", "Not enoutgh memory");
            return NULL;
        }
        new->key = 1 + rand() % SIZE; //заносим случайное число из диапазона от 1 до значения, равного количеству узлов
//      new->key = value[idx++];
//      printf("key = %d ", new->key);
        new->left = NULL; //и инициализируем остальные
        new->right = NULL;
        BinTree* curr = tree; //создаем и инициализируем два указателя: на текущий узел
        BinTree* parent = tree; //и на родителя
        if (tree == NULL) {
            tree = new; //если это первый узел, то он корень дерева
        } else {
            while(curr->key != new->key) {
                parent = curr;
                if (curr->key > new->key) { //раз это дерево поиска, то меньший ключ слева, больший справа
                    curr = curr->left;
                    if (curr == NULL) { //место для вставки найдено
                        parent->left = new;
                        break;
                    }
                } else {
                    curr = curr->right;
                    if (curr == NULL) {
                        parent->right = new;
                        break;
                    }
                }
            }
        }
//    free(curr);
//    free(parent);
    }
    return tree;
}

/*
Задание 3
рассчитает, какой процент из созданных деревьев является сбалансированными.
*/
void percentBal(int countBalance, int countTree) {
    printf("Процент сбалансированных деревьев %2f (всего %d сбалансированных из %d)\n", ((double)countBalance / (double)countTree) * 100, countBalance, countTree);
}

/*
Задание 4
Написать рекурсивную функцию бинарного поиска в дереве хранящемся в узлах, а не в массиве.
*/
boolean preOrderSeek(BinTree *root, int value) { //прямой (корень - левый - правый) обход, хорош для копирования
    if (root) {
        return root->key == value || preOrderSeek(root->left, value) || preOrderSeek(root->right, value);
    }
}

boolean inOrderSeek(BinTree *root, int value) { //центрированный (левый - корень - правый) обход, хорош для нашего дерева, обходит по возврастанию значений в узлах
    if (root) {
        return inOrderSeek(root->left, value) || root->key == value || inOrderSeek(root->right, value);
    }
}

boolean postOrderSeek(BinTree *root, int value) { //обратный (левый - правый - корень) обход, хорош для удаления
    if (root) {
        return postOrderSeek(root->left, value)|| postOrderSeek(root->right, value) || root->key == value;
    }
}

boolean binSearch(BinTree *root, int value, int type) {
    clock_t start, end; //будем измерять время выполнения
    boolean result = false;
    if (root == NULL)
        return false; //если дерево не существует
    if (root->key == value)
        return true; //если искомое число в корне

    switch (type) {
    case 0: //обход в прямом порядке
        start = clock(); //засекаем время
        result = preOrderSeek(root, value);
        end = clock(); //фиксируем время выполнения
        printf("Time executed preOrderSeek %.4f second(s)\n", (double) (end - start) / CLOCKS_PER_SEC);
        break;
    
    case 1: //обход в "центрированном" порядке
        start = clock();
        result = inOrderSeek(root, value);
        end = clock();
//        printf("Time executed inOrderSeek %f second(s)\n", (double) (end - start) / CLOCKS_PER_SEC);
        break;
    
    case 2: //обход в обратном порядке
        start = clock();
        result = postOrderSeek(root, value);
        end = clock();
        printf("Time executed postOrderSeek %.4f second(s)\n", (double) (end - start) / CLOCKS_PER_SEC);
        break;
    
    default:
        break;
    } 
    return result;
}

/* Вспомогательные и служебные функции */
void printBinTree(BinTree *root) {
    if (root) {
        printf("%d", root->key);
        if (root->left || root->right) {
            printf("(");
            if (root->left)
                printBinTree(root->left);
            else
                printf("NULL");
            printf(",");
            if (root->right)
                printBinTree(root->right);
            else
                printf("NULL");
            printf(")");
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////
int main(const int argc, const char **argv){
    BinTree *tr[50] = {NULL};
    int sum = 0;
    const int countTree = 50;
    for (int i = 0; i < countTree; ++i) {
        tr[i] = buildTree(tr[i], SIZE);
    }
/**
    for (int i = 0; i < countTree; ++i) {
        printf("Дерево %d\n", i);
        printBinTree(tr[i]);
        puts("\n");
    }
/**/
    int value = 347;
    printf("%s\n", "Введите число для поиска");
    fflush(stdout);
    scanf("%d", &value);
    for (int i = 0; i < countTree; ++i) {
//        printf("Искомое число %s найдено в массиве %d\n", binSearch(tr[i], value, 0) ? "" : "НЕ", i);
        printf("Искомое число %s найдено в массиве %d\n", binSearch(tr[i], value, 1) ? "" : "НЕ", i);
//        printf("Искомое число %s найдено в массиве %d\n", binSearch(tr[i], value, 2) ? "" : "НЕ", i);
    }
    
    for (int i = 0; i < countTree; ++i) {
//        printf("Дерево %d\n", i);
//        printf("Height Left %d, Height Right %d\n", heightTree(tr[i]->left), heightTree(tr[i]->right));
//        printf("Дерево %d %s сбалансировано\n", i, checkBalance(tr[i]) ? "" : "НЕ");
        if (checkBalance(tr[i])) sum++;
    }

    percentBal(sum, countTree);

    return 0;
}