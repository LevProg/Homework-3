#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct Product {
    char name[100];
    int code;
    int price;
    struct Product* next;
};
struct Product* productList = NULL;

struct Product* createProduct(const char* name, int code, int price) {
    struct Product* product = (struct Product*)malloc(sizeof(struct Product));
    strcpy(product->name, name);
    product->code = code;
    product->price = price;
    product->next = NULL;
    return product;
}

void addProduct(struct Product** head, const char* name, int code, int price) {
    struct Product* newProduct = createProduct(name, code, price);
    newProduct->next = *head;
    *head = newProduct;
}

void sortProducts(struct Product** head) {
    struct Product* sorted = NULL;

    while (*head != NULL) {
        struct Product* current = *head;
        *head = (*head)->next;

        if (sorted == NULL || current->code-sorted->code < 0) {
            current->next = sorted;
            sorted = current;
        }
        else {
            struct Product* temp = sorted;
            while (temp->next != NULL && current->code-temp->next->code >= 0) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
    }

    *head = sorted;
}

void printTop10(struct Product* head, int n) {
    for (int i = 0; i < n && head != NULL; i++) {
        printf("Название: %s, Артикул: %d, Стоимость: %d\n", head->name, head->code, head->price);
        head = head->next;
    }
}
struct Product* findProduct(struct Product* head, int searchCode) {
    while (head != NULL) {
        if (head->code == searchCode) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}
void readFile(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Ошибка при открытии файла");
        return 1;
    }
    while (1) {
        char name[100];
        int code;
        int price;
        if (fscanf(file, "%s %d %d\n", name, &code, &price) == 3) {
            struct Product* existingProduct = findProduct(productList, code);
            if (existingProduct != NULL) {
                if (strcmp(existingProduct->name, name) != 0) {
                    printf("Ошибка: Два товара с одинаковым артикулом, но разными названиями\n");
                    fclose(file);
                    _Exit(1);
                }
            }
            else {
                addProduct(&productList, name, code, price);
            }
        }
        else {
            break;
        }
    }
    sortProducts(&productList);
}

int main() {

    setlocale(LC_ALL, "Rus");
    readFile("file_example.txt");

    printTop10(productList, 10);

    int searchCode;
    printf("Введите код товара для поиска: ");
    scanf("%d", &searchCode);

    struct Product* foundProduct = findProduct(productList, searchCode);
    if (foundProduct != NULL) {
        printf("Товар найден: Название: %s, Артикул: %d, Стоимость: %d\n", foundProduct->name, foundProduct->code, foundProduct->price);
    }
    else {
        printf("Товар с артикулом %d не найден\n", searchCode);
    }

    while (productList != NULL) {
        struct Product* temp = productList;
        productList = productList->next;
        free(temp);

        return 0;
    }
}