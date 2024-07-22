#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "card.h"

void play_game();
void play_round(Player* players, int* button, Card* deck);

#endif // GAME_H