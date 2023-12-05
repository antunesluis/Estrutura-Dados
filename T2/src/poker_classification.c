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

int* create_rank_counts(ListCards* deck, int num_rank) {
    int* rank_counts = create_dynamic_array(num_rank);

    for (size_t i = 0; i < list_size(deck); i++) {
        Card* C = list_get_card(deck, i);
        int rank = get_rank(C);
        rank_counts[rank - 2]++;  // Ajuste para o enum começar em RANK_2
    }

    return rank_counts;
}

bool has_specific_rank_occurrences(int* rank_counts, int target_occurrences) {
    for (int i = 0; i < NUM_RANKS - 1; i++) {
        if (rank_counts[i] == target_occurrences) {
            return true;
        }
    }

    return false;
}

bool search_n_of_a_kind(ListCards* deck, int num_rank, int target_occurrences) {
    int* rank_counts = create_rank_counts(deck, num_rank);

    bool result = has_specific_rank_occurrences(rank_counts, target_occurrences);

    free(rank_counts);
    return result;
}

bool search_three_of_a_kind(ListCards* deck, int num_rank) {
    return search_n_of_a_kind(deck, num_rank, NUM_CARDS_FOR_3K);
}

bool search_two_pair(ListCards* deck, int num_rank) {
    int* rank_counts = create_rank_counts(deck, num_rank);

    if (has_specific_rank_occurrences(rank_counts, NUM_CARDS_FOR_PAIR)) {
        int pair_count = 0;

        for (int i = RANK_2; i <= NUM_RANKS; i++) {
            if (rank_counts[i] == NUM_CARDS_FOR_PAIR) {
                pair_count++;
            }
        }

        free(rank_counts);
        return pair_count == 2;
    }

    free(rank_counts);
    return false;
}

bool search_pair(ListCards* deck, int num_rank) {
    return search_n_of_a_kind(deck, num_rank, NUM_CARDS_FOR_PAIR);
}

