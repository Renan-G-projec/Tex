// Ad Maiorem Dei Gloriam!
#include "editor.hpp"

static TerminalSize getTerminalSize();

#ifdef _WIN32

#else

#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>

static struct termios oldt, newt;
void Editor::initTerminal() {
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt; // Copy

    // Echo need to be disabled because it dessyncs with the screen frequently
    newt.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void Editor::restoreTerminal() {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

static TerminalSize getTerminalSize() {
    winsize ws;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);

    return {ws.ws_row, ws.ws_col};
}

#endif

Editor::Editor() {
    initTerminal();
    mTerminalSize = getTerminalSize();
}

Editor::~Editor() {
    if (mCurrentFile.is_open()) {
        saveFile();
        mCurrentFile.close();
    }
    
    restoreTerminal();
}

bool Editor::loadFile(const std::string& filepath) {
    if (mCurrentFile.is_open()) mCurrentFile.close();
    
    mCurrentFile.clear();
    mCurrentFile.open(filepath, std::ios::in | std::ios::out);
    if (!mCurrentFile.is_open()) {
        std::cout << "Error: Could not open " << filepath << '\n';
        return false;
    }
    
    // Just pushes a empty string
    mCurrentFileLines.push_back({});
    while (std::getline(mCurrentFile, mCurrentFileLines.back())) {
        mCurrentFileLines.push_back({});
    }
    return true;
}

void Editor::start() {
    render();
    while (mRunning) {
        processInput();
    }
    saveFile();
}

void Editor::processInput() {
    // Linux base implementation for now
    char inputBuffer[3];
    read(STDIN_FILENO, inputBuffer, sizeof(inputBuffer)/sizeof(inputBuffer[0]));
    if (inputBuffer[0] == '\n') {
        mCursorPos.row++;
        mCursorPos.col = 0;
        mCurrentFileLines.emplace(mCurrentFileLines.cbegin() + mCursorPos.row + 1);
    } else if (inputBuffer[0] == '\033') {
        mRunning = false;
    } else {
        insertAtCursor(inputBuffer[0]);
        mCursorPos.col++;
    }
    render();
}

void Editor::insertAtCursor(char ch) {
    std::string &currentLine = mCurrentFileLines[mCursorPos.row];
    //if (currentLine.size() >= mCursorPos.col + 1) currentLine.reserve(currentLine.size() * 2);
    currentLine.insert(mCursorPos.col, 1, ch);
}

void Editor::render() {
    constexpr auto clearScreen = [](){
        std::cout << "\033[H\033[2J\033[3J";
        std::cout.flush();
    };

    clearScreen();
    for (auto line : mCurrentFileLines) {
        std::cout << line << "\n";
    }
    std::cout << "\033[" << mCursorPos.row + 1 << ';' << mCursorPos.col + 1 << 'H';
    std::cout.flush();
}

void Editor::saveFile() {
    mCurrentFile.clear();
    mCurrentFile.seekp(0);
    for (const auto& line : mCurrentFileLines) {
        mCurrentFile << line;
    }
    mCurrentFile.flush();
}