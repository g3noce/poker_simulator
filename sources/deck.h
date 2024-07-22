#ifndef DECK_H
#define DECK_H

#include "card.h"
#include "player.h"

#define DECK_SIZE 52
#define COMMUNITY_CARDS 5

void initialize_deck(Card** deck);
void shuffle_deck(Card* deck);
void deal_hands(Card* deck, Player* players);
void deal_community_cards(Card* deck, Card* community_cards);

#endif // DECK_H