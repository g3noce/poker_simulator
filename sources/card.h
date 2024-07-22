#ifndef CARD_H
#define CARD_H

#define RED "\033[7;31m"
#define GREEN "\033[7;32m"
#define YELLOW "\033[7;33m"
#define BLUE "\033[7;34m"
#define MAGENTA "\033[7;35m"
#define CYAN "\033[7;36m"
#define RESET "\033[0m"

#include <stdint.h>

typedef struct {
    char rank;
    char suit;
    uint32_t value;
} Card;

void print_card(Card card);
void print_hand(Card* hand, int size);

#endif // CARD_H