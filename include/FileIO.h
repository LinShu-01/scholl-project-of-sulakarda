#pragma once
#include"../include/chess.hpp"
using namespace std;
void Test();
class Chess;
class FileIO {
public:
	bool SaveGame (const string& filename);
	Chess LoadGame(const string& filename);
};
