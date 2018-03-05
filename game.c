/*
 * game.c
 *
 *  Created on: Aug 14, 2017
 *      Author: tala
 */

#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

INVALID_MOVE_MSG isValidMove(ChessGame* src,int fromX, int fromY, int toI, int toJ){
	if(!src){
		printf("ERROR: null pointer in function isValidMove\n");
		return ILLEGAL_MOVE; //will never be reached
	}
	char piece = src->gameBoard[fromX][fromY];
	INVALID_MOVE_MSG msg;
	if(fromX<0 || fromX>7 || fromY<0 || fromY>7 || toI<0 || toI>7 || toJ<0 || toJ>7){
		return INVALID_POSITION;
	}
	if (piece==EMPTY_ENTRY || isOppositeColor(piece,src->currentPlayer) ){
		return NO_PIECE_IN_SOURCE;
	}

	if(src->currentPlayer==WHITE_PLAYER_SYMBOL){
		switch(piece){
			case WHITE_PAWN:
				msg = isValidPawn(src->gameBoard,fromX,fromY,toI,toJ,WHITE_PLAYER_SYMBOL);
				break;
			case WHITE_BISHOP:
				msg = isValidBishop(src->gameBoard,fromX,fromY,toI,toJ,WHITE_PLAYER_SYMBOL);
				break;
			case WHITE_ROOK:
				msg = isValidRook(src->gameBoard,fromX,fromY,toI,toJ,WHITE_PLAYER_SYMBOL);
				break;
			case WHITE_KNIGHT:
				msg = isValidKnight(src->gameBoard,fromX,fromY,toI,toJ,WHITE_PLAYER_SYMBOL);
				break;
			case WHITE_QUEEN:
				msg = isValidQueen(src->gameBoard,fromX,fromY,toI,toJ,WHITE_PLAYER_SYMBOL);
				break;
			case WHITE_KING:
				msg = isValidKing(src->gameBoard,fromX,fromY,toI,toJ,WHITE_PLAYER_SYMBOL);
				break;
			}
	}
	else{

		switch(piece){
			case BLACK_PAWN:
				msg = isValidPawn(src->gameBoard,fromX,fromY,toI,toJ,BLACK_PLAYER_SYMBOL);
				break;
			case BLACK_BISHOP:
				msg = isValidBishop(src->gameBoard,fromX,fromY,toI,toJ,BLACK_PLAYER_SYMBOL);
				break;
			case BLACK_ROOK:
				msg = isValidRook(src->gameBoard,fromX,fromY,toI,toJ,BLACK_PLAYER_SYMBOL);
				break;
			case BLACK_KNIGHT:
				msg = isValidKnight(src->gameBoard,fromX,fromY,toI,toJ,BLACK_PLAYER_SYMBOL);
				break;
			case BLACK_QUEEN:
				msg = isValidQueen(src->gameBoard,fromX,fromY,toI,toJ,BLACK_PLAYER_SYMBOL);
				break;
			case BLACK_KING:
				msg = isValidKing(src->gameBoard,fromX,fromY,toI,toJ,BLACK_PLAYER_SYMBOL);
				break;
		}
	}
	return msg;
}

INVALID_MOVE_MSG isValidPawn(char (*gameBoard)[8] ,int fromX,int fromY,int toI,int toJ,char curr_player){
	if (curr_player==WHITE_PLAYER_SYMBOL){
		if (toI <= fromX){
			return ILLEGAL_MOVE;
		}
		if(fromY!=toJ){
			if(abs(fromY-toJ)>1){
				return ILLEGAL_MOVE;
			}
			//if this point is reached, then j=y+1 || j=y-1 which is potentially ok
			if((toI-fromX)!=1){
				return ILLEGAL_MOVE;
			}
			//if this point is reached, then (j=y+1 || j=y-1) && (toI=fromX+1) : about to capture
			if (gameBoard[toI][toJ]!=EMPTY_ENTRY){ //is it trying to capture?
				if (!(isOppositeColor(gameBoard[toI][toJ],WHITE_PLAYER_SYMBOL)))
					return ILLEGAL_MOVE;
				return VALID_MOVE;
			}
			else //trying to capture an empty spot
				return ILLEGAL_MOVE;
		}
		//at this point we know toJ==fromY
		if (fromX==1){ //if pawn is at starting position
			if(toI-fromX > 2){
				return ILLEGAL_MOVE;
			}
			else if (toI-fromX == 2){
				if (gameBoard[fromX+1][fromY]==EMPTY_ENTRY && gameBoard[fromX+2][fromY]==EMPTY_ENTRY)
					return VALID_MOVE;
				return ILLEGAL_MOVE;
			}
			else{
				if (gameBoard[fromX+1][fromY]==EMPTY_ENTRY)
					return VALID_MOVE;
				return ILLEGAL_MOVE;
			}
		} //reach if not at starting position
		else{
			if (-fromX+toI==1 && gameBoard[fromX+1][fromY]==EMPTY_ENTRY)
				return VALID_MOVE;
			return ILLEGAL_MOVE;
		}
	}
	else {
		if (toI >= fromX){
			return ILLEGAL_MOVE;
		}
		if(fromY!=toJ){
			if(abs(fromY-toJ)>1){
				return ILLEGAL_MOVE;
			}
			//if this point is reached, then j=y+1 || j=y-1 which is potentially ok
			if((fromX-toI)!=1){
				return ILLEGAL_MOVE;
			}
			//if this point is reached, then (j=y+1 || j=y-1) && (toI=fromX+1) : about to capture
			if (gameBoard[toI][toJ]!=EMPTY_ENTRY){ //is it trying to capture?
				if (!(isOppositeColor(gameBoard[toI][toJ],BLACK_PLAYER_SYMBOL)))
					return ILLEGAL_MOVE;
				return VALID_MOVE;
			}
			else //trying to capture an empty spot
				return ILLEGAL_MOVE;
		}
		//at this point we know toJ==fromY
		if (fromX==6){ //if pawn is at starting position
			if(fromX-toI > 2){
				return ILLEGAL_MOVE;
			}
			else if (fromX-toI == 2){
				if (gameBoard[fromX-1][fromY]==EMPTY_ENTRY && gameBoard[fromX-2][fromY]==EMPTY_ENTRY)
					return VALID_MOVE;
				return ILLEGAL_MOVE;
			}
			else{
				if (gameBoard[fromX-1][fromY]==EMPTY_ENTRY)
					return VALID_MOVE;
				return ILLEGAL_MOVE;
			}
		} //reach if not at starting position
		else{
			if (fromX-toI==1 && gameBoard[fromX-1][fromY]==EMPTY_ENTRY)
				return VALID_MOVE;
			return ILLEGAL_MOVE;
		}
	}
}

