#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include "Board.h"
#include <unordered_map>

using namespace std;
//priority_queue中透過F函式判斷優先度
struct Comparator_F {
	bool operator()(Board* lhs, Board* rhs) {
		return lhs->getF() > rhs->getF();
	}
};
//priority_queue中透過G函式判斷優先度
struct Comparator_G {
	bool operator()(Board* lhs, Board* rhs) {
		return lhs->getG() > rhs->getG();
	}
};
//priority_queue中透過H函式判斷優先度
struct Comparator_H {
	bool operator()(Board* lhs, Board* rhs) {
		return lhs->getH() > rhs->getH();
	}
};
//用於RBFS()中vector的sort
bool cmp(pair<int, Board*>p1 , pair<int, Board*>p2) {
	return p1.first < p2.first;
}
//雜湊表
size_t hashing(vector<vector<int>> puzzles) {
	string result;
	for (size_t i = 0; i < puzzles.size(); ++i) {
		for (size_t j = 0; j < puzzles[i].size(); ++j) {
			string tmp;
			if (puzzles[i][j] == 10) {
				tmp = "A";
			}
			else if (puzzles[i][j] == 11) {
				tmp = "B";
			}
			else if (puzzles[i][j] == 12) {
				tmp = "C";
			}
			else if (puzzles[i][j] == 13) {
				tmp = "D";		
			}
			else if (puzzles[i][j] == 14) {
				tmp = "E";
			}
			else if (puzzles[i][j] == 15) {
				tmp = "F";
			}
			else {
				tmp = to_string(puzzles[i][j]);
			}
			result += tmp;
		}
	}
	return hash<string>{}(result);
}
//Iterative-Deepening Search (IDS)
void IDS(Board*start,  Board* final) {
	int depth = 0;
	size_t Memoryspace = 0;
	size_t StateChange = 0;
	cout << "Starting IDS Algorithm... \n";
	unordered_map<size_t, vector<vector<int>>> visited;
	list< Board* > q;
	q.push_front(start);

	while (!q.empty()) {
		Board* current = q.front();
		q.pop_front();
		size_t key = hashing(current->getPuzzles());
		visited[key] = current->getPuzzles();
		StateChange++;

		if (current->getG() > depth) {
			depth += 2;
		}

		if (*current == *final) {
			current->printPath();
			cout << "Space= " << Memoryspace << endl;
			cout << "StateChange= " << StateChange << endl;
			cout << "Cost= " << current->getG() << endl;
			q.clear();
			visited.clear();
			return;
		}
		else if (depth > current->getG()) {
			for (size_t i = 0; i < 4; ++i) {
				pair<int, int> coord = current->getCoordinates(); //找到0的位置
				if (current->canGenerate(coord.first, coord.second, i, current->getPuzzles().size())) {//0走得方向
					Board* tmp = current->generateChilds(coord.first, coord.second, i);//Current產生的child放在tmp，並在這裡產生新的board
					tmp->setParent(current);
					tmp->calculateHeuristic(*final);
					tmp->calculatePath(*current);
					tmp->calculateF();
					size_t tmpKey = hashing(tmp->getPuzzles());
					if (visited.find(tmpKey) == visited.end()) {
						q.push_front(tmp);
						visited[tmpKey] = tmp->getPuzzles();
						Memoryspace += 1;
					}
				}
			}
		}
		else {
			for (size_t i = 0; i < 4; ++i) {
				pair<int, int> coord = current->getCoordinates(); //找到0的位置
				if (current->canGenerate(coord.first, coord.second, i, current->getPuzzles().size())) {//0走得方向
					Board* tmp = current->generateChilds(coord.first, coord.second, i);//Current產生的child放在tmp，並在這裡產生新的board
					tmp->setParent(current);
					tmp->calculateHeuristic(*final);
					tmp->calculatePath(*current);
					tmp->calculateF();
					size_t tmpKey = hashing(tmp->getPuzzles());
					if (visited.find(tmpKey) == visited.end()) {
						q.push_back(tmp);
						visited[tmpKey] = tmp->getPuzzles();
						Memoryspace += 1;
					}
				}
			}
		}
	}
	cout << "No Solution" << endl;
	visited.clear();

}
//Uniform-Cost Search
void UCS(Board* start, Board* final) {
	cout << "starting Uniform-Cost Search Algorithm... \n";
	size_t Memoryspace = 0;
	size_t StateChange = 0;
	//creating a priority queue to store each board
	priority_queue<Board*, vector<Board*>, Comparator_G> q;
	//creating map to keep in mind already visited states
	unordered_map<size_t, vector<vector<int>>> visited;
	start->calculateHeuristic(*final);
	start->calculateF();
	q.push(start);

	while (!q.empty()) {

		Board* min = q.top();
		q.pop();
		size_t key = hashing(min->getPuzzles());
		visited[key] = min->getPuzzles();
		StateChange++;
		if (*min == *final) {
			min->printPath();
			cout << "Space= " << Memoryspace << endl;
			cout << "StateChange= " << StateChange << endl;
			cout << "Cost= " << min->getG() << endl;
			while (!q.empty()) {
				q.pop();
			}
			visited.clear();
			return;
		}
		for (size_t i = 0; i < 4; ++i) {
			pair<int, int> coord = min->getCoordinates(); //找到0的位置
			if (min->canGenerate(coord.first, coord.second, i, min->getPuzzles().size())) {//0走得方向
				Board* tmp = min->generateChilds(coord.first, coord.second, i);//min產生的child放在tmp，並在這裡產生新的board
				tmp->setParent(min);
				tmp->calculateHeuristic(*final); //計算function_H
				tmp->calculatePath(*min); //計算function_G
				tmp->calculateF(); //計算function_F
				size_t tmpKey = hashing(tmp->getPuzzles());
				if (visited.find(tmpKey) == visited.end()) {
					q.push(tmp);
					visited[tmpKey] = tmp->getPuzzles();
					Memoryspace += 1;
				}
			}
		}
	}

	cout << "No Solution" << endl;
	visited.clear();
}
//Greedy Best-First Search
void GBFS(Board* start, Board* final) {
	cout << "starting GBFS Algorithm... \n";
	size_t Memoryspace = 0;
	size_t StateChange = 0;
	//creating a priority queue to store each board
	priority_queue<Board*, vector<Board*>, Comparator_H> q;
	//creating map to keep in mind already visited states
	unordered_map<size_t, vector<vector<int>>> visited;
	start->calculateHeuristic(*final);
	start->calculateF();
	q.push(start);

	while (!q.empty()) {

		Board* min = q.top();
		q.pop();
		size_t key = hashing(min->getPuzzles());
		visited[key] = min->getPuzzles();
		StateChange++;
		if (*min == *final) {
			min->printPath();
			cout << "Space= " << Memoryspace << endl;
			cout << "StateChange= " << StateChange << endl;
			cout << "Cost= " << min->getG() << endl;
			while (!q.empty()) {
				q.pop();
			}
			visited.clear();
			return;
		}
		for (size_t i = 0; i < 4; ++i) {
			pair<int, int> coord = min->getCoordinates(); //找到0的位置
			if (min->canGenerate(coord.first, coord.second, i, min->getPuzzles().size())) {//0走得方向
				Board* tmp = min->generateChilds(coord.first, coord.second, i);//min產生的child放在tmp，並在這裡產生新的board
				tmp->setParent(min);
				tmp->calculateHeuristic(*final);
				tmp->calculatePath(*min);
				tmp->calculateF();
				size_t tmpKey = hashing(tmp->getPuzzles());
				if (visited.find(tmpKey) == visited.end()) {
					q.push(tmp);
					visited[tmpKey] = tmp->getPuzzles();
					Memoryspace += 1;
				}
			}
		}
	}

	cout << "No Solution" << endl;
	visited.clear();
}
// A* search
void Astar(Board* start, const Board* final) {
	cout << "Starting Astar Algorithm... \n";
	size_t Memoryspace = 0;
	size_t StateChange = 0;
	//creating a priority queue to store each board
	priority_queue<Board*, vector<Board*>, Comparator_F> q;
	//creating map to keep in mind already visited states
	unordered_map<size_t, vector<vector<int>>> visited;
	start->calculateHeuristic(*final);
	start->calculateF();
	q.push(start);

	while (!q.empty()) {

		Board* min = q.top();
		q.pop();
		size_t key = hashing(min->getPuzzles());
		visited[key] = min->getPuzzles();
		StateChange++;
		if (*min == *final) {
			min->printPath();
			cout << "Space= " << Memoryspace << endl;
			cout << "StateChange= " << StateChange << endl;
			cout << "Cost= " << min->getG() << endl;
			while (!q.empty()) {
				q.pop();
			}
			visited.clear();
			return;
		}
		for (size_t i = 0; i < 4; ++i) {
			pair<int, int> coord = min->getCoordinates(); //找到0的位置
			if (min->canGenerate(coord.first, coord.second, i, min->getPuzzles().size())){ //0走得方向
				Board* tmp = min->generateChilds(coord.first, coord.second, i);//min產生的child放在tmp，並在這裡產生新的board
				tmp->setParent(min);
				tmp->calculateHeuristic(*final);
				tmp->calculatePath(*min);
				tmp->calculateF();
				size_t tmpKey = hashing(tmp->getPuzzles());
				if (visited.find(tmpKey) == visited.end()) {
					q.push(tmp);
					visited[tmpKey] = tmp->getPuzzles();
					Memoryspace+=1;
				}
				
			}
		}
	}

	cout << "No Solution" << endl;
	visited.clear();
}
//Recursive Best - First Search(RBFS)
bool RBFS(Board* start, Board* final) {
	//creating a priority queue to store each board
	priority_queue<Board*, vector<Board*>, Comparator_F> q;
	//creating map to keep in mind already visited states
	unordered_map<size_t, vector<vector<int>>> visited;
	static int Memoryspace = 1;
	static int StateChange = 0;
	static int f_limit = 1000000;
	start->SetFlimit(f_limit);
	static Board* Goal;
	static Board* Current;
	Goal = final;
	Current = start;
	while (1) {
		vector <pair <int, Board*>> children;
		Current->SetFlimit(f_limit);
		if (*Current == *final) {
			Current->printPath();
			cout << "Space= " << Memoryspace << endl;
			cout << "StateChange= " << StateChange << endl;
			cout << "Cost= " << Current->getG() << endl;
			return 1;
		}

		if (Current->CheckHaveChildOrNot() == 0) {//判斷這個點有沒有走過，如果沒有走過
			for (size_t i = 0; i < 4; ++i) {
				pair<int, int> coord = Current->getCoordinates(); //找到0的位置
				if (Current->canGenerate(coord.first, coord.second, i, Current->getPuzzles().size())) { //0走得方向
					Board* tmp = Current->generateChilds(coord.first, coord.second, i);//Current產生的child放在tmp，並在這裡產生新的board
					Current->SetChildren(tmp);
					tmp->setParent(Current);
					tmp->calculateHeuristic(*final);
					tmp->calculatePath(*Current);
					tmp->calculateF();
					size_t tmpKey = hashing(tmp->getPuzzles());
					if (visited.find(tmpKey) == visited.end()) {
						q.push(tmp);
						visited[tmpKey] = tmp->getPuzzles();
					}
					children.push_back(make_pair(tmp->getF(), tmp));
				}
			}
		}
		else {//有走過
			for (size_t i = 0; i < Current->Children_Size(); i++) {
				Board* tmp = Current->GetChildren(i);
				children.push_back(make_pair(tmp->getF(), tmp));
			}
		}
		sort(children.begin(), children.end(), cmp);
		//如果child[0]小於等於flimit且child[0]也小於等於flimit
		if ((children[0].first < f_limit || children[0].first == f_limit) && (children[1].first < f_limit || children[1].first == f_limit)) {
			Current = children[0].second;
			f_limit = children[1].first;
			Memoryspace++;
			StateChange++;
		}
		//如果child[0]小於等於flimit但child[0]大於flimit
		else if ((children[0].first < f_limit || children[0].first == f_limit) && children[1].first > f_limit) {
			Current = children[0].second;
			Memoryspace++;
			StateChange++;
		}
		//child[0]和child[1]皆大於flimit
		else {
			Current->ResetF_function(children[0].first);
			Current = Current->GetParent();
			f_limit = Current->GetFlimit();
			Memoryspace--;
			StateChange++;
		}
		
		children.clear();
	}
	
	delete Goal;
	delete Current;
	return 0;
}

