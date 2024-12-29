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

	Board* generateChilds(int x, int y, int pos); //���ͤl�`�I

	bool operator==(const Board& rhs); // Operator ==
	bool operator<(const Board& rhs); // Operator <
	void calculateHeuristic(const Board & final); //�p��Heuristic
	void calculatePath(const Board& parent); //�p����|(G�禡)
	void calculateF(); //�p��F�禡
	void setParent(Board* parent); //�]�w���`�I
	
	bool canGenerate(int x, int y, int pos,int size); // �P�_0�i�H���o��V
	pair<int, int> getCoordinates()const; //���0����m

	int getF() const; // �o��F���
	int getG() const; //�o��G���
	int getH() const; //�o��H���
	void SetF(int); //�]�wF���
	void SetG(int); //�]�wG���
	void SetH(int); //�]�wH���

//RBFS�ϥ�-------------------------------------------------------------
	void ResetF_function(int);//��RBFS�ϥΡA�Ψӭ��s�]�wF�禡
	Board* GetParent();//�o����`�I
	void SetFlimit(int);
	int GetFlimit();
	bool CheckHaveChildOrNot();//�P�_���I�O�_��children
	int Children_Size();//�o��children���Ӽ�
	void SetChildren(Board*); //�schildren
	Board* GetChildren(int );//�N���s���L��ChildrenŪ�X��
//---------------------------------------------------------------------
	void printBoard();//�L�XBoard()
	void printPath(); //��path��X�ӡA�I�sBoard()
	vector<vector<int>> getPuzzles()const; //�o���e��Puzzle�ˤl
};

#endif STATE