// AlgLab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdlib.h>
#include <ctype.h>
#include <string>
using namespace std;

typedef struct LIFO {
    char data;
    struct LIFO* next;
}LIFO;

void push(LIFO** head, int data) {
    LIFO* tmp = new LIFO;
    tmp->next = *head;
    tmp->data = data;
    *head = tmp;
}


char pop(LIFO** head) {
    LIFO* out;
    int data;
    out = *head;
    *head = (*head)->next;
    data = out->data;
    delete out;
    return data;
}

void NewMem(char** arr, int size) {
    *arr = new char[size];
}

void clean(char** arr) {
    delete[] *arr;
}

void try_again() {
    std::cin.clear();
    while (std::cin.get() != '\n');
    std::cout << "Неверный запрос, попробуйте еще раз! \n";
}

void f() {
    std::cout << "Выберете нужное действие: \n1)Структура динамического массива\n2)Реализация стека на структуре односвязного списка\n3)Завершить программу\n";
    std::cout << "Введите число 1, 2 или 3! \n";
}

int main()
{
    int size = 0, choice, flag;
    char* arr;
    string line;
    LIFO* head = new LIFO;
    head = NULL;
    int i = 0;
    setlocale(LC_CTYPE, "rus");
    f();
    while (!(std::cin >> choice)) try_again();
    std::cin.clear();
    while (std::cin.get() != '\n');
    while (choice != 3) {
        switch (choice) {
            case 1:
                cout << "Введите желаемый размер динамического массива\n";
                std::cin >> size;
                NewMem(&arr, size);
                cout << "Массив заполняется случайными буквами: ";
                for (int i = 0; i < size; i++) arr[i] = char(rand() % 26 + 0x61);
                for (int i = 0; i < size; i++) cout << arr[i] << " ";
                clean(&arr);
                cout << endl;
                cout << "Попробуйте еще раз.\n";
                f();
                while (!(std::cin >> choice)) try_again();
                std::cin.clear();
                while (std::cin.get() != '\n');
                break;
            case 2:
                std::cin.clear();
                std::cout << "Введите алгебраическое выражение. Используйте натуральные числа и операции '+', '-', '*', '/', '!', '^' а также круглые скобки.\n";
                char symbol;
                std::cout << "Инфиксная запись: ";
                cin >> line;
                std::cout << "Обратная польская запись: ";
                i = 0;
                flag = 0;
                while ( i < line.length()) {
                    if (isdigit(line[i])) {
                        cout << line[i];
                        if (!isdigit(line[i + 1])) cout << " ";
                    }
                    else if (line[i] == '!') cout << line[i] << " ";
                    else if (line[i] == ')') { 
                        if (head == NULL) {
                            flag = 1;
                            cout << "Ошибка1! Скобки несогласованны!";
                        }
                        else symbol = pop(&head);
                        while (symbol != '(') {
                            cout << symbol << ' ';                           
                            if ( head == NULL) {
                                cout << "Ошибка2! Скобки несогласованны!";
                                flag = 1;
                                break;
                            }
                            symbol = pop(&head);
                        }
                    }
                    if (flag == 1) break;
                    else if (line[i] == '(') push(&head, line[i]);
                    else if (line[i] == '*' || line[i] == '/') {
                        if (head != NULL) {
                            while (head->data == '*' || head->data == '/' || head->data == '^') {
                                cout << pop(&head) << " ";
                                if (head == NULL) break;
                            }
                        }
                        push(&head, line[i]);
                    }
                    else if (line[i] == '+' || line[i] == '-') {
                        if (head != NULL) {
                            while (head->data == '*' || head->data == '/' || head->data == '+' || head->data == '-' || head->data == '^') {
                                cout << pop(&head) << " ";
                                if (head == NULL) break;
                            }
                        }
                        push(&head, line[i]);
                    }
                    else if (line[i] == '^') {
                        if (head != NULL) {
                            while (head->data == '^') {
                                cout << pop(&head) << " ";
                                if (head == NULL) break;
                            }
                        }
                        push(&head, line[i]);
                    }

                    i++;
                }
                while (head != NULL) {
                    if (head->data == '(') {
                        cout << "Ошибка! Скобки несогласованны!\n";
                        break;
                    }
                    cout << pop(&head) << " ";
                }
                cout << endl;
                cout << "Попробуйте еще раз.\n";
                f();
                while (!(std::cin >> choice)) try_again();
                std::cin.clear();
                while (std::cin.get() != '\n');
                break; 
            default:
                cout << "Попробуйте еще раз.\n";
                f();
                while (!(std::cin >> choice)) try_again();
                std::cin.clear();
                while (std::cin.get() != '\n');
        }
    }
}

