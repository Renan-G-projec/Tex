// Ad Maiorem Dei Gloriam!
#include "editor.hpp"

#ifdef _WIN32

#else

#include <termios.h>
#include <unistd.h>

static struct termios oldt, newt;
void Editor::initTerminal() {
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt; // Copy

    // Echo need to be disabled because it dessyncs with the screen frequently
    newt.c_cflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void Editor::restoreTerminal() {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

#endif

Editor::Editor() {
    initTerminal();
}

Editor::~Editor() {
    if (mCurrentFile) {
        saveFile();
        delete mCurrentFile;
    }

    restoreTerminal();
}

void Editor::loadFile(const std::string& filepath) {
    if (mCurrentFile) {
        delete mCurrentFile;
    }

    mCurrentFile = new std::fstream(filepath);
    if (!mCurrentFile->is_open()) {
        delete mCurrentFile;
        mCurrentFile = nullptr;
        std::cout << "Error: Could not open " << filepath << '\n'; 
    }

    // Just pushes a empty string
    mCurrentFileLines.push_back({});
    while (std::getline(*mCurrentFile, mCurrentFileLines.back())) {
        mCurrentFileLines.push_back({});
    }
}

void Editor::saveFile() {
    if (!mCurrentFile) return;
    for (auto line : mCurrentFileLines) {
        *mCurrentFile << line << '\n';
    }
    mCurrentFile->flush();
}