#include "poker_cards.h"
#include "CardRanking.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>
#include <time.h>

int main() {

    srand((unsigned int)time(NULL));

    ListCards* List_player = list_create();
    ListCards* List_Robot = list_create();



    void create_primary_deck(List_player, List_Robot);



    //create_player_deck; 

    //create_robot_deck; 

    Card* C = card_create(1, 2);
    list_add_first(L, C);

    Card* C2 = card_create(3, 4);
    list_add_first(L, C2);

    list_print(L);

    return 0;
}