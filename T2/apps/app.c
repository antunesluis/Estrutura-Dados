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

    list_destroy(&deck_1);
    list_destroy(&deck_2);

    return 0;
}