INVALID_MOVE_MSG isValidBishop(char (*gameBoard)[8],int fromX,int fromY,int toI,int toJ,char curr_player){
	if((fromY-toJ)==0 || (fromX-toI)==0){
		return ILLEGAL_MOVE;
	}
	if((fromY-toJ)!=(fromX-toI) && (fromY-toJ)!= -(fromX-toI)) //changed this in 21.9
		return ILLEGAL_MOVE;
	if (gameBoard[toI][toJ]!=EMPTY_ENTRY){
		if (!isOppositeColor(gameBoard[toI][toJ],curr_player))
			return ILLEGAL_MOVE;
	}
	int minY = (fromY>toJ) ? toJ:fromY ;
	int maxY = fromY+toJ-minY;
	int minX = (fromX>toI) ? toI:fromX ;
	int maxX = fromX+toI-minX;
	if((fromX-toI)==(fromY-toJ)){
		for(minY+=1,minX+=1 ; minX<maxX&&minY<maxY; minY++,minX++){
			if(gameBoard[minX][minY]!=EMPTY_ENTRY)
				return ILLEGAL_MOVE;
		}
		return VALID_MOVE;
	}
	if((fromX-toI)== -(fromY-toJ)){
		for(minY+=1,maxX-=1; (minY<maxY)&&(minX<maxX); maxX--,minY++){
			if(gameBoard[maxX][minY]!=EMPTY_ENTRY)
				return ILLEGAL_MOVE;
		}
		return VALID_MOVE;
	}
	return ILLEGAL_MOVE;
}
INVALID_MOVE_MSG isValidRook(char (*gameBoard)[8],int fromX,int fromY,int toI,int toJ,char curr_player){
	if (!((fromX==toI)||(fromY==toJ))){
		return ILLEGAL_MOVE;
	}
	if (gameBoard[toI][toJ]!=EMPTY_ENTRY){
		if (!isOppositeColor(gameBoard[toI][toJ],curr_player))
			return ILLEGAL_MOVE;
	}

	int minY = (fromY>toJ) ? toJ:fromY ;
	int maxY = fromY+toJ-minY;
	int minX = (fromX>toI) ? toI:fromX ;
	int maxX = fromX+toI-minX;
	if (fromX==toI) //if it's moving horizontally
	{
		for (minY+=1;minY<maxY;minY++){
			if (gameBoard[fromX][minY]!=EMPTY_ENTRY)
				return ILLEGAL_MOVE;
		}
		return VALID_MOVE;
	}
	else { //moving vertically
		for (minX+=1;minX<maxX;minX++){
			if (gameBoard[minX][fromY]!=EMPTY_ENTRY)
				return ILLEGAL_MOVE;
		}
		return VALID_MOVE;
	}
	return ILLEGAL_MOVE;

}
INVALID_MOVE_MSG isValidKnight(char (*gameBoard)[8],int fromX,int fromY,int toI,int toJ,char curr_player){
	if (gameBoard[toI][toJ]!=EMPTY_ENTRY){
		if (!isOppositeColor(gameBoard[toI][toJ],curr_player))
			return ILLEGAL_MOVE;
	}
	if (((fromY-toJ==1)&&(toI-fromX==2))||((fromY-toJ==1)&&(fromX-toI==2))||
		((toJ-fromY==1)&&(toI-fromX==2))||((toJ-fromY==1)&&(fromX-toI==2))||
		((fromY-toJ==2)&&(toI-fromX==1))||((fromY-toJ==2)&&(fromX-toI==1))||
		((toJ-fromY==2)&&(toI-fromX==1))||((toJ-fromY==2)&&(fromX-toI==1)))
		return VALID_MOVE;
	return ILLEGAL_MOVE;
}
INVALID_MOVE_MSG isValidKing(char (*gameBoard)[8],int fromX,int fromY,int toI,int toJ,char curr_player){
	if (gameBoard[toI][toJ]!=EMPTY_ENTRY){
		if (!isOppositeColor(gameBoard[toI][toJ],curr_player))
			return ILLEGAL_MOVE;
	}
	if(toI==fromX){
		if(toJ==fromY+1 || toJ==fromY-1){
			return VALID_MOVE;
		}
		return ILLEGAL_MOVE;
	}//reach this point if x!=i
	if(abs(toI-fromX)<=1){
		if(abs(fromY-toJ)<=1){
			return VALID_MOVE;
		}
		return ILLEGAL_MOVE;
	}
	return ILLEGAL_MOVE;
}

