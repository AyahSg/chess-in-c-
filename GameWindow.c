/*
 * GameWindow.c
 *
 *  Created on: Sep 24, 2017
 *      Author: Ayah
 */

#include "GameWindow.h"
#include <stdio.h>


GameWidget** createGameWindowWidgets(SDL_Renderer* renderer, ChessGame* game, int* num){
	if (renderer == NULL || game==NULL ) {
		return NULL ;
	}
	GameWidget** widgets = malloc(sizeof(GameWidget*) * 40);
	if (widgets == NULL ) {
		return NULL ;
	}
	SDL_Rect restartR = { .x = 600, .y = 40, .h = 50, .w = 180 };
	SDL_Rect saveR = { .x = 600, .y = 100, .h = 50, .w = 180 };
	SDL_Rect loadR = { .x = 600, .y = 160, .h = 50, .w = 180 };
	SDL_Rect undoR = { .x = 600, .y = 220, .h = 50, .w = 180 };
	SDL_Rect mainmenuR = { .x = 600, .y = 480, .h = 50, .w = 180 };
	SDL_Rect exitR = { .x = 600, .y = 540, .h = 50, .w = 180 };
	SDL_Rect currentTurnR = {.x=600,.y=310,.h=76,.w=200};
	widgets[0] = createGameButton(renderer, &restartR, "./images/restart.bmp",RESTART_BUTTON,1);
	widgets[1] = createGameButton(renderer, &saveR, "./images/gamesave.bmp",SAVE_BUTTON,1);
	widgets[2] = createGameButton(renderer, &loadR, "./images/gameload.bmp",LOAD_GAME_BUTTON,1);
	if (game->gameMode==GAME_MODE_1){
		widgets[3] = createGameButton(renderer, &undoR, "./images/gameundo.bmp",UNDO_BUTTON,1); //according to game mode
	}
	else{
		widgets[3] = createGameButton(renderer, &undoR, "./images/gameundo.bmp",UNDO_BUTTON,0); //according to game mode
	}
	widgets[4] = createGameButton(renderer, &mainmenuR, "./images/mainmenu.bmp",MAIN_MENU_BUTTON,1);
	widgets[5] = createGameButton(renderer, &exitR, "./images/gameexit.bmp",EXIT_GAME_BUTTON,1);
	widgets[6] = createGameButton(renderer, &currentTurnR, "./images/CurrentTurnWhite.bmp",CURRENT_TURN_WHITE,0);
	widgets[7] = createGameButton(renderer, &currentTurnR, "./images/CurrentTurnBlack.bmp",CURRENT_TURN_BLACK,0);
	SDL_Rect pieceR; pieceR.w=68; pieceR.h=68;
	int widgetsIndex=8;
	for (int i=0;i<8;i++){
		for (int j=0;j<8;j++){
			if (game->gameBoard[i][j]!=EMPTY_ENTRY){
			pieceR.x=68*j +27 ;
			pieceR.y= (-68*i +27+68*7);
			fflush(stdout);
			switch(game->gameBoard[i][j]){
			case WHITE_PAWN:
				widgets[widgetsIndex] = createGameButton(renderer, &pieceR, "./images/YellowP.bmp",WHITE_PAWN_BUTTON,0);
				break;
			case WHITE_BISHOP:
				widgets[widgetsIndex] = createGameButton(renderer, &pieceR, "./images/YellowB.bmp",WHITE_BISHOP_BUTTON,0);
				break;
			case WHITE_KNIGHT:
				widgets[widgetsIndex] = createGameButton(renderer, &pieceR, "./images/YellowN.bmp",WHITE_KNIGHT_BUTTON,0);
				break;
			case WHITE_ROOK:
				widgets[widgetsIndex] = createGameButton(renderer, &pieceR, "./images/YellowR.bmp",WHITE_ROOK_BUTTON,0);
				break;
			case WHITE_KING:
				widgets[widgetsIndex] = createGameButton(renderer, &pieceR, "./images/YellowK.bmp",WHITE_KING_BUTTON,0);
				break;
			case WHITE_QUEEN:
				widgets[widgetsIndex] = createGameButton(renderer, &pieceR, "./images/YellowQ.bmp",WHITE_QUEEN_BUTTON,0);
				break;
			case BLACK_PAWN:
				widgets[widgetsIndex] = createGameButton(renderer, &pieceR, "./images/BrownP.bmp",BLACK_PAWN_BUTTON,0);
				break;
			case BLACK_BISHOP:
				widgets[widgetsIndex] = createGameButton(renderer, &pieceR, "./images/BrownB.bmp",BLACK_BISHOP_BUTTON,0);
				break;
			case BLACK_KNIGHT:
				widgets[widgetsIndex] = createGameButton(renderer, &pieceR, "./images/BrownN.bmp",BLACK_KNIGHT_BUTTON,0);
				break;
			case BLACK_ROOK:
				widgets[widgetsIndex] = createGameButton(renderer, &pieceR, "./images/BrownR.bmp",BLACK_ROOK_BUTTON,0);
				break;
			case BLACK_KING:
				widgets[widgetsIndex] = createGameButton(renderer, &pieceR, "./images/BrownK.bmp",BLACK_KING_BUTTON,0);
				break;
			case BLACK_QUEEN:
				widgets[widgetsIndex] = createGameButton(renderer, &pieceR, "./images/BrownQ.bmp",BLACK_QUEEN_BUTTON,0);
				break;
			}
			widgetsIndex++;
			}
		}
	}
	*num=widgetsIndex;
	int b=0;
		for (int i=0; i<widgetsIndex-1;i++){
			if (widgets[i]==NULL){
				b=1; break;
			}
		}
		if (b==1){
			for (int i=0; i<widgetsIndex;i++){
				destroyGameWidget(widgets[i]);
			}
			free(widgets);
			printf("ERROR: couldn't create game window widgets\n");
			return NULL;
		}
		GameButton* currentTurnBlackButt=(GameButton*) widgets[7]; //always the white player begins playing
		currentTurnBlackButt->isShown=0;
	return widgets;
}

