/*
 * mainAux.c
 *
 *  Created on: Aug 16, 2017
 *      Author: tala
 */

#include "mainAux.h"
#include "minimax.h"
#include "savedGames.h"



void setting_state(ChessGame * game){
	if(!game){
		printf("ERROR: null pointer in function setting_state in mainAux.c\n");fflush(stdout);
		return;
	}
	printSettingState();
	char user_input[MAX_SIZE];
	while(game->isInSetting){
		fgets(user_input,MAX_SIZE,stdin);
		Command* cmd = ParseLine(user_input);
		handle_command_setting_state(game, cmd);
	}//reach this point if user entered the command "start", this takes us to game state
	game_state(game);
}

void game_state(ChessGame* game){
	if(!game){
		printf("ERROR: null pointer in function game_state in mainAux.c\n");fflush(stdout);
		return;
	}
	game->shouldGoToNextTurn=false;
	if(GetMode(game)==GAME_MODE_2 || (GetMode(game)==GAME_MODE_1 && GetCurrentPlayer(game)==GetUserColor(game))){
		printBoard(game); fflush(stdout);
		printEnterYourMove(game->currentPlayer);
		char user_input[MAX_SIZE];
		while(!game->isInSetting && !game->shouldGoToNextTurn){
			fgets(user_input,MAX_SIZE,stdin);
			Command* cmd = ParseLine(user_input);
			handle_command_game_state(game, cmd);
			if(game->shouldGoToNextTurn){
				break;
			}
		}//reach here only if switched to settings state
		if(game->shouldGoToNextTurn){
			game_state(game);
		}
		if(game->isInSetting){
			setting_state(game);
		}
	}
	else{//computer's turn
		computer_play_console(game);
	}
}

void handle_command_setting_state(ChessGame* game, Command* cmd){
	if(!cmd){
		printf("ERROR: null pointer in function handle_command_setting_state in mainAux.c\n");fflush(stdout);
		return;
	}
	if (cmd->cmd==GAME_MODE){
		if(cmd->arg==1 || cmd->arg==2){
			SetMode(game, cmd->arg);
			printGameModeSet(cmd->arg);
		}
		else{
			printWrongGameMode();
		}
	}
	else if(cmd->cmd==DIFFICULTY){
		int diff=cmd->arg;
		if(game->gameMode==GAME_MODE_1){
			if( (0<diff && diff<=4) || (diff==5 && game->supported)){
				SetDifficulty(game, diff);
			}
			else{
				printDifficulty(diff, game->supported);
			}
		}
		else{
			printf("difficulty settings are available only in 1-player mode\n");fflush(stdout);
		}
	}
	else if(cmd->cmd==USER_COLOR){
		if(game->gameMode==GAME_MODE_1){
			if(cmd->arg==0 || cmd->arg==1){
				SetColor(game,cmd->arg);
			}
			else{
				printf("wrong user color: value should be either 0 or 1\n");fflush(stdout);
			}
		}
		else{
			printf("user_color settings are available only in 1-player mode\n");fflush(stdout);
		}

	}
	else if(cmd->cmd==LOAD){
		FILE_MSG loadRes= load (game, cmd->filepath);
		if (loadRes==FILE_SUCCESS){
			game->isInSetting=true;
		}
		if (loadRes==FILE_ERROR){
			game->isInSetting=true;
			printFileLoadError();
		}
	}
	else if(cmd->cmd==DEFAULT){
		if(!cmd->thereIsAnArg){
			defaultSettings(game);
		}
	}
	else if(cmd->cmd==PRINT_SETTING){
		if(!cmd->thereIsAnArg){
			printSettings(game->gameMode, game->gameDifficulty, game->currentPlayer);
			game->isInSetting=true;
		}
	}
	else if(cmd->cmd==QUIT){
		if(!cmd->thereIsAnArg){
			printExiting();
			destroyCommand(cmd);
			quitGame(game);

		}
	}
	else if(cmd->cmd==START){
		if(!cmd->thereIsAnArg){
			game->isInSetting=false;
		}
	}
	else{
		printf("invalid command in settings state - needs to be modified probably");fflush(stdout);
	}
	destroyCommand(cmd);
}

