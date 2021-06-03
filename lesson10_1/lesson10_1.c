/*
* Работа над ошибками.
* Домашнее задание к уроку 10
* курса "Алгоритмы и структуры данных"
* автор Недокунев А.В.
* среда разработки VSCode /компилятор MinGW/
* codepage UTF-8
* Задание 2
* Создать функцию, копирующую односвязный список (без удаления первого списка).
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
} List;

typedef struct {
    Node *head;
    int size;
    Node *tail;
} ListNew;

void init (List *list) {
    list->head = NULL;
    list->size = 0;
}

void initNew (ListNew *list) {
    list->head = NULL;
    list->size = 0;
    list->tail = NULL;
}


boolean pushList(List *List, T value) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) {
        printf("%s \n", "Not enout memory");
        return false;
    }
    tmp->dat = value;
    tmp->next = List->head;

    List->head = tmp;
    List->size++;
    return true;
}

void printNode(Node *n) {
    if (n == NULL) {
        printf("[]");
        return;
    }
    printf("[%c]", n->dat);
}

void printList(List *list) {
    Node *current = list->head;
    if (current == NULL) {
        printNode(current);
    } else {
        do {
            printNode(current);
            current = current->next;
        } while (current != NULL);
    }
    printf(" Size: %d \n", list->size);
}

void printListNew(ListNew *list) {
    Node *current = list->head;
    if (current == NULL) {
        printNode(current);
    } else {
        do {
            printNode(current);
            current = current->next;
        } while (current != NULL);
    }
    printf(" Size: %d \n", list->size);
}

void fillList(List *list) {
    char *s; // = "123qwe";
    int numchar = 0;
    s = (char*)malloc(1000);
    printf("%s \n", "Введите строку :");
    fflush(stdout);
    scanf("%s", s);
    while (s[numchar] != '\0'){
        pushList(list, s[numchar++]);
    }
}

/*
Первый вариант
Алгоритм следующий:
Используем другой тип списка, у которого есть указатель на только на "голову", но и на "хвост".
При добавлении нового элемента используем указатель не на "голову", а на "хвост".
*/

boolean copy2List(List *orig, ListNew *copy) { 
    Node* currOrig = orig->head; //создаем указатель на текущий элемент исходного списка
    Node* currCopy = copy->tail; //создаем указатель на 
    for (int i = 0; i < orig->size; ++i) { //в цикле по количеству элементов исходного списка 
        Node *tmp = (Node*) malloc(sizeof(Node)); //создаем узлы
        if (tmp == NULL) { //если система не может выделить память для нового узла - значит память закончилась
            printf("%s\n", "Недостаточно памяти");
            return false;
        }
        if (copy->size == 0) copy->head = tmp; //для первого элемента целевого списка устанавливаем на него указатель на "голову"
        copy->size++; //элементов стало больше :)
        tmp->dat = currOrig->dat; //копируем данные
        tmp->next = NULL; //указатель на следующий элемент NULL, ведь мы создаем список в обратном порядке
        if (copy->tail != NULL) copy->tail->next = tmp; //если создаваемый элемент не первый (он же "хвост") - устанавливаем на него указатель в предыдущем элементе
        currOrig = currOrig->next; //передвигаем указатель на текущий элемент исходного списка
        copy->tail = tmp; //новый "хвост" целевого списка, который мы присвоим полю "next" следующего элемента
    }
    free(currOrig); //не забываем освободить память
    return true;
}

/*
Второй вариант
Алгоритм следующий:
сначала создаем пустой список, а потом идем по узлам обеих списков
и копируем данные
*/

boolean pushForCopy(List* list, int size){
    for (int i = 0; i < size; i++){ //в цикле по количеству элементов в исходном списке создаем новый список
        Node* tmp = (Node*) malloc(sizeof(Node));
        if (tmp == NULL) { //если память закончилась
            printf("%s\n", "Не хватает памяти");
            return false;
        }
        tmp->dat = 0; //инициализируем данные узла
        tmp->next = list->head;
        list->head = tmp; //устанавливаем указатель на "голову" на созданный элемент
        list->size++; //элементов стало больше :)
    }
}

void copy2ListNew(List* listFrom, List* listTo) { 
    pushForCopy(listTo, listFrom->size); //создаем пустой список
    Node* currFrom = listFrom->head; //указатель на элемент исходного списка
    Node* currTo = listTo->head; //указатель на элемент целевого списка
    for (int i = 0; i < listFrom->size; i++) { //в цикле копируем данные из одного списка в другой
        currTo->dat = currFrom->dat;
        currFrom = currFrom->next; //не забываем "передвигать" указатели
        currTo = currTo->next;
    }
    free(currTo); //и не забываем освобождать память от указателей
    free(currFrom);
}

/*
Третий вариант
Алгоритм следующий:
сохраняем указатель на созданный элемент
и в следующем цикле устанавливаем по нему 
в уже ставшем предыдущим элементе
укзатель на вновь создаваемый элемент
*/

boolean copy2ListV3(List* listFrom, List* listTo) {
    Node* currTo = listTo->head; //создаем указатель на текущий элемент целевого списка
    Node* prevTo = NULL; //создаем указатель на предыдущий элемент целевого списка

    for (Node* currFrom = listFrom->head; currFrom != NULL; currFrom = currFrom->next) { //в  цикле, пока указатель на текущий элемент исходного списка не станет NULL, т.е. пока список не кончится (альтернатива for (int i = 0; i < listFrom->size; ++i))
        Node* tmp = (Node*) malloc(sizeof(Node)); //создаем новый узел целевого списка

        if (tmp == NULL) { //если конечно память еще есть...
             printf("%s\n", "Не хватает памяти");
            return false;
        }

        currTo = tmp; //вновь созданный элемент - текущий
        currTo->dat = currFrom->dat; //копируем данные
        listTo->size++; //элементов в целевом списке стало больше :)

        if (prevTo != NULL) {
            prevTo->next = currTo; //если элемент целевого списка не первый - устанавливаем в предыдущем указатель на текущий элемент
        } else {
            listTo->head = currTo; //если элемент целевого списка первый - делаем его "головой"
        }

        prevTo = currTo; //сохраняем указатель на текущий элемент для следующего цикла
    }

    currTo->next = NULL; //поскольку последний созданный элемент у нас "хвост" - инициализируем поле "next"

    free(currTo); //освобождаем память
    free(prevTo); //currFrom объявлен в цикле
    return true;
}

int main(const int argc, const char **argv) {
    ListNew *copyList = (ListNew*) malloc(sizeof(ListNew));
    List *copyListNew = (List*) malloc(sizeof(List));
    List *copyListV3 = (List*) malloc(sizeof(List));
    List *origList = (List*) malloc(sizeof(List));

    if (copyList == NULL || copyListNew == NULL || copyListV3 == NULL || origList == NULL) {
        printf("%s\n", "Не хватает памяти");
        return 1;
    }
    init(origList);
    init(copyListNew);
    init(copyListV3);
    initNew(copyList);
    fillList(origList);

    copy2List(origList, copyList);
    printList(origList);
    printListNew(copyList);

    copy2ListNew(origList, copyListNew);
    printList(origList);
    printList(copyListNew);

    copy2ListV3(origList, copyListV3);
    printList(origList);
    printList(copyListV3);

    return 0;
}