#ifndef HAND_EVALUATION_H
#define HAND_EVALUATION_H

#include "card.h"
#include "player.h"

#define PLAYER_HAND_SIZE 2
#define COMMUNITY_CARDS 5
#define TOTAL_HAND_SIZE (PLAYER_HAND_SIZE + COMMUNITY_CARDS)

uint32_t hash_function(uint32_t x);
uint32_t eval5(const Card* hand);
uint32_t eval7(const Card* all_cards);
void determine_winner(Player* players, int pot, Card* community_cards);

#endif // HAND_EVALUATION_H