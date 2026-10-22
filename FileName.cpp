#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct node
{
    char inf[256];
    int  prior;
    struct node* next;
};

struct node* head = NULL, * last = NULL;
int dlina = 0;

struct node* get_struct(void);
void review(void);
struct node* find(char* name);
void del(char* name);
void clear_list(void);

void enqueue_fifo(void);
struct node* dequeue_fifo(void);
void fifo_menu(void);

void enqueue_priority(void);
struct node* dequeue_priority(void);
void priority_menu(void);

void push(void);
struct node* pop(void);
void stack_menu(void);

struct node* get_struct(void)
{
    struct node* p = NULL;
    char s[256];
    int pr;

    p = (struct node*)malloc(sizeof(struct node));
    if (p == NULL)
    {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }

    printf("Введите название объекта: ");
    scanf_s("%s", s, 256);
    strcpy_s(p->inf, 256, s);

    printf("Введите приоритет: ");
    scanf_s("%d", &pr);
    p->prior = pr;

    p->next = NULL;
    return p;
}

void review(void)
{
    struct node* struc = head;

    if (head == NULL)
    {
        printf("Список пуст\n");
        return;
    }

    while (struc)
    {
        printf("Имя - %s, приоритет - %d\n", struc->inf, struc->prior);
        struc = struc->next;
    }
}

struct node* find(char* name)
{
    struct node* struc = head;

    if (head == NULL)
    {
        printf("Список пуст\n");
        return NULL;
    }

    while (struc)
    {
        if (strcmp(name, struc->inf) == 0)
            return struc;
        struc = struc->next;
    }

    printf("Элемент не найден\n");
    return NULL;
}

void del(char* name)
{
    struct node* struc = head;
    struct node* prev = NULL;
    int flag = 0;

    if (head == NULL)
    {
        printf("Список пуст\n");
        return;
    }

    while (struc)
    {
        if (strcmp(name, struc->inf) == 0)
        {
            flag = 1;
            struct node* to_del = struc;

            if (prev == NULL)
                head = struc->next;
            else
                prev->next = struc->next;

            if (struc == last)
                last = prev;

            struc = struc->next;
            free(to_del);
            dlina--;
        }
        else
        {
            prev = struc;
            struc = struc->next;
        }
    }

    if (flag == 0)
        printf("Элемент не найден\n");
}

void clear_list(void)
{
    struct node* p = head;
    while (p)
    {
        struct node* tmp = p;
        p = p->next;
        free(tmp);
    }
    head = NULL;
    last = NULL;
    dlina = 0;
}

void enqueue_fifo(void)
{
    struct node* p = get_struct();
    if (p == NULL) return;

    if (head == NULL)
    {
        head = p;
        last = p;
    }
    else
    {
        last->next = p;
        last = p;
    }
    dlina++;
}

struct node* dequeue_fifo(void)
{
    struct node* p;

    if (head == NULL)
    {
        printf("Очередь пуста\n");
        return NULL;
    }

    p = head;
    head = head->next;

    if (head == NULL)
        last = NULL;

    p->next = NULL;
    dlina--;
    return p;
}

void fifo_menu(void)
{
    int choice;
    char name[256];
    struct node* p;

    do
    {
        printf("\n--- Обычная очередь (FIFO) ---\n");
        printf("1. Добавить элемент\n");
        printf("2. Извлечь элемент\n");
        printf("3. Просмотр\n");
        printf("4. Найти\n");
        printf("5. Удалить по имени\n");
        printf("0. Назад\n");
        printf("Выбор: ");
        scanf_s("%d", &choice, 256);

        switch (choice)
        {
        case 1:
            enqueue_fifo();
            break;

        case 2:
            p = dequeue_fifo();
            if (p != NULL)
            {
                printf("Извлечён: %s (приоритет=%d)\n", p->inf, p->prior);
                free(p);
            }
            break;

        case 3:
            review();
            break;

        case 4:
            printf("Имя: ");
            scanf_s("%s", name, 256);
            p = find(name); if (p != NULL)
                printf("Найден: %s (приоритет=%d)\n", p->inf, p->prior);
            break;

        case 5:
            printf("Имя: ");
            scanf_s("%s", name, 256);
            del(name);
            break;

        case 0:
            break;

        default:
            printf("Неверный пункт\n");
        }
    } while (choice != 0);
}

