#include<bits/stdc++.h>
#include "MancalaBoard.h"

using namespace std;


#define MAX 100000
#define MIN  -100000


int minimax(MancalaBoard *mancalaBoard, int depth, bool maximizingPlayer, int alpha, int beta,int playerNo)
{
    if (depth == 0 || mancalaBoard->isGameOver()){
        int value ;
        if(playerNo==0){
                value = mancalaBoard->Heuristic3(playerNo);


        }
        else{
                value = mancalaBoard->Heuristic1(playerNo);
        }
        mancalaBoard->setHeuristicValue(value);
        return 0;
    }

    if (maximizingPlayer)
    {
        int best = MIN,moveNo = -1;

        for (int i = 1; i <= 6; i++)
        {
            int value = mancalaBoard->getBinValue(playerNo,i) ;
            if(value == 0) continue;

            MancalaBoard tempMancalaBoard;
           tempMancalaBoard.copyBoard(mancalaBoard);
//           for (int i = 0; i < 2; ++i) {
//                for (int j = 0; j <= 6; ++j) {
//                    tempMancalaBoard.setBinValue(i,j,mancalaBoard->getBinValue(i,j));
//                }
//            }





            tempMancalaBoard.updateBoard(playerNo,i);


            if(value-i==0 || (value-i)%13==0 ){

                tempMancalaBoard.additionalMove+=mancalaBoard->additionalMove+1;
                minimax(&tempMancalaBoard,depth - 1 , maximizingPlayer , alpha, beta,playerNo);

            }

            else{
                int val1 = minimax(&tempMancalaBoard,depth - 1,!maximizingPlayer, alpha, beta,playerNo);
            }
            int val = tempMancalaBoard.getHeuristicValue();

            //deallocate
            tempMancalaBoard.deallocateBoard();

            if(best<val){
                best = max(best, val);

                moveNo = i;
            }
            alpha = max(alpha, best);
            // Alpha Beta Pruning
            if (beta <= alpha)
                break;
        }
        //return best;
        mancalaBoard->setHeuristicValue(best);
        return moveNo;
    }
    else
    {
        int best = MAX,moveNo=-1;

        for (int i = 1; i <= 6; i++)
        {
            int value = mancalaBoard->getBinValue(playerNo^1,i);//...........................
            if(value==0) continue;

            MancalaBoard tempMancalaBoard;
            tempMancalaBoard.copyBoard(mancalaBoard);
//           for (int i = 0; i < 2; ++i) {
//                for (int j = 0; j <= 6; ++j) {
//                    tempMancalaBoard.setBinValue(i,j,mancalaBoard->getBinValue(i,j));
//                }
//            }



            tempMancalaBoard.updateBoard(playerNo^1,i);//..........................

            if(value-i==0 || (value-i)%13==0 ){
                minimax(&tempMancalaBoard,depth - 1,maximizingPlayer, alpha, beta,playerNo);
            }

            else{
                int val1 = minimax(&tempMancalaBoard,depth - 1,!maximizingPlayer, alpha, beta,playerNo);
            }
            int val = tempMancalaBoard.getHeuristicValue();

            //deallocate
            tempMancalaBoard.deallocateBoard();

            if(best>val){
                best = min(best, val);
                moveNo = i;
            }
            beta = min(beta, best);
            // Alpha Beta Pruning
            if (beta <= alpha)
                break;
        }
        //return best;
       // mancalaBoard.setHeuristicValue(best);
       mancalaBoard->setHeuristicValue(best);
        return moveNo;
    }
}

void AIvsAI()
{
    MancalaBoard mancalaBoard;
    mancalaBoard.BoardPrint();

    int binInput;
    cout<<"--------------------------\n";
    int playerNo = 0;
    while(!mancalaBoard.isGameOver()){

        int binNo = minimax(&mancalaBoard, 5, true, MIN, MAX ,playerNo);
        cout<<"Player NO : " <<playerNo<< "___ binNo :"<<binNo<<'\n';

        int value = mancalaBoard.getBinValue(playerNo,binNo);

        mancalaBoard.updateBoard(playerNo,binNo);
        mancalaBoard.BoardPrint();

        if(!((value-binNo)==0 || (value-binNo)%12==0)){
            playerNo^=1;
        }
    }


    mancalaBoard.winner();

    cout<<"AI 1 : "<<mancalaBoard.player0_pt<<"\n";
    cout<<"AI 2 : "<<mancalaBoard.player1_pt<<"\n";

    if(mancalaBoard.player0_pt > mancalaBoard.player1_pt){
        cout<<"Winner is AI 1\n";
    }
    else if(mancalaBoard.player0_pt < mancalaBoard.player1_pt){
        cout<<"Winner is AI 2\n";
    }
    else {
        cout<<"Draw\n";
    }

    mancalaBoard.deallocateBoard();
}

void AIvsHuman()
{
    MancalaBoard mancalaBoard;

    mancalaBoard.BoardPrint();

    int binInput;
    cout<<"--------------------------\n";
    int playerNo = 0;
    while(!mancalaBoard.isGameOver()){

        if(playerNo == 0){
            int binNo = minimax(&mancalaBoard, 10, true, MIN, MAX ,playerNo);
            cout<<"Player NO : " <<playerNo<< "___ binNo :"<<binNo<<'\n';

            int value = mancalaBoard.getBinValue(playerNo,binNo);

            mancalaBoard.updateBoard(playerNo,binNo);

            mancalaBoard.BoardPrint();

            if(!((value-binNo)==0 || (value-binNo)%12==0)){
                playerNo^=1;
            }
        }
        else{

            int binNo;
            cout<<"Enter Bin No : ";
            cin>>binNo;

            if(mancalaBoard.getBinValue(playerNo,binNo)==0){
                cout<<"Invalid move\n";
                continue;
            }

            int value = mancalaBoard.getBinValue(playerNo,binNo);

            mancalaBoard.updateBoard(playerNo,binNo);

            mancalaBoard.BoardPrint();

            if(!((value-binNo)==0 || (value-binNo)%12==0)){
                playerNo^=1;
            }
        }
    }

    mancalaBoard.winner();

    cout<<"AI     : "<<mancalaBoard.player0_pt<<"\n";
    cout<<"Human  : "<<mancalaBoard.player1_pt<<"\n";

    if(mancalaBoard.player0_pt > mancalaBoard.player1_pt){
        cout<<"Winner is AI \n";
    }
    else if(mancalaBoard.player0_pt < mancalaBoard.player1_pt){
        cout<<"Winner is Human\n";
    }
    else {
        cout<<"Draw\n";
    }

    mancalaBoard.deallocateBoard();
}

int main()
{

      //  AIvsAI();

        AIvsHuman();



}
