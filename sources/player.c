#include "player.h"
#include "utils.h"
#include <stdio.h>

const char* POSITIONS[NUM_PLAYERS] = {"BTN", "SB", "BB", "UTG", "MP", "CO"};

void initialize_players(Player** players) {
    *players = (Player*)safe_malloc(NUM_PLAYERS * sizeof(Player));
    for (int i = 0; i < NUM_PLAYERS; i++) {
        (*players)[i].chips = INITIAL_CHIPS;
        (*players)[i].current_bet = 0;
        (*players)[i].is_folded = 0;
        (*players)[i].is_all_in = 0;
        (*players)[i].position = POSITIONS[i];
        (*players)[i].vpip_count = 0;
        (*players)[i].pfr_count = 0;
        (*players)[i].hands_played = 0;
    }
}

void rotate_positions(int* button) {
    *button = (*button + 1) % NUM_PLAYERS;
}

int count_active_players(Player* players) {
    int count = 0;
    for (int i = 0; i < NUM_PLAYERS; i++) {
        if (players[i].chips > 0) {
            count++;
        }
    }
    return count;
}

void print_player_stats(Player* players) {
    printf("\n--- Player Statistics ---\n");
    for (int i = 0; i < NUM_PLAYERS; i++) {
        float vpip = players[i].hands_played > 0 ? (float)players[i].vpip_count / players[i].hands_played * 100 : 0;
        float pfr = players[i].hands_played > 0 ? (float)players[i].pfr_count / players[i].hands_played * 100 : 0;
        printf("Player %d (%s): VPIP: %.2f%%, PFR: %.2f%%\n", i + 1, players[i].position, vpip, pfr);
    }
}