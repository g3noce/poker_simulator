@echo off

REM Create obj directory if it doesn't exist
if not exist obj mkdir obj

REM Compile each .c file into a .o file in the obj directory
cd .\sources\
gcc -c main.c -o ../obj/main.o
gcc -c game.c -o ../obj/game.o
gcc -c player.c -o ../obj/player.o
gcc -c card.c -o ../obj/card.o
gcc -c deck.c -o ../obj/deck.o
gcc -c hand_evaluation.c -o ../obj/hand_evaluation.o
gcc -c betting.c -o ../obj/betting.o
gcc -c ui.c -o ../obj/ui.o
gcc -c utils.c -o ../obj/utils.o
gcc -c lookup_tables.c -o ../obj/lookup_tables.o
cd ..

REM Link all .o files into the final executable
gcc obj/*.o -o poker_simulation.exe

echo Compilation complete. Executable 'poker_simulation.exe' created.
.\poker_simulation.exe