int main() {

	int i_search;
	cout << "1:IDS  2:UCS  3:GBFS  4:A*  5:RBFS" << endl;
	cin >> i_search;
	while (i_search != -0) {
		
		//vector<vector<int>> g = { { 1,2,3 },{ 4,5,6 },{ 7,8,0 } };
		//vector<vector<int>> g = { { 5,8,6 },{ 0,7,4 },{ 2,3,1 } };
		vector<vector<int>> g = { { 1,2,3,4 },{ 5,6,7,8 },{ 9,10,11,12 },{ 13,14,15,0 } };
		Board* goal = new Board(g);

		
		//vector<vector<int>> ex = { { 8,6,4 }, { 0,7,2 }, { 5,1,3 } };
		//vector<vector<int>> ex = { { 5,8,6 },{ 7,3,4 },{ 2,0,1 } };
		vector<vector<int>> ex = { { 1,2,3,4 },{ 6,7,8,0 },{ 5,10,11,12 },{ 9,13,14,15 } };
		Board* origin = new Board(ex);
		cout << "Exam : " << endl;
		for (size_t i = 0; i < ex.size(); ++i) {
			for (size_t j = 0; j < ex.size(); ++j) {
				cout << ex[i][j] << ' ';
			}
			cout << endl;
		}
		cout << "Goal : " << endl;
		for (size_t i = 0; i < g.size(); ++i) {
			for (size_t j = 0; j < g.size(); ++j) {
				cout << g[i][j] << ' ';
			}
			cout << endl;
		}
		if (i_search == 1) {
			IDS(origin, goal);
		}
		else if (i_search == 2) {
			UCS(origin, goal);
		}
		else if (i_search == 3) {
			GBFS(origin, goal);
		}
		else if (i_search == 4) {
			Astar(origin, goal);
		}
		else if (i_search == 5) {
			cout << "Starting RBFS Algorithm... \n";
			if (RBFS(origin, goal)!=1) {
				cout << "No Solution" << endl;
			}
			
		}
		delete origin;
		delete goal;
		cout << "1:IDS  2:UCS  3:GBFS  4:A*  5:RBFS" << endl;
		cin >> i_search;
		
	}
	return 0;
}
