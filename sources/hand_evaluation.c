#include "hand_evaluation.h"
#include "lookup_tables.h"
#include <string.h>
#include <stdio.h>
#include <limits.h>

uint32_t hash_function(uint32_t x) {
    x += 0xe91aaa35;
    x ^= x >> 16;
    x += x << 8;
    x &= 0xffffffff;
    x ^= x >> 4;
    uint32_t b = (x >> 8) & 0x1ff;
    uint32_t a = (x + (x << 2)) >> 19;
    uint32_t r = (a ^ HASH_ADJUST[b]) & 0x1fff;
    return HASH_VALUES[r];
}

uint32_t eval5(const Card* hand) {
    uint32_t c1 = hand[0].value, c2 = hand[1].value, c3 = hand[2].value, c4 = hand[3].value, c5 = hand[4].value;
    uint32_t q = (c1 | c2 | c3 | c4 | c5) >> 16;

    if (0xf000 & c1 & c2 & c3 & c4 & c5) {
        return FLUSHES[q];
    }

    uint32_t s = UNIQUE_5[q];
    if (s) {
        return s;
    }

    uint32_t p = (c1 & 0xff) * (c2 & 0xff) * (c3 & 0xff) * (c4 & 0xff) * (c5 & 0xff);
    return hash_function(p);
}

uint32_t eval7(const Card* all_cards) {
    uint32_t min_score = UINT32_MAX;
    Card combination[5];
    for (int i = 0; i <= TOTAL_HAND_SIZE - 5; i++) {
        for (int j = i + 1; j <= TOTAL_HAND_SIZE - 4; j++) {
            for (int k = j + 1; k <= TOTAL_HAND_SIZE - 3; k++) {
                for (int l = k + 1; l <= TOTAL_HAND_SIZE - 2; l++) {
                    for (int m = l + 1; m <= TOTAL_HAND_SIZE - 1; m++) {
                        combination[0] = all_cards[i];
                        combination[1] = all_cards[j];
                        combination[2] = all_cards[k];
                        combination[3] = all_cards[l];
                        combination[4] = all_cards[m];

                        uint32_t score = eval5(combination);

                        if (score < min_score) {
                            min_score = score;
                        }
                    }
                }
            }
        }
    }
    return min_score;
}

void determine_winner(Player* players, int pot, Card* community_cards) {
    uint32_t best_score = UINT32_MAX;
    int winner_indices[NUM_PLAYERS];
    int num_winners = 0;

    for (int i = 0; i < NUM_PLAYERS; i++) {
        if (players[i].is_folded) continue;

        Card all_cards[TOTAL_HAND_SIZE];
        memcpy(all_cards, players[i].hand, PLAYER_HAND_SIZE * sizeof(Card));
        memcpy(all_cards + PLAYER_HAND_SIZE, community_cards, COMMUNITY_CARDS * sizeof(Card));

        uint32_t score = eval7(all_cards);

        printf("Player %d: ", i + 1);
        print_hand(players[i].hand, PLAYER_HAND_SIZE);
        printf(" | Best Hand Score = %u\n", score);

        if (score < best_score) {
            best_score = score;
            num_winners = 1;
            winner_indices[0] = i;
        } else if (score == best_score) {
            winner_indices[num_winners++] = i;
        }
    }

    if (num_winners > 0) {
        int split_pot = pot / num_winners;
        printf("Players with the best hand score (%u) split the pot of %d chips:\n", best_score, pot);
        for (int i = 0; i < num_winners; i++) {
            int winner = winner_indices[i];
            printf("Player %d wins %d chips!\n", winner + 1, split_pot);
            players[winner].chips += split_pot;
        }
    } else {
        printf("No winner for the pot.\n");
    }
}