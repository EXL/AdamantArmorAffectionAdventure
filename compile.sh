#!/bin/bash
gcc -O3 *.c -DPC32 -lSDL -lSDL_mixer -lGL -lm -o release/game
echo All done?
cd release
./game
cd ..
