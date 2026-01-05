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
bool FileIO::SaveGame()
{
	string time=GetCurrentTime("%Y-%m-%d_%H-%M-%S");
	string filename="../output/game_save_"+time+".txt";
	//将数据记录下来
	ofstream ofs;
	ofs.open(filename, ios::out);
	Chess c;
	vector<vector<Qizi>>ch_c = c.getboard();
	for (int i = 0; i < BOARD_SIZE; i++) 
	{
		for (int j = 0; j < BOARD_SIZE; j++) 
		{
			ofs << ch_c[i][j].now_<<" ";
		}
		ofs << endl;
	}
	
	//关闭文件
	ofs.close();
	return true;
}
string FileIO::Get_load_filename()
{
    string directory = "../output";
    vector<string> txtFiles;

    for (const auto &entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            txtFiles.push_back(entry.path().filename().string());
        }
    }

    reverse(txtFiles.begin(), txtFiles.end());

    cout << "请你输入你需要回的存档(只会显示前20个)(存档前的序号):" << endl;
    for (int i = 0; i < txtFiles.size() && i < 20; i++) {
        cout << i << " : " << txtFiles[i] << endl;
    }

    int ret;
    cin >> ret;

    return directory + "/" + txtFiles[ret];
}
Chess FileIO::LoadGame(const string& filename) 
{
	//读取数据
	Chess m_chess;
	vector<vector<Qizi>>& c =m_chess.getboard();
	ifstream ifs;
	ifs.open(filename, ios::in);
	if (!ifs.is_open()) 
	{
		cout << "文件打开失败，没有该文件" << endl;
		exit(0);
	}
	m_chess.setOnum_color_init();//进行初始化
	for (int row = 0; row < BOARD_SIZE; row++) 
	{
		for (int col = 0; col < BOARD_SIZE; col++) 
		{
			int value;
			ifs >> value;
			c[row][col].now_ = (Play)value;//这个位置的棋子是黑棋还是白棋
			//该棋子在哪条颜色的线上
			if (0 == row || 5 == row || 0 == col || 5 == col) c[row][col].isyellow_ = true;
			else c[row][col].isyellow_ = false;
			if (1 == col || 4 == col || row == 1 && col == 0 || row == 4 && col == 0 ||
				row == 1 && col == 5 || row == 4 && col == 5)
				c[row][col].isblue_ = true;
			else c[row][col].isblue_ = false;
			if (3 == col || 2 == col || 2 == row || 3 == row)	c[row][col].isgreen_ = true;
			else c[row][col].isgreen_ = false;
			//记录弧线上的棋子
			m_chess.setOnum_color(value,row,col);
		}
	}
	//关闭文件
	ifs.close();
	return m_chess;
}