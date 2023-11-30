#include "poker_game.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>
#include <time.h>

int main() {

    srand((unsigned int)time(NULL));

    ListCards* deck_1 = list_create();
    ListCards* deck_2 = list_create();

    create_decks(deck_1, deck_2);

    Player* p1 = create_player(deck_1);
    Player* p2 = create_player(deck_2);

    read_decks(p1);



    //create_player_deck; 

    //create_robot_deck; 

    // Card* C = card_create(1, 2);
    // list_add_first(L, C);

    // Card* C2 = card_create(3, 4);
    // list_add_first(L, C2);

    // list_print(L);

    return 0;
}