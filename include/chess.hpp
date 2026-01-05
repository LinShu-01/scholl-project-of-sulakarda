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
	//bool isblue_hu_,isgreen_hu;
	//LineNode* yellow_line_, * blue_line_, * green_line_;
};//棋子
class Chess {
	//struct LineNode {
	//	LineNode* up_, * down_, * left_, * right_;
	//	LineNode() :up_(nullptr), down_(nullptr), left_(nullptr), right_(nullptr) {}
	//};//颜色线

	std::vector<std::vector<Qizi>> board_;//棋盘
	struct Onum {
		int num_play[2];//0为black,1为white
	} blue_O_[4], green_O_[4];
	int black_total_num_, white_total_num_;

public:
	Chess();
	std::vector<std::vector<Qizi>>& getboard();
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
};
