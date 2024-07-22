#include "deck.h"
#include "utils.h"
#include "lookup_tables.h"
#include <stdlib.h>
#include <string.h>

void initialize_deck(Card** deck) {
    *deck = (Card*)safe_malloc(DECK_SIZE * sizeof(Card));
    int index = 0;
    for (int i = 0; i < NUM_RANKS; i++) {
        for (int j = 0; j < NUM_SUITS; j++) {
            (*deck)[index].rank = RANK_SYMBOLS[i];
            (*deck)[index].suit = SUIT_SYMBOLS[j];
            (*deck)[index].value = RANKS[i] | SUITS[j] | PRIMES[i];
            index++;
        }
    }
}

void shuffle_deck(Card* deck) {
    for (int i = DECK_SIZE - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

void deal_hands(Card* deck, Player* players) {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        for (int j = 0; j < PLAYER_HAND_SIZE; j++) {
            players[i].hand[j] = deck[i * PLAYER_HAND_SIZE + j];
        }
    }
}

void deal_community_cards(Card* deck, Card* community_cards) {
    for (int i = 0; i < COMMUNITY_CARDS; i++) {
        community_cards[i] = deck[NUM_PLAYERS * PLAYER_HAND_SIZE + i];
    }
}