// test_c.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>

struct Node
{
    int *value;
    Node *next;
    Node *prev;
};

struct List 
{
    size_t size;
    Node *head;
    Node *tail;
};

int main()
{
    char str[80];
    int i;

    // struct Node node { 25 };
    // printf("%d", node.value);

    printf("Enter your family name: ");
    scanf("%79s", str);
    printf("Enter your age: ");
    scanf("%d", &i);
    printf("Mr. %s , %d years old.\n", str, i);
    printf("Enter a hexadecimal number: ");
    scanf("%x", &i);
    printf("You have entered %#x (%d).\n", i, i);

    return 0;
}

List* createList() {
    List* tmp = (List*)malloc(sizeof(List));
    tmp->size = 0;
    tmp->head = tmp->tail = NULL;
    return tmp;
}

void deleteList(List** list)
{
    Node* tmp = (*list)->head;
    Node* next = NULL;

    while (tmp) {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(*list);
    (*list) = NULL;
}

void pushFront(List* list, int* data)
{
    Node* tmp = (Node*)malloc(sizeof(Node));
    if (tmp == NULL) {
        exit(1);
    }

    tmp->value = data;
    tmp->next = list->head;
    tmp->prev = NULL;

    if (list->head) {
        list->head->prev = tmp;
    }

    if (list->tail == NULL) {
        list->tail = tmp;
    }

    list->size++;
}

int* popFront(List* list) {
    Node* head;
    int* tmp;

    if (list->head == NULL) {
        exit(2);
    }

    head = list->head;
    list->head = list->head->next;
    if (list->tail == head) {
        list->tail = NULL;
    }
    if (list->head) {
        list->head->prev = NULL;
    }

    tmp = head->value;
    free(head);
    return tmp;
}

void pushBack(List* list, int* value) 
{
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        exit(3);
    }

    node->value = value;
    node->next = NULL;
    node->prev = list->tail;

    if (list->tail) {
        list->tail->next = node;
    }

    list->tail = node;

    if (list->head == NULL) {
        list->head = node;
    }

    list->size++;
}

int* popBack(List* list) {
    Node* node;
    int* value;

    if (list->tail == NULL) {
        exit(4);
    }

    node = list->tail;
    list->tail = list->tail->prev;
    if (node == list->head) {
        list->head == NULL;
    }

    if (list->tail) {
        list->tail->next = NULL;
    }

    value = list->tail->value;
    free(node);
    list->size--;
    return value;
}

Node* search(List* list, size_t index) 
{
    if (list->head == NULL) {
        exit(5);
    }
    size_t i = 0;

    Node* tmp = list->head;
    while (tmp && i < index) {
        tmp = tmp->next;
        i++;
    }

    return tmp;
}

void insert(List* list, size_t index, int* value)
{
    Node* ins = NULL;
    Node* find = NULL;
    find = search(list, index);
    if (find == NULL) {
        exit(6);
    }

    ins = (Node*)malloc(sizeof(Node));

    ins->value = value;
    ins->prev = find;
    ins->next = find->next;

    if (find->next) {
        find->next->prev = ins;
    }
    find->next = ins;

    if (!ins->next) {
        list->tail = ins;
    }

    if (!find->prev) {
        list->head = find;
    }

    list->size++;
}

int* deleteEl(List* list, size_t index) {
    Node* find = NULL;
    int* value;
    find = search(list, index);
    if (find == NULL) {
        exit(7);
    }
    if (find->prev) {
        find->prev->next = find->next;
    }
    if (find->next) {
        find->next->prev = find->prev;
    }
    if (!find->next) {
        list->tail = find->prev;
    }
    if (!find->prev) {
        list->head = find->next;
    }
    value = find->value;
    free(find);
    list->size--;
    return value;
}

void printList(List* list) {
    Node* node;
    if (list->head == NULL) {
        exit(8);
    }
    node = list->head;
    while (node) {
        printf("%d ", node->value);
        node = node->next;
    }
    printf("/n");
}

// https://learnc.info/adt/double_linked_list.html#:~:text=%D0%94%D0%B2%D1%83%D1%81%D0%B2%D1%8F%D0%B7%D0%BD%D1%8B%D0%B9%20%D1%81%D0%BF%D0%B8%D1%81%D0%BE%D0%BA%20%2D%20%D1%8D%D1%82%D0%BE%20%D1%81%D1%82%D1%80%D1%83%D0%BA%D1%82%D1%83%D1%80%D0%B0%20%D0%B4%D0%B0%D0%BD%D0%BD%D1%8B%D1%85,%D0%BF%D1%80%D0%B5%D0%B4%D1%8B%D0%B4%D1%83%D1%89%D0%B8%D0%B9%20%D1%83%D0%B7%D0%B5%D0%BB%20%D0%B8%20%D1%81%D0%BB%D0%B5%D0%B4%D1%83%D1%8E%D1%89%D0%B8%D0%B9%20%D1%83%D0%B7%D0%B5%D0%BB.&text=%D0%92%20%D1%81%D0%BB%D1%83%D1%87%D0%B0%D0%B5%2C%20%D0%BA%D0%BE%D0%B3%D0%B4%D0%B0%20%D0%B2%20%D1%81%D0%BF%D0%B8%D1%81%D0%BA%D0%B5,(%D1%81%D0%BE%D0%BE%D1%82%D0%B2%D0%B5%D1%82%D1%81%D1%82%D0%B2%D0%B5%D0%BD%D0%BD%D0%BE%D0%B5%2C%20%D0%BE%D0%BD%D0%B8%20%D1%80%D0%B0%D0%B2%D0%BD%D1%8B).