GameWindow* createChessGameWindow(ChessGame* game){
	GameWindow* res = malloc(sizeof(GameWindow));
		SDL_Window* window = SDL_CreateWindow("Chess Champion", SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
		SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
				SDL_RENDERER_ACCELERATED);
		int num=8; //used to updating the number of widgets in case some pieces were missing in some loaded game
		GameWidget** widgets = createGameWindowWidgets(renderer,game,&num);
		if (res == NULL || window == NULL || renderer == NULL
				|| widgets == NULL || game==NULL ) {
			free(res);
			free(widgets);
			//We first destroy the renderer
			SDL_DestroyRenderer(renderer); //NULL safe
			SDL_DestroyWindow(window); //NULL safe
			return NULL ;
		}
		SDL_Surface* loadingSurface = NULL;
		// insert background of window here !
		loadingSurface = SDL_LoadBMP("Board brown.bmp");
		if (loadingSurface == NULL ) {
			free(res);
			free(widgets);
			SDL_FreeSurface(loadingSurface);
			//We first destroy the renderer
			SDL_DestroyRenderer(renderer); //NULL safe
			SDL_DestroyWindow(window); //NULL safe
			printf("ERROR: couldn't create Board brown.bmp background surface\n");
			return NULL ;
		}
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
		if (texture == NULL ) {
			SDL_FreeSurface(loadingSurface);
			free(res);
			free(widgets);
			SDL_FreeSurface(loadingSurface);
			SDL_DestroyTexture(texture);
			//We first destroy the renderer
			SDL_DestroyRenderer(renderer); //NULL safe
			SDL_DestroyWindow(window); //NULL safe
			printf("ERROR: couldn't create Board brown.bmp background texture\n");
			return NULL;
		}
		SDL_FreeSurface(loadingSurface);
		res->widgets = widgets;
		res->numOfWidgets = num;
		res->bgTexture=texture;
		res->window = window;
		res->windowRenderer = renderer;
		res->ChessGame=game;
		if (GetMode(game)==GAME_MODE_1 && GetUserColor(game)==BLACK_PLAYER_SYMBOL){ //if the computer will begin the game
			res->isUserInputBlocked=1;
		}
		else res->isUserInputBlocked=0;
		res->lastUsedWidget=NULL;
		return res;
}

