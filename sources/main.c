#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

int main() {
    srand((unsigned int)time(NULL));
    play_game();
    return 0;
}