void enqueue_priority(void)
{
    struct node* p = get_struct();
    struct node* cur;

    if (p == NULL) return;

    if (head == NULL)
    {
        head = p;
        last = p;
        dlina++;
        return;
    }

    if (p->prior > head->prior)
    {
        p->next = head;
        head = p;
        dlina++;
        return;
    }

    cur = head;
    while (cur->next != NULL && cur->next->prior >= p->prior)
        cur = cur->next;

    p->next = cur->next;
    cur->next = p;

    if (p->next == NULL)
        last = p;

    dlina++;
}

struct node* dequeue_priority(void)
{
    struct node* p;

    if (head == NULL)
    {
        printf("Очередь пуста\n");
        return NULL;
    }

    p = head;
    head = head->next;

    if (head == NULL)
        last = NULL;

    p->next = NULL;
    dlina--;
    return p;
}

void priority_menu(void)
{
    int choice;
    char name[256];
    struct node* p;

    do
    {
        printf("\n--- Приоритетная очередь ---\n");
        printf("1. Добавить элемент\n");
        printf("2. Извлечь элемент\n");
        printf("3. Просмотр\n");
        printf("4. Найти\n");
        printf("5. Удалить по имени\n");
        printf("0. Назад\n");
        printf("Выбор: ");
        scanf_s("%d", &choice, 256);

        switch (choice)
        {
        case 1:
            enqueue_priority();
            break;

        case 2:
            p = dequeue_priority();
            if (p != NULL)
            {
                printf("Извлечён: %s (приоритет=%d)\n", p->inf, p->prior);
                free(p);
            }
            break;

        case 3:
            review();
            break;

        case 4:
            printf("Имя: ");
            scanf_s("%s", name, 256);
            p = find(name);
            if (p != NULL)
                printf("Найден: %s (приоритет=%d)\n", p->inf, p->prior);
            break;

        case 5:
            printf("Имя: ");
            scanf_s("%s", name, 256);
            del(name);
            break;

        case 0:
            break;

        default:
            printf("Неверный пункт\n");
        }
    } while (choice != 0);
}

void push(void)
{
    struct node* p = get_struct();

    if (p == NULL) return;

    p->next = head;
    head = p;

    if (last == NULL)
        last = p;

    dlina++;
}

struct node* pop(void)
{
    struct node* p;

    if (head == NULL)
    {
        printf("Стек пуст\n");
        return NULL;
    }

    p = head;
    head = head->next;

    if (head == NULL)
        last = NULL;

    p->next = NULL;
    dlina--;
    return p;
}

void stack_menu(void)
{
    int choice;
    char name[256];
    struct node* p;

    do
    {
        printf("\n--- Стек ---\n");
        printf("1. Добавить элемент\n");
        printf("2. Извлечь элемент\n");
        printf("3. Просмотр\n");
        printf("4. Найти\n");
        printf("5. Удалить по имени\n");
        printf("0. Назад\n");
        printf("Выбор: ");
        scanf_s("%d", &choice, 256);

        switch (choice)
        {
        case 1:
            push();
            break;

        case 2:
            p = pop();
            if (p != NULL)
            {
                printf("Извлечён: %s\n", p->inf);
                free(p);
            }
            break;

        case 3:
            review();
            break;

        case 4:
            printf("Имя: ");
            scanf_s("%s", name, 256);
            p = find(name);
            if (p != NULL)
                printf("Найден: %s\n", p->inf);
            break;

        case 5:
            printf("Имя: ");
            scanf_s("%s", name, 256);
            del(name);
            break;

        case 0:
            break;

        default:printf("Неверный пункт\n");
        }
    } while (choice != 0);
}

int main(void)
{
    setlocale(LC_ALL, "Russian");
    int choice;

    do
    {
        printf("\nГЛАВНОЕ МЕНЮ\n");
        printf("1. Обычная очередь (FIFO)\n");
        printf("2. Приоритетная очередь\n");
        printf("3. Стек\n");
        printf("0. Выход\n");
        printf("Выбор: ");
        scanf_s("%d", &choice, 256);

        switch (choice)
        {
        case 1:
            clear_list();
            fifo_menu();
            break;

        case 2:
            clear_list();
            priority_menu();
            break;

        case 3:
            clear_list();
            stack_menu();
            break;

        case 0:
            break;

        default:
            printf("Неверный пункт\n");
        }
    } while (choice != 0);

    clear_list();
    return 0;
}