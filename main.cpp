#include <iostream>
#include <string.h>

using namespace std;

struct NilaiMatKul {
    char nim[11];
    char nama[30];
    char nilai[2];
};

struct element {
    NilaiMatKul matKul;
    struct element *next;
};

struct list {
    struct element *first;
};

void createList(list *l) {
    (*l).first = NULL;
}

int countElement(list L) {
    int hasil = 0;
    if (L.first != NULL) {
        element *elmt;

        elmt = L.first;
        while (elmt != NULL) {
            hasil = hasil + 1;

            elmt = elmt->next;
        }
    }

    return hasil;
}

void printElement(list l) {
    if (l.first != NULL) {
        element *item;
        item = l.first;
        while (item != NULL) {
            cout << "Telefono: " << item->matKul.nim << endl;
            cout << "Nombre: " << item->matKul.nama << endl;
            cout << "Edad: " << item->matKul.nilai << endl;
            cout << "========================================" << endl;
            item = item->next;
        }
    }
}

void addFirst(char nim[], char nama[], char nilai[], list *l) {
    element *item;
    item = (element *) malloc(sizeof(element));
    strcpy(item->matKul.nim, nim);
    strcpy(item->matKul.nama, nama);
    strcpy(item->matKul.nilai, nilai);

    item->next = (*l).first;
    (*l).first = item;
    item = NULL;
}

void addAfter(element *prec, char nim[], char nama[], char nilai[]) {
    element *item;

    item = (element *) malloc(sizeof(element));
    strcpy(item->matKul.nim, nim);
    strcpy(item->matKul.nama, nama);
    strcpy(item->matKul.nilai, nilai);
    item->next = prec->next;
    prec->next = item;
}

void addLast(char nim[], char nama[], char nilai[], list *L) {
    if ((*L).first == NULL) {
        addFirst(nim, nama, nilai, L);
    } else {
        element *item;
        item = (element *) malloc(sizeof(element));
        strcpy(item->matKul.nim, nim);
        strcpy(item->matKul.nama, nama);
        strcpy(item->matKul.nilai, nilai);
        item->next = NULL;

        element *last = (*L).first;

        while (last->next != NULL) {
            last = last->next;
        }

        last->next = item;
    }
}

void delFirst(list *L) {
    if ((*L).first != NULL) {
        element *item = (*L).first;
        (*L).first = (*L).first->next;
        item->next = NULL;
        free(item);
    }
}

void delAfter(element *prec) {
    element *item = prec->next;
    prec->next = item->next;
    item->next = NULL;
    free(item);
}

void delLast(list *L) {
    if ((*L).first != NULL) {
        if (countElement(*L) == 1) {
            delFirst(L);
        } else {
            element *last = (*L).first;
            element *before_last = last;

            while (last->next != NULL) {
                before_last = last;
                last = last->next;
            }

            before_last->next = NULL;
            free(last);
        }
    }
}

/* Unused method */
void dellAll(list *L) {
    if (countElement(*L) != 0) {
        int i;
        for (i = countElement(*L); i >= 1, i--;) {
            delLast(L);
        }
    }
}

int main() {
    struct list l;
    createList(&l);

    cout << "Elementos agregados:\n\n" << endl;
    addFirst("3322322334", "Marcos", "32", &l);
    addAfter(l.first, "3345465342", "Daniela", "23");
    addLast("3366453476", "Angelica", "16", &l);
    printElement(l);

    //Eliminar elementos:
    delLast(&l);
    delAfter(l.first);
    delFirst(&l);
    printElement(l);
    return 0;
}
