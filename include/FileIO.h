#pragma once
#include <string>

class Chess;

class FileIO {
private:
    std::string saveDirectory = "saves/";

public:
    std::string GetCurrentTime(const std::string &format);
    bool SaveGame();
    std::string Get_load_filename();
    Chess LoadGame(const std::string &filename);
};
