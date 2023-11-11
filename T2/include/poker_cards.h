#ifndef POKER_CARDS_H
#define POKER_CARDS_H

#include <stdbool.h>
#include <stddef.h>

typedef struct _card Card;
typedef struct _doubly_node DoublyNode, Node;
typedef struct _doubly_linked_list DoublyLinkedList, ListCards;

typedef enum {
    HEARTS = 1,
    DIAMONDS,
    CLUBS,
    SPADES
} Suit;

ListCards* list_create();
Card* card_create(int rank, Suit suit);
Node* node_crete(Card* card);
void list_destroy(ListCards** L_ref);
bool list_is_empty(const ListCards* L);
void check_empty_list(const ListCards* L, const char* function_name);

size_t list_size(const ListCards* L);
void list_destroy(ListCards** L_ref);
void list_add_first(ListCards* L, Card* card);
void list_add_last(ListCards* L, Card* card);
void list_print(const ListCards* L);
Card* list_get_val(const ListCards* L, int index);
void list_inverted_print(const ListCards* L);
void list_remove(ListCards* L, Card* card);

#endif