#include "Board.h"
using namespace std;

Board::Board(vector<vector<int>> puzzles)
{
	this->puzzles = puzzles;
	this->f = 0;
	this->g = 0;
	this->h = 0;
	this->parent = nullptr;
}

Board::Board(const Board& rhs)
{
	this->puzzles = rhs.puzzles;
	this->parent = nullptr;
	this->h = 0;
	this->g = 0;
	this->f = 0;
}

pair<int, int> Board::getCoordinates() const
{
	for (size_t i = 0; i < this->puzzles.size(); ++i) {
		for (size_t j = 0; j < this->puzzles[i].size(); ++j) {
			if (this->puzzles[i][j] == 0) {
				return pair<int, int>(i, j);
			}
		}
	}
}

bool Board::canGenerate(int x, int y, int pos,int size)
{
	bool flag = false;
	switch (pos) {
	case 0: flag = y - 1 >= 0; break;
	case 1: flag = x - 1 >= 0; break;
	case 2: flag = y + 1 <= size-1; break;
	case 3: flag = x + 1 <= size-1; break;
	}
	return flag;
}

void Board::swapEl(int x, int y, int newX, int newY)
{
	swap(this->puzzles[x][y], this->puzzles[newX][newY]);
}

Board* Board::generateChilds(int x, int y, int pos)
{
	pair<int, int> coord = this->getCoordinates();
	switch (pos) {
	case 0: {
		Board* newBoard = new Board(*this);
		newBoard->swapEl(x, y, x, y - 1);
		return newBoard;
		break;
	}
	case(1): {
		Board* newBoard = new Board(*this);
		newBoard->swapEl(x, y, x - 1, y);
		return newBoard;
		break;
	}
	case(2): {

		Board* newBoard = new Board(*this);
		newBoard->swapEl(x, y, x, y + 1);
		return newBoard;
		break;

	}
	case(3): {
		Board* newBoard = new Board(*this);
		newBoard->swapEl(x, y, x + 1, y);
		return newBoard;
		break;

	}
	}
}

bool Board::operator==(const Board& rhs)
{
	for (size_t i = 0; i < this->puzzles.size(); ++i) {
		if (this->puzzles[i] != rhs.puzzles[i]) {
			return false;
		}
	}
	return true;
}

bool Board::operator<(const Board& rhs)
{
	return this->f < rhs.f;
}

void Board::calculateHeuristic(const Board & final)
{
	bool found;
	int  Heuristic = 0;
	for (int i = 0; i < this->puzzles.size(); ++i) {
		for (int j = 0; j < this->puzzles[i].size(); ++j) {
			found = false;
			for (int i2 = 0; i2 < this->puzzles.size(); i2++) {
				for (int j2 = 0; j2 < this->puzzles[i2].size(); j2++){
					if (this->puzzles[i2][j2] == final.puzzles[i][j]) {
						Heuristic += abs(i - i2) + abs(j - j2);
						found = true;
					}
					if (found) {
						break;
					}
				}
				if (found) {
					break;
				}
			}
		}
	}
	this->h = Heuristic;
	/*int sum = 0;
	for (size_t i = 0; i < this->puzzles.size(); ++i) {
		for (size_t j = 0; j < this->puzzles[i].size(); ++j) {
			if (this->puzzles[i][j] != final.puzzles[i][j]) {
				++sum;
			}
		}
	}
	this->h = sum;*/
}

void Board::calculatePath(const Board& parent)
{
	this->g = parent.g + 1;
}

void Board::setParent(Board* parent)
{
	this->parent = parent;
}

void Board::calculateF()
{
	this->f = this->g + this->h;
}

int Board::getF() const
{
	return this->f;
}

int Board::getG() const
{
	return this->g;
}

int Board::getH() const
{
	return this->h;
}

void Board::printBoard()
{
	for (size_t i = 0; i < this->puzzles.size(); ++i) {
		for (size_t j = 0; j < this->puzzles[i].size(); ++j) {
			cout << this->puzzles[i][j] << ' ';
		}
		cout << endl;
	}
}

void Board::printPath()
{
	if (this->parent == nullptr) {
		this->printBoard();
		cout << endl;
		return;
	}
	this->parent->printPath();
	this->printBoard();
	cout << endl;
}

vector<vector<int>> Board::getPuzzles() const
{
	return this->puzzles;
}

void Board::ResetF_function(int number) {
	this->f = number;
}

Board* Board::GetParent() {
	return this->parent;
}

void Board::SetFlimit(int number) {
	this->f_limit = number;
}

int Board::GetFlimit() {
	return this->f_limit;
}

void Board::SetF(int number) {
	this->f = number;
}

void Board::SetG(int number) {
	this->g = number;
}

void Board::SetH(int number) {
	this->h = number;
}

bool Board::CheckHaveChildOrNot() {
	if (this->children.empty()) {
		return 0;
	}
	return 1;
}

void Board::SetChildren(Board* children) {
	this->children.push_back(children);
}

int Board::Children_Size() {
	return this->children.size();
}

Board* Board::GetChildren(int i) {
	return this->children[i];
}