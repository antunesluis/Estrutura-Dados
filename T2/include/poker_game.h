#ifndef CARD_RANKING_H
#define CARD_RANKING_H

#include "poker_cards.h"
#include "poker_decks.h"

#include <stdbool.h>
#include <stddef.h>

typedef struct _game_hand GameHand;
typedef struct _player Player;

void create_decks(ListCards* list_player, ListCards* list_robot);
Player* create_player(ListCards* deck);
void destroy_player(Player** P_ref);

void read_decks(Player* p);
void ia_read_decks(Player* p);
void read_player_hands(Player* P);

#endif