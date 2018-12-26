/*
 * simulator.c
 *
 *  Created on: Nov 16, 2018
 *      Author: cprogrammer
 */


#include "simulator.h"
//The getSimulatedPrice() function takes a ticker symbol and the pMyPortfolio struct
// as input parameters and returns a current (simulated) price of that particular the ticker symbol.

//This function allows user to obtain the current price of a specific stock by providing the ticker.
//The new price is also saved in the “position” struct for that stock.
//This function should only be called after a call to  initalizePortfolioSimulator().
//If the ticker is not found, a “-1” is returned and an error is displayed.

double getSimulatedPrice(MyPortfolio* pMyPortfolio, char* ticker){
	//int i;
	double perturbation;
	double multiplier;
	double currentPrice;
	Position* pPosition;

	pPosition = findStock(pMyPortfolio,ticker);
	if (pPosition == 0)  return -1;

	currentPrice = pPosition->price;

	perturbation=2/currentPrice;
 	//for(i=0;i<10;i++){
 	multiplier = ((double) rand())/RAND_MAX*perturbation;
 	multiplier -= perturbation/2;
 	multiplier +=1;
      //  printf("New price=%.4lf\n",multiplier*currentPrice);
	//}
 	currentPrice =  currentPrice * multiplier;
 	pPosition->price = currentPrice;
	return (currentPrice);
}