INVALID_MOVE_MSG isValidQueen(char (*gameBoard)[8],int fromX,int fromY,int toI,int toJ,char curr_player){
	if (isValidRook(gameBoard,fromX,fromY,toI,toJ,curr_player)!=VALID_MOVE && isValidBishop(gameBoard,fromX,fromY,toI,toJ,curr_player)!=VALID_MOVE)
		return ILLEGAL_MOVE;
	return VALID_MOVE;
}

bool isOppositeColor(char piece,char curr_player){
	if (curr_player==WHITE_PLAYER_SYMBOL){
		// make sure piece is black
		if (piece==BLACK_PAWN || piece==BLACK_BISHOP || piece==BLACK_ROOK ||
			piece==BLACK_QUEEN || piece==BLACK_KING || piece==BLACK_KNIGHT)
			return true;
	}
	else{
		if (piece==WHITE_PAWN || piece==WHITE_BISHOP || piece==WHITE_ROOK ||
			piece==WHITE_QUEEN || piece==WHITE_KING || piece==WHITE_KNIGHT)
			return true;
	}
	return false;
}

void play(int fromX,int fromY,int toI,int toJ,ChessGame* src){
	if(!src){
		printf("ERROR: null pointer in function play\n");
		return;
	}
	INVALID_MOVE_MSG move_msg= isValidMove(src,fromX,fromY,toI,toJ);
	if(move_msg==VALID_MOVE){
		if(did_I_put_myself_In_Check(src,fromX,fromY,toI,toJ)){
			move_msg=ILLEGAL_MOVE;
		}
	}
	if(move_msg==INVALID_POSITION){
		printInvalidPosition();
		printEnterYourMove(src->currentPlayer);
	}
	if(move_msg==NO_PIECE_IN_SOURCE){
		printNoPieceContained();
		printEnterYourMove(src->currentPlayer);
	}
	if(move_msg==ILLEGAL_MOVE){
		printIllegalMove();
		printEnterYourMove(src->currentPlayer);
	}
	if(move_msg==VALID_MOVE){
		RESULT_MSG msg;
		if((GetMode(src)==GAME_MODE_1 && GetCurrentPlayer(src)==GetUserColor(src)) || GetMode(src)==GAME_MODE_2){
			msg=SetMove(src,fromX,fromY,toI,toJ);
		}
		if(GetMode(src)==GAME_MODE_1 && GetCurrentPlayer(src)!=GetUserColor(src)){//if AI's turn
			msg=SetMove(src,fromX,fromY,toI,toJ);
		}
		if(msg==CHECKMATE){
			printCheckmate(src->currentPlayer);
			quitGame(src);
		}
		if(msg==TIE){
			if(GetCurrentPlayer(src)==GetUserColor(src)){ //if user is the one who made the tie
				printTieByPlayer();
			}
			else{ //if computer is the one who made the tie
				printTieByComputer();
			}
			quitGame(src);
		}
		if(msg==CHECK){
			if((GetMode(src)==1 && GetCurrentPlayer(src)==GetUserColor(src))){ //if user is the one checking the computer
				printCheckByPlayer(!GetUserColor(src));
			}
			else if(GetMode(src)==1 && GetCurrentPlayer(src)!=GetUserColor(src)){ //if computer is the one checking the user
				printCheckByComputer(src);
			}
			else if(GetMode(src)==2){
				printCheckByPlayer(!GetCurrentPlayer(src)); //threatened is the one who is not currently playing
			}
			ChangeCurrentPlayer(src);
			src->shouldGoToNextTurn=1;
		}
		if(msg==ELSE){
			ChangeCurrentPlayer(src);
			src->shouldGoToNextTurn=1;
		}
	}
}

