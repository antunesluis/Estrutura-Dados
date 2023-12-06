#include "poker_cards.h"
#include "poker_decks.h"
#include "poker_classification.h"
#include "poker_player_hands.h"


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>
#include <time.h>

typedef struct _game_hand {
    ListCards* cards;
    unsigned int points;
} GameHand;


typedef struct _player {
    ListCards* deck;
    GameHand* hands;
    int num_hands;
    int cards_per_hand;
} Player;


#define NUM_HANDS 5
#define NUM_CARDS_PER_HAND 5

#define RSF_POINTS 1000
#define SF_POINTS 750
#define FOUR_K_POINTS 500
#define FH_POINTS 300
#define FL_POINTS 200
#define ST_POINTS 150
#define THREE_K_POINTS 100
#define TWO_P_POINTS 50
#define ONE_P_POINTS 25
#define HIGHCARD_POINTS 0


void wait_for_enter() {
    printf("Press Enter to continue...");
    while (getchar() != '\n');
}

void clear_terminal() {
    printf("\033[2J\033[1;1H");
}

void init_hand(GameHand* h) {
    h->cards = list_create();
    h->points = 0;
}

Player* create_player(ListCards* deck) {
    Player* p = (Player*)calloc(1, sizeof(Player));

    p->deck = deck;
    p->num_hands = NUM_HANDS;
    p->cards_per_hand = NUM_CARDS_PER_HAND;
    p->hands = (GameHand*)calloc(p->num_hands, sizeof(GameHand));

    for (int i = 0; i < p->num_hands; i++) {
        init_hand(&p->hands[i]);
    }

    return p;
}

void destroy_player(Player** P_ref) {
    Player* P = *P_ref;

    for (int i = 0; i < P->num_hands; i++) {
        list_destroy(&P->hands[i].cards);
    }

    free(P->hands);
    free(P->deck);
    free(P);

    *P_ref = NULL;
}

void add_card_to_hand(ListCards* hand, Rank rank, Suit suit) {
    Card* C = card_create(rank, suit);
    list_add_first(hand, C);
}

bool validate_index_bounds(size_t deck_size, int index) {
    if (index < 0 || index >= deck_size) {
        printf("\nÍndice inválido. O valor deve estar entre 0 e %lu: ", deck_size - 1);
        return false;
    }

    return true;
}

void print_all_hands(Player* P) {
    printf("\n---- Maos criadas ----\n");

    for (int i = 0; i < P->num_hands; i++) {
        printf("\nMao %d:", i + 1);
        printf("\nPontuação: %u", P->hands[i].points);
        list_cards_print(P->hands[i].cards);
    }
}

void check_missing_cards(ListCards* deck, ListCards* hand_cards) {
    unsigned int n_cards_missing = 5 - list_size(hand_cards);

    if (list_size(hand_cards) > 0 && list_size(deck) > 0) {
        for (int i = 0; i < n_cards_missing; i++) {
            move_random_card_to_player(deck, hand_cards);
        }
    }
}

int search_for_classification(Player* P, ListCards* hand_cards) {
    if (search_royal_straight_flush(P->deck, hand_cards)) {
        return RSF_POINTS;
    }

    if (search_straight_flush(P->deck, hand_cards)) {
        return SF_POINTS;
    }

    if (search_four_of_a_kind(P->deck, hand_cards)) {
        return FOUR_K_POINTS;
    }

    if (search_full_house(P->deck, hand_cards)) {
        return FH_POINTS;
    }

    if (search_flush(P->deck, hand_cards)) {
        return FL_POINTS;
    }

    if (search_straight(P->deck, hand_cards)) {
        return ST_POINTS;
    }

    if (search_three_of_a_kind(P->deck, hand_cards)) {
        return THREE_K_POINTS;
    }

    if (search_two_pair(P->deck, hand_cards)) {
        return TWO_P_POINTS;
    }

    if (search_pair(P->deck, hand_cards)) {
        return ONE_P_POINTS;
    }

    create_hand_high_card(P->deck, hand_cards, P->cards_per_hand);
    return HIGHCARD_POINTS;
}

void read_hands(Player* P) {
    clear_terminal();
    printf("\n---- Deck Original ----\n");
    list_cards_print(P->deck);

    for (int i = 0; i < P->num_hands; i++) {
        P->hands[i].points = search_for_classification(P, P->hands[i].cards);
    }

    for (int i = 0; i < P->num_hands; i++) {
        check_missing_cards(P->deck, P->hands[i].cards);
    }
    print_all_hands(P);
}