#ifndef MANCALABOARD_H
#define MANCALABOARD_H



class MancalaBoard {

private:
    int **board;
    int heuristicValue;

public:

    MancalaBoard();

    void allocateBoard();
    void initialSetValue();
    int getBinValue(int row, int col);
    void setBinValue(int row, int col,int value);
    int isGameOver();
    void updateBoard(int row, int col);
    void deallocateBoard();
    void copyBoard(MancalaBoard temp);
    void BoardPrint();
    int Heuristic();
    int getHeuristicValue();

};



#endif
