#include <bits/stdc++.h>

using namespace std;


// Here it is guaranteed that for depth 13, the program
// will take about let's say less than minute for any possible state.
const int NumberOfMovesToCalculate = 13;




vector<int> GetMoves(const vector<int>& board, int turn, int score) {

    vector<int> moves;
    if (!turn) {

        bool opponentHasStones = 0;
        for (int i = 7; i < 14; i++) {
            if (board[i]) {
                opponentHasStones = 1;
                break;
            }
        }

        if (!opponentHasStones) {
            for (int i = 0; i < 7; i++) {
                if (!board[i]) {
                    continue;
                }
                else if (board[i] == 1) {
                    if (score && (i + 1 >= 7)) {
                        moves.push_back(i);
                    }
                }
                else if (i + board[i] >= 7) {
                    moves.push_back(i);
                }
            }
        }
        else {
            for (int i = 0; i < 7; i++) {
                if (board[i] == 0) {
                    continue;
                }
                if (board[i] == 1) {
                    if (score) {
                        moves.push_back(i);
                    }
                }
                else {
                    moves.push_back(i);
                }
            }
        }

    }
    else {

        bool opponentHasStones = 0;
        for (int i = 0; i < 7; i++) {
            if (board[i]) {
                opponentHasStones = 1;
                break;
            }
        }

        if (!opponentHasStones) {
            for (int i = 7; i < 14; i++) {
                if (!board[i]) {
                    continue;
                }
                else if (board[i] == 1) {
                    if (score && (i + 1 >= 14)) {
                        moves.push_back(i);
                    }
                }
                else if (i + board[i] >= 14) {
                    moves.push_back(i);
                }
            }
        }
        else {
            for (int i = 7; i < 14; i++) {
                if (board[i] == 0) {
                    continue;
                }
                if (board[i] == 1) {
                    if (score) {
                        moves.push_back(i);
                    }
                }
                else {
                    moves.push_back(i);
                }
            }
        }

    }

    return moves;

}


int MakeMove(vector<int>& board, int hole) {

    int how = board[hole];
    board[hole] = 0;
    int pos = (hole + 1) % 14;
    while (how--) {

        board[pos]++;
        pos++;
        pos %= 14;

    }

    pos--;
    pos += 14;
    pos %= 14;

    int increase = 0;
    while (1) {

        if ((board[pos] == 2) || (board[pos] == 4)) {
            increase += board[pos];
            board[pos] = 0;
            pos--;
            pos += 14;
            pos %= 14;

        }
        else {
            break;
        }

    }

    return increase;

}


int Play(vector<int> board, bool turn, int myScore, int opponentScore, int depth,
         int alpha, int beta) {

    if (depth == 0) {
        return myScore - opponentScore;
    }

    if (!turn) {

        int choice = -10000;
        vector<int> moves = GetMoves(board, turn, myScore);
        for (const int& hole : moves) {

            vector<int> boardCopy = board;
            int myScoreCopy = myScore;
            myScoreCopy += MakeMove(boardCopy, hole);
            choice = max(choice,
                         Play(boardCopy, !turn, myScoreCopy, opponentScore, depth - 1, alpha, beta));

            alpha = max(alpha, choice);
            if (beta <= alpha) {
                break;
            }

        }

        if (choice == -10000) {
            myScore += accumulate(board.begin(), board.begin() + 7, 0);
            return (myScore - opponentScore);
        }

        return choice;

    }
    else {

        int choice = 10000;
        vector<int> moves = GetMoves(board, turn, opponentScore);
        for (const int& hole : moves) {

            vector<int> boardCopy = board;
            int opponentScoreCopy = opponentScore;
            opponentScoreCopy += MakeMove(boardCopy, hole);
            choice = min(choice,
                         Play(boardCopy, !turn, myScore, opponentScoreCopy, depth - 1, alpha, beta));

            beta = min(beta, choice);
            if (beta <= alpha) {
                break;
            }

        }

        if (choice == 10000) {
            opponentScore += accumulate(board.begin() + 7, board.end(), 0);
            return (myScore - opponentScore);
        }

        return choice;

    }

}


