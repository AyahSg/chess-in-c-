/*
 * savedGames.c
 *
 *  Created on: Aug 23, 2017
 *      Author: Ayah
 */
#include "savedGames.h"
#include <string.h>
#include <assert.h>
#include <ctype.h>

void createXML(ChessGame* src, FILE* file){
	if(!src || !file){
		printf("ERROR: null pointer in function createXML in savedGames.c\n");fflush(stdout);
		return;
	}
	fprintf(file,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	fprintf (file,"<game>\n");
	fprintf (file,"<current_turn>%d</current_turn>\n",src->currentPlayer);
	fprintf (file,"<game_mode>%d</game_mode>\n",src->gameMode);
	fprintf (file,"<difficulty>%d</difficulty>\n",src->gameDifficulty);
	fprintf (file,"<user_color>%d</user_color>\n",src->playerColor);
	fprintf (file,"<board>\n");
	for (int i=ROWS-1;i>=0;i--){ //we need to start the printing from row 8
		fprintf(file,"<row_%d>",i+1);
		for (int j=0;j<COLUMNS;j++){
			fprintf(file,"%c",src->gameBoard[i][j]);
		}
		fprintf(file,"</row_%d>\n",i+1);
	}
	fprintf(file,"</board>\n");
	fprintf (file,"</game>\n");
}

long fsize(FILE * file)

{
    if(fseek(file, 0, SEEK_END))
        return -1;

    long size = ftell(file);
    if(size < 0)
        return -1;

    if(fseek(file, 0, SEEK_SET))
        return -1;

    return size;
}

FILE_MSG fileCopy(char* from, char* to){
	FILE* fromf=fopen(from,"r");
	FILE* tof=fopen(to,"r+");
	if (!fromf) return FILE_ERROR;
	if (!tof) return FILE_ERROR;
	char arr[80];
	while(fscanf(fromf,"%s",arr)!=EOF){
		fprintf(tof,"%s\n",arr);
	}

	fclose(tof);
	fclose(fromf);
	return FILE_SUCCESS;
}

void updateSavedSlots(int cnt){
	char* from=(char*)malloc(sizeof(char)*12);
	char* to=(char*)malloc(sizeof(char)*12);
	if(!from || !to){
		printf("ERROR: memory allocation fail in function updateSavedSlots in savedGames.c\n");
		fflush(stdout);
		return;
	}
	for (int i=cnt-1; i>=0;i--){
		//shift the files from the (i-1)th slot to the (i)th slot
		if (i+1<GAME_SLOTS){
			sprintf(from,"%d",i); strcat(from,".xml");
			sprintf(to,"%d",i+1); strcat(to,".xml");
			fileCopy(from,to);
		}
	}
	free(from); free(to);
}
int numOfSavedGames(){
	char* buf=(char*)malloc(sizeof(char)*12);
	if(!buf){
		printf("ERROR: memory allocation fail in function updateSavedSlots in savedGames.c\n");
		fflush(stdout);
	}
	int size,cnt=0; //counts the saved games until now, in ordert to update the rest...
	for (int i=0; i<GAME_SLOTS;i++){
		sprintf(buf,"%d",i); //converts i to a string and puts it in buf
		strcat(buf,".xml");
		FILE* file=fopen(buf,"r");
		if (!file){
			file=fopen(buf,"w");
		}
		size = fsize(file);
		fflush(file);
		if (!file)
			return FILE_ERROR;
		if (size>0){
			cnt++;
		}
		fclose(file);
	}
	free(buf);

	return cnt;

}
FILE_MSG save(ChessGame * src , char* filepath){
	char* buf=(char*)malloc(sizeof(char)*12);
	if(!buf){
		printf("ERROR: memory allocation fail in function updateSavedSlots in savedGames.c\n");
		fflush(stdout);
		return FILE_ERROR;
	}

	int size,cnt=0; //counts the saved games until now, in order to update the rest...
	for (int i=0; i<GAME_SLOTS;i++){
		sprintf(buf,"%d",i); //converts i to a string and puts it in buf
		strcat(buf,".xml");
		FILE* file=fopen(buf,"r");
		if (!file){
			file=fopen(buf,"w");
		}
		size = fsize(file);
		fflush(file);
		if (!file)
			return FILE_ERROR;
		if (size>0){
			cnt++;
		}
		fclose(file);
	} //by now we know how many files are saved
	free(buf);
	if (cnt>0){
		updateSavedSlots(cnt);
	}

	FILE* filef=fopen(filepath,"r+"); //assuming the user give the .xml suffix?
	if (!filef)
		return FILE_ERROR;
	createXML(src, filef);
	fflush(filef);
	fclose(filef);
	return FILE_SUCCESS;
}

FILE_MSG consoleSave(ChessGame * src , char* filepath){
	FILE* filef=fopen(filepath,"w"); //assuming the user give the .xml suffix?
	if (!filef)
		return FILE_ERROR;
	createXML(src, filef);
	fclose(filef);
	return FILE_SUCCESS;
}

void getInfoFromRowI(int index,char *rowInfo,ChessGame * src){
	if(!src){
		printf("ERROR: null pointer in function getInfoFromRowI in savedGames.c\n");
		fflush(stdout);
		return;
	}
	int n=strlen(rowInfo);
	assert(n==8);
	for(int j=0;j<n;j++){
		src->gameBoard[index][j]=rowInfo[j];
	}
}

void XMLparser(ChessGame *src, FILE* ifp){
	if(!src || !ifp){
		printf("ERROR: null pointer in function XMLparser in savedGames.c\n");fflush(stdout);
		return;
	}
	char str[40];
	char strCopy[40];
	char *p=NULL;
	int index;
	while(strcmp("</game>",str)!=0){
		fscanf(ifp,"%s",str);
		strcpy(strCopy,str);
		p=strtok(strCopy,">");
		char potentialIND= *(p+strlen(p)-1);
		if(isdigit(potentialIND)){
			index=potentialIND-48;
			p=strtok(NULL,"<");
			getInfoFromRowI(index-1,p,src);
		}
		else if(strcmp("<current_turn",p)==0){
			p=strtok(NULL,"<");
			src->currentPlayer=*p-48;

		}
		else if(strcmp("<game_mode",p)==0){
			p=strtok(NULL,"<");
			src->gameMode=*p-48;
		}
		else if(strcmp("<difficulty",p)==0){
			p=strtok(NULL,"<");
			src->gameDifficulty=*p-48;
		}
		else if(strcmp("<user_color",p)==0){
			p=strtok(NULL,"<");
			src->playerColor=*p-48;
		}
	}
}

FILE_MSG load (ChessGame* src, char* filepath){
	FILE* data = fopen(filepath,"r");
	if (!data) return FILE_ERROR;
	XMLparser(src,data);
	if(!src->supported&&src->gameDifficulty==5){
		printExpertLevelNotSupportedInLoad();
		return 	EXPERT_NOT_SUPPORTED;
	}
	return FILE_SUCCESS;
}


void printExpertLevelNotSupportedInLoad(){
	printf("Expert level not supported\n");fflush(stdout);
}


void printFileLoadError(){
	printf("Error: File doesn’t exist or cannot be opened\n"); fflush(stdout); //TYPO!!!!
}
