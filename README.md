This is a chess game with GUI and console mode. The players can be two humans playing against each other or one human against the computer. To run the game, download the folder or clone the repository to your computer. run the "make" command in terminal. The executable for the program will be named “𝑐ℎ𝑒𝑠𝑠𝑝𝑟𝑜𝑔”. The graphical mode is specified as a command line argument:
./chessprog -c – will start the program in console mode.
./ chessprog -g – will start the program in GUI mode.
./ chessprog – will execute the program; with the default execution mode - console

when you run the executable first thing you'll see is the settings. you have to choose the following:
- The game mode: the game has two operating modes, either 1 player or 2 players mode (the modes are represented by 1 or 2 respectively). In a '1-player' mode, the user plays against an AI opponent. In a '2-player' mode the game is played with two different opponents. The default value is 1.
- The difficulty level of the game: If the game is operating in a '1-player' mode, then there are 4 difficulty levels; 1, 2, 3 and 4. These numbers represent the following levels: noob, easy, moderate and hard. To get bonus, you need to implement level 5 which represents an expert level. The default value: 2.
- User color: in a '1-player' mode, the user may specify her color. The color can be either black or white and in console mode these colors are represented by 0 and 1 (0 represents black and 1 represents white). The default value: 1


The AI used in the project is the minimax algorithm whose depth is defined in the difficulty level. Thus in difficulty 3, the depth of the minimax tree is 3 as well. Also pruning is added to the algorithm for more efficiency.
