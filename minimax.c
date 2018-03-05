/*
 * minimax.c
 *
 *  Created on: Aug 28, 2017
 *      Author: tala
 */
#include "minimax.h"
#include <limits.h>

int* mybestmoveInt(ChessGame * currentGame,int maxDepth){
	int* result=(int*)malloc(sizeof(int)*4);
	if(!result){
		printf("ERROR: memory allocation fail in function mybestmoveInt in minimax.c\n");fflush(stdout);
	}
	RESULT_MSG msg;
	int fromX,fromY,toI,toJ;
	int curr_player=GetCurrentPlayer(currentGame);
	int tmp_res;
	int h,k,hMin,hMax,kMin,kMax;
	char piece;
	int alpha=INT_MIN;
	int beta=INT_MAX;
	int biggestMax=INT_MIN;
	for(int i=0 ; i<ROWS ; i++){
		for(int j=0; j<COLUMNS; j++){
			piece=currentGame->gameBoard[i][j];
			if(piece==EMPTY_ENTRY || isOppositeColor(piece,curr_player))continue;
			else if((piece==WHITE_PAWN || piece==BLACK_PAWN)){
				hMin=-2; hMax=2; kMin=-1; kMax=1;
			}
			else if((piece==WHITE_BISHOP || piece==BLACK_BISHOP || piece==WHITE_ROOK || piece==BLACK_ROOK || piece==WHITE_QUEEN || piece==BLACK_QUEEN)){
				hMin=-7; hMax=7; kMin=-7; kMax=7;
			}
			else if((piece==WHITE_KING || piece==BLACK_KING)){
				hMin=-1; hMax=1; kMin=-1; kMax=1;
			}
			else if((piece==WHITE_KNIGHT || piece==BLACK_KNIGHT)){
				hMin=-2; hMax=2; kMin=-2; kMax=2;
			}
			for(h=hMin ; h<=hMax ; h++){
				for(k=kMin ; k<=kMax ; k++){
					if(isValidMove(currentGame,i,j,i+h,j+k)==VALID_MOVE && !did_I_put_myself_In_Check(currentGame,i,j,i+h,j+k)){
						ChessGame * copy=GameCopy(currentGame);
						if(!copy){
							printf("ERROR: null pointer in function mybestmoveInt in minimax.c\n");fflush(stdout);
							return NULL;
						}
						msg=SetMove(copy,i,j,i+h,j+k);
						if(msg==CHECKMATE){
							biggestMax=INT_MAX;
							fromX=i;
							fromY=j;
							toI=i+h;
							toJ=j+k;
							result[0]=fromX;
							result[1]=fromY;
							result[2]=toI;
							result[3]=toJ;
							return result;
						}
						ChangeCurrentPlayer(copy);
						tmp_res=minimaxInt(copy,maxDepth-1,false,alpha,beta);
						GameDestory(copy);
						if((tmp_res > biggestMax)){
							biggestMax=tmp_res;
							fromX=i;
							fromY=j;
							toI=i+h;
							toJ=j+k;
						}
					}//end of isvalid move
				}//end of k
			}//end of h
		}//end of j for
	}//end of i for
	result[0]=fromX;
	result[1]=fromY;
	result[2]=toI;
	result[3]=toJ;
	return result;
}


