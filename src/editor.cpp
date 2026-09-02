// Ad Maiorem Dei Gloriam!
#include "editor.hpp"

Editor::~Editor() {
    if (mCurrentFile) {
        saveFile();
        delete mCurrentFile;
    }
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