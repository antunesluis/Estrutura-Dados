#ifndef POKER_CLASSIFICATION_H
#define POKER_CLASSIFICATION_H

bool search_pair(ListCards* deck, ListCards* hand_cards);
bool search_two_pair(ListCards* deck, ListCards* hand_cards);
bool search_three_of_a_kind(ListCards* deck, ListCards* hand_cards);
bool search_straight(ListCards* deck, ListCards* hand_cards);

#endif  