void destroyChessGameWidgets(GameWindow* src){
	int i = 0;
	for (; i < src->numOfWidgets; i++) {
		destroyGameWidget(src->widgets[i]);
	}
}

void destroyChessGameWindow(GameWindow* src){
	if (src == NULL ) {
		return;
	}
	destroyChessGameWidgets(src);
	free(src->widgets);
	if (src->bgTexture != NULL ) {
		SDL_DestroyTexture(src->bgTexture);
	}
	SDL_DestroyRenderer(src->windowRenderer);
	SDL_DestroyWindow(src->window);
	free(src);
}

void drawChessGameWindow(GameWindow* src){
	if (src == NULL ) {
		return;
	}
	SDL_Rect bgR = {.h = 600, .w = 600 };
	SDL_Rect panelR = {.h=600,.w=200,.x=600};

	SDL_RenderCopy(src->windowRenderer, src->bgTexture, NULL, &bgR);
	SDL_SetRenderDrawColor(src->windowRenderer,188,113,43,255);
	SDL_RenderFillRect(src->windowRenderer,&panelR);
	GameButton* whiteTurn =(GameButton*) src->widgets[6]->data;
	GameButton* blackTurn =(GameButton*) src->widgets[7]->data;
	if (GetCurrentPlayer(src->ChessGame)==WHITE_PLAYER_SYMBOL){
		whiteTurn->isShown=1;
		blackTurn->isShown=0;
	}
	else {
		whiteTurn->isShown=0;
		blackTurn->isShown=1;
	}
	int i = 0;
	for (; i < src->numOfWidgets; i++) {
		src->widgets[i]->drawGameWidget(src->widgets[i]);
	}
	SDL_RenderPresent(src->windowRenderer);
}
int map_from_mouse_position_to_rect_position(int mousePos){
	if ((mousePos-27)%68==0){
		return mousePos;
	}
	return mousePos-((mousePos-27)%68);
}
int inTheSameLocation(int x, int y, int i, int j){
	if (x==i && y==j) return 1;
	return 0;
}
GameWidget* findWidgetInAGivenLocation(GameWindow* src,int XLocation, int YLocation){
	for (int i=0;i<src->numOfWidgets;i++){
		GameButton* button = (GameButton*) src->widgets[i]->data;
		if (inTheSameLocation(button->location->x,button->location->y,XLocation,YLocation) && button->isShown){
				return src->widgets[i];
		}
	}
	return NULL;
}
void showWidgetinAgivenLocation(GameWindow* src,int x, int y, GAME_BUTTON piece){
	for (int i=0;i<src->numOfWidgets;i++){
		GameButton* button = (GameButton*) src->widgets[i]->data;
		GAME_BUTTON name = button->buttonName;
		if (inTheSameLocation(button->location->x,button->location->y,x,y)
				&& !(button->isShown) && name==piece){
			button->isShown=1;
			break;
		}
	}
}

