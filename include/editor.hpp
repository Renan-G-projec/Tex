// Ad Maiorem Dei Gloriam!
#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <string>
#include <vector>
#include <fstream>

class Editor {
public:
    Editor();
    ~Editor();

    void loadFile(const std::string& filepath);
    void start();
private:

    void initTerminal();
    void restoreTerminal();

    void saveFile();

    std::fstream *mCurrentFile{nullptr};
    std::vector<std::string> mCurrentFileLines; // To refactor this. For now shall be enough
};

#endif