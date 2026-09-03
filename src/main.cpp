// Ad Maiorem Dei Gloriam!
#include <iostream>
#include "editor.hpp"

int main() {
    Editor editor;

    editor.loadFile("src/main.cpp");
    editor.start();
    return 0;
}