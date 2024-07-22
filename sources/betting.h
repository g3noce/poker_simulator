#ifndef BETTING_H
#define BETTING_H

#include "player.h"

#define SMALL_BLIND 10
#define BIG_BLIND 20

typedef struct {
    int chips;
    int bet;
    int is_folded;
    int is_all_in;
    const char* position;
} PlayerInfo;

typedef struct {
    PlayerInfo players[NUM_PLAYERS];
    int pot_size;
    int current_bet;
    int big_blind;
    int button_index;
    int active_player_index;
    Card active_player_hand[2];
} PreflopInfo;

void preflop_betting_round(Player* players, int starting_player, int* pot, int* current_bet);
PreflopInfo gather_preflop_info(Player* players, int active_player_index, int pot, int current_bet, int big_blind);

#endif // BETTING_H