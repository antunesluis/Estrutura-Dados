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
    ListCards* deck;
    GameHand* hands;
    int num_hands;
    int cards_per_hand;
} Player;


#define NUM_SUITS 4
#define NUM_RANKS 14
#define NUM_HANDS 5 
#define NUM_CARD_PER_HANDS 5 

void wait_for_enter() {
    printf("Press Enter to continue...");
    while (getchar() != '\n');
}

void clear_terminal() {
    printf("\033[2J\033[H");  // Sequências de escape ANSI para limpar o terminal
}

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
    int random_card_index = rand() % (list_size(starter_deck));
    Card* C = list_get_card(starter_deck, random_card_index);

    add_card_deck(player_deck, get_rank(C), get_suit(C));
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

void create_decks(ListCards* deck_p1, ListCards* deck_p2) {
    ListCards* starter_deck = create_starter_deck();

    // printf("\nStarter deck antes de embaralhar: ");
    // list_cards_print(starter_deck);

    shuffle_deck(starter_deck);

    // printf("\nStarter deck depois de embaralhar: ");
    // list_cards_print(starter_deck);

    while (list_size(starter_deck) > 0) {
        move_random_card_to_player(starter_deck, deck_p1);
        move_random_card_to_player(starter_deck, deck_p2);
    }

    free(starter_deck);
}

void init_hand(GameHand* h) {
    h->cards = list_create();
    h->points = 0;
}

Player* create_player(ListCards* deck) {
    Player* p = (Player*)calloc(1, sizeof(Player));

    p->deck = deck;
    p->num_hands = NUM_HANDS;
    p->cards_per_hand = NUM_CARD_PER_HANDS;
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

bool check_index_bounds(size_t deck_size, int index) {
    if (index < 0 || index >= deck_size) {
        printf("Índice inválido. Por favor, digite um valor entre 0 e %lu: ", deck_size - 1);
        return false;
    }

    return true;
}

Card* question_card_hand(ListCards* deck) {
    int card_index = 0;

    list_cards_print(deck);
    printf("\nDigite o número da carta que você deseja incluir na sua mão: ");

    while (true) {
        if (scanf("%d", &card_index) != 1 || !check_index_bounds(list_size(deck), card_index)) {
            while (getchar() != '\n');
        }
        else {
            break;
        }
    }

    return list_get_card(deck, card_index);
}

ListCards* read_cards_hand(ListCards* deck) {
    ListCards* hand = list_create();

    for (int i = 0; i < NUM_CARD_PER_HANDS; i++) {
        Card* C = question_card_hand(deck);
        add_card_deck(hand, get_rank(C), get_suit(C));
        list_remove(deck, C);
    }

    return hand;
}


void print_hand(ListCards* hand) {
    clear_terminal();

    printf("---- Mao criada com sucesso ----\n");
    list_cards_print(hand);

    wait_for_enter();

}

void read_player_hands(Player* P) {

    for (int i = 0; i < P->num_hands; i++) {
        printf("\nCriando a mao numero %d:\n", i + 1);
        P->hands[i].cards = read_cards_hand(P->deck);
        print_hand(P->hands[i].cards);
    }

}