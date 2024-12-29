#include <bits/stdc++.h>
#include <string>
#include <stddef.h>

#define QNUM 8
#define Col 7   //8-1
using namespace std;

typedef pair<int, vector< vector<int> > > P;
typedef tuple<int, int, vector< vector<int> > > T;

size_t hashing(int ,int ,vector< vector<int> > );
bool IDS(int [QNUM][QNUM], int, int&, int&);
bool UCS(int [QNUM][QNUM]);
bool GBFS(int [QNUM][QNUM]);
bool Astar(int [QNUM][QNUM]);
int RBFS(int [QNUM][QNUM], int, int&, int&, int);
bool Check_Is_Save(int [QNUM][QNUM], int, int);
void Solution(int [QNUM][QNUM]);
int compute_h(int [QNUM][QNUM], int);

int main()
{
    while(1){
        int board[QNUM][QNUM] = {0, 0, 0, 0, 0, 0, 0, 0,    //Input 8*8
                                 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 1, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0};
        int bo[QNUM][QNUM];
        for(int i = 0; i < QNUM; i++)   //Set up the chessboard
        {
            for(int j = 0; j < QNUM; j++)
                bo[i][j] = board[i][j];
        }
        int n;
        int zero = 0, one = 1;
        cout << "1:IDS  2:UCS  3:GBFS  4:A*  5:RBFS" << endl;
        cin >> n;
        if(n == 1){
            printf("Iterative-Deepening Search:\n");
            if(IDS(bo, 0, zero, one) == false)
                printf("No Solution!\n");
            system("pause");
        }
        else if(n == 2){
            printf("\nUniform-Cost Search:\n");
            if(UCS(bo) == false)
                printf("No Solution!\n");
            system("pause");
        }
        else if(n == 3){
            printf("\nGreedy Best First Search:\n");
            if(GBFS(bo) == false)
                printf("No Solution!\n");
            system("pause");
        }
        else if(n == 4){
            printf("\nA Star Search:\n");
            if(Astar(bo) == false)
                printf("No Solution!\n");
            system("pause");
        }
        else if(n == 5){
            printf("\nRecursive Best First Search:\n");
            if(RBFS(board, 0, zero, one, 1e9) != 0)
                printf("No Solution!\n");
            system("pause");
        }
    }
    return 0;
}

//hashtable
size_t hashing(int H,int col,vector< vector<int> > board) {
	string result;
	for (size_t i = 0; i < board.size(); ++i) {
		for (size_t j = 0; j < board[i].size(); ++j) {
			string tmp;
            tmp = to_string(board[i][j]);
			result += tmp;
		}
	}
	result += to_string(H);
	result += to_string(col);
	return hash<string>{}(result);
}

void Solution(int board[QNUM][QNUM])    //Print processes and results of algorithms
{
    for (int i = 0; i < QNUM; i++)
    {
        for (int j = 0; j < QNUM; j++)
            if(board[i][j] == 0)
                printf(" 0 ");
            else
                printf(" 1 ");
        printf("\n");
    }
    printf("\n\n");
}

bool Check_Is_Save(int board[QNUM][QNUM], int row, int col)   //Examine whether or not every queen is save.
{
    int i, j;
    for (i = 0; i < QNUM; i++)
        if (board[row][i])
            return false;
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;
    for (i = row, j = col; i < QNUM && j < QNUM; i++, j++)
        if (board[i][j])
            return false;
    for (i = row, j = col; j >= 0 && i < QNUM; i++, j--)
        if (board[i][j])
            return false;
    for (i = row, j = col; j < QNUM && i >= 0; i--, j++)
        if (board[i][j])
            return false;
    return true;
}

bool IDS(int board[QNUM][QNUM], int col, int& moves, int& cond)
{
    if (col >= QNUM)
    {
        Solution(board);
        printf("The number of movements: %d\n", moves);
        printf("The maximum number of states ever saved: %d\n", cond);
        return true;
    }
    for(int i = 0; i < QNUM; i++){
        if(board[i][col] == 1){
            moves++;
            if (IDS(board, col + 1, moves, cond))
                return true;
        }
    }
    for (int i = 0; i < QNUM; i++)
    {
        cond++;
        if (Check_Is_Save(board, i, col))
        {
            moves++;
            board[i][col] = 1;
            if (IDS(board, col + 1, moves, cond))
                return true;
            board[i][col] = 0;
        }
    }
    return false;
}

