/*
* trading.c
* author: Adapted from submission of Priya Sigler by Saeed Rajput
* date: Nov 25, 2018 by Priya
* updated: Nov 2, 92018 by Saeed
*/


#include "trading.h"

int savePortfolio(char* filename, MyPortfolio* pMyPortfolio) {
	FILE* pFile = 0;
	int i;

	pFile = fopen(filename, "w");
	if (pFile == 0) {
		printf("Could not open file %s for read\n", filename);
		return 0;
	}

	fprintf(pFile, "%lf\n", pMyPortfolio->balance);
	fprintf(pFile, "%d\n", pMyPortfolio->positionsSize);
	fprintf(pFile, "%d\n", pMyPortfolio->positionsCapacity);

	for (i = 0; i < pMyPortfolio->positionsSize; i++) {
		fprintf(pFile, "%s %lf %lf\n", pMyPortfolio->positions[i].ticker, pMyPortfolio->positions[i].price, pMyPortfolio->positions[i].shares);
	}
	if (pFile) fclose(pFile);
	return 1;
}

int readPortfolio(char* filename, MyPortfolio* pMyPortfolio) {
	FILE* pFile = 0;
	pFile = fopen(filename, "r");
	int i = 0;
	if (pFile == 0) {
		printf("Could not open file %s for read\n", filename);
		return 0;
	}
	fscanf(pFile, "%lf", &pMyPortfolio->balance);
	fscanf(pFile, "%d", &pMyPortfolio->positionsSize);
	fscanf(pFile, "%d", &pMyPortfolio->positionsCapacity);

	while (fscanf(pFile, "%s %lf %lf\n", pMyPortfolio->positions[i].ticker, &(pMyPortfolio->positions[i].price), &(pMyPortfolio->positions[i].shares))>0
		&& i< pMyPortfolio->positionsCapacity) {
		i++;
	}
	pMyPortfolio->positionsSize = i;
	if (pFile) fclose(pFile);


	return i;

}

void printStock(Position* pPosition) {
	printf("Ticker: %s\n", pPosition->ticker);
	printf("Price: %.4lf\n", pPosition->price);
	printf("Shares: %.4lf\n", pPosition->shares);
}

void printPortfolio(MyPortfolio* pMyPortfolio) {
	int j;
	double totalValue;
	double newBalance;

	newBalance = getBalance(pMyPortfolio);
	totalValue = newBalance;

	printf("====================================\n");
	printf("Balance: %.4lf\n", newBalance);
	for (j = 0; j < pMyPortfolio->positionsSize; j++) {
		printf("Ticker: %s; ", pMyPortfolio->positions[j].ticker);
		printf("Price: %.4lf; ", pMyPortfolio->positions[j].price);
		printf("Shares: %.4lf\n", pMyPortfolio->positions[j].shares);
		totalValue +=((pMyPortfolio->positions[j].price) * (pMyPortfolio->positions[j].shares));
	}
	printf("Total Value= %.4lf\n", totalValue);
}

double getBalance(MyPortfolio* pMyPortfolio) {
	return (pMyPortfolio->balance);
}

double buy(MyPortfolio* pMyPortfolio, char* ticker, double shares) {
	Position* pPosition;
	double cost;

	pPosition = findStock(pMyPortfolio, ticker);
	cost = shares * pPosition->price;

	if (cost > pMyPortfolio->balance) {
		printf("Balance (%.2lf) is too low buy %.2lf shares of %s\n", pMyPortfolio->balance,shares,ticker);
		return 0;
	}
	pMyPortfolio->balance -= cost;
	pPosition->shares += shares;
	return -cost;
}

double sell(MyPortfolio* pMyPortfolio, char* ticker, double shares) {
	Position* pPosition;
	double proceeds;

	pPosition = findStock(pMyPortfolio, ticker);
	if (pPosition->shares < shares) {
		printf("Not enough shares (%.2lf) of %s available to sell %.2lf\n",pPosition->shares,ticker,shares);
		return 0;
	}

	proceeds = pPosition->price * shares;
	pMyPortfolio->balance += proceeds;
	pPosition->shares -= shares;
	return proceeds;
}

double buyWithPermission(MyPortfolio* pMyPortfolio, char* ticker, double shares) {
	double newPrice;
	double cost;
	Position* pPosition;
	char buyDecision;

	newPrice = getSimulatedPrice(pMyPortfolio, ticker);
	if (newPrice < 0) {
		return 0;
	}

	pPosition = findStock(pMyPortfolio, ticker);
	printStock(pPosition);

	printf("Would you like to buy %s stock at price of $%.2lf? [y/n] ", ticker,newPrice);
	scanf(" %c", &buyDecision);

	if (buyDecision == 'y') {
		cost = buy(pMyPortfolio, ticker, shares);
		return cost;
	}

	return 0;
}

double sellWithPermission(MyPortfolio* pMyPortfolio, char* ticker, double shares) {
	double newPrice;
	double profit;
	Position* pPosition;
	char sellDecision;

	newPrice = getSimulatedPrice(pMyPortfolio, ticker);
	if (newPrice < 0) {
		return 0;
	}

	pPosition = findStock(pMyPortfolio, ticker);
	printStock(pPosition);

	printf("Would you like to sell %s stock at price of $%.2lf? [y/n] ", ticker,newPrice);
	scanf(" %c", &sellDecision);

	if (sellDecision == 'y') {
		profit = sell(pMyPortfolio, ticker, shares);
		return profit;
	}
	return 0;
}