RESULT_MSG SetMove(ChessGame * src, int fromX, int fromY, int toI, int toJ){
	if(!src){
		printf("ERROR: null pointer in function SetMove\n");
		return ELSE; //will never happen because src will be checked before reaching this function.
	}
	src->undoCountPerTurn=0; //reset counter of undo commands because now it's a new turn
	char piece = src->gameBoard[fromX][fromY];
	char pieceInDestination = src->gameBoard[toI][toJ];
	src->gameBoard[fromX][fromY] = EMPTY_ENTRY;
	src->gameBoard[toI][toJ] = piece;
	MovesHistoryUpdate(src,fromX,fromY,toI,toJ);
	PlayerDestinataionUpdate(src,pieceInDestination);
	return result_of_current_move(src);
}



bool Simple_SetMove(ChessGame * src, int fromX, int fromY, int toI, int toJ){
	if(!src){
		printf("ERROR: null pointer in function Simple_SetMove\n");
		return ELSE; //will never happen because src will be checked before reaching this function.
	}
	src->undoCountPerTurn=0; //reset counter of undo commands because now it's a new turn
	char piece = src->gameBoard[fromX][fromY];
	char pieceInDestination = src->gameBoard[toI][toJ];
	src->gameBoard[fromX][fromY] = EMPTY_ENTRY;
	src->gameBoard[toI][toJ] = piece;
	MovesHistoryUpdate(src,fromX,fromY,toI,toJ);
	PlayerDestinataionUpdate(src,pieceInDestination);

	int oppKingX=-1,oppKingY=-1,myX=-1,myY=-1;
	find_opponent_king(src,&oppKingY,&oppKingY);
	if(isInCheckMate(src,myX,myY,oppKingX,oppKingY)){
		return true;
	}
	return false;
}
/**
 * this function is no longer in use, please don't grade it.
 */
void pawn_promotion(ChessGame* src,char piece,int toI, int toJ){
	char * user_input=(char*)malloc(sizeof(char)*MAX_SIZE);
	if(!user_input){
		//handle later
	}
	while(true){
		printPawnPromotion_player();
		fgets(user_input,MAX_SIZE,stdin);
		char * strCopy = (char*)malloc(sizeof(char)*strlen(user_input)+1);
		if(!strCopy){
			//handle later
		}
		strcpy(strCopy,user_input);
		char * pch;
		pch = strtok (strCopy," \n\t\r");
		char * CopyPch = (char*)malloc(sizeof(char)*strlen(pch));
		if(!CopyPch){
			//handle later
		}
		strcpy(CopyPch,pch);
		pch = strtok (NULL, " \n\t\r");
		if(pch!='\0'){ //the user entered another argument after blank characters
			printInvalidTypePawnPromotion();
			continue; //to next iteration
		}
		if(strcmp(CopyPch,"queen")==0){
			if(piece==WHITE_PAWN)src->gameBoard[toI][toJ] = WHITE_QUEEN;
			if(piece==BLACK_PAWN)src->gameBoard[toI][toJ] = BLACK_QUEEN;
			break;
		}
		if(strcmp(CopyPch,"knight")==0){
			if(piece==WHITE_PAWN)src->gameBoard[toI][toJ] = WHITE_KNIGHT;
			if(piece==BLACK_PAWN)src->gameBoard[toI][toJ] = BLACK_KNIGHT;
			break;
		}
		if(strcmp(CopyPch,"rook")==0){
			if(piece==WHITE_PAWN)src->gameBoard[toI][toJ] = WHITE_ROOK;
			if(piece==BLACK_PAWN)src->gameBoard[toI][toJ] = BLACK_ROOK;
			break;
		}
		if(strcmp(CopyPch,"bishop")==0){
			if(piece==WHITE_PAWN)src->gameBoard[toI][toJ] = WHITE_BISHOP;
			if(piece==BLACK_PAWN)src->gameBoard[toI][toJ] = BLACK_BISHOP;
			break;
		}
		if(strcmp(CopyPch,"pawn")==0){
			if(piece==WHITE_PAWN)src->gameBoard[toI][toJ] = WHITE_PAWN;
			if(piece==BLACK_PAWN)src->gameBoard[toI][toJ] = BLACK_PAWN;
			break;
		}
		printInvalidTypePawnPromotion();
		free(CopyPch);
		free(strCopy);
	}
	free(user_input);
}


RESULT_MSG result_of_current_move(ChessGame * src){
	if(!src){
		printf("ERROR: null pointer in function result_of_current_move\n");fflush(stdout);
		return ELSE;
	}
	int kingX=-1,kingY=-1;
	int dangerousPieceX=-1,dangerousPieceY=-1;
	find_opponent_king(src,&kingX, &kingY);
	if(did_I_put_Opponent_In_Check(src,kingX,kingY, &dangerousPieceX, &dangerousPieceY)){
		if(isInCheckMate(src, dangerousPieceX, dangerousPieceY, kingX, kingY)){
			return CHECKMATE;
		}
		return CHECK;
	}
	if(isItATie(src,kingX,kingY)){
		return TIE;
	}
	return ELSE;
}


