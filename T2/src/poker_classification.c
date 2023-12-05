#include "poker_cards.h"
#include "poker_decks.h"
#include "poker_classification.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>
#include <time.h>

#define NUM_SUITS 4
#define NUM_RANKS 14

#define NUM_CARDS_FOR_PAIR 2
#define NUM_CARDS_FOR_3K 3


int* create_dynamic_array(size_t size) {
    int* array = (int*)calloc(size, sizeof(int));

    if (array == NULL) {
        fprintf(stderr, "Memory allocation failure\n");
        exit(EXIT_FAILURE);
    }

    return array;
}

int* create_rank_counts(ListCards* deck) {
    int* rank_counts = create_dynamic_array(RANK_N);

    for (size_t i = 0; i < list_size(deck); i++) {
        Card* C = list_get_card(deck, i);
        int rank = get_rank(C);
        rank_counts[rank]++;
    }

    return rank_counts;
}

// bool has_specific_rank_occurrences(int* rank_counts, int target_occurrences) {
//     for (int i = 0; i < NUM_RANKS - 1; i++) {
//         if (rank_counts[i] == target_occurrences) {
//             return true;
//         }
//     }

//     return false;
// }

void draw_card_by_rank(ListCards* deck, int rank, ListCards* hand_cards) {
    Card* C = list_get_card_by_rank(deck, rank);
    add_card_to_deck(hand_cards, get_rank(C), get_suit(C));
    list_remove(deck, C);
}

bool search_straight(ListCards* deck, ListCards* hand_cards) {
    int* rank_counts = create_rank_counts(deck);

    for (int i = RANK_10; i <= RANK_ACE; i++) {
        if (rank_counts[i] == 0) {
            free(rank_counts);
            return false;
        }

        Card* C = list_get_card_by_rank(deck, i);
        add_card_to_deck(hand_cards, get_rank(C), get_suit(C));
        list_remove(deck, C);
    }

    free(rank_counts);
    return true;
}

bool search_three_of_a_kind(ListCards* deck, ListCards* hand_cards) {
    int* rank_counts = create_rank_counts(deck);

    for (int i = RANK_2; i <= RANK_ACE; i++) {
        if (rank_counts[i] == NUM_CARDS_FOR_3K) {
            draw_card_by_rank(deck, i, hand_cards);
            draw_card_by_rank(deck, i, hand_cards);
            draw_card_by_rank(deck, i, hand_cards);
            free(rank_counts);
            return true;
        }
    }

    free(rank_counts);
    return true;
}

bool search_two_pair(ListCards* deck, ListCards* hand_cards) {
    int* rank_counts = create_rank_counts(deck);
    int pair_count = 0;

    for (int i = RANK_2; i <= RANK_ACE; i++) {
        if (rank_counts[i] == NUM_CARDS_FOR_PAIR) {
            pair_count++;
        }
    }

    free(rank_counts);

    if (pair_count >= 2) {
        search_pair(deck, hand_cards);
        search_pair(deck, hand_cards);

        return true;
    }

    return false;
}

bool search_pair(ListCards* deck, ListCards* hand_cards) {
    int* rank_counts = create_rank_counts(deck);

    for (int i = RANK_2; i <= RANK_ACE; i++) {
        if (rank_counts[i] == NUM_CARDS_FOR_PAIR) {
            draw_card_by_rank(deck, i, hand_cards);
            draw_card_by_rank(deck, i, hand_cards);

            free(rank_counts);
            return true;
        }
    }

    free(rank_counts);
    return false;
}

