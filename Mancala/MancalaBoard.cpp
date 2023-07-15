#include<bits/stdc++.h>
#include "MancalaBoard.h"

using namespace std;


MancalaBoard::MancalaBoard()
{
    allocateBoard();
    initialSetValue();
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
void MancalaBoard::copyBoard(MancalaBoard temp)
{
    for (int i = 0; i < 2; ++i) {
        for (int j = 1; j <= 6; ++j) {
            board[i][j] = temp.getBinValue(i,j);
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

    for(int i = col-1;i>=0;i--){
            setBinValue(row,i,getBinValue(row,i)+1);
            value--;
            if(value==0)return;
    }

    int j = row;
    while(value>0){
        for(int i = 6;i>0;i--){
            setBinValue(j^1,i,getBinValue(j^1,i)+1);
            value--;
            if(value==0)return;
        }

        for(int i=6;i>=0;i--){
            value--;
            setBinValue(j,i,getBinValue(j,i)+1);

            if(i!=0){

                if(value==0){
                    if(getBinValue(j,i)==1){
                        int val = getBinValue(j^1,i);
                        setBinValue(j^1,i,0);
                        setBinValue(j,i,0);
                        setBinValue(j,0,val+1);
                    }
                    return;
                }
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


        for (int j = 1; j <= 6; ++j) {
            cout<<getBinValue(0,j)<<" | ";
        }
        cout<<'\n';

        for (int j = 6; j > 0; j--) {
            cout<<getBinValue(1,j)<<" | ";
        }
        cout<<"\n\n";


}

int MancalaBoard::Heuristic()
{
    return  heuristicValue=getBinValue(0,0)-getBinValue(1,0);
}
int MancalaBoard::getHeuristicValue()
{
    return heuristicValue;

}

void MancalaBoard::deallocateBoard()
{
    for (int i = 0; i < 2; ++i) {
        delete[] board[i];
    }
    delete[] board;
}