bool UCS(int chessboard[QNUM][QNUM])
{
    vector< vector<int> > state(QNUM, vector<int>(QNUM));
    vector< vector<int> > tempv;
    priority_queue< P, vector <P>, less<P> > q;
    int moves = 0, cond = 1;
    for(int i = 0; i < QNUM; i++)
    {
        for(int j = 0; j < QNUM; j++)
            state[i][j] = chessboard[i][j];
    }
    q.push(P(0, state));
    while(!q.empty())
    {
        P temp = q.top();
        q.pop();
        int board[QNUM][QNUM];
        tempv = temp.second;
        int col = temp.first;
        for(int i = 0; i < QNUM; i++)
        {
            for(int j = 0; j < QNUM; j++)
                board[i][j] = tempv[i][j];
        }
        moves++;
        int flag = 0;
        for(int i = 0; i < QNUM; i++){
            if(board[i][col] == 1){
                cond++;
                if(col == Col){
                    Solution(board);
                    printf("The number of movements: %d\n", moves);
                    printf("The maximum number of states ever saved: %d\n", cond);
                    return true;
                }
                else
                    q.push(P(col + 1, tempv));
                flag=1;
            }
        }
        if(flag == 0){
            for (int i = 0; i < QNUM; i++)
            {
                if (Check_Is_Save(board, i, col))
                {
                    cond++;
                    board[i][col] = 1;
                    for(int i = 0; i < QNUM; i++)
                    {
                        for(int j = 0; j < QNUM; j++)
                            tempv[i][j] = board[i][j];
                    }
                    if(col == Col)
                    {
                        Solution(board);
                        moves++;
                        printf("The number of movements: %d\n", moves);
                        printf("The maximum number of states ever saved: %d\n", cond);
                        return true;
                    }
                    else
                        q.push(P(col + 1, tempv));
                    board[i][col] = 0;
                }
            }
        }
    }
    return false;
}

int compute_h(int board[QNUM][QNUM], int col)
{
    int cnt = 0;
    for (int i = col+1; i < QNUM; i++)
    {
        for (int j = 0; j < QNUM; j++)
        {
            if(board[j][i] != 1){
                board[j][i] = 1;
                if (!Check_Is_Save(board, j, i))
                    cnt++;
                board[j][i] = 0;
            }
        }
    }
    return cnt;
}

int compute_h2(int board[QNUM][QNUM], int col)
{
    int cnt = 0;
    cnt = QNUM - col -1 ;
    return cnt;
}

bool GBFS(int chessboard[QNUM][QNUM])
{
    vector< vector<int> > state(QNUM, vector<int>(QNUM));
    vector< vector<int> > tempv;
    priority_queue< T, vector <T>, greater<T> > q;
    int moves = 0, cond = 1;
    for(int i = 0; i < QNUM; i++)
    {
        for(int j = 0; j < QNUM; j++)
            state[i][j] = chessboard[i][j];
    }
    q.push(T(0, 0, state));
    while(!q.empty())
    {
        T temp = q.top();
        q.pop();
        int board[QNUM][QNUM];
        tempv = get<2>(temp);
        int col = get<1>(temp);

        for(int i = 0; i < QNUM; i++)
        {
            for(int j = 0; j < QNUM; j++)
                board[i][j] = tempv[i][j];
        }
        moves++;
        int flag = 0;

        for(int i = 0; i < QNUM; i++){
            if(board[i][col] == 1){
                cond++;
                if(col == Col){
                    Solution(board);
                    printf("The number of movements: %d\n", moves);
                    printf("The maximum number of states ever saved: %d\n", cond);
                    return true;
                }
                else
                    q.push(T(compute_h(board, col), col + 1, tempv));
                flag=1;
            }
        }
        if(flag == 0){
            for (int i = 0; i < QNUM; i++)
            {
                if (Check_Is_Save(board, i, col))
                {
                    cond++;
                    board[i][col] = 1;
                    for(int i = 0; i < QNUM; i++)
                    {
                        for(int j = 0; j < QNUM; j++)
                            tempv[i][j] = board[i][j];
                    }
                    if(col == Col)
                    {
                        Solution(board);
                        moves++;
                        printf("The number of movements: %d\n", moves);
                        printf("The maximum number of states ever saved: %d\n", cond);
                        return true;
                    }
                    else
                        q.push(T(compute_h(board, col), col + 1, tempv));

                    board[i][col] = 0;
                }
            }
        }
    }
    return false;
}

