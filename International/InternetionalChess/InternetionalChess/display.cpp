//
//  display.cpp
//  InternetionalChess
//
//  Created by 姚晨 on 2025/11/11.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

void displayChess(){
    //控制Chess显示的行数
    int line = 0;
    //初始化chess
    vector<vector<string>>chess{{"rook","knight","bishop","queen","king","bishop","knight","rook"},
        {"pawn","pawn","pawn","pawn","pawn","pawn","pawn","pawn"},
        
        {"Pawn","Pawn","Pawn","Pawn","Pawn","Pawn","Pawn","Pawn"},
        {"Rook","Knight","Bishop","Queen","King","Bishop","Knight","Kook"}
    };
    cout <<"\t"<< "a\t" << "b\t\t"<< "c\t\t"<< "d\t\t"<< "e\t\t"<< "f\t\t"<< "g\t\t"<< "h\t\t"<<"\t"<<endl;
    //显示竖列
    for (int i=0,q=8; i<8; i++,q--) {
        //控制横列
        
        if(i==1 || i==6 || i==7)line++;
        //显示编号
        if(i==0 || i==1 || i==6 || i==7){
            cout << q <<"\t";
        }else{
            cout << q <<"\t"<<endl;
        }
        for (int j=0; j<8; j++){
            if(i==0 || i==1 || i==6 || i==7){
                
                cout <<chess[line][j]<<"\t";
                if(j==7)cout<<endl;
                    
            }else{
                break;
            }
        }
    }
    cout <<"\t"<< "a\t" << "b\t\t"<< "c\t\t"<< "d\t\t"<< "e\t\t"<< "f\t\t"<< "g\t\t"<< "h\t\t"<<"\t"<<endl;
    
}
