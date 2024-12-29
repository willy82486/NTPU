#ifndef STATE
#define STATE

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm> 
#include <ctime> 
#include <cmath> 
#include <list> 
using std::vector;
using std::pair;

class Board {

private:
	vector<vector<int>> puzzles;
	// heuristic function : numbers of cells that are not in the correct place
	int h;
	// path lenght
	int g;
	// the sum of h and g
	int f;

	Board* parent;

	void swapEl(int x, int y, int newX, int newY);

	int f_limit;

	vector<Board*> children;

public:

	Board(vector<vector<int>> puzzles); //Constructor
	Board(const Board& rhs); //Constructor

	Board* generateChilds(int x, int y, int pos); //產生子節點

	bool operator==(const Board& rhs); // Operator ==
	bool operator<(const Board& rhs); // Operator <
	void calculateHeuristic(const Board & final); //計算Heuristic
	void calculatePath(const Board& parent); //計算路徑(G函式)
	void calculateF(); //計算F函式
	void setParent(Board* parent); //設定父節點
	
	bool canGenerate(int x, int y, int pos,int size); // 判斷0可以走得方向
	pair<int, int> getCoordinates()const; //找到0的位置

	int getF() const; // 得到F函數
	int getG() const; //得到G函數
	int getH() const; //得到H函數
	void SetF(int); //設定F函數
	void SetG(int); //設定G函數
	void SetH(int); //設定H函數

//RBFS使用-------------------------------------------------------------
	void ResetF_function(int);//給RBFS使用，用來重新設定F函式
	Board* GetParent();//得到父節點
	void SetFlimit(int);
	int GetFlimit();
	bool CheckHaveChildOrNot();//判斷此點是否有children
	int Children_Size();//得到children的個數
	void SetChildren(Board*); //存children
	Board* GetChildren(int );//將有存取過的Children讀出來
//---------------------------------------------------------------------
	void printBoard();//印出Board()
	void printPath(); //把path找出來，呼叫Board()
	vector<vector<int>> getPuzzles()const; //得到當前的Puzzle樣子
};

#endif STATE