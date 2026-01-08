#pragma once
#include "chess.hpp"
#include <vector>
#include <utility>

struct Move {
    int now_row, now_col, new_row, new_col;
    int score;
    
    Move() : now_row(-1), now_col(-1), new_row(-1), new_col(-1), score(0) {}
    Move(int nr, int nc, int nnr, int nnc) 
        : now_row(nr), now_col(nc), new_row(nnr), new_col(nnc), score(0) {}
};

class ChessAI {
private:
    Chess chess_backup_; // 备份棋盘用于搜索
    Play ai_color_;
    Play player_color_;
    int difficulty_; // 1:简单 2:中等 3:困难
    int search_depth_;
    
    // 评估函数
    int evaluateBoard(const Chess& chess);
    int evaluatePosition(int row, int col, Play color, const Chess& chess);
    
    // 极小极大算法
    int minimax(Chess& chess, int depth, int alpha, int beta, bool isMaximizing);
    
    // 获取所有可能的移动
    std::vector<Move> getAllPossibleMoves(Chess& chess, Play color);
    
    // 移动棋子（用于搜索）
    bool makeMove(Chess& chess, const Move& move, Play color);
    void undoMove(Chess& chess, const Move& move, const Qizi& captured);

public:
    ChessAI(Play ai_color, Play player_color);
    
    // AI 计算最佳移动
    Move getBestMove(Chess& chess);
    
    // 难度设置
    void setDifficulty(int level); // 1:简单 2:中等 3:困难
    
    // 获取搜索深度
    int getSearchDepth() const { return search_depth_; }
};