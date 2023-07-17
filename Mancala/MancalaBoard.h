#ifndef MANCALABOARD_H
#define MANCALABOARD_H



class MancalaBoard {

private:
    int **board;
    int heuristicValue;

public:

    MancalaBoard();

    int additionalMove,stone_capture;

    void allocateBoard();
    void updateBoard(int row, int col);
    void deallocateBoard();
    void copyBoard(MancalaBoard *temp);
    void BoardPrint();

    void initialSetValue();
    int getBinValue(int row, int col);
    void setBinValue(int row, int col,int value);
    int isGameOver();

    int Heuristic0(int playerNo);
    int Heuristic1(int playerNo);
    int Heuristic2(int playerNo);
    int Heuristic3(int playerNo);
    int getHeuristicValue();
    void setHeuristicValue(int value);

    int player0_pt, player1_pt;
    void winner();

};



#endif
