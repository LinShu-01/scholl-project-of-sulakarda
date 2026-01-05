#include "../include/FileIO.h"
#include "../include/chess.hpp"
#include <string>

using namespace std;  // 添加这行

int main() {
    FileIO file;

    // 保存存档
    file.SaveGame();

    // 选择要加载的文件
    string filename = file.Get_load_filename();

    // 加载棋局
    Chess chess = file.LoadGame(filename);

    // 打印棋盘（如果你 chess 有 printboard）
    chess.printboard();

    return 0;
}
