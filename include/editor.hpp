// Ad Maiorem Dei Gloriam!
#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

struct CursorPosition {
    unsigned int row, col;
};

struct TerminalSize {
    unsigned int rows, cols;
};

class Editor {
public:
    Editor();
    ~Editor();

    // Success if the file is 
    bool loadFile(const std::string& filepath);
    void start();
private:

    bool mRunning = true;

    static void initTerminal();
    static void restoreTerminal();

    void processInput();
    void insertAtCursor(char);
    void saveFile();
    void render();

    std::fstream mCurrentFile;
    std::vector<std::string> mCurrentFileLines; // To refactor this. For now shall be enough
    CursorPosition mCursorPos = {0};
    TerminalSize mTerminalSize;
};

#endif