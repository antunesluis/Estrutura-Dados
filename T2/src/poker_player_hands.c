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
} Player;


#define NUM_HANDS 5


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

void print_hand(ListCards* hand_cards) {
    //clear_terminal();
    printf("\n---- Mao criada com sucesso ----\n");
    list_cards_print(hand_cards);
    puts("");
}

void print_all_hands(Player* P) {
    //clear_terminal();

    printf("\n---- Maos criadas ----\n");

    for (int i = 0; i < P->num_hands; i++) {
        printf("\nMao %d:", i + 1);
        printf("\nPontuação: %u", P->hands[i].points);
        list_cards_print(P->hands[i].cards);
    }
}

int search_for_classification(Player* P, ListCards* hand_cards) {
    int pontos = 0;

    if (search_pair(P->deck, hand_cards)) {
        pontos = 1000;
        return pontos;
    }

    if (search_two_pair(P->deck, hand_cards)) {
        pontos = 930;
        return pontos;
    }

    if (search_three_of_a_kind(P->deck, hand_cards)) {
        pontos = 432;
        return pontos;
    }

    if (search_straight(P->deck, hand_cards)) {
        pontos = 323;
        return pontos;
    }

    return pontos;  // ou apenas "return 0;" se preferir
}

void read_hands(Player* P) {
    printf("\n---- Deck Original ----");
    list_cards_print(P->deck);

    for (int i = 0; i < P->num_hands; i++) {


        P->hands[i].points = search_for_classification(P, P->hands[i].cards);
        print_hand(P->hands[i].cards);
        printf("PONTOS: %d", P->hands[i].points);
    }

    print_all_hands(P);
}


