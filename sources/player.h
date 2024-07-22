#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"

#define NUM_PLAYERS 6
#define PLAYER_HAND_SIZE 2
#define INITIAL_CHIPS 1000

typedef struct {
    Card hand[PLAYER_HAND_SIZE];
    int chips;
    int current_bet;
    int is_folded;
    int is_all_in;
    const char* position;
    int vpip_count;
    int pfr_count;
    int hands_played;
} Player;

void initialize_players(Player** players);
void rotate_positions(int* button);
int count_active_players(Player* players);
void print_player_stats(Player* players);

#endif // PLAYER_H