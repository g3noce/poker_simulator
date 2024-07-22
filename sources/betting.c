#include "betting.h"
#include "ui.h"
#include <string.h>
#include <stdio.h>

int get_button_index(Player* players) {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        if (strcmp(players[i].position, "BTN") == 0) {
            return i;
        }
    }
    return 0;
}

PreflopInfo gather_preflop_info(Player* players, int active_player_index, int pot, int current_bet, int big_blind) {
    PreflopInfo info;

    for (int i = 0; i < NUM_PLAYERS; i++) {
        info.players[i].chips = players[i].chips;
        info.players[i].bet = players[i].current_bet;
        info.players[i].is_folded = players[i].is_folded;
        info.players[i].is_all_in = players[i].is_all_in;
        info.players[i].position = players[i].position;
    }

    info.pot_size = pot;
    info.current_bet = current_bet;
    info.big_blind = big_blind;
    info.button_index = get_button_index(players);
    info.active_player_index = active_player_index;

    info.active_player_hand[0] = players[active_player_index].hand[0];
    info.active_player_hand[1] = players[active_player_index].hand[1];

    return info;
}

void preflop_betting_round(Player* players, int starting_player, int* pot, int* current_bet) {
    int active_players = NUM_PLAYERS;
    int players_checked_or_called = 0;
    int big_blind_index = (starting_player - 1 + NUM_PLAYERS) % NUM_PLAYERS;

    while (players_checked_or_called < active_players && active_players > 1) {
        for (int i = 0; i < NUM_PLAYERS; i++) {
            int player_index = (starting_player + i) % NUM_PLAYERS;

            if (players[player_index].is_folded || players[player_index].is_all_in) {
                continue;
            }

            PreflopInfo info = gather_preflop_info(players, player_index, *pot, *current_bet, BIG_BLIND);

            printf("Player %d (%s) (Chips: %d) - Current bet: %d - Pot: %d\n", 
                    player_index + 1, players[player_index].position, players[player_index].chips, players[player_index].current_bet, *pot);
            print_hand(players[player_index].hand, PLAYER_HAND_SIZE);
            printf("\nOptions: 0-Fold, 1-Call/Check, 2-Raise\n");

            int choice = get_valid_choice(0, 2);
            switch (choice) {
                case 0: // Fold
                    players[player_index].is_folded = 1;
                    active_players--;
                    printf("Player %d %sfolds%s.\n\n", player_index + 1, RED, RESET);
                    break;
                case 1: // Call/Check
                    {
                        int call_amount = *current_bet - players[player_index].current_bet;
                        if (call_amount > 0 || player_index != big_blind_index) {
                            players[player_index].vpip_count++;
                        }
                        if (call_amount > players[player_index].chips) {
                            call_amount = players[player_index].chips;
                            players[player_index].is_all_in = 1;
                            printf("Player %d is all-in!\n", player_index + 1);
                        }
                        players[player_index].chips -= call_amount;
                        *pot += call_amount;
                        players[player_index].current_bet += call_amount;
                        printf("Player %d %scalls/checks%s for : %d\n\n", player_index + 1, GREEN, RESET, call_amount);
                        players_checked_or_called++;
                    }
                    break;
                case 2: // Raise
                    {
                        players[player_index].vpip_count++;
                        players[player_index].pfr_count++;
                        int min_raise = *current_bet + (*current_bet - players[player_index].current_bet);
                        if (min_raise < BIG_BLIND) min_raise = BIG_BLIND;
                        printf("Enter raise amount (minimum %d): ", min_raise);
                        int raise_amount = get_valid_choice(min_raise, players[player_index].chips);

                        if (raise_amount > players[player_index].chips) {
                            raise_amount = players[player_index].chips;
                            players[player_index].is_all_in = 1;
                            printf("Player %d is all-in!\n", player_index + 1);
                        }

                        int total_bet = players[player_index].current_bet + raise_amount;
                        players[player_index].chips -= raise_amount;
                        *pot += raise_amount;
                        players[player_index].current_bet = total_bet;
                        
                        printf("Player %d %sraises%s to %d.\n\n", player_index + 1, YELLOW, RESET, total_bet);
                        
                        if (total_bet > *current_bet) {
                            *current_bet = total_bet;
                            players_checked_or_called = 1;
                        } else {
                            players_checked_or_called++;
                        }
                    }
                    break;
            }

            if (players_checked_or_called >= active_players || active_players <= 1) {
                return;
            }
        }
    }
}