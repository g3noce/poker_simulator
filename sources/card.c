#include "card.h"
#include <stdio.h>

void print_card(Card card) {
    const char* color;
    switch (card.suit) {
        case 'h': color = RED; break;
        case 'd': color = CYAN; break;
        case 'c': color = YELLOW; break;
        case 's': color = GREEN; break;
        default: color = RESET;
    }
    printf("%s%c%c%s ", color, card.rank, card.suit, RESET);
}

void print_hand(Card* hand, int size) {
    for (int i = 0; i < size; i++) {
        print_card(hand[i]);
    }
}