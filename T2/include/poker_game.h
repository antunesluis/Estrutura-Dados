#ifndef CARD_RANKING_H
#define CARD_RANKING_H

#include "poker_cards.h"

#include <stdbool.h>
#include <stddef.h>

typedef struct _game_hand GameHand;
typedef struct _player Player;

void create_primary_decks(ListCards* list_player, ListCards* list_robot);
Player* create_player(ListCards* deck);

void read_decks(Player* p);
void ia_read_decks(Player* p);

#endif