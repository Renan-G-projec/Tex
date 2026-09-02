// Ad Maiorem Dei Gloriam!
#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class Editor {
public:
    Editor();
    ~Editor();

    void loadFile(const std::string& filepath);
    void start();
private:

    static void initTerminal();
    static void restoreTerminal();

    void saveFile();

    std::fstream *mCurrentFile{nullptr};
    std::vector<std::string> mCurrentFileLines; // To refactor this. For now shall be enough
};

#endif