void handle_command_game_state(ChessGame* game, Command* cmd){
	if(!cmd){
		printf("ERROR: null pointer in function handle_command_game_state in mainAux.c\n");fflush(stdout);
		return;
	}
	if (cmd->cmd==MOVE){
		int fromX=cmd->fromX, fromY=cmd->fromY, toI=cmd->toI, toJ=cmd->toJ;
		destroyCommand(cmd);
		play(fromX,fromY,toI,toJ,game);
		return;
	}
	else if(cmd->cmd==GET_MOVES){
		if(GetDifficulty(game) > 2){
			printf("get_moves is supported only in difficulty level 1 and 2\n");fflush(stdout);
			game->shouldGoToNextTurn=false;
		}
		else{
			get_moves(game,cmd->fromX,cmd->fromY);
			game->shouldGoToNextTurn=false;
		}
	}
	else if(cmd->cmd==SAVE){
		FILE_MSG saveRes=consoleSave(game, cmd->filepath);
		if (saveRes==FILE_ERROR){
			printFileCreationError();
		}
		printEnterYourMove(game->currentPlayer);
	}
	else if(cmd->cmd==UNDO){
		if(!cmd->thereIsAnArg){
			game->shouldGoToNextTurn=false;
			if(game->gameMode==GAME_MODE_1){
				int user_color=GetUserColor(game);
				int computer_color= !user_color;
				int computer_last_x=game->movesHistory->talaMoves[0];
				int computer_last_y=game->movesHistory->talaMoves[1];
				int computer_last_i=game->movesHistory->talaMoves[2];
				int computer_last_j=game->movesHistory->talaMoves[3];
				int user_last_x=game->movesHistory->talaMoves[4];
				int user_last_y=game->movesHistory->talaMoves[5];
				int user_last_i=game->movesHistory->talaMoves[6];
				int user_last_j=game->movesHistory->talaMoves[7];

				GAME_MESSAGE un = undo_move(game);
				undo_move(game);
				if(un==NO_HISTORY){
					printEmptyHistory();
				}
				else{
					printBoard(game);
					printUndoneMoves(computer_color,computer_last_x,computer_last_y,computer_last_i,computer_last_j,
							user_color,user_last_x,user_last_y,user_last_i,user_last_j);
				}
				printEnterYourMove(user_color);

			}
			else{
				game->shouldGoToNextTurn=false;
				printUndoUnavailable();
				printEnterYourMove(game->currentPlayer);
			}
		}
		else{
			game->shouldGoToNextTurn=false;
			printEnterYourMove(game->currentPlayer);
		}
	}
	else if(cmd->cmd==RESET){
		if(!cmd->thereIsAnArg){
			reset(game);
		}
		else{
			printEnterYourMove(game->currentPlayer);
		}
	}
	else if(cmd->cmd==QUIT){
		game->shouldGoToNextTurn=false;
		printExiting();
		destroyCommand(cmd);
		quitGame(game);
	}
	else{
		game->shouldGoToNextTurn=false;
		printEnterYourMove(game->currentPlayer);
	}
	destroyCommand(cmd);
}


void computer_play_console(ChessGame * game){
	if(!game){
		printf("ERROR: null pointer in function computer_play_console in cmdparser.c\n");fflush(stdout);
		return;
	}
	ChessGame * copy=GameCopy(game);
	int diff=GetDifficulty(game);
	int* result= mybestmoveInt(copy,diff);
	char movedPiece=game->gameBoard[result[0]][result[1]];
	printComputerMove(movedPiece,result[0],result[1],result[2],result[3]);
	play(result[0],result[1],result[2],result[3],game);
	GameDestory(copy);
	free(result);
	game_state(game);
}


void printSettingState(){
	printf("Specify game setting or type 'start' to begin a game with the current setting:\n");
	fflush(stdout);
	return;
}

