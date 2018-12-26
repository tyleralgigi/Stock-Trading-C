/*
 ============================================================================
 Name        : project3_003.c
 Author      : Saeed Rajput
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "common.h"
#include "simulator.h"
#include "trading.h"
#include "tradingApp.h"

void print(){
    printf("Hello\n");
}

void test(){
	char* fileName = "mystocks.txt";
	char* portfolioFileName = "myportfolio.txt";
	MyPortfolio myPortfolio;
	double price =0.0;
	myPortfolio.positionsCapacity = MAX_MY_STOCKS;
	myPortfolio.balance = 20000.0;

	Position* pPosition=0;
	double cost;
	char ticker[10] = "FEYE";
	double shares = 100.0;


	printf("Testing Initialize Portfolio\n");
	initializePortfolio(fileName, &myPortfolio);
	printPortfolio(&myPortfolio);

	printf("\nTrying to Find %s\n",ticker);
	pPosition = findStock(&myPortfolio, ticker);
	if(!pPosition) printf("Error\n");
	printStock(pPosition);

	printf("\nTrying to get new price of %s\n",ticker);
	price = getSimulatedPrice(&myPortfolio,ticker);
	printf("Test price function getSimulatedPrice(). New price is %.2lf\n",price);
	printStock(pPosition);

	printf("\nBuying %.2lf shares of %s\n",shares,ticker);
	cost  = buy(&myPortfolio, ticker,shares);
	printPortfolio(&myPortfolio);
	//printf("I now have %.2lf shares of %s\n",pPosition->shares, pPosition->ticker);
	//printf("New balance is=%.2lf\n",myPortfolio.balance);

	strcpy(ticker,"FSLR");
	price = getSimulatedPrice(&myPortfolio,ticker);
	printf("\nBuying %.2lf shares of %s\n",shares,ticker);
	cost  = buy(&myPortfolio, ticker,shares);
	printPortfolio(&myPortfolio);

	shares=50;
	strcpy(ticker,"FEYE");
	//ticker="FEYE";
	price = getSimulatedPrice(&myPortfolio,ticker);
	printf("\nSelling %.2lf shares of %s\n",shares,ticker);
	cost  = sell(&myPortfolio, ticker,shares);
	printPortfolio(&myPortfolio);

	shares =100;
	strcpy(ticker,"EXTR");
	printf("\nBuying %.2lf shares of %s with permission\n",shares,ticker);
	cost  = buyWithPermission(&myPortfolio, ticker,shares);
	printf("cost/proceeds=%.2lf\n",cost);
	printPortfolio(&myPortfolio);

	shares =1000;
	strcpy(ticker,"CLNE");
	printf("\nBuying %.2lf shares of %s with permission\n",shares,ticker);
	cost  = buyWithPermission(&myPortfolio, ticker,shares);
	printf("cost/proceeds=%.2lf\n",cost);
	printPortfolio(&myPortfolio);

	shares =500;
	strcpy(ticker,"CLNE");
	printf("\nSelling %.2lf shares of %s with permission\n",shares,ticker);
	cost  = sellWithPermission(&myPortfolio, ticker,shares);
	printf("cost/proceeds=%.2lf\n",cost);
	printPortfolio(&myPortfolio);

	printf("\nSaving Portfolio\n");
	if(savePortfolio(portfolioFileName,&myPortfolio)){
		printf("File %s saved successfully. Please, confirm it in your folder\n",portfolioFileName);
	}else{
		printf("File %s saving NOT successful\n",portfolioFileName);
	}

	printf("\nTesting Reading Portfolio\n");
	if(readPortfolio(portfolioFileName,&myPortfolio)){
		printPortfolio(&myPortfolio);
	}else{
		printf("File %s Reading NOT successful\n",portfolioFileName);
	}

	//printPortfolio(&myPortfolio);
	//print();

}
void test4(){
    char* fileName = "mystocks.txt";
    MyPortfolio myPortfolio;
    myPortfolio.positionsCapacity = MAX_MY_STOCKS;
    myPortfolio.balance = 20000.0;
    initializePortfolio(fileName, &myPortfolio);
    
    menu(&myPortfolio);
}

int main(void) {
	//test();
    test4();
    //process();
	return EXIT_SUCCESS;
}
