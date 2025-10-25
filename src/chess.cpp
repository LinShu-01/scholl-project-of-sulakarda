#include "../include/chess.hpp"
#include<iostream>
using namespace std;


Chess::Chess()
{
	init();
}

std::vector<std::vector<Qizi>>& Chess::getboard()
{
	return board_;
}

bool Chess::in_board(int now_row, int now_col, int new_row, int new_col)
{
	return  !(new_row >= BOARD_SIZE || new_col >= BOARD_SIZE ||
		new_row < 0 || new_col < 0 ||
		now_row >= BOARD_SIZE || now_col >= BOARD_SIZE ||
		now_row < 0 || now_col < 0

		);
}

int Chess::in_blue_O(int now_row, int now_col)
{
	if (!in_board(now_row, now_col, now_row, now_col) || !board_[now_row][now_col].isblue_)
		return -1;
	else if (now_row == 0 && (now_col == 1 || now_col == 4)) {
		if (1 == now_col) return 1;
		return 0;
	}
	else if (now_row == 1 && (now_col == 0 || now_col == 1 || now_col == 4 || now_col == 5)) {
		if (now_col < 2) return 1;
		return 0;
	}
	else if (now_row == 4 && (now_col == 0 || now_col == 1 || now_col == 4 || now_col == 5)) {
		if (now_col < 2) return 2;
		return 3;
	}
	else if (now_row == 5 && (now_col == 1 || now_col == 4)) {
		if (1 == now_col) return 2;
		return 3;
	}
	return -1;
}

int Chess::in_green_O(int now_row, int now_col)
{
	if (!in_board(now_row, now_col, now_row, now_col) || !board_[now_row][now_col].isgreen_)
		return -1;
	if (now_row == 0 && (now_col == 2 || now_col == 3)) {
		if (2 == now_col) return 1;
		return 0;
	}
	else if (now_row == 1 && (now_col == 2 || now_col == 3)) {
		if (2 == now_col) return 1;
		return 0;
	}
	else if (now_row == 2) {
		if (now_col < 3) return 1;
		return 0;
	}
	else if (now_row == 3) {
		if (now_col < 3) return 2;
		return 3;
	}
	else if (now_row == 4 && (now_col == 2 || now_col == 3)) {
		if (2 == now_col)return 2;
		return 3;
	}
	else if (now_row == 5 && (now_col == 2 || now_col == 3)) {
		if (2 == now_col) return 2;
		return 3;
	}
	return -1;
}

void Chess::init()
{
	//
	board_.assign(BOARD_SIZE, std::vector<Qizi>(BOARD_SIZE));
	white_total_num_ = black_total_num_ = 2 * BOARD_SIZE;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 2; j++){
			blue_O_[i].num_play[j] = 0;
			green_O_[i].num_play[j] = 0;
		}
	}
	blue_O_[0].num_play[0] = 3;
	blue_O_[1].num_play[0] = 3;
	blue_O_[2].num_play[1] = 3;
	blue_O_[3].num_play[1] = 3;
	green_O_[0].num_play[0] = 2;
	green_O_[1].num_play[0] = 2;
	green_O_[2].num_play[1] = 2;
	green_O_[3].num_play[1] = 2;
	//
	for (int row = 0; row < BOARD_SIZE; row++) {
		for (int col = 0; col < BOARD_SIZE; col++) {

			if (0 == row || 1 == row) board_[row][col].now_ = BLACK;
			else if (4 == row || 5 == row) board_[row][col].now_ = WHITE;
			else board_[row][col].now_ = EMPTY;
			//判断是否在线上
			if (0 == row || 5 == row || 0 == col || 5 == col) board_[row][col].isyellow_ = true;
			else board_[row][col].isyellow_ = false;
			if (1 == col || 4 == col || row == 1 && col == 0 || row == 4 && col == 0 ||
				row == 1 && col == 5 || row == 4 && col == 5)
				board_[row][col].isblue_ = true;
			else board_[row][col].isblue_ = false;
			if (3 == col || 2 == col || 2 == row || 3 == row)	board_[row][col].isgreen_ = true;
			else board_[row][col].isgreen_ = false;



		}
	}
}

bool Chess::move(int now_row, int now_col, int new_row, int new_col,Play now_play)
{
    if (!in_board(now_row,now_col,new_row,new_col)) return false;
    int drow = abs(new_row - now_row), dcol = abs(new_col - now_col);
    if (drow > 1 || dcol > 1) return false;
    if (now_play != board_[now_row][now_col].now_) return false;

    if (EMPTY == board_[new_row][new_col].now_ && EMPTY !=board_[now_row][now_col].now_) {

        if (-1 != in_blue_O(now_row, now_col)) {
            if (board_[now_row][now_col].now_ == BLACK) blue_O_[in_blue_O(now_row, now_col)].num_play[0]--;
            else blue_O_[in_blue_O(now_row, now_col)].num_play[1]--;
        }

        if (-1 != in_green_O(now_row, now_col)) {
            if (board_[now_row][now_col].now_ == BLACK) green_O_[in_green_O(now_row, now_col)].num_play[0]--;
            else green_O_[in_green_O(now_row, now_col)].num_play[1]--;
        }

        if (-1 != in_blue_O(new_row, new_col)) {
            if (board_[new_row][new_col].now_ == BLACK) blue_O_[in_blue_O(new_row, new_col)].num_play[0]++;
            else blue_O_[in_blue_O(new_row, new_col)].num_play[1]++;
        }

        if (-1 != in_green_O(new_row, new_col)) {
            if (board_[new_row][new_col].now_ == BLACK) green_O_[in_green_O(new_row, new_col)].num_play[0]++;
            else green_O_[in_green_O(new_row, new_col)].num_play[1]++;
        }

        board_[new_row][new_col].now_ = board_[now_row][now_col].now_;
        board_[now_row][now_col].now_ = EMPTY;
        return true;
    }
    return false;
}




