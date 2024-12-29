#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
#include <ctime>
#include <cmath>
#include <cstring>
#include <windows.h>
#include <algorithm>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

#define CODE 724
#define CODE2 724


using namespace std;

bool comp(pair<int,int> a,pair<int,int> b);
bool comp2(pair<int,int> a,pair<int,int> b);

class Card{

private:
    map<string,int> Suit;
    //-----------------------------------------------------------------
    string Spade[9]={
                  "|             |",
                  "|      *      |",
                  "|    *****    |",
                  "|  *********  |",
                  "| *********** |",
                  "|  *** * ***  |",
                  "|     ***     |",
                  "|    *****    |",
                  "|             |"
    };
    string Heart[9]={
                  "|             |",
                  "|   **   **   |",
                  "|  **** ****  |",
                  "| *********** |",
                  "|  *********  |",
                  "|   *******   |",
                  "|     ***     |",
                  "|      *      |",
                  "|             |"
    };
    string Diamond[9]={
                  "|             |",
                  "|      *      |",
                  "|     ***     |",
                  "|    *****    |",
                  "|   *******   |",
                  "|    *****    |",
                  "|     ***     |",
                  "|      *      |",
                  "|             |"
    };
    string Club[9]={
                  "|             |",
                  "|     ***     |",
                  "|    *****    |",
                  "|  ** *** **  |",
                  "| **** * **** |",
                  "|  **  *  **  |",
                  "|     ***     |",
                  "|    *****    |",
                  "|             |"
    };
    string Space[9]={
                  "               ",
                  "               ",
                  "               ",
                  "               ",
                  "               ",
                  "               ",
                  "               ",
                  "               ",
                  "               "
    };
    string Number[14]={" ","A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    string Asuit[5]={" ","Spade","Heart","Diamond","Club"};
    //-------------------------------------------------------------------------------------
    vector<pair<int,int> > player[52],canthrow[52],fold[52],NumberOfCard,secretplayer[52];
    int field[3][4],PlayerNum,total[52],checkfield[3][4],checktotal[52];
    int checkflag;
//-----------------------------------------------------------------------------
public:
    Card();
    Card(int);
    void SetColor(int = 7);
    bool Deal(int);//判斷當前手牌是出牌還是蓋牌
    void Run();//讀取每次輸入
    bool ChooseCard(int ,pair<int,int>);//人的出牌判斷
    bool FoldCard(int ,pair<int,int>);//人的蓋牌判斷
    void PrintHuman();//人的手牌
    void PrintField();//場上的牌
    void Finish();//結算點數

    int read();//讀檔
    int ERR(int );
};


#endif // CARD_H_INCLUDED

