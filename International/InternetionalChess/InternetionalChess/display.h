//
//  display.h
//  InternetionalChess
//
//  Created by 姚晨 on 2025/11/11.
//
#ifndef _DISPLAY_H_
#define _DISPLAY_H_
#include <iostream>
#include <string>
#include "search.h"
void displayChess();
void searchRecord(std::string color,std::string chessType,int vertical,char length,int display);
void batch_display();
void batch_displayTXT();
void wait_for_enter();
void clearScreen();
void waitAnyKey();
#endif