void printGameModeSet(int mode){
	if (mode==GAME_MODE_1){
		printf("Game mode is set to 1 player\n"); fflush(stdout);
	}
	if (mode==GAME_MODE_2){
		printf("Game mode is set to 2 players\n"); fflush(stdout);
	}
}

void printWrongGameMode(){
	printf("Wrong game mode\n"); fflush(stdout);
}

void printDifficulty(int dif, bool supported){ //call function if dif>=5
	if (dif==5 && supported==false){
		printf("Expert level not supported, please choose a value between 1 to 4:\n"); fflush(stdout);
	}
	if(dif<1 || dif>5) {
		printf("Wrong difficulty level. The value should be between 1 to 5\n"); fflush(stdout);
	}
}

void printSettings(int mode, int dif, int curr_player){
	printf("SETTINGS:\n"); fflush(stdout);
	if (mode==GAME_MODE_2){
		printf("GAME_MODE: 2\n"); fflush(stdout);
	}
	if (mode==GAME_MODE_1){
		printf("GAME_MODE: 1\n");
		printf("DIFFICULTY_LVL: %d\n",dif);
		if (curr_player==WHITE_PLAYER_SYMBOL){
			printf("USER_CLR: WHITE\n"); fflush(stdout);
		}
		else {
			printf("USER_CLR: BLACK\n"); fflush(stdout);
		}
	}
}

void printFileCreationError(){
	printf("File cannot be created or modified\n"); fflush(stdout);
}

void printUndoUnavailable(){
		printf("Undo command not available in 2 players mode\n"); fflush(stdout); //typo
}

void printEmptyHistory(){
	printf("Empty history, move cannot be undone\n"); fflush(stdout);
}


void printUndoneMoves(int playerX,int x, int y, int w, int z, int playerY, int i, int j, int m, int n){
	char Y=translateIntToChar(y);
	char Z=translateIntToChar(z);
	char J=translateIntToChar(j);
	char N=translateIntToChar(n);
	if (playerX==BLACK_PLAYER_SYMBOL){
		printf("Undo move for player black : <%d,%c> -> <%d,%c>\n",w+1,Z,x+1,Y); fflush(stdout);//tala added "+1"
		printf("Undo move for player white : <%d,%c> -> <%d,%c>\n",m+1,N,i+1,J); fflush(stdout);
	}
	if (playerY==BLACK_PLAYER_SYMBOL){
		printf("Undo move for player white : <%d,%c> -> <%d,%c>\n",w+1,Z,x+1,Y); fflush(stdout);
		printf("Undo move for player black : <%d,%c> -> <%d,%c>\n",m+1,N,i+1,J); fflush(stdout);
	}
}


void printComputerMove(char piece,int x, int y, int i, int j){
	char Y = translateIntToChar(y);
	char J = translateIntToChar(j);
	if (piece==WHITE_PAWN || piece==BLACK_PAWN){
		printf("Computer: move pawn at <%d,%c> to <%d,%c>\n",x+1,Y,i+1,J); fflush(stdout);
	}
	if (piece==WHITE_BISHOP || piece==BLACK_BISHOP){
		printf("Computer: move bishop at <%d,%c> to <%d,%c>\n",x+1,Y,i+1,J); fflush(stdout);
	}
	if (piece==WHITE_ROOK || piece==BLACK_ROOK){
		printf("Computer: move rook at <%d,%c> to <%d,%c>\n",x+1,Y,i+1,J); fflush(stdout);
	}
	if (piece==WHITE_KNIGHT || piece==BLACK_KNIGHT){
		printf("Computer: move knight at <%d,%c> to <%d,%c>\n",x+1,Y,i+1,J); fflush(stdout);
	}
	if (piece==WHITE_QUEEN || piece==BLACK_QUEEN){
		printf("Computer: move queen at <%d,%c> to <%d,%c>\n",x+1,Y,i+1,J); fflush(stdout);
	}
	if (piece==WHITE_KING || piece==BLACK_KING){
		printf("Computer: move king at <%d,%c> to <%d,%c>\n",x+1,Y,i+1,J); fflush(stdout);
	}
}



