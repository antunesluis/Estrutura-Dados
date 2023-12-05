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

typedef enum {
    RANK_2 = 2,
    RANK_3,
    RANK_4,
    RANK_5,
    RANK_6,
    RANK_7,
    RANK_8,
    RANK_9,
    RANK_10,
    RANK_JACK,
    RANK_QUEEN,
    RANK_KING,
    RANK_ACE,
} Rank;

ListCards* list_create();
void list_destroy(ListCards** L_ref);

Node* node_crete(Card* card);
Card* card_create(Rank rank, Suit suit);
void list_destroy(ListCards** L_ref);

bool list_is_empty(const ListCards* L);
void check_empty_list(const ListCards* L, const char* function_name);
size_t list_size(const ListCards* L);

void list_add_first(ListCards* L, Card* card);
void list_add_last(ListCards* L, Card* card);

void linked_print(const ListCards* L);
void linked_inverted_print(const ListCards* L);
void list_cards_print(const ListCards* L);

void list_set_card(ListCards* L, int index, Card* new_card);
Card* list_get_card(const ListCards* L, int index);
Card* list_get_card_by_rank(const ListCards* L, Rank rank);


void list_remove(ListCards* L, Card* card);


int get_rank(Card* C);
Suit get_suit(Card* C);
void print_card(Card* c);



#endif