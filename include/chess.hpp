#pragma once
#include<vector>
#include<cstdlib>

#define BOARD_SIZE 6

enum Play
{
    BLACK,
    WHITE,
    EMPTY
};
struct Qizi {
    Play now_;
    bool isyellow_, isblue_, isgreen_;
};//棋子
class Chess {

    std::vector<std::vector<Qizi>> board_;//棋盘
    struct Onum {
        int num_play[2];//0为black,1为white
    } blue_O_[4], green_O_[4];
    int black_total_num_, white_total_num_;

public:
    Chess();
    std::vector<std::vector<Qizi>>& getboard();
    const std::vector<std::vector<Qizi>>& getboard() const;
    bool in_board(int now_row, int now_col, int new_row, int new_col);
    int in_blue_O(int now_row, int now_col);//
    int in_green_O(int now_row, int now_col);//
    void init();//
    bool move(int now_row, int now_col, int new_row, int new_col,Play now_play);
    bool move_u(int now_row, int now_col, int new_row, int new_col, Play now_play);
    bool black_checkwin();
    bool white_checkwin();
    bool eat_blue(int now_row, int now_col, int new_row, int new_col, Play now_play);
    bool eat_green(int now_row, int now_col, int new_row, int new_col, Play now_play);
    bool gameover();
    bool checkwin(Play now_p);
    //LoadGame需要的函数
    void setOnum_color_init();
    void setOnum_color(int value,int row,int col);//1.统计黑棋和白棋的数量。2.计算blue_0和green_0
    void printboard();//
    //用于AI计算的评估函数
    int getPieceCount(Play color);
    bool isValidMove(int now_row, int now_col, int new_row, int new_col, Play color);
    //用于AI的辅助方法
    Qizi getPiece(int row, int col) const;
    void setPiece(int row, int col, const Qizi& piece);
    bool canMove(int now_row, int now_col, int new_row, int new_col, Play color);
    std::vector<std::pair<int, int>> getPossibleMoves(int row, int col, Play color);
};