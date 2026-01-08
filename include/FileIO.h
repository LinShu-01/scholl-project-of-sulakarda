#pragma once
#include<string>
#include"chess.hpp"
using namespace std;

class FileIO {
private:
    string GetCurrentTime(const string& format = "%Y-%m-%d_%H-%M-%S");
public:
    bool SaveGame(const Chess& chess);
    string Get_load_filename();
    Chess LoadGame(const string& filename);
};