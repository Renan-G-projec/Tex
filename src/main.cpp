// Ad Maiorem Dei Gloriam!
#include <iostream>
#include "editor.hpp"

void printHelp(const char *name) {
    std::cout   << "Usage: " << name << " <file>\n"
                << "Simple text editor - Tex\n"
                << "ESC saves and exits.\n"
                << "Ctrl-S saves only.\n"
                << "Ctrl-C exits only.\n";
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        std::cout << "Error: No file specified.\n"; 
        printHelp(argv[0]);
        return EXIT_FAILURE;
    }
    Editor editor;

    editor.loadFile(argv[1]);
    editor.start();
    return EXIT_SUCCESS;
}