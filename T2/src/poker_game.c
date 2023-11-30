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
#define NUM_RANKS 14
#define NUM_HANDS 5 


void add_card_to_list(ListCards* L, Card* card) {
    list_add_first(L, card);
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

void add_card_deck(ListCards* deck, int rank, Suit suit) {
    Card* C = card_create(rank, suit);
    list_add_first(deck, C);
}

void move_random_card_to_player(ListCards* starter_deck, ListCards* player_deck) {
    int random_card_index = rand() % list_size(starter_deck);
    Card* C = list_get_card(starter_deck, random_card_index);

    add_card_deck(player_deck, get_rank(C), get_suit(C));
    list_remove(starter_deck, C);
}

void create_decks(ListCards* deck_p1, ListCards* deck_p2) {
    ListCards* starter_deck = create_starter_deck();

    printf("\nStarter deck: ");
    list_cards_print(starter_deck);

    while (list_size(starter_deck) > 0) {
        move_random_card_to_player(starter_deck, deck_p1);
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