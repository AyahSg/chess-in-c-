/*
 * cmdparser.c
 *
 *  Created on: Aug 15, 2017
 *      Author: tala
 */



#include "cmdparser.h"

#include <ctype.h>

char translateIntToChar(int i){
	char res=65+i;
	return res;
}
int translateCharToInt(char c){
	return c-65;
}
bool notInRange(int i){
	if (i>7 || i<0)
		return true;
	return false;
}



bool ParserIsInt(char* str){

	   if (*str == '-') //if negative number
	      ++str;

	   if (!*str) //if empty or just '-'
	      return false;

	   while (*str) //is it all digits?
	   {
	     if (!isdigit(*str))
	         return false;
	      else
	    	  ++str;
	   }
	   return true;

}

void initialize(Command *cmd){
	if(!cmd){
		printf("ERROR: null pointer of type Command in function initialize in cmdparser.c\n");fflush(stdout);
	}
	cmd->TOisValid=false;
	cmd->arg=-1;
	cmd->cmd=INVALID_COMMAND;
	cmd->fromX=-1;
	cmd->fromY=-1;
	cmd->thereIsAnArg=false;
	cmd->toI=-1;
	cmd->toJ=-1;
}

SP_COMMAND getCommand(char *pch){
	if (strcmp(pch ,"game_mode")==0){
		return GAME_MODE;
	}
	if (strcmp(pch ,"difficulty")==0){
		return DIFFICULTY;
	}
	if (strcmp(pch ,"user_color")==0){
		return USER_COLOR;
	}
	if (strcmp(pch ,"load")==0){
		return LOAD;
	}
	if (strcmp(pch ,"default")==0){
		return DEFAULT;
	}
	if (strcmp(pch ,"print_setting")==0){
		return PRINT_SETTING;
	}
	if (strcmp(pch ,"quit")==0){
		return QUIT;
	}
	if (strcmp(pch ,"start")==0){
		return START;
	}
	if (strcmp(pch ,"move")==0){
		return MOVE;
	}
	if (strcmp(pch ,"castle")==0){
		return CASTLE;
	}
	if (strcmp(pch ,"get_moves")==0){
		return GET_MOVES;
	}
	if (strcmp(pch ,"save")==0){
		return SAVE;
	}
	if (strcmp(pch ,"undo")==0){
		return UNDO;
	}
	if (strcmp(pch ,"reset")==0){
		return RESET;
	}
	return INVALID_COMMAND;
}

Command* createCommand(){
	Command* cmd=(Command*)malloc(sizeof(Command));
	char * fpath = (char*) malloc(sizeof(char)*MAX_SIZE);
	if(!cmd || !fpath){
		printf("ERROR: memory allocation falied in function createCommand in cmdparser.c\n");fflush(stdout);
		return NULL;
	}
	cmd->filepath=fpath;
	initialize(cmd);
	return cmd;
}

Command* ParseLine(char* str){
	Command* cmd = createCommand();
	bool isFirstPos=true; //when a command requires user to type <x,y> ,check if this is the first tuple given by user.
	bool firstTimeInThisLoop=true;
	char * strCopy= (char*)malloc(sizeof(char)*strlen(str)+1);
	if(!strCopy){
		printf("ERROR: memory allocation falied in function ParseLine in cmdparser.c\n");
		fflush(stdout);
		return NULL;
	}
	strcpy(strCopy,str);
	char * pch;
	pch = strtok (strCopy," \n\t\r");
	while (pch != NULL)
		{
		if(firstTimeInThisLoop){
			cmd->cmd=getCommand(pch);
			firstTimeInThisLoop=false;
			if (cmd->cmd==INVALID_COMMAND){
				free(strCopy);
				return cmd;
			}
		}
		else if(ParserIsInt(pch)){ //MOAB said some cases won't be checked such as user entering two arguments for a command that needs only one
			cmd->thereIsAnArg = true;
			cmd->arg = atoi(pch);
		}
		else if(*pch=='<' && *(pch+2)==',' && *(pch+4)=='>' && isFirstPos){
			cmd->thereIsAnArg = true;
			if(cmd->cmd==MOVE || cmd->cmd==GET_MOVES || cmd->cmd==CASTLE){
				cmd->fromX= *(pch+1) - 48; //cast numeric char such as '0','1',etc to and int with same value 0,1,etc
				cmd->fromX-=1; //because indexing starts with 0, but user starts with 1
				cmd->fromY=translateCharToInt(*(pch+3));
				isFirstPos=false;
			}
			else{ //a command other than move,get_moves,castle
				cmd->arg=-1; //set cmd->arg to an invalid one
				free(strCopy);
 				return cmd;
			}
		}
		else if(*pch=='<' && *(pch+2)==',' && *(pch+4)=='>' && !isFirstPos){
			cmd->thereIsAnArg = true;
			if(cmd->cmd==MOVE){
				cmd->toI= *(pch+1) - 48; //cast numeric char such as '0','1',etc to and int with same value 0,1,etc
				cmd->toI-=1; //because indexing starts with 0, but user starts with 1
				cmd->toJ=translateCharToInt(*(pch+3));
			}
			else{
				cmd->arg=-1;
				free(strCopy);
				return cmd;
			}
		}
		else if(strcmp("to",pch)==0){
			cmd->thereIsAnArg = true;
			if(cmd->cmd==MOVE){
				cmd->TOisValid=1;
			}
			else{
				cmd->arg=-1;
				free(strCopy);
				return cmd;
			}
		}
		else{
			strcpy(cmd->filepath,pch);
		}
		pch = strtok (NULL, " \n\t\r");
	}//end of while
	if(pch){
		free(pch);
	}
	free(strCopy);
	return cmd;
}

void destroyCommand(Command* cmd){
	if(!cmd){
		return;
	}
	if(!cmd->filepath){
		free(cmd);
		return;
	}
	free(cmd->filepath);
	free(cmd);
}

