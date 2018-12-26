//
//  tradingApp.h
//  projectFour
//
//  Created by Tyler Algigi on 11/30/18.
//  Copyright © 2018 Tyler Algigi. All rights reserved.
//

#ifndef tradingApp_h
#define tradingApp_h

#include <stdio.h>
#include "common.h"
#include "simulator.h"
#include "trading.h"

void menu(MyPortfolio* pMyPortfolio);
void viewProtfolio(MyPortfolio* pMyPortfolio);
double buyShares(MyPortfolio* pMyPortfolio);
double sellShares(MyPortfolio* pMyPortfolio);
void checkCurrentStocks(MyPortfolio* pMyPortfolio);
double totalWorth(MyPortfolio* pMyPortfolio);
#endif /* tradingApp_h */
