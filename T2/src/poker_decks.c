#include "poker_cards.h"
#include "poker_decks.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>
#include <time.h>

#define NUM_SUITS 4
#define NUM_RANKS 14


void add_card_to_deck(ListCards* deck, int rank, Suit suit) {
    Card* C = card_create(rank, suit);
    list_add_first(deck, C);
}

void move_random_card_to_player(ListCards* starter_deck, ListCards* player_deck) {
    int random_card_index = rand() % (list_size(starter_deck));
    Card* C = list_get_card(starter_deck, random_card_index);

    add_card_to_deck(player_deck, get_rank(C), get_suit(C));
    list_remove(starter_deck, C);
}

void shuffle_deck(ListCards* deck) {
    int n = list_size(deck);
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        if (i != j) {
            // Troca as cartas nas posições i e j
            Card* card_i = list_get_card(deck, i);
            Card* card_j = list_get_card(deck, j);

            list_set_card(deck, i, card_j);
            list_set_card(deck, j, card_i);
        }
    }
}

ListCards* create_starter_deck() {
    ListCards* deck = list_create();

    for (int i = 1; i <= NUM_SUITS; i++) {
        for (int j = 2; j <= NUM_RANKS; j++) {
            Card* C = card_create(j, i);
            list_add_first(deck, C);
        }
    }

    return deck;
}

void create_decks(ListCards* deck_p1, ListCards* deck_p2) {
    ListCards* starter_deck = create_starter_deck();
    shuffle_deck(starter_deck);

    while (list_size(starter_deck) > 0) {
        move_random_card_to_player(starter_deck, deck_p1);
        move_random_card_to_player(starter_deck, deck_p2);
    }

    free(starter_deck);
}