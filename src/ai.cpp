#include "ai.hpp"
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>

ChessAI::ChessAI(Play ai_color, Play player_color)
    : ai_color_(ai_color), player_color_(player_color), difficulty_(2), search_depth_(4)
{
}

void ChessAI::setDifficulty(int level)
{
    difficulty_ = level;
    switch (level) {
        case 1: search_depth_ = 2; break; // 简单
        case 2: search_depth_ = 4; break; // 中等
        case 3: search_depth_ = 6; break; // 困难
        default: search_depth_ = 4;
    }
}

// 评估棋盘得分
int ChessAI::evaluateBoard(const Chess& chess)
{
    const std::vector<std::vector<Qizi>>& board = chess.getboard();
    int ai_score = 0;
    int player_score = 0;
    
    // 统计棋子数量和位置分值
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j].now_ == ai_color_) {
                ai_score += 10;
                // 靠近对方底部得分更高
                if (ai_color_ == BLACK) {
                    ai_score += (BOARD_SIZE - i - 1) * 2;
                } else {
                    ai_score += i * 2;
                }
                // 有特殊标记加分
                if (board[i][j].isyellow_) ai_score += 5;
                if (board[i][j].isblue_) ai_score += 3;
                if (board[i][j].isgreen_) ai_score += 3;
            }
            else if (board[i][j].now_ == player_color_) {
                player_score += 10;
                if (player_color_ == BLACK) {
                    player_score += (BOARD_SIZE - i - 1) * 2;
                } else {
                    player_score += i * 2;
                }
                if (board[i][j].isyellow_) player_score += 5;
                if (board[i][j].isblue_) player_score += 3;
                if (board[i][j].isgreen_) player_score += 3;
            }
        }
    }
    
    return ai_score - player_score;
}

// 获取所有可能的移动
std::vector<Move> ChessAI::getAllPossibleMoves(Chess& chess, Play color)
{
    std::vector<Move> moves;
    const std::vector<std::vector<Qizi>>& board = chess.getboard();
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j].now_ == color) {
                // 获取该棋子的所有可能移动
                std::vector<std::pair<int, int>> possible = chess.getPossibleMoves(i, j, color);
                for (auto& pos : possible) {
                    moves.push_back(Move(i, j, pos.first, pos.second));
                }
            }
        }
    }
    
    return moves;
}

// 极小极大算法
int ChessAI::minimax(Chess& chess, int depth, int alpha, int beta, bool isMaximizing)
{
    // 递归终止条件
    if (depth == 0 || chess.gameover()) {
        return evaluateBoard(chess);
    }
    
    Play current_color = isMaximizing ? ai_color_ : player_color_;
    std::vector<Move> moves = getAllPossibleMoves(chess, current_color);
    
    if (moves.empty()) {
        return evaluateBoard(chess);
    }
    
    if (isMaximizing) {
        int maxEval = -10000;
        for (auto& move : moves) {
            // 尝试移动
            const std::vector<std::vector<Qizi>>& board = chess.getboard();
            Qizi captured = board[move.new_row][move.new_col];
            
            if (chess.move(move.now_row, move.now_col, move.new_row, move.new_col, current_color)) {
                int eval = minimax(chess, depth - 1, alpha, beta, false);
                
                // 撤销移动（恢复棋盘）
                chess.move(move.new_row, move.new_col, move.now_row, move.now_col, current_color);
                const_cast<std::vector<std::vector<Qizi>>&>(chess.getboard())[move.new_row][move.new_col] = captured;
                
                maxEval = std::max(maxEval, eval);
                alpha = std::max(alpha, eval);
                if (beta <= alpha) break; // Alpha-beta剪枝
            }
        }
        return maxEval;
    } else {
        int minEval = 10000;
        for (auto& move : moves) {
            const std::vector<std::vector<Qizi>>& board = chess.getboard();
            Qizi captured = board[move.new_row][move.new_col];
            
            if (chess.move(move.now_row, move.now_col, move.new_row, move.new_col, current_color)) {
                int eval = minimax(chess, depth - 1, alpha, beta, true);
                
                chess.move(move.new_row, move.new_col, move.now_row, move.now_col, current_color);
                const_cast<std::vector<std::vector<Qizi>>&>(chess.getboard())[move.new_row][move.new_col] = captured;
                
                minEval = std::min(minEval, eval);
                beta = std::min(beta, eval);
                if (beta <= alpha) break;
            }
        }
        return minEval;
    }
}

// 获取最佳移动
Move ChessAI::getBestMove(Chess& chess)
{
    std::vector<Move> moves = getAllPossibleMoves(chess, ai_color_);
    
    if (moves.empty()) {
        return Move(); // 无法移动
    }
    
    Move best_move = moves[0];
    int best_score = -10000;
    
    for (auto& move : moves) {
        const std::vector<std::vector<Qizi>>& board = chess.getboard();
        Qizi captured = board[move.new_row][move.new_col];
        
        if (chess.move(move.now_row, move.now_col, move.new_row, move.new_col, ai_color_)) {
            int score = minimax(chess, search_depth_ - 1, -10000, 10000, false);
            
            // 撤销移动
            chess.move(move.new_row, move.new_col, move.now_row, move.now_col, ai_color_);
            const_cast<std::vector<std::vector<Qizi>>&>(chess.getboard())[move.new_row][move.new_col] = captured;
            
            if (score > best_score) {
                best_score = score;
                best_move = move;
            }
        }
    }
    
    return best_move;
}