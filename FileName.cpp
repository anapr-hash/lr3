#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
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
struct node* get_struct_no_prior(void);
void review(void);
void review_no_prior(void);
struct node* find(char* name);
void del(char* name);
void del_to_end(char* name);
void clear_list(void);

void enqueue_fifo(void);
struct node* dequeue_fifo(void);
void fifo_menu(void);

void enqueue_priority(void);
struct node* dequeue_priority(void);
void change_by_priority(void);
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

struct node* get_struct_no_prior(void)
{
    struct node* p = NULL;
    char s[256];

    p = (struct node*)malloc(sizeof(struct node));
    if (p == NULL)
    {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }

    printf("Введите название объекта: ");
    scanf_s("%s", s, 256);
    strcpy_s(p->inf, 256, s);

    p->prior = 0;
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

void review_no_prior(void)
{
    struct node* struc = head;

    if (head == NULL)
    {
        printf("Список пуст\n");
        return;
    }

    while (struc)
    {
        printf("Имя - %s\n", struc->inf);
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

void del_to_end(char* name)
{
    if (head == NULL)
    {
        printf("Список пуст\n");
        return;
    }

    struct node* to_move[1024];
    int n = 0;

    struct node* struc = head;
    while (struc)
    {
        if (strcmp(name, struc->inf) == 0)
            to_move[n++] = struc;
        struc = struc->next;
    }

    if (n == 0)
    {
        printf("Элемент не найден\n");
        return;
    }

    for (int i = 0; i < n; i++)
    {
        struct node* m = to_move[i];

        if (m == last) continue;

        if (m == head)
        {
            head = m->next;
        }
        else
        {
            struct node* p = head;
            while (p->next != m) p = p->next;
            p->next = m->next;
        }

        last->next = m;
        last = m;
        m->next = NULL;
    }
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

void change_by_priority(void)
{
    int pr;
    char new_name[256];
    char answer;
    struct node* struc = head;
    int found = 0;
    int count = 0;

    if (head == NULL)
    {
        printf("Список пуст\n");
        return;
    }

    printf("Введите приоритет для поиска: ");
    scanf_s("%d", &pr);

    while (struc)
    {
        if (struc->prior == pr)
        {
            found = 1;
            break;
        }
        struc = struc->next;
    }

    if (!found)
    {
        printf("Элементы с приоритетом %d не найдены\n", pr);
        return;
    }

    printf("Элементы с приоритетом %d:\n", pr);
    struc = head;
    while (struc)
    {
        if (struc->prior == pr)
        {
            count++;
            printf("  %d) Имя - %s\n", count, struc->inf);
        }
        struc = struc->next;
    }

    struc = head;
    count = 0;
    while (struc)
    {
        if (struc->prior == pr)
        {
            count++;
            printf("\nЭлемент %d: '%s'\n", count, struc->inf);
            printf("Изменить имя? (y/n): ");
            scanf_s(" %c", &answer, 1);

            if (answer == 'y' || answer == 'Y')
            {
                printf("Введите новое имя: ");
                scanf_s("%s", new_name, 256);
                strcpy_s(struc->inf, 256, new_name);
                printf("Имя изменено на '%s'\n", struc->inf);
            }
            else
            {
                printf("Пропущено\n");
            }
        }
        struc = struc->next;
    }

    printf("\nИзменение завершено\n");
}

void priority_menu(void)
{
    int choice;
    char name[256];
    struct node* p;

    do
    {
        printf("\nПриоритетная очередь\n");
        printf("1. Добавить элемент\n");
        printf("2. Извлечь элемент\n");
        printf("3. Просмотр\n");
        printf("4. Найти\n");
        printf("5. Удалить по имени\n");
        printf("6. Изменить имя по приоритету\n");
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

        case 6:
            change_by_priority();
            break;

        case 0:
            break;

        default:
            printf("Неверный пункт\n");
        }
    } while (choice != 0);
}

void enqueue_fifo(void)
{
    struct node* p = get_struct_no_prior();
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
        printf("\nОбычная очередь\n");
        printf("1. Добавить элемент\n");
        printf("2. Извлечь элемент\n");
        printf("3. Просмотр\n");
        printf("4. Найти\n");
        printf("5. Удалить по имени (в конец очереди)\n");
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
                printf("Извлечён: %s\n", p->inf);
                free(p);
            }
            break;

        case 3:
            review_no_prior();
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
            del_to_end(name);
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
    struct node* p = get_struct_no_prior();

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
        printf("\nСтек\n");
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
            review_no_prior();
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

        default:
            printf("Неверный пункт\n");
        }
    } while (choice != 0);
}


int main(void)
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");

    int choice;

    do
    {
        printf("\nГЛАВНОЕ МЕНЮ\n");
        printf("1. Обычная очередь\n");
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
