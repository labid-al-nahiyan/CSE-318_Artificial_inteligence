#include<bits/stdc++.h>
#include "MancalaBoard.h"

using namespace std;


MancalaBoard::MancalaBoard()
{
    allocateBoard();
    initialSetValue();
    additionalMove=0;
    stone_capture=0;
}

void MancalaBoard::allocateBoard()
{
    board = new int*[2];
    for (int i = 0; i < 2; ++i) {
        board[i] = new int[7];
    }
}

void MancalaBoard::initialSetValue()
{
    for (int i = 0; i < 2; ++i) {
        for (int j = 1; j <= 6; ++j) {
            board[i][j] = 4;
        }
    }
    board[0][0] = 0;
    board[1][0] = 0;
}
void MancalaBoard::copyBoard(MancalaBoard *temp)
{
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j <= 6; ++j) {
            board[i][j] = temp->getBinValue(i,j);
        }
    }
}

int MancalaBoard::getBinValue(int row , int col)
{
    return board[row][col];
}

void MancalaBoard::setBinValue(int row , int col,int value)
{
    board[row][col] = value;
}

void MancalaBoard::updateBoard(int row , int col)
{

    int value  = getBinValue(row,col);

    setBinValue(row,col,0);

    int j = row;

    for(int i = col-1;i>=0;i--){
            setBinValue(j,i,getBinValue(j,i)+1);
            value--;

            if(value==0){
                if(i!=0 && getBinValue(j^1,7-i)!=0){
                    if(getBinValue(j,i)==1){
                        int val = getBinValue(j^1,7-i);
                        stone_capture += val;
                        setBinValue(j^1,7-i,0);
                        setBinValue(j,i,0);
                        setBinValue(j,0,getBinValue(j,0)+val+1);
                    }
                }
                return;
            }
    }


    while(value>0){
        for(int i = 6;i>0;i--){
            setBinValue(j^1,i,getBinValue(j^1,i)+1);

            value--;
            if(value==0)return;
        }

        for(int i=6;i>=0;i--){
            value--;
            setBinValue(j,i,getBinValue(j,i)+1);
            if(value==0){

                if(i!=0 && getBinValue(j^1,7-i)!=0){
                    if(getBinValue(j,i)==1){
                        int val = getBinValue(j^1,7-i);
                        stone_capture += val;
                        setBinValue(j^1,7-i,0);
                        setBinValue(j,i,0);
                        setBinValue(j,0,getBinValue(j,0)+val+1);
                    }

                }
                return;
            }

        }
    }

}

int MancalaBoard::isGameOver()
{
    int player1 = 1 , player2 = 1;

    for(int i=1;i<=6;i++){
        if( board[0][i] != 0 ){
            player1 = 0;
            break;
        }
    }
    for(int i=1;i<=6;i++){
        if(board[1][i]!=0){
            player2 = 0 ;
            break;
        }
    }

    if(player1 || player2) return 1;

    return 0;

}

void MancalaBoard::BoardPrint()
{
        cout<<"___________________________________\n";
        cout<<"|    |";
        for (int j = 1; j <= 6; ++j) {
            cout<<getBinValue(0,j)<<" | ";
        }
        cout<<"    |\n| "<<getBinValue(0,0)<<"  |----------------------|  "<<getBinValue(1,0)<<"  |\n";

        cout<<"|    |";
        for (int j = 6; j >= 1; j--) {
            cout<<getBinValue(1,j)<<" | ";
        }
        cout<<"    |\n";

        cout<<"------------------------------------\n";

}

int MancalaBoard::Heuristic0(int playerNo)
{
    return  getBinValue(playerNo,0)-getBinValue(playerNo^1,0);
}

int MancalaBoard::Heuristic1(int playerNo)
{
    int value = getBinValue(playerNo,0)-getBinValue(playerNo^1,0);
    value*=2;

    int value1=0;
    for(int i =1;i<=6;i++){
        value1 += getBinValue(playerNo,i)-getBinValue(playerNo^1,i);
    }

    value1*=3;

    setHeuristicValue(value1+value);
    return getHeuristicValue();
}

int MancalaBoard::Heuristic2(int playerNo)
{
    int value = heuristicValue=getBinValue(playerNo,0)-getBinValue(playerNo^1,0);
    value*=2;

    int value1=0;
    for(int i =1;i<=6;i++){
        value1 += getBinValue(playerNo,i)-getBinValue(playerNo^1,i);
    }
    value1*=3;

    setHeuristicValue(value1+value+additionalMove);

    return getHeuristicValue();
}

int MancalaBoard::Heuristic3(int playerNo)
{
    int value = heuristicValue=getBinValue(playerNo,0)-getBinValue(playerNo^1,0);


    int value1=0;
    for(int i =1;i<=6;i++){
        value1 += getBinValue(playerNo,i)-getBinValue(playerNo^1,i);
    }
    value*=5;
    value1*=3;

    setHeuristicValue(value1+value+5*additionalMove+(rand()%5+1)*stone_capture);

    return getHeuristicValue();
}

int MancalaBoard::getHeuristicValue()
{
    return heuristicValue;

}
void MancalaBoard::setHeuristicValue(int value)
{

    heuristicValue = value;
}

void MancalaBoard::winner()
{
    player0_pt = getBinValue(0,0); player1_pt = getBinValue(1,0);

    for(int i =1;i<=6;i++){
        player0_pt += getBinValue(0,i);
        player1_pt += getBinValue(1,i);
    }


}

void MancalaBoard::deallocateBoard()
{
    for (int i = 0; i < 2; ++i) {
        delete[] board[i];
    }
    delete[] board;
}
