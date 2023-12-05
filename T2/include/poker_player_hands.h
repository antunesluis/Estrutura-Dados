#ifndef POKER_PLAYER_H
#define POKER_PLAYER_H

#include "poker_cards.h"
#include "poker_decks.h"

#include <stdbool.h>
#include <stddef.h>

typedef struct _game_hand GameHand;
typedef struct _player Player;


void read_hands(Player* P);


void create_decks(ListCards* list_player, ListCards* list_robot);
Player* create_player(ListCards* deck);
void destroy_player(Player** P_ref);

void read_player_hands(Player* P);
void read_decks(Player* p);

void add_card_to_hand(ListCards* hand, Rank rank, Suit suit);
void draw_card_by_rank(ListCards* deck, int rank, ListCards* hand_cards);

#endif