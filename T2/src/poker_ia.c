#include "poker_cards.h"
#include "poker_decks.h"
#include "poker_ia.h"
#include "poker_player_hands.h"


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>
#include <time.h>

#define RSF_POINTS 1000
#define SF_POINTS 750
#define FOURK_POINTS 500
#define FH_POINTS 300
#define FL_POINTS 200
#define ST_POINTS 150
#define THREEK_POINTS 100
#define TWOP_POINTS 50
#define ONEP_POINTS 25
#define HIGHCARD_POINTS 0


#define NUM_HANDS 5
#define NUM_CARD_PER_HANDS 5

void deal_cards_to_hand_by_rank(ListCards* deck, ListCards* hand, Rank rank) {
    Card* C = list_get_card_by_rank(deck, rank);
    add_card_to_deck(hand, get_rank(C), get_suit(C));
    list_remove(deck, C);
}


void hand_add_royal_straight_flush(ListCards* deck, ListCards* hand) {
    deal_cards_to_hand_by_rank(deck, hand, RANK_10);
    deal_cards_to_hand_by_rank(deck, hand, RANK_JACK);
    deal_cards_to_hand_by_rank(deck, hand, RANK_QUEEN);
    deal_cards_to_hand_by_rank(deck, hand, RANK_KING);
    deal_cards_to_hand_by_rank(deck, hand, RANK_ACE);
}

bool search_royal_straight_flush(ListCards* deck) {
    int count_10 = 0, count_jack = 0, count_queen = 0, count_king = 0, count_ace = 0;

    for (size_t i = 0; i < list_size(deck); i++) {
        Card* C = list_get_card(deck, i);

        switch (get_rank(C)) {
        case RANK_10:
            count_10++;
            break;
        case RANK_JACK:
            count_jack++;
            break;
        case RANK_QUEEN:
            count_queen++;
            break;
        case RANK_KING:
            count_king++;
            break;
        case RANK_ACE:
            count_ace++;
            break;
        }
    }

    return (count_10 > 0 && count_jack > 0 && count_queen > 0 && count_king > 0 && count_ace > 0);
}

void search_classify_for_hand(ListCards* deck, ListCards* hand) {
    search_royal_straight_flush(deck);
}