GAME_BUTTON pieceNameAccordingToGameWindow(char piece){
	switch (piece){
	case WHITE_BISHOP:
		return WHITE_BISHOP_BUTTON;
	case WHITE_PAWN:
		return WHITE_PAWN_BUTTON;
	case WHITE_KING:
		return WHITE_KING_BUTTON;
	case WHITE_KNIGHT:
		return WHITE_KNIGHT_BUTTON;
	case WHITE_QUEEN:
		return WHITE_QUEEN_BUTTON;
	case WHITE_ROOK:
		return WHITE_ROOK_BUTTON;
	case BLACK_BISHOP:
		return BLACK_BISHOP_BUTTON;
	case BLACK_PAWN:
		return BLACK_PAWN_BUTTON;
	case BLACK_KING:
		return BLACK_KING_BUTTON;
	case BLACK_KNIGHT:
		return BLACK_KNIGHT_BUTTON;
	case BLACK_QUEEN:
		return BLACK_QUEEN_BUTTON;
	case BLACK_ROOK:
		return BLACK_ROOK_BUTTON;
	default:
		break;
	}
	return NONE_GAME_BUTTON;
}
int* undone_moves_gui(ChessGame * src){
	int * lastmove=(int*)calloc(4,sizeof(int));
	int last_x=src->movesHistory->talaMoves[0];
	int last_y=src->movesHistory->talaMoves[1];
	int last_i=src->movesHistory->talaMoves[2];
	int last_j=src->movesHistory->talaMoves[3];
	lastmove[0]=last_x;
	lastmove[1]=last_y;
	lastmove[2]=last_i;
	lastmove[3]=last_j;
	return lastmove;
}
UNDO_MSG undoMoveGUI(GameWindow* src){
	ChessGame* game = src->ChessGame;
	int* undoneMovesArr = undone_moves_gui(game);
	int originalX, originalY, recentX, recentY;
	originalX=undoneMovesArr[0];
	originalY=undoneMovesArr[1];
	recentX=undoneMovesArr[2];
	recentY=undoneMovesArr[3];
	int recentXRect = 68*recentY +27;
	int recentYRect = (27+68*7-68*recentX);
	int originalXRect=68*originalY +27;
	int originalYRect=(27+68*7-68*originalX);
	GAME_MESSAGE res = undo_move(game);
	if (res!=GAME_SUCCESS) return UNDO_FAILURE;
	GameWidget* pieceMovedBack = findWidgetInAGivenLocation(src,recentXRect,recentYRect); //the widget is still there according to game window
	updateWidgetLocation(pieceMovedBack,originalXRect,originalYRect);
	if (game->gameBoard[recentX][recentY]!=EMPTY_ENTRY){
		GAME_BUTTON piece = pieceNameAccordingToGameWindow(game->gameBoard[recentX][recentY]);
		showWidgetinAgivenLocation(src,recentXRect,recentYRect,piece);
	}
	drawChessGameWindow(src);
	free(undoneMovesArr);
	return UNDO_SUCCESS;
}

void captureThePiece(GameWindow* src, int DestX,int DestY){
	for (int i=0;i<src->numOfWidgets;i++){
		GameButton* button = (GameButton*) src->widgets[i]->data;
		if (button->location->x==DestX &&button->location->y==DestY ){
			button->isShown=0;
		}
	}
}

GAME_BUTTON handleMoveResult(GameWindow* src, RESULT_MSG res){
		switch(res){
		case CHECK:
			ChangeCurrentPlayer(src->ChessGame);
			ChessGame* game = src->ChessGame;
			if (GetMode(game)==GAME_MODE_1 && GetCurrentPlayer(game)!=GetUserColor(game)){
				src->isUserInputBlocked=1; //it means that it's computer's turn now
			}
			return GAME_CHECK;
		case CHECKMATE: return GAME_CHECKMATE;
		case TIE: return GAME_TIE;
		default: break;
		}
		return NONE_GAME_BUTTON;
}
RESULT_MSG computerPlay(GameWindow* src){
	ChessGame* game=src->ChessGame;
	ChessGame* copy=GameCopy(game);
	int diff=GetDifficulty(copy);
	int * result=mybestmoveInt(copy,diff);
	int fromX=result[0];
	int fromY=result[1];
	int toI=result[2];
	int toJ=result[3];
	char pieceInDest=game->gameBoard[toI][toJ];
	int fromXRec = 68*fromY +27;
	int fromYRec = (27+68*7-68*fromX);
	int toIRec = 68*toJ +27;
	int toJRec = (27+68*7-68*toI);
	GameWidget* movedPiece = findWidgetInAGivenLocation(src,fromXRec,fromYRec);
	if (pieceInDest!=EMPTY_ENTRY){
		captureThePiece(src,toIRec,toJRec);
	}
	RESULT_MSG res = SetMove(game,fromX,fromY,toI,toJ);
	updateWidgetLocation(movedPiece,toIRec,toJRec);
	GameDestory(copy);
	free(result);
	return res;
}

