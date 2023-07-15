#include<bits/stdc++.h>
#include "MancalaBoard.h"

using namespace std;


#define MAX 10000
#define MIN  -10000


struct Value
{
    int binNo;
    int heuristicValue;
};
int minimax(MancalaBoard mancalaBoard, int depth, bool maximizingPlayer, int alpha, int beta)
{
    if (depth == 5 || mancalaBoard.isGameOver()){
        int value =  mancalaBoard.Heuristic();
        return value;
    }

    if (maximizingPlayer)
    {
        int best = MIN,moveNo = -1;

        for (int i = 1; i <= 6; i++)
        {
            if(mancalaBoard.getBinValue(0,i) == 0) continue;

            MancalaBoard tempMancalaBoard;
            tempMancalaBoard.copyBoard(mancalaBoard);
            tempMancalaBoard.updateBoard(0,i);


            int val1 = minimax(tempMancalaBoard,depth + 1,false, alpha, beta);
            int val = tempMancalaBoard.getHeuristicValue();
            //deallocate
            tempMancalaBoard.deallocateBoard();

            if(best<=val){
                best = max(best, val);
                alpha = max(alpha, best);
                moveNo = i;
            }

            // Alpha Beta Pruning
            if (beta <= alpha)
                break;
        }
        //return best;
        return moveNo;
    }
    else
    {
        int best = MAX,moveNo=-1;

        for (int i = 1; i <= 6; i++)
        {
            if(mancalaBoard.getBinValue(1,i)==0) continue;

            MancalaBoard tempMancalaBoard;
            tempMancalaBoard.copyBoard(mancalaBoard);
            tempMancalaBoard.updateBoard(1,i);

            int val1 = minimax(tempMancalaBoard,depth + 1,true, alpha, beta);
            int val = tempMancalaBoard.getHeuristicValue();

            //deallocate
            tempMancalaBoard.deallocateBoard();

            if(best>=val){
                best = min(best, val);
                beta = min(beta, best);
                moveNo = i;
            }
            // Alpha Beta Pruning
            if (beta <= alpha)
                break;
        }
        //return best;
        return moveNo;
    }
}

int main()
{

    MancalaBoard mancalaBoard;

    mancalaBoard.BoardPrint();

    int binInput;
    cout<<"--------------------------\n";
    while(!mancalaBoard.isGameOver()){

        int binNo = minimax(mancalaBoard, 0, true, MIN, MAX );
        cout<<binNo<<'\n';
        mancalaBoard.updateBoard(0,binNo);

        mancalaBoard.BoardPrint();

        cout<<"Enter Bin No : \n";

        cin>>binInput;

        mancalaBoard.updateBoard(1,binInput);

        mancalaBoard.BoardPrint();

    }

}