int minimaxInt(ChessGame* currentGame, int maxDepth, bool isMaximizing, int alpha, int beta){
	if(!currentGame){
		printf("ERROR: null pointer in function minimaxInt in minimax.c\n");fflush(stdout);
	}
	int curr_player=GetCurrentPlayer(currentGame);
	RESULT_MSG msg;
	int tmp_res;
	char piece;
	int h,k,hMin,hMax,kMin,kMax;
	if(isTerminal(currentGame)|| maxDepth==0){
		return naive_scoring(currentGame,isMaximizing);
	}
	int smallestMin=INT_MAX;
	int biggestMax=INT_MIN;
	for(int i=ROWS-1 ; i>=0 ; i--){
		for(int j=COLUMNS-1; j>=0; j--){
			piece=currentGame->gameBoard[i][j];
			if(piece==EMPTY_ENTRY || isOppositeColor(piece,curr_player))continue;
			else if((piece==WHITE_PAWN || piece==BLACK_PAWN)){
				hMin=-2; hMax=2; kMin=-1; kMax=1;
			}
			else if((piece==WHITE_BISHOP || piece==BLACK_BISHOP || piece==WHITE_ROOK || piece==BLACK_ROOK || piece==WHITE_QUEEN || piece==BLACK_QUEEN)){
				hMin=-7; hMax=7; kMin=-7; kMax=7;
			}
			else if((piece==WHITE_KING || piece==BLACK_KING)){
				hMin=-1; hMax=1; kMin=-1; kMax=1;
			}
			else if((piece==WHITE_KNIGHT || piece==BLACK_KNIGHT)){
				hMin=-2; hMax=2; kMin=-2; kMax=2;
			}
			for(h=hMin ; h<=hMax ; h++){
				for(k=kMin ; k<=kMax ; k++){
					if(isValidMove(currentGame,i,j,i+h,j+k)==VALID_MOVE && !did_I_put_myself_In_Check(currentGame,i,j,i+h,j+k)){
						ChessGame * copy=GameCopy(currentGame);
						if(!copy){
							printf("ERROR: null pointer in function minimaxInt in minimax.c\n");fflush(stdout);
						}
						msg=SetMove(copy,i,j,i+h,j+k);
						if(msg==CHECKMATE && isMaximizing){
							return INT_MAX;
						}
						if(msg==CHECKMATE && !isMaximizing){
							return INT_MIN;
						}
						ChangeCurrentPlayer(copy);
						tmp_res=minimaxInt(copy,maxDepth-1,!isMaximizing,alpha,beta);
						GameDestory(copy);
						if((tmp_res > biggestMax) && isMaximizing ){
							biggestMax=tmp_res;
						}
						if( alpha>biggestMax && isMaximizing){
							alpha=biggestMax;
						}
						if(beta<=alpha){
							break;
						}

						if((tmp_res < smallestMin) && !isMaximizing ){
							smallestMin=tmp_res;
						}
						if( beta<smallestMin && !isMaximizing){
							beta=smallestMin;
						}
						if(beta<=alpha){
							break;
						}
					}//end of isvalid move
				}//end of h
			}//end of k
		}//end of j for
	}//end of i for
	if(isMaximizing){
		return biggestMax;
	}
	else{
		return smallestMin;
	}
}//close function minimaxInt



int naive_scoring(ChessGame* currentGame,bool isMaximizing){
	if(!currentGame){
		printf("ERROR: null pointer in function naive_scroring in minimax.c\n");fflush(stdout);
	}

	if(!isMaximizing){
		ChangeCurrentPlayer(currentGame);
	}
	int counter=0;
	char piece;
	for(int i=0 ; i<ROWS ; i++){
		for(int j=0; j<COLUMNS; j++){
			piece=currentGame->gameBoard[i][j];
			if(piece==WHITE_PAWN || piece==BLACK_PAWN){
				if(isOppositeColor(piece,GetCurrentPlayer(currentGame)))
					counter-=1;
				else
					counter+=1;
			}
			if(piece==WHITE_BISHOP || piece==BLACK_BISHOP){
				if(isOppositeColor(piece,GetCurrentPlayer(currentGame)))
					 counter-=3;
				else
					counter+=3;
			}
			if(piece==WHITE_KNIGHT || piece==BLACK_KNIGHT){
				if(isOppositeColor(piece,GetCurrentPlayer(currentGame)))
					counter-=3;
				else
					counter+=3;
			}
			if(piece==WHITE_ROOK || piece==BLACK_ROOK){
				if(isOppositeColor(piece,GetCurrentPlayer(currentGame)))
					counter-=5;
				else
					counter+=5;
			}
			if(piece==WHITE_QUEEN || piece==BLACK_QUEEN){
				if(isOppositeColor(piece,GetCurrentPlayer(currentGame)))
					counter-=9;
				else
					counter+=9;
			}
			if(piece==WHITE_KING || piece==BLACK_KING){
				if(isOppositeColor(piece,GetCurrentPlayer(currentGame)))
					counter-=100;
				else
					counter+=100;
			}
		} //end of j
	} //end of i
	if(!isMaximizing){
		ChangeCurrentPlayer(currentGame);
	}
	return counter;
}

bool isTerminal(ChessGame* currentGame){
	if(!currentGame){
		printf("ERROR: null pointer in function isTerminal in minimax.c\n");fflush(stdout);
		return NULL;
	}
	int kingX,kingY;
	find_opponent_king(currentGame, &kingX, &kingY);
	if(isItATie(currentGame,kingX,kingY))return true;
	return false;
}
