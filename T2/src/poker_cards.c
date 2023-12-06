#include "poker_cards.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>

typedef struct _card {
    Rank rank;
    Suit suit;
} Card;


typedef struct _doubly_node {
    Card* card;
    struct _doubly_node* prev;
    struct _doubly_node* next;
} DoublyNode, Node;


typedef struct _doubly_linked_list {
    Node* begin;
    Node* end;
    size_t size;
} DoublyLinkedList, ListCards;



Card* card_create(Rank rank, Suit suit) {
    Card* C = (Card*)calloc(1, sizeof(Card));
    C->rank = rank;
    C->suit = suit;

    return C;
}

Node* node_crete(Card* card) {
    Node* node = (Node*)calloc(1, sizeof(Node));
    node->prev = NULL;
    node->next = NULL;
    node->card = card;

    return node;
}

ListCards* list_create() {
    ListCards* L = (ListCards*)calloc(1, sizeof(ListCards));
    L->begin = NULL;
    L->end = NULL;
    L->size = 0;

    return L;
}

void list_destroy(ListCards** L_ref) {
    ListCards* L = *L_ref;

    Node* p = L->begin;
    Node* aux = NULL;

    while (p != NULL) {
        aux = p;
        p = p->next;
        free(aux->card);
        free(aux);
    }
    free(L);

    *L_ref = NULL;
}

bool list_is_empty(const ListCards* L) {
    return L->size == 0;
}

void check_empty_list(const ListCards* L, const char* function_name) {
    if (list_is_empty(L)) {
        fprintf(stderr, "ERROR in '%s'\n", function_name);
        fprintf(stderr, "List is empty\n");
        exit(EXIT_FAILURE);
    }
}

size_t list_size(const ListCards* L) {
    //check_empty_list(L, "List_size");
    return L->size;
}

void list_add_first(ListCards* L, Card* card) {
    Node* p = node_crete(card);

    p->next = L->begin;

    if (list_is_empty(L)) {
        L->end = p;
    }
    else {
        L->begin->prev = p;
    }

    // List_is_empty(L) ? (L->end = p) : (L->begin->prev = p); 
    L->begin = p;
    L->size++;

}

void list_add_last(ListCards* L, Card* card) {
    Node* p = node_crete(card);
    p->prev = L->end;

    if (list_is_empty(L)) {
        L->begin = p;
    }
    else {
        L->end->next = p;
    }

    // List_is_empty(L) ? (L->begin = p) : (L->end->prev = p);
    L->end = p;
    L->size++;
}

void list_set_card(ListCards* L, int index, Card* new_card) {
    check_empty_list(L, "list_set_card");

    if (index < 0 || index >= L->size) {
        fprintf(stderr, "ERROR in 'list_set_card'\n");
        fprintf(stderr, "Invalid index: %d\n", index);
        fprintf(stderr, "Try an index within [0, %lu]\n", L->size - 1);
        exit(EXIT_FAILURE);
    }

    Node* p = L->begin;
    for (int i = 0; i != index; i++) {
        p = p->next;
    }

    p->card = new_card;
}

Card* list_get_card(const ListCards* L, int index) {
    check_empty_list(L, "List_get_val");

    if (index < 0 || index >= L->size) {
        fprintf(stderr, "ERROR in 'List_get_val'\n");
        fprintf(stderr, "invalid index: %d\n", index);
        fprintf(stderr, "Try an index within [0, %lu]\n", L->size - 1);
        exit(EXIT_FAILURE);
    }

    Node* p = L->begin;
    for (int i = 0; i != index; i++) {
        p = p->next;
    }

    return p->card;
}

Card* list_get_card_by_rank(const ListCards* L, Rank rank) {
    check_empty_list(L, "List_get_val");

    Node* p = L->begin;
    for (int i = 0; i != L->size; i++) {
        if (p->card->rank == rank) {
            break;
        }

        p = p->next;
    }

    return p->card;
}

Card* list_get_card_by_suit(const ListCards* L, Suit suit) {
    check_empty_list(L, "List_get_val");

    Node* p = L->begin;
    for (int i = 0; i != L->size; i++) {
        if (p->card->suit == suit) {
            break;
        }

        p = p->next;
    }

    return p->card;
}

Card* list_get_card_by_rank_and_suit(const ListCards* L, Rank rank, Suit suit) {
    check_empty_list(L, "List_get_val");

    Node* p = L->begin;
    for (int i = 0; i != L->size; i++) {
        if (p->card->suit == suit && p->card->rank == rank) {
            break;
        }

        p = p->next;
    }

    return p->card;
}

bool list_contains_card(const ListCards* L, Rank rank, Suit suit) {
    check_empty_list(L, "List_get_val");

    Node* p = L->begin;
    for (int i = 0; i != L->size; i++) {
        if (p->card->suit == suit && p->card->rank == rank) {
            return true;
        }

        p = p->next;
    }

    return false;
}

void list_cards_print(const ListCards* L) {
    Node* p = L->begin;

    //printf("\nCartas restantes: %lu\n", L->size);

    puts("");
    for (int i = 0; i < L->size; i++) {
        printf("\t%02d. : ", i);
        printf("rank: %d, valete: %d\n", p->card->rank, p->card->suit);
        p = p->next;
    }
    puts("");
}

void list_remove(ListCards* L, Card* card) {
    if (list_is_empty(L)) {
        return;
    }
    Node* p = L->begin;

    // caso 1: o elemento está na cabeça da lista
    if (L->begin->card == card) {
        L->begin = p->next;

        // a lista possui apenas um único elemento
        if (L->end == p) {
            L->end = NULL;
        }
        // a lista possui mais de um elemento
        else {
            L->begin->prev = NULL;
        }

        free(p);
        L->size--;
    }
    else {
        p = p->next;

        while (p != NULL) {
            if (p->card == card) {
                p->prev->next = p->next;

                // caso 3: o elemento está no final da lista
                if (L->end == p) {
                    L->end = p->prev;
                }
                // caso 2: o elemento está no meio da lista
                else {
                    p->next->prev = p->prev;
                }

                free(p);
                p = NULL;
                L->size--;
            }
            else {
                p = p->next;
            }
        }
    }
    free(card);
}

int get_rank(Card* C) {
    return C->rank;
}

Suit get_suit(Card* C) {
    return C->suit;
}

void print_card(Card* c) {
    printf("rank: %d\n", c->rank);
    printf("suit: %d\n", c->suit);
}

