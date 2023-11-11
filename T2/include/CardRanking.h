#ifndef CARD_RANKING_H
#define CARD_RANKING_H

#include "poker_cards.h"

#include <stdbool.h>
#include <stddef.h>

void create_primary_deck(ListCards* list_player, ListCards* list_robot);
void create_player_hands(ListCards* L);
void create_robot_hands(ListCards* L);







#endif