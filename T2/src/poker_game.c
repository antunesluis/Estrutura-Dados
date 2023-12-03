#include "poker_cards.h"
#include "poker_decks.h"
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

bool validate_index_bounds(size_t deck_size, int index) {
    if (index < 0 || index >= deck_size) {
        printf("\nÍndice inválido. Por favor, digite um valor entre 0 e %lu: ", deck_size - 1);
        return false;
    }

    return true;
}

int get_index_for_card(ListCards* deck) {
    int card_index = 0;
    printf("\nDigite o número da carta que você deseja incluir na sua mão: ");

    while (true) {
        if (scanf("%d", &card_index) != 1 || !validate_index_bounds(list_size(deck), card_index)) {
            while (getchar() != '\n');
        }
        else {
            break;
        }
    }
    puts("");

    return card_index;
}

Card* get_user_selected_card(ListCards* deck) {
    list_cards_print(deck);
    int card_index = get_index_for_card(deck);

    return list_get_card(deck, card_index);
}

ListCards* read_cards_hand(ListCards* deck) {
    ListCards* hand = list_create();

    for (int i = 0; i < NUM_CARD_PER_HANDS; i++) {
        Card* C = get_user_selected_card(deck);
        add_card_to_deck(hand, get_rank(C), get_suit(C));
        list_remove(deck, C);
    }

    return hand;
}

void print_hand(ListCards* hand) {
    clear_terminal();
    printf("\n---- Mao criada com sucesso ----\n");
    list_cards_print(hand);
}

void print_all_hands(Player* P) {
    clear_terminal();
    printf("\n---- Maos criadas ----\n");

    for (int i = 0; i < P->num_hands; i++) {
        printf("\nMao %d:", i + 1);
        printf("\nPontuação: %u", P->hands[i].points);
        list_cards_print(P->hands[i].cards);
    }
}

void read_player_hands(Player* P) {
    for (int i = 0; i < P->num_hands; i++) {
        //clear_terminal();
        printf("\n---- Criando a mao numero %d ----\n", i + 1);

        P->hands[i].cards = read_cards_hand(P->deck);
        print_hand(P->hands[i].cards);
    }
    print_all_hands(P);
}