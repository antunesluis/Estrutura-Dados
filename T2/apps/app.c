#include "poker_cards.h"
#include <stdio.h>

int main() {

    ListCards* L = list_create();
    Card* C = card_create(1, 2);
    list_add_first(L, C);

    Card* C2 = card_create(3, 4);
    list_add_first(L, C2);

    list_print(L);

    return 0;
}