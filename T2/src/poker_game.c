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

ListCards* create_starter_deck() {
    ListCards* deck = list_create();

    for (int i = 1; i <= NUM_SUITS; i++) {
        for (int j = 2; j <= NUM_RANKS; j++) {
            Card* C = card_create(j, i);
            add_card_to_list(deck, C);
        }
    }

    // list_cards_print(deck);

    return deck;
}

void move_random_card_to_player(ListCards* starter_deck, ListCards* player_deck) {
    srand((unsigned int)time(NULL));

    int random_card_index = rand() % list_size(starter_deck);
    Card* C = list_get_card(starter_deck, random_card_index);

    // // printf("Até aqui 2 !!");

    add_card_to_list(player_deck, C);
    list_remove(starter_deck, C);
}

void create_decks(ListCards* deck_p1, ListCards* deck_p2) {
    ListCards* starter_deck = create_starter_deck();

    printf("\n\n\n");
    list_cards_print(starter_deck);

    // // printf("Até aqui!!");

    while (list_size(starter_deck) != 0) {
        // // printf("Até aqui 3!!");
        move_random_card_to_player(starter_deck, deck_p1);
        // // printf("Até aqui 4!!");
        move_random_card_to_player(starter_deck, deck_p2);
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


