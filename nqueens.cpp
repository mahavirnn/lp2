#include<bits/stdc++.h>
using namespace std;

class CSP {
    int n;
    vector<string> board;
    vector<vector<string>> poss;
public:
    CSP() {
        n = 0;
        board.resize(n);
    }

    void takeInput() {
        cout << "Enter number of rows :- ";
        cin >> n;

        board.resize(n);
        string tmp(n,'.');
        for(int i = 0;i < n;i++) board[i] = tmp;
    }

    void placeNQueensUtil(int col,vector<string> &board,map<int,bool> &ud, map<int,bool> &ld, map<int,bool> &l) {
        if(col >= n) {
            poss.push_back(board);
            return;
        }

        for(int row = 0;row < n;row++) {
            if(!ud[n-1 + col-row] && !ld[row+col] && !l[row]) {
                ud[n-1 + col-row] = true;
                ld[row+col] = true;
                l[row] = true;
                board[row][col] = 'Q';

                placeNQueensUtil(col+1,board,ud,ld,l);

                ud[n-1 + col-row] = false;
                ld[row+col] = false;
                l[row] = false;
                board[row][col] = '.';
            }
        }
    }

    void placeNQueens() {
        map<int,bool> ud,ld,l;

        placeNQueensUtil(0,board,ud,ld,l);

        cout << "Total Possibilites: " << poss.size() << "\n";
        printPoss();
    }

    void printPoss() {
         for(auto mat : poss) {
            cout << "----------------------------------------------------------------\n";
            for(int r = 0;r < n;r++) {
                 for(int c = 0;c < n;c++){
                    cout << mat[r][c];
                 }
                 cout << "\n";
            }
        }
        cout << "----------------------------------------------------------------\n";
    }

};

int main() {

    CSP obj;

    obj.takeInput();
    obj.placeNQueens();

    return 0;
}
