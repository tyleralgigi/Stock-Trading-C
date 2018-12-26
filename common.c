

/*
 * common.c
 *
 *  Created on: Nov 16, 2018
 *      Author: cprogrammer
 */
#include "common.h"

//This function will read the file with name in fileName and populate positions[]  array in
// the portfolio with the proper ticker symbols for all the stocks but the “shares” are all
//set to 0.0.  (test() function will set this filename to be mystocks.txt).
int initializePortfolio(char* fileName, MyPortfolio* pMyPortfolio){
    FILE* pFile=0;
    pFile = fopen(fileName,"r");
    int i=0;
    if(pFile==0) {
    	printf("Could not open file %s for read\n",fileName);
    	return 0;
    }
    while(fscanf(pFile,"%s %lf",pMyPortfolio->positions[i].ticker,&(pMyPortfolio->positions[i].price))>0
    		     && i< pMyPortfolio->positionsCapacity
                ){
    	pMyPortfolio->positions[i].shares = 0.0;
        i++;
    }
    pMyPortfolio->positionsSize = i;
    if(pFile) fclose(pFile);
	return i;
}

//This function finds the Position (stock) corresponding to the ticker symbol provided and
//return the pointer to that Position struct.

Position* findStock(MyPortfolio* pMyPortfolio, char* ticker){
    int i;
    for(i=0;i<pMyPortfolio->positionsSize;i++){
    	if(strcmp(ticker,pMyPortfolio->positions[i].ticker)==0){
    		return &(pMyPortfolio->positions[i]);
    	}
    }
    printf("Error: Ticker %s not found in MyPortfolio\n",ticker);
	return 0;
}