GAME_BUTTON handleEventGameWindow(GameWindow* src, SDL_Event* event){
	GAME_BUTTON res=NONE_GAME_BUTTON;
	if(src == NULL || event==NULL){
		return NONE_GAME_BUTTON;
	}
	if (src->isUserInputBlocked){ //it means that it's computer's turn
		RESULT_MSG res = computerPlay(src);
		src->isUserInputBlocked=0;
		if (res!=ELSE){
			return handleMoveResult(src,res);
		}
			ChangeCurrentPlayer(src->ChessGame);
			return NONE_GAME_BUTTON;
	}
	for(int i=0;i<src->numOfWidgets;i++){ //else we need to handle the event
		res = src->widgets[i]->handleEvent(src->widgets[i],event,src->lastUsedWidget,src->isUserInputBlocked);
		if (res==DROPPED_PIECE){
			GameButton* button=(GameButton*) src->lastUsedWidget->data;
			int OriginalX=(27+68*7-button->originalLocation->y)/68;
			int OriginalY=((button->originalLocation->x)-27)/68;
			int updateLocationX= map_from_mouse_position_to_rect_position(button->location->x);
			int updateLocationY= map_from_mouse_position_to_rect_position(button->location->y);
			int DestX=(27+68*7-updateLocationY)/68;
			int DestY=(updateLocationX-27)/68; //translating the data of the move
			INVALID_MOVE_MSG res =isValidMove(src->ChessGame,OriginalX,OriginalY,DestX,DestY);
			if (did_I_put_myself_In_Check(src->ChessGame,OriginalX,OriginalY,DestX,DestY)){
				res=ILLEGAL_MOVE;
			}
			if (res!=VALID_MOVE ){
				button->location->x=button->originalLocation->x;
				button->location->y=button->originalLocation->y;
				return NONE_GAME_BUTTON; //return the piece to its place
			}
			else { //else it means that the move was valid so now we need to call setmove
				if (src->ChessGame->gameBoard[DestX][DestY]!=EMPTY_ENTRY){
					captureThePiece(src,updateLocationX,updateLocationY);
				}
				RESULT_MSG result =SetMove(src->ChessGame,OriginalX,OriginalY,DestX,DestY);
				updateWidgetLocation(src->lastUsedWidget,updateLocationX,updateLocationY);
				if (result==ELSE){
					ChangeCurrentPlayer(src->ChessGame);
					if (GetMode(src->ChessGame)==GAME_MODE_2){
						return NONE_GAME_BUTTON;
					}
					else{ //else it's computer's turn
						src->isUserInputBlocked=1;
						return NONE_GAME_BUTTON;
					}
			}
				else{ //it's a check\checkmate\tie
					return handleMoveResult(src,result);
				}
		}
		}
		else if (res==DRAGGED_PIECE){
			SDL_RenderClear(src->windowRenderer);
			return NONE_GAME_BUTTON; //we want the user to continue dragging til the button's released
		}
		else if (res!=NONE_GAME_BUTTON && res!=DRAGGED_PIECE){
			src->lastUsedWidget=src->widgets[i];//update lastUsedWidget
			if (res==MAIN_MENU_BUTTON || res==EXIT_GAME_BUTTON||res==LOAD_GAME_BUTTON
					||res==X_GAME_BUTTON){
				return res;
			}
			if (res==RESTART_BUTTON){
				destroyChessGameWidgets(src);
				ClearGameWithoutChangingSetting(src->ChessGame);
				if (GetMode(src->ChessGame)==GAME_MODE_1 && GetUserColor(src->ChessGame) == BLACK_PLAYER_SYMBOL){
					src->isUserInputBlocked=1;
				}
				src->ChessGame->currentPlayer=WHITE_PLAYER_SYMBOL;
				GameWidget** widgets=createGameWindowWidgets(src->windowRenderer,src->ChessGame,&(src->numOfWidgets));
				src->widgets=widgets;
				return NONE_GAME_BUTTON; //we don't chessmanager to make any change
			}
			if (res==SAVE_BUTTON){
				save(src->ChessGame,"0.xml");
				return NONE_GAME_BUTTON;
			}
			if (res==UNDO_BUTTON){
				UNDO_MSG msg = undoMoveGUI(src);
				if (msg==UNDO_FAILURE)
					return NONE_GAME_BUTTON;
				undoMoveGUI(src);
				return NONE_GAME_BUTTON;
			}
			return NONE_GAME_BUTTON;
		}
	}
	return res;
}
void hideGameWindow (GameWindow* src){
	SDL_HideWindow(src->window);
}
void showGameWindow (GameWindow* src){
	SDL_ShowWindow(src->window);
}