bool did_I_put_Opponent_In_Check(ChessGame * src,int oppkingX, int oppkingY, int *ptrToDangerousX, int *ptrToDangerousY){
	if(!src){
		printf("ERROR: null pointer in function did_I_put_Opponent_In_Check\n");fflush(stdout);
		return false;
	}
	char curr_piece;
	for(int i=0; i<ROWS; i++){
		for(int j=0; j<COLUMNS; j++){
			curr_piece=src->gameBoard[i][j];
			//go over all current player's pieces and find if one of them can move to where the opposite king is!
			//if such a piece is found then this is a check
			if(!isOppositeColor(curr_piece,src->currentPlayer) && curr_piece!=EMPTY_ENTRY){ //if piece belongs to current player
				if(isValidMove(src,i,j,oppkingX,oppkingY)==VALID_MOVE){ //if my piece at i,j can attack the opposite king
					if(!did_I_put_myself_In_Check(src,i,j,oppkingX,oppkingY)){
						*ptrToDangerousX=i;
						*ptrToDangerousY=j;
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool did_I_put_myself_In_Check(ChessGame * src, int fromX, int fromY, int toI, int toJ){
	if(!src){
		printf("ERROR: null pointer in function did_I_put_myself_In_Check\n");fflush(stdout);
		return false;
	}
	ChessGame * copy = GameCopy(src);
	Simple_SetMove(copy, fromX,fromY,toI,toJ);
	int mykingX, mykingY;
	char curr_piece;
	find_my_king(copy,&mykingX,&mykingY);
	ChangeCurrentPlayer(copy); //current player set to opponent
	for(int i=0; i<ROWS; i++){
		for(int j=0; j<COLUMNS; j++){
			curr_piece=copy->gameBoard[i][j];
			//go over all opponent player's pieces and find if one of them can move to where my king is!
			if(isOppositeColor(curr_piece,src->currentPlayer)){ //if piece belongs to opponent player
				if(isValidMove(copy,i,j,mykingX,mykingY)==VALID_MOVE){ //if my piece at i,j can attack the opposite king
					GameDestory(copy);
					return true;
				}
			}
		}
	}
	GameDestory(copy);
	return false;
}


bool isInCheckMate(ChessGame * src, int dangerousPieceX, int dangerousPieceY, int kingX, int kingY){
	if(!src){
		printf("ERROR: null pointer in function isInCheckMate\n");fflush(stdout);
		return false;
	}
	if(kingCanEscape(src,kingX,kingY)
		|| canBlockCheck(src,dangerousPieceX,dangerousPieceY,kingX,kingY)
		|| canCaptureCheckingPiece(src,dangerousPieceX,dangerousPieceY)){
		return false;
	}
	return true;
}

bool kingCanEscape(ChessGame * src, int kingX, int kingY){
	if(!src){
		printf("ERROR: null pointer in function kingCanEscape\n");fflush(stdout);
		return false;
	}
	ChessGame * copy=GameCopy(src); //hypothetic game
	ChangeCurrentPlayer(copy); //set the player to be the one in danger
	for(int i=kingX-1; i<=kingX+1; i++){
		for (int j=kingY-1; j<=kingY+1; j++){
			if(isValidMove(copy,kingX,kingY,i,j)==VALID_MOVE){
				if(!did_I_put_myself_In_Check(copy,kingX,kingY,i,j)){
					GameDestory(copy);
					return true;
				}
			}
		}
	}
	GameDestory(copy);
	return false;
}

bool canCaptureCheckingPiece(ChessGame * src, int dangerousPieceX, int dangerousPieceY){
	if(!src){
		printf("ERROR: null pointer in function canCaptureCheckingPiece\n");fflush(stdout);
		return false;
	}
	ChessGame * copy=GameCopy(src);
	ChangeCurrentPlayer(copy); //set player in copy to the the player under check (in danger)
	for(int i=0; i<ROWS;i++){
		for(int j=0; j<COLUMNS; j++){
			if( isValidMove(copy,i,j,dangerousPieceX,dangerousPieceY)==VALID_MOVE && !did_I_put_myself_In_Check(copy,i,j,dangerousPieceX,dangerousPieceY)){
				GameDestory(copy);
				return true;
			}
		}
	}
	GameDestory(copy);
	return false;
}

/*
 * helper function for function canBlockCheck
 */
bool canBlockBishop(ChessGame * copy,int fromX,int fromY,int toI, int toJ, int minX, int minY, int maxX, int maxY){
	if(!copy){
		printf("ERROR: null pointer in function canBlockBishop\n");fflush(stdout);
		return false;
	}
	if((fromX-toI)==(fromY-toJ)){
		for(minY+=1,minX+=1 ; minX<maxX&&minY<maxY; minY++,minX++){
			if(can_victim_block_threat(copy,minX,minY)){
				return true;
			}
		}
	}
	else if((fromX-toI)== -(fromY-toJ)){
		for(minY+=1,maxX-=1; (minY<maxY)&&(minX<maxX); maxX--,minY++){
			if(can_victim_block_threat(copy,maxX,minY)){
				return true;
			}
		}
	}
	GameDestory(copy);
	return false;
}


/*
 * helper function for function canBlockCheck
 */
bool canBlockRook(ChessGame * copy,int fromX,int toI, int minX, int minY, int maxX, int maxY){
	if(!copy){
		printf("ERROR: null pointer in function canBlockRook\n");fflush(stdout);
		return false;
	}
	if (fromX==toI){ //if it's moving horizontally
		for (minY+=1;minY<maxY;minY++){
			if(can_victim_block_threat(copy,minX,minY)){
				return true;
			}
		}
	}
	else { //moving vertically
		for (minX+=1;minX<maxX;minX++){
			if(can_victim_block_threat(copy,minX,minY)){
				return true;
			}
		}
	}
	GameDestory(copy);
	return false;
}

bool canBlockCheck(ChessGame * src, int dangerousPieceX, int dangerousPieceY, int kingX, int kingY){
	if(!src){
		printf("ERROR: null pointer in function canBlockCheck\n");fflush(stdout);
		return false;
	}
	ChessGame * copy=GameCopy(src);
	ChangeCurrentPlayer(copy); //current player in copy now is the one in danger!
	char dangerous_piece=copy->gameBoard[dangerousPieceX][dangerousPieceY];
	int fromX=dangerousPieceX, fromY=dangerousPieceY;
	int toI=kingX, toJ=kingY;
	int minY = (fromY>toJ) ? toJ:fromY ;
	int maxY = fromY+toJ-minY;
	int minX = (fromX>toI) ? toI:fromX ;
	int maxX = fromX+toI-minX;
	if(dangerous_piece==WHITE_BISHOP || dangerous_piece==BLACK_BISHOP){
		return canBlockBishop(copy,fromX,fromY,toI,toJ,minX,minY,maxX,maxY);
	} //end of is dangerous piece bishop

	else if(dangerous_piece==WHITE_QUEEN || dangerous_piece==BLACK_QUEEN){
		if (fromX==toI || fromY==toJ){ //if it's moving like a rook
			return canBlockRook(copy,fromX,toI,minX,minY,maxX,maxY);
		}

		else if((fromX-toI)==(fromY-toJ) || (fromX-toI)== -(fromY-toJ)){ //if it's moving like a bishop
			return canBlockBishop(copy,fromX,fromY,toI,toJ,minX,minY,maxX,maxY);
		}
		GameDestory(copy);
		return false;
	}//of is dangerous piece a queen

	else if(dangerous_piece==WHITE_ROOK || dangerous_piece==BLACK_ROOK){
		return canBlockRook(copy, fromX, toI, minX, minY, maxX, maxY);
	} //of is dangerous piece a rook

	GameDestory(copy);
	return false;
	//if reached here then false should be returned because there is no way to block a knight,it jumps over all pieces!
	// no way to block a threatening pawn because he must be adjacent to the king in danger
	//no way to block a threatening king because he must be adjacent to the king in danger
}

bool can_victim_block_threat(ChessGame * src, int toI, int toJ){
	if(!src){
		printf("ERROR: null pointer in function can_victim_block_threat\n");fflush(stdout);
		return false;
	}
	for(int i=0;i<ROWS;i++){
		for(int j=0;j<COLUMNS;j++){
			int curr_piece=src->gameBoard[i][j];
			if(!isOppositeColor(curr_piece,src->currentPlayer) && curr_piece!=WHITE_KING && curr_piece!=BLACK_KING && curr_piece!=EMPTY_ENTRY){ //if piece belongs to the one in danger
				if(isValidMove(src,i,j,toI,toJ)==VALID_MOVE){ // if a piece that belongs to the endangered player can move to block the threat
					GameDestory(src);
					return true;
				}
			}
		}
	}
	return false;
}



bool isItATie(ChessGame *src,int kingX,int kingY){
	if(!src){
		printf("ERROR: null pointer in function isItATie\n");fflush(stdout);
		return false;
	}
	int *p1=NULL,*p2=NULL;
	if(did_I_put_Opponent_In_Check(src,kingX,kingY,p1,p2)){
		return false; //because if the game is checked then it's not a tie
	}
	//reach here only if the game is not checked yet
	//check if opponent has any valid move
	src->currentPlayer=!(src->currentPlayer);
	for(int i=0; i<ROWS; i++){
		for (int j=0; j<COLUMNS; j++){
			for(int k=0; k<ROWS; k++){
				for (int h=0; h<COLUMNS; h++){
					if(isValidMove(src,i,j,k,h)==VALID_MOVE && !did_I_put_myself_In_Check(src,i,j,k,h)){
						src->currentPlayer=!(src->currentPlayer); //keep everything as it was before calling this func
						return false;
					}
				}
			}
		}
	}
	src->currentPlayer=!(src->currentPlayer);//keep everything as it was before calling this func
	return true;
}


void find_opponent_king(ChessGame * src, int* kingX, int* kingY){
	if(!src){
		printf("ERROR: null pointer in function find_opponent_king\n");fflush(stdout);
		return;
	}
	char potential_king;
	//find the position of the opponent's king
	for(int i=0; i<ROWS; i++){
		for(int j=0; j<COLUMNS; j++){
			potential_king=src->gameBoard[i][j];
			if(src->currentPlayer==WHITE_PLAYER_SYMBOL && potential_king==BLACK_KING){
				*kingX=i;
				*kingY=j;
			}
			if(src->currentPlayer==BLACK_PLAYER_SYMBOL && potential_king==WHITE_KING){
				*kingX=i;
				*kingY=j;
			}
		}
	}
}


void find_my_king(ChessGame * src, int* kingX, int* kingY){
	if(!src){
		printf("ERROR: null pointer in function find_my_king\n");fflush(stdout);
		return;
	}
	char potential_king;
	//find the position of my own king
	for(int i=0; i<ROWS; i++){
		for(int j=0; j<COLUMNS; j++){
			potential_king=src->gameBoard[i][j];
			if(src->currentPlayer==WHITE_PLAYER_SYMBOL && potential_king==WHITE_KING){
				*kingX=i;
				*kingY=j;
			}
			if(src->currentPlayer==BLACK_PLAYER_SYMBOL && potential_king==BLACK_KING){
				*kingX=i;
				*kingY=j;
			}
		}
	}
}

void MovesHistoryUpdate(ChessGame* src, int fromX, int fromY, int toI, int toJ){
	if(!src){
		printf("ERROR: null pointer in function MovesHistoryUpdate\n");fflush(stdout);
		return;
	}
	if (ChessArrayListSize(src->movesHistory)==ChessArrayListMaxSize(src->movesHistory)){
		ChessArrayListRemoveLast(src->movesHistory);
		ChessArrayListRemoveLast(src->movesHistory);
		ChessArrayListRemoveLast(src->movesHistory);
		ChessArrayListRemoveLast(src->movesHistory);
	}
		ChessArrayListAddFirst(src->movesHistory,toJ);
		ChessArrayListAddFirst(src->movesHistory,toI);
		ChessArrayListAddFirst(src->movesHistory,fromY);
		ChessArrayListAddFirst(src->movesHistory,fromX);
}

void PlayerDestinataionUpdate(ChessGame* src, char piece){
	if(!src){
		printf("ERROR: null pointer in function PlayerDestinataionUpdate\n");fflush(stdout);
		return;
	}
	int charVal = (int) piece;
	if (src->currentPlayer==WHITE_PLAYER_SYMBOL){
		if (ChessArrayListSize(src->Player1LastDestinations)==ChessArrayListMaxSize(src->Player1LastDestinations)){
			ChessArrayListRemoveLast(src->Player1LastDestinations);
		}
		ChessArrayListAddFirst(src->Player1LastDestinations,charVal);
	}
	else {
		if (ChessArrayListSize(src->Player2LastDestinations)==ChessArrayListMaxSize(src->Player2LastDestinations)){
			ChessArrayListRemoveLast(src->Player2LastDestinations);
		}
		ChessArrayListAddFirst(src->Player2LastDestinations,charVal);
	}
}
GAME_MESSAGE undo_move(ChessGame * src){
	if (!src){
		printf("ERROR: null pointer in function undo_move\n");fflush(stdout);
		return INVALID_ARGUMENT;
	}
	if(ChessArrayListSize(src->movesHistory)==0){
		return NO_HISTORY;
	}
	if(src->undoCountPerTurn > src->historySize){
		printf("you invoked undo move more than 3 times! not allowed\n");fflush(stdout);
	}
	src->undoCountPerTurn++;

	int recentI = src->movesHistory->talaMoves[2];
	int recentJ = src->movesHistory->talaMoves[3];
    char tmp = src->gameBoard[recentI][recentJ];
    int originalX =src->movesHistory->talaMoves[0];
    int originalY =src->movesHistory->talaMoves[1];
    src->gameBoard[originalX][originalY]=tmp;
    char recentPiece= EMPTY_ENTRY;
    if (src->currentPlayer==WHITE_PLAYER_SYMBOL){
         recentPiece = (char)ChessArrayListGetFirst(src->Player2LastDestinations);
         ChessArrayListRemoveFirst(src->Player2LastDestinations);
    }
    else {
        recentPiece = (char)ChessArrayListGetFirst(src->Player1LastDestinations);
        ChessArrayListRemoveFirst(src->Player1LastDestinations);
    }
    src->gameBoard[recentI][recentJ]=recentPiece;

    ChessArrayListRemoveFirst(src->movesHistory);
    ChessArrayListRemoveFirst(src->movesHistory);
    ChessArrayListRemoveFirst(src->movesHistory);
    ChessArrayListRemoveFirst(src->movesHistory);
    ChangeCurrentPlayer(src);
	return GAME_SUCCESS;
}






void reset(ChessGame * src){
	if(!src){
		printf("ERROR: null pointer in function reset\n");fflush(stdout);
		return;
	}
	src->isInSetting=true;
	printRestarting();
	ClearGame(src);
	return;
}

void quitGame(ChessGame* game){
	if(!game){
		printf("ERROR: null pointer in function quitGame\n");fflush(stdout);
	}
	GameDestory(game);
	exit(-1);
}

void get_moves(ChessGame * src, int x, int y){
	if(!src){
		printf("ERROR: null pointer in function reset\n");fflush(stdout);
		return;
	}
	int curr_player=GetCurrentPlayer(src);
	char piece=src->gameBoard[x][y];
	INVALID_MOVE_MSG msg;
	for(int i=0;i<ROWS;i++){
		for(int j=0;j<COLUMNS;j++){
			msg=isValidMove(src,x,y,i,j);
			if(msg==INVALID_POSITION){
				printInvalidPosition();
			}
			if(msg==NO_PIECE_IN_SOURCE){
				printNoPieceContainedGetMoves(curr_player);
			}
			if(msg==VALID_MOVE && !did_I_put_myself_In_Check(src,x,y,i,j)){
				char J = translateIntToChar2(j);
				ChessGame * copy=GameCopy(src);
				copy->gameBoard[i][j]=piece;
				if(opponent_can_reach_position(copy,i,j)){
					if(isOppositeColor(src->gameBoard[i][j],curr_player)){
						printf("<%d,%c>*^\n",i+1,J);fflush(stdout);
					}
					else{
						printf("<%d,%c>*\n",i+1,J);fflush(stdout);
					}
					GameDestory(copy);
				}
				else if(isOppositeColor(src->gameBoard[i][j],curr_player)){
					printf("<%d,%c>^\n",i+1,J);fflush(stdout);
				}
				else{
					printf("<%d,%c>\n",i+1,J);fflush(stdout);
				}
			}
		}
	}
}


bool opponent_can_reach_position(ChessGame * game,int position1,int position2){
	if(!game){
		printf("ERROR: null pointer in function opponent_can_reach_position\n");fflush(stdout);
	}
	ChangeCurrentPlayer(game);
	for(int i=0;i<ROWS;i++){
		for(int j=0;j<COLUMNS;j++){
			if(game->gameBoard[i][j]==EMPTY_ENTRY){
				continue;
			}
			if(!isOppositeColor(game->gameBoard[i][j],GetCurrentPlayer(game))){
				if(isValidMove(game,i,j,position1,position2)==VALID_MOVE && !did_I_put_myself_In_Check(game,i,j,position1,position2)){
					return true;
				}
			}
		}
	}
	return false;
}

void printExiting(){
	printf("Exiting...\n");fflush(stdout);
}

void printEnterYourMove(int curr_player){
	if (curr_player==WHITE_PLAYER_SYMBOL){
		printf("white player - enter your move:\n"); fflush(stdout); //should it be white or White?
	}
	if (curr_player==BLACK_PLAYER_SYMBOL){
		printf("black player - enter your move:\n"); fflush(stdout); //black or Black?
	}
}

void printInvalidPosition(){
	printf("Invalid position on the board\n"); fflush(stdout);
}

void printNoPieceContained(){
	printf("The specified position does not contain your piece\n"); fflush(stdout);
}


void printNoPieceContainedGetMoves(int curr_player){
	printf("The specified position does not contain %d player piece\n",curr_player); fflush(stdout);
}



void printIllegalMove(){
	printf("Illegal move\n"); fflush(stdout);
}

void printCheckByPlayer(int threatened){
	if (threatened==WHITE_PLAYER_SYMBOL){
		printf("Check: white King is threatened!\n"); fflush(stdout);
	}
	if (threatened==BLACK_PLAYER_SYMBOL){
		printf("Check: black King is threatened!\n"); fflush(stdout);
	}
}

void printCheckByComputer(){
	printf("Check!\n");fflush(stdout);
}

void printCheckmate(int winner){
	if (winner==WHITE_PLAYER_SYMBOL){
		printf("Checkmate! white player wins the game\n"); fflush(stdout); //white or White?
	}
	if (winner==BLACK_PLAYER_SYMBOL){
		printf("Checkmate! black player wins the game\n"); fflush(stdout); //black or Black?
	}
}

void printTieByPlayer(){
	printf("The game is tied\n"); fflush(stdout);
}

void printTieByComputer(){
	printf("The game ends in a tie\n"); fflush(stdout);
}

void printRestarting(){
	printf("Restarting...\n"); fflush(stdout);
}

void printPawnPromotion_player(){
	printf("Pawn promotion- please replace the pawn by queen, rook, knight, bishop or pawn:\n");fflush(stdout);
}

void printPawnPromotion_AI(){}

void printInvalidTypePawnPromotion(){
	printf("Invalid Type\n");fflush(stdout);
}
