#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<filesystem>
#include <algorithm>
#include"../include/FileIO.h"
#include"../include/chess.hpp"
using namespace std;
namespace fs = std::filesystem;

string FileIO::GetCurrentTime(const string& format)
{
    //获取当前时间
    time_t now=time(0);
    //转换为结构化时间
    tm *timeinfo=localtime(&now);
    //准备输出缓冲区
    char buffer[80];
    //格式化时间
    strftime(buffer,sizeof(buffer),format.c_str(),timeinfo);
    //将字符数组转换成string并返回
    return string(buffer);
}

bool FileIO::SaveGame(const Chess& chess)
{
    string time=GetCurrentTime("%Y-%m-%d_%H-%M-%S");
    string filename="../output/game_save_"+time+".txt";
    //将数据记录下来
    ofstream ofs;
    ofs.open(filename, ios::out);
    
    if (!ofs.is_open()) {
        cout << "文件打开失败，无法保存游戏!" << endl;
        return false;
    }
    
    const vector<vector<Qizi>>& ch_c = chess.getboard();
    
    // 保存棋盘状态
    for (int i = 0; i < BOARD_SIZE; i++) 
    {
        for (int j = 0; j < BOARD_SIZE; j++) 
        {
            ofs << ch_c[i][j].now_ << " ";
            // 保存棋子的标记状态
            ofs << (ch_c[i][j].isyellow_ ? 1 : 0) << " ";
            ofs << (ch_c[i][j].isblue_ ? 1 : 0) << " ";
            ofs << (ch_c[i][j].isgreen_ ? 1 : 0) << " ";
        }
        ofs << endl;
    }
    
    //关闭文件
    ofs.close();
    cout << "游戏已保存到: " << filename << endl;
    return true;
}

string FileIO::Get_load_filename()
{
    string directory = "../output";
    
    // 检查目录是否存在
    if (!fs::exists(directory)) {
        cout << "存档目录不存在!" << endl;
        return "";
    }
    
    vector<string> txtFiles;

    for (const auto &entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            txtFiles.push_back(entry.path().filename().string());
        }
    }

    if (txtFiles.empty()) {
        cout << "没有找到存档文件!" << endl;
        return "";
    }

    reverse(txtFiles.begin(), txtFiles.end());

    cout << "\n请选择要加载的存档 (只会显示前20个) (输入序号):" << endl;
    for (int i = 0; i < txtFiles.size() && i < 20; i++) {
        cout << i << " : " << txtFiles[i] << endl;
    }

    int ret;
    cin >> ret;
    
    if (ret < 0 || ret >= txtFiles.size()) {
        cout << "无效的选择!" << endl;
        return "";
    }

    return directory + "/" + txtFiles[ret];
}

Chess FileIO::LoadGame(const string& filename) 
{
    //读取数据
    Chess m_chess;
    vector<vector<Qizi>>& c = m_chess.getboard();
    ifstream ifs;
    ifs.open(filename, ios::in);
    
    if (!ifs.is_open()) 
    {
        cout << "文件打开失败，没有该文件" << endl;
        return m_chess;
    }
    
    m_chess.setOnum_color_init();//进行初始化
    
    for (int row = 0; row < BOARD_SIZE; row++) 
    {
        for (int col = 0; col < BOARD_SIZE; col++) 
        {
            int value;
            int yellow, blue, green;
            
            ifs >> value >> yellow >> blue >> green;
            
            c[row][col].now_ = (Play)value;//这个位置的棋子是黑棋还是白棋
            
            // 恢复棋子的标记状态
            c[row][col].isyellow_ = (yellow == 1);
            c[row][col].isblue_ = (blue == 1);
            c[row][col].isgreen_ = (green == 1);
            
            //记录弧线上的棋子
            if (value != EMPTY) {
                m_chess.setOnum_color(value, row, col);
            }
        }
    }
    
    //关闭文件
    ifs.close();
    return m_chess;
}