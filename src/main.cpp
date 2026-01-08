#include "../include/FileIO.h"
#include "../include/chess.hpp"
#include "../include/ai.hpp"
#include <string>
#include <iostream>

using namespace std;

int main() {
    FileIO file;
    int game_mode = 0;
    string filename;
    Chess chess;

    // 菜单选择
    cout << "=== 象棋游戏 ===" << endl;
    cout << "1. 新游戏 (人 vs 电脑)" << endl;
    cout << "2. 新游戏 (人 vs 人)" << endl;
    cout << "3. 加载存档" << endl;
    cout << "请选择: ";
    cin >> game_mode;

    if (game_mode == 3) {
        // 加载存档
        filename = file.Get_load_filename();
        if (filename == "") {
            cout << "加载失败，退出游戏!" << endl;
            return 0;
        }
        chess = file.LoadGame(filename);
    } else {
        // 新游戏
        chess.init();
    }

    chess.printboard();

    // 初始化 AI
    ChessAI ai(WHITE, BLACK);
    
    int difficulty = 0;
    if (game_mode == 1) {
        cout << "\n选择难度: 1(简单) 2(中等) 3(困难): ";
        cin >> difficulty;
        if (difficulty < 1 || difficulty > 3) difficulty = 2;
        ai.setDifficulty(difficulty);
    }

    Play current_player = BLACK;
    bool game_continue = true;

    // 游戏主循环
    while (!chess.gameover() && game_continue) {
        cout << "\n" << (current_player == BLACK ? "黑棋" : "白棋") << "的回合" << endl;

        if (current_player == BLACK) {
            // 人类玩家输入
            int now_row, now_col, new_row, new_col;
            
            cout << "输入当前位置 (行 列): ";
            cin >> now_row >> now_col;
            
            cout << "输入目标位置 (行 列): ";
            cin >> new_row >> new_col;

            if (chess.move(now_row, now_col, new_row, new_col, BLACK)) {
                cout << "移动成功!" << endl;
                current_player = WHITE;
            } else {
                cout << "无效的移动，请重试!" << endl;
                continue;
            }
        } else if (game_mode == 1) {
            // AI 自动计算移动
            cout << "AI 正在思考..." << endl;
            Move ai_move = ai.getBestMove(chess);
            
            if (ai_move.now_row != -1) {
                if (chess.move(ai_move.now_row, ai_move.now_col, 
                              ai_move.new_row, ai_move.new_col, WHITE)) {
                    cout << "AI 移动: (" << ai_move.now_row << "," << ai_move.now_col 
                         << ") -> (" << ai_move.new_row << "," << ai_move.new_col << ")" << endl;
                    current_player = BLACK;
                } else {
                    cout << "AI 移动失败!" << endl;
                    break;
                }
            } else {
                cout << "AI 无法移动，游戏结束!" << endl;
                break;
            }
        } else {
            // 人 vs 人模式，白棋也是人类输入
            int now_row, now_col, new_row, new_col;
            
            cout << "输入当前位置 (行 列): ";
            cin >> now_row >> now_col;
            
            cout << "输入目标位置 (行 列): ";
            cin >> new_row >> new_col;

            if (chess.move(now_row, now_col, new_row, new_col, WHITE)) {
                cout << "移动成功!" << endl;
                current_player = BLACK;
            } else {
                cout << "无效的移动，请重试!" << endl;
                continue;
            }
        }

        // 打印棋盘
        chess.printboard();

        // 检查是否游戏结束
        if (chess.gameover()) {
            if (chess.checkwin(BLACK)) {
                cout << "\n黑棋胜利!" << endl;
            } else if (chess.checkwin(WHITE)) {
                cout << "\n白棋胜利!" << endl;
            }
        }
    }

    // 询问是否保存
    cout << "\n是否保存游戏? (1=是, 0=否): ";
    int save_choice = 0;
    cin >> save_choice;
    
    if (save_choice == 1) {
        file.SaveGame(chess);
    }

    cout << "游戏结束，谢谢游玩!" << endl;
    return 0;
}