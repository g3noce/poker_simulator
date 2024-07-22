#include "game.h"
#include "deck.h"
#include "betting.h"
#include "hand_evaluation.h"
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>

void play_game() {
    Card* deck;
    Player* players;
    int button = 0;

    initialize_deck(&deck);
    initialize_players(&players);

    while (count_active_players(players) > 5) {
        play_round(players, &button, deck);

        printf("\n--- Chip Counts ---\n");
        for (int i = 0; i < NUM_PLAYERS; i++) {
            printf("Player %d (%s): %d chips\n", i + 1, players[i].position, players[i].chips);
        }

        print_player_stats(players);

        printf("\nPress Enter to continue to the next round...");
        while (getchar() != '\n');
    }

    // Find the winner
    for (int i = 0; i < NUM_PLAYERS; i++) {
        if (players[i].chips > 0) {
            printf("\nPlayer %d (%s) wins the game with %d chips!\n", i + 1, players[i].position, players[i].chips);
            break;
        }
    }

    // Free allocated memory
    free(deck);
    free(players);
}

void play_round(Player* players, int* button, Card* deck) {
    int pot = 0;
    Card community_cards[COMMUNITY_CARDS];

    // Reset player states and increment hands played
    for (int i = 0; i < NUM_PLAYERS; i++) {
        players[i].current_bet = 0;
        players[i].is_folded = 0;
        players[i].is_all_in = 0;
        players[i].hands_played++;
    }

    shuffle_deck(deck);
    deal_hands(deck, players);

    int small_blind = (*button + 1) % NUM_PLAYERS;
    int big_blind = (*button + 2) % NUM_PLAYERS;
    
    // Post blinds
    players[small_blind].chips -= SMALL_BLIND;
    players[small_blind].current_bet = SMALL_BLIND;
    players[big_blind].chips -= BIG_BLIND;
    players[big_blind].current_bet = BIG_BLIND;
    pot = SMALL_BLIND + BIG_BLIND;

    printf("\n--- New Round ---\n");
    printf("Button is Player %d (%s)\n", *button + 1, players[*button].position);
    printf("Small Blind: Player %d (%s) - %d chips\n", small_blind + 1, players[small_blind].position, SMALL_BLIND);
    printf("Big Blind: Player %d (%s) - %d chips\n", big_blind + 1, players[big_blind].position, BIG_BLIND);

    // Preflop betting round
    printf("\n--- Preflop Betting Round ---\n");
    int current_bet = BIG_BLIND;
    preflop_betting_round(players, (big_blind + 1) % NUM_PLAYERS, &pot, &current_bet);

    // Deal community cards
    printf("\n--- Community Cards ---\n");
    deal_community_cards(deck, community_cards);
    for (int i = 0; i < COMMUNITY_CARDS; i++) {
        print_card(community_cards[i]);
    }
    printf("\n");

    // Showdown
    printf("\n--- Showdown ---\n");
    determine_winner(players, pot, community_cards);

    // Rotate button
    rotate_positions(button);
}