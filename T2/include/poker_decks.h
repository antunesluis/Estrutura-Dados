#ifndef POKER_DECKS_H
#define POKER_DECKS_H

#include "poker_cards.h"

ListCards* create_starter_deck();
void shuffle_deck(ListCards* deck);
void add_card_to_deck(ListCards* deck, int rank, Suit suit);
void move_random_card_to_player(ListCards* starter_deck, ListCards* player_deck);

#endif