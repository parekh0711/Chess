# Chess
Chess developed in C using X11 for GUI. Includes single player and two player modes
Representation of board is done using integer two dimensional array. 
main.c contains all functions for validating moves and detecting checks/checkmate and draws.
I have coded the engine using an algorithm I thought of based on Minimax. It thinks 5 moves ahead from any given function and evaluates every possible legal move.

## Compilation Instructions 

For dependencies: 
```
sudo apt-get update 
sudo apt-get install lesstif2-dev OR sudo apt-get install libmotif-dev
```

For compiling:
```
gcc engine.h engine.c main.c -lX11
./a.out
````

The program then accepts input for choice of mode and color.
