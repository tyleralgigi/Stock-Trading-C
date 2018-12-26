//
//  tradingApp.c
//  projectFour
//
//  Created by Tyler Algigi on 11/30/18.
//  Copyright © 2018 Tyler Algigi. All rights reserved.
//

#include "tradingApp.h"
#include <stdbool.h>

void viewProtfolio(MyPortfolio* pMyPortfolio){
    printf("Balance: %lf", pMyPortfolio->balance);
    for(int i = 0;i<pMyPortfolio->positionsSize;i++){
        printf("Ticker: %s ", pMyPortfolio->positions[i].ticker);
        printf("Price: %lf ", pMyPortfolio->positions[i].price);
        printf("Shares: %lf \n", pMyPortfolio->positions[i].shares);
    }
}

double buyShares(MyPortfolio* pMyPortfolio){
    double newPrice;
    double cost;
    Position* pPosition;
    char buyDecision;
    char ticker[10];
    double shares = 0;
    
    printf("What stock would you like to buy?\n");
    for(int i = 0;i<pMyPortfolio->positionsSize;i++){
        printf("%s  ", pMyPortfolio->positions[i].ticker);
    }
    printf("\n");
    scanf(" %s", ticker);
    newPrice = getSimulatedPrice(pMyPortfolio, ticker);
    if (newPrice < 0) {
        return 0;
    }
    
    pPosition = findStock(pMyPortfolio, ticker);
    printStock(pPosition);
    
    printf("How many shares would you like to buy?");
    scanf(" %lf", &shares);
    
    printf("Comfirming that you would like to buy %lf of %s at price of $%.2lf? [y/n] ", shares,ticker,newPrice);
    scanf(" %c", &buyDecision);

    if (buyDecision == 'y') {
        cost = buy(pMyPortfolio, ticker, shares);
        return cost;
    }

    return 0;

}

double sellShares(MyPortfolio* pMyPortfolio){
    double newPrice;
    double profit;
    Position* pPosition;
    char sellDecision;
    char ticker[10];
    double shares = 0;
    
    printf("What stock would you like to buy?\n");
    for(int i = 0;i<pMyPortfolio->positionsSize;i++){
        printf("%s  ", pMyPortfolio->positions[i].ticker);
    }
    printf("\n");
    scanf(" %s", ticker);
    
    newPrice = getSimulatedPrice(pMyPortfolio, ticker);
    if (newPrice < 0) {
        return 0;
    }
    
    pPosition = findStock(pMyPortfolio, ticker);
    printStock(pPosition);
    
    printf("How many shares would you like to buy?");
    scanf(" %lf", &shares);
    
    printf("Comfirming that you would like to sell %lf of %s at price of $%.2lf? [y/n] ", shares,ticker,newPrice);
    scanf(" %c", &sellDecision);
    
    if (sellDecision == 'y') {
        profit = sell(pMyPortfolio, ticker, shares);
        return profit;
    }
    return 0;
}

void checkCurrentStocks(MyPortfolio* pMyPortfolio){
    for(int i = 0;i<pMyPortfolio->positionsSize;i++){
        printf("Ticker: %s ", pMyPortfolio->positions[i].ticker);
        printf("Price: %lf \n", pMyPortfolio->positions[i].price);

    }
}

double totalWorth(MyPortfolio* pMyPortfolio){
    double totalWorth;
    double stocks;
    
    for(int i = 0;i<pMyPortfolio->positionsSize;i++){
        stocks = (pMyPortfolio->positions[i].price) * (pMyPortfolio->positions[i].shares);
        printf("%lf\n", stocks);
        totalWorth = totalWorth + stocks;
        printf("%lf\n", totalWorth);
    }
    totalWorth += pMyPortfolio->balance;
    printf("Totoal portfolio Worth: %lf\n", totalWorth);
    return totalWorth;
}

void menu(MyPortfolio* pMyPortfolio){
    bool run = true;
    char runDecision;
    //char runMenuAgain;
    printf("Welcome to Tylers Stock Trading\n");
    printf("Attempting to Initialize Portfolio...\n");
    printf("======================================================\n");
    printf("Enter which menu option you would like to procced with:\n1.View Portfolio\n2.Buy Shares\n3.Sell Shares\n4.Check Current Stock Prices\n5.Check total Portfolio Worth\n6.Exit\n");
    int menuNum = 0;
    scanf("%d", &menuNum);
    

    while(run==true){
        if(menuNum==1){
            viewProtfolio(pMyPortfolio);
            run=false;
        }else if (menuNum==2){
            buyShares(pMyPortfolio);
            run=false;
        }else if (menuNum==3){
            sellShares(pMyPortfolio);
            run=false;
        }else if (menuNum==4){
            checkCurrentStocks(pMyPortfolio);
            run=false;
        }else if (menuNum==5){
            totalWorth(pMyPortfolio);
            run=false;
        }else if (menuNum==6){
            printf("Exiting");
            run=false;
        }else{
            printf("Please enter a 1,2,3,4,5 or 6:");
            scanf("%d", &menuNum);
        }
    }
    
    if(menuNum!=6){
        printf("Would you like to run again? [y/n]\n");
        scanf(" %c", &runDecision);
        if (runDecision == 'y') {
            menu(pMyPortfolio);
        }
    }

    
    
    /*printf("\nWould you like to see the menu options again? [y/n]\n");
    scanf("%c", &runMenuAgain);
    
    if(strcmp(&runMenuAgain, "y")==0){
        menu(pMyPortfolio);
    }else{
        exit(0);
    }*/
}