bool Astar(int chessboard[QNUM][QNUM])
{
    vector< vector<int> > state(QNUM, vector<int>(QNUM));
    vector< vector<int> > tempv;
    priority_queue< T, vector <T>, greater<T> > q;
    int moves = 0, cond = 1;
    for(int i = 0; i < QNUM; i++)
    {
        for(int j = 0; j < QNUM; j++)
            state[i][j] = chessboard[i][j];
    }
    q.push(T(0, 0, state));
    while(!q.empty())
    {
        T temp = q.top();
        q.pop();
        int board[QNUM][QNUM];
        tempv = get<2>(temp);
        int col = get<1>(temp);

        for(int i = 0; i < QNUM; i++)
        {
            for(int j = 0; j < QNUM; j++)
                board[i][j] = tempv[i][j];
        }
        moves++;
        int flag = 0;

        for(int i = 0; i < QNUM; i++){
            if(board[i][col] == 1){
                cond++;
                if(col == Col){
                    Solution(board);
                    printf("The number of movements: %d\n", moves);
                    printf("The maximum number of states ever saved: %d\n", cond);
                    return true;
                }
                else
                    q.push(T(compute_h(board, col) + col + 1, col + 1, tempv));
                flag=1;
            }
        }
        if(flag == 0){
            for (int i = 0; i < QNUM; i++)
            {
                if (Check_Is_Save(board, i, col))
                {
                    cond++;
                    board[i][col] = 1;
                    for(int i = 0; i < QNUM; i++)
                    {
                        for(int j = 0; j < QNUM; j++)
                            tempv[i][j] = board[i][j];
                    }
                    if(col == Col)
                    {
                        Solution(board);
                        moves++;
                        printf("The number of movements: %d\n", moves);
                        printf("The maximum number of states ever saved: %d\n", cond);
                        return true;
                    }
                    else
                        q.push(T(compute_h(board, col) + col + 1, col + 1, tempv));
                    board[i][col] = 0;
                }
            }
        }
    }
    return false;
}

int RBFS(int chessboard[QNUM][QNUM], int col, int& moves, int& cond, int limit)
{
    vector< vector<int> > state(QNUM, vector<int>(QNUM));
    static priority_queue< T, vector <T>, greater<T> > q;
    static unordered_map<size_t, vector<vector<int>>> visited;

    for(int i = 0; i < QNUM; i++)
    {
        for(int j = 0; j < QNUM; j++)
            state[i][j] = chessboard[i][j];
    }
    int flag = 0;

    for(int i = 0; i < QNUM; i++){
        if(chessboard[i][col] == 1){
            cond++;
            if(col == Col){
                cond -= q.size();
                while(!q.empty()){
                    q.pop();
                }
                visited.clear();
                Solution(chessboard);
                printf("The number of movements: %d\n", moves);
                printf("The maximum number of states ever saved: %d\n", cond);
                return true;
            }
            else{
                size_t tmpKey = hashing(compute_h2(chessboard, col), col + 1, state);
                if (visited.find(tmpKey) == visited.end()){
                    q.push(T(compute_h2(chessboard, col), col + 1, state));
                    visited[tmpKey] = state;
                }
            }
            if(col == 0)
                q.push(T(compute_h2(chessboard, col), col + 1, state));
            flag=1;
        }
    }

    if(flag == 0){
        for (int i = 0; i < QNUM; i++)
        {
            if (Check_Is_Save(chessboard, i, col))
            {
                cond++;
                chessboard[i][col] = 1;
                for(int i = 0; i < QNUM; i++)
                {
                    for(int j = 0; j < QNUM; j++)
                        state[i][j] = chessboard[i][j];
                }
                if(col == Col)
                {
                    cond -= q.size();
                    while(!q.empty()){
                        q.pop();
                    }
                    visited.clear();
                    Solution(chessboard);
                    moves++;
                    printf("The number of movements: %d\n", moves);
                    printf("The maximum number of states ever saved: %d\n", cond);
                    return 0;
                }
                else{
                    size_t tmpKey = hashing(compute_h2(chessboard, col), col + 1, state);
                    if (visited.find(tmpKey) == visited.end()){
                        q.push(T(compute_h2(chessboard, col), col + 1, state));
                        visited[tmpKey] = state;
                    }
                }
                chessboard[i][col] = 0;
            }
        }
    }

    while(!q.empty())
    {
        T tem = q.top();
        if(get<0>(tem) == 1e9)
        {
            q.pop();
            continue;
        }
        if(get<0>(tem) > limit){
            return get<0>(tem);
        }
        else
        {
            q.pop();
            T tem2 = q.top();
            int w[QNUM][QNUM];
            for(int i = 0; i < QNUM; i++)
            {
                for(int j = 0; j < QNUM; j++)
                    w[i][j] = get<2>(tem)[i][j];
            }
            moves++;
            get<0>(tem) = RBFS(w, get<1>(tem), moves, cond, min(limit, get<0>(tem2)));
            if(get<0>(tem) == 0)
                return 0;
            size_t tmpKey = hashing(get<0>(tem),get<1>(tem),get<2>(tem));
            if (visited.find(tmpKey) == visited.end()){
                q.push(tem);
                visited[tmpKey] = (get<0>(tem),get<1>(tem),get<2>(tem));
            }
        }
    }
    return 1e9;
}
