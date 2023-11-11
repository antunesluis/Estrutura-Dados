#include "poker_cards.h"
#include "CardRanking.h"

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


#define NUM_SUITS 4
#define NUM_RANKS 13

void create_primary_deck(ListCards* list_player, ListCards* list_robot) {
    srand((unsigned int)time(NULL));

    for (int i = 1; i <= NUM_SUITS; i++) {
        for (int j = 2; j <= NUM_RANKS; j++) {
            int random_number = rand() % 2;  // Gera 0 ou 1

            Card* C = create_card(j, i);
            add_card_to_list(random_number == PLAYER ? list_player : list_robot, C);
        }
    }
}

void add_card_to_list(ListCards* L, Card* card) {
    list_add_first(L, card);
}

void create_player_hands(ListCards* L) {
    // ListCards* hand_1 = list_create();
    // ListCards* hand_2 = list_create();
    // ListCards* hand_3 = list_create();
    // ListCards* hand_4 = list_create();
    // ListCards* hand_5 = list_create();
}

void create_robot_hands(ListCards* L) {

}






