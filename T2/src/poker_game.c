#include "poker_cards.h"
#include "poker_game.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>
#include <time.h>


typedef enum {
    PLAYER,
    ROBOT
} PlayerType;


typedef struct _game_hand {
    ListCards* cards;
    unsigned int points;
} GameHand;


typedef struct _player {
    ListCards* primary_deck;
    GameHand* hands;
    int num_hands;
} Player;


#define NUM_SUITS 4
#define NUM_RANKS 13
#define NUM_HANDS 5 


void add_card_to_list(ListCards* L, Card* card) {
    list_add_first(L, card);
}

void create_primary_decks(ListCards* deck_1, ListCards* deck_2) {
    srand((unsigned int)time(NULL));

    for (int i = 1; i <= NUM_SUITS; i++) {
        for (int j = 2; j <= NUM_RANKS; j++) {
            int random_number = rand() % 2;  // Gera 0 ou 1

            Card* C = card_create(j, i);

            // Adiciona cartas aleatoriamente aos decks dos jogadores
            if (random_number == 0) {
                add_card_to_list(deck_1, C);
            }
            else {
                add_card_to_list(deck_2, C);
            }
        }
    }
}

void init_hand(GameHand* h) {
    h->cards = list_create();
    h->points = 0;
}

Player* create_player(ListCards* deck) {
    Player* p = (Player*)calloc(1, sizeof(Player));

    p->primary_deck = deck;
    p->num_hands = NUM_HANDS;
    p->hands = (GameHand*)calloc(p->num_hands, sizeof(GameHand));

    for (int i = 0; i < p->num_hands; i++) {
        init_hand(&p->hands[i]);
    }

    return p;
}

void read_decks(Player* p) {
    // for (int i = 0; i < p->num_hands; i++) {
    //     list_cards_print(p->primary_deck);
    // }

    list_cards_print(p->primary_deck);

}