bool Chess::move_u(int now_row, int now_col, int new_row, int new_col, Play now_play)
{
    if (EMPTY == board_[new_row][new_col].now_) {
        move(now_row, now_col, new_row, new_col, now_play);
        return true ;
    }
    return (eat_blue(now_row, now_col, new_row, new_col, now_play)
        || eat_green(now_row, now_col, new_row, new_col, now_play));
    
}

bool Chess::black_checkwin()
{
	if (0 == white_total_num_) return true;
	return false;
}

bool Chess::white_checkwin()
{
	if (0 == black_total_num_) return true;
	return false;
}
bool Chess::eat_blue(int now_row, int now_col, int new_row, int new_col, Play now_play)
{
    if (!in_board(now_row, now_col, new_row, new_col)) return false;
    if (EMPTY==now_play || now_play != board_[now_row][now_col].now_) return false;
    int drow = abs(new_row - now_row), dcol = abs(new_col - now_col);
    int b_index_new = in_blue_O(new_row, new_col);
    
    if (-1!=b_index_new && drow<2 && dcol<2) {
        if (blue_O_[b_index_new].num_play[board_[now_row][now_col].now_] == 0 
            || 1== blue_O_[b_index_new].num_play[board_[now_row][now_col].now_]&&board_[now_row][now_col].isblue_) {
            if (BLACK == board_[new_row][new_col].now_) black_total_num_--;
            else white_total_num_--;
            blue_O_[b_index_new].num_play[board_[new_row][new_col].now_]--;
            board_[new_row][new_col].now_ = EMPTY;
            move(now_row, now_col, new_row, new_col, now_play);
            return true;
        }
    }
    return false;
}
bool Chess::eat_green(int now_row, int now_col, int new_row, int new_col, Play now_play)
{
    if (!in_board(now_row, now_col, new_row, new_col)) return false;
    if (EMPTY == now_play || now_play != board_[now_row][now_col].now_) return false;
    int drow = abs(new_row - now_row), dcol = abs(new_col - now_col);
    int g_index = in_green_O(new_row, new_col);

    if (-1 != g_index && drow < 2 && dcol < 2) {
        if (green_O_[g_index].num_play[board_[now_row][now_col].now_] == 0
            || 1== green_O_[g_index].num_play[board_[now_row][now_col].now_]&&board_[now_row][now_col].isgreen_) {
            if (BLACK == board_[new_row][new_col].now_) black_total_num_--;
            else white_total_num_--;
            green_O_[g_index].num_play[board_[new_row][new_col].now_]--;
            board_[new_row][new_col].now_ = EMPTY;
            move(now_row, now_col, new_row, new_col, now_play);
            return true;
        }
    }
    return false;
}
bool Chess::gameover()
{
    return false;
}

bool Chess::checkwin(Play now_p)
{
    if (now_p == BLACK && 0 == white_total_num_ || now_p == WHITE && 0 == black_total_num_) return true;
    else if (gameover() &&
        (BLACK == now_p && black_total_num_ > white_total_num_ || 
        WHITE == now_p && white_total_num_ > black_total_num_))
        return true;
    return false;
}
void Chess::setOnum_color_init() 
{
	blue_O_[0].num_play[0] = 0;
	blue_O_[1].num_play[0] = 0;
	blue_O_[2].num_play[1] = 0;
	blue_O_[3].num_play[1] = 0;
	green_O_[0].num_play[0] = 0;
	green_O_[1].num_play[0] = 0;
	green_O_[2].num_play[1] = 0;
	green_O_[3].num_play[1] = 0;
}
void Chess::setOnum_color(int value,int row,int col) 
{
	//初始化黑、白棋的数量，方便统计目前各棋子的数量
	static int black_num = 0;
	static int white_num = 0;
	if (value == 0)black_num++;
	if (value == 1)white_num++;
	int sign = 0;//记录第几象限
	int ret=value;//记录是黑棋还是白棋
	if (ret != 2) 
	{
		if (in_blue_O(row, col) != -1)
		{
			sign = in_blue_O(row, col);
			blue_O_[sign].num_play[ret]++;
		}
		else if(in_green_O(row,col)!=-1)
		{
			sign = in_green_O(row, col);
			green_O_[sign].num_play[ret]++;
		}
	}


	black_total_num_ = black_num;
	white_total_num_ = white_num;
}

void Chess::printboard()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			cout << "第" << i << "象限： ";
			cout << blue_O_[i].num_play[j] << " ";
			cout << green_O_[i].num_play[j] << " ";
		}
		cout << endl;
	}
}