void PrintTheBoard(const vector<int>& board, int myScore,
                   int opponentScore, int toPrint) {

    cout << "          " << opponentScore << endl << endl << "   ";
    for (int i = 13; i >= 7; i--) {
        cout << board[i] << " ";
    }

    cout << endl << endl << "   ";

    for (int i = 0; i < 7; i++) {
        cout << board[i] << " ";
    }
    cout << endl << "   ";
    for (int i = 0; i < 7; i++) {
        int helper = log10(board[i]);
        for (int j = 0; j < helper; j++) {
            cout << " ";
        }
        if (i == toPrint) {
            cout << "*";
        }
        else {
            cout << "  ";
        }
    }
    cout << endl << "          " << myScore << endl;
    cout << "   #################" << endl << endl;


    /*
    cout << "          " << myScore << endl << endl;

    for (int i = 6; i >= 0; i--) {
        int helper = log10(board[i]);
        for (int j = 0; j < helper; j++) {
            cout << " ";
        }
        if (i == toPrint) {
            cout << "*";
        }
        cout << "    ";

    }
    cout << endl;
    for (int i = 6; i >= 0; i--) {
        cout << board[i] << "   ";
    }
    cout << endl << endl << endl;

    for (int i = 7; i < 14; i++) {
        cout << board[i] << "   ";
    }
    cout << endl << endl << "          " << opponentScore << endl << endl;

    cout << "   ###################" << endl;
    */

}


int main() {

    vector<int> board(14, 7);
    int myScore = 0;
    int opponentScore = 0;

    int turnToCin;
    cout << "If you want to play first press 1, else press 2:" << endl;
    cin >> turnToCin;


    bool turn;
    if (turnToCin == 2) {

        turn = 0;

    }
    else {

        turn = 1;

    }


    PrintTheBoard(board, myScore, opponentScore, -1);


    while (1) {

        if (!turn) {

            pair<int, int> choice = {-10000, 1};
            vector<int> moves = GetMoves(board, turn, myScore);
            for (const int& hole : moves) {

                vector<int> boardCopy = board;
                int myScoreCopy = myScore;
                myScoreCopy += MakeMove(boardCopy, hole);
                choice = max(choice,
                             {Play(boardCopy, 1, myScoreCopy, opponentScore, NumberOfMovesToCalculate - 1, -10000, 10000), hole});

            }

            if (choice.first == -10000) {
                myScore += accumulate(board.begin(), board.begin() + 7, 0);
                opponentScore += accumulate(board.begin() + 7, board.end(), 0);
                break;
            }
            else {
                myScore += MakeMove(board, choice.second);
            }

            PrintTheBoard(board, myScore, opponentScore, choice.second);

            turn = !turn;

        }
        else {

            vector<int> allowedMoves = GetMoves(board, 1, opponentScore);
            if ((int)allowedMoves.size() == 0) {
                opponentScore += accumulate(board.begin() + 7, board.end(), 0);
                myScore += accumulate(board.begin(), board.begin() + 7, 0);
                break;
            }

            cout << "It is your turn, choose what to play from 1 to 7:" << endl;

            bool ok = 0;
            int hole;
            while (!ok) {

                cin >> hole;
                hole += 6;
                for (const int& currentHole : allowedMoves) {
                    if (hole == currentHole) {
                        ok = 1;
                        break;
                    }
                }
                if (ok) {
                    break;
                }
                else {
                    cout << "Invalid move, choose another hole:" << endl;
                }

            }

            cout << endl;


            opponentScore += MakeMove(board, hole);
            PrintTheBoard(board, myScore, opponentScore, -1);

            turn = !turn;

        }

    }



    cout << "The Game has ended..." << endl;

    PrintTheBoard(board, myScore, opponentScore, -1);

    cout << "Computer's score: " << myScore << endl;
    cout << "Mr. z score: " << opponentScore << endl << endl;


    if (myScore > opponentScore) {
        cout << "I won as usual..." << endl;
    }
    else if (opponentScore > myScore) {
        cout << "Gongrats, you won." << endl;
    }
    else {
        cout << "Wow, it is a tie." << endl;
    }

    cout << "Goodbye..." << endl;


    return 0;
}
