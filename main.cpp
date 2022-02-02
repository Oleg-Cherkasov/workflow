#include <iostream>

#include "workers.h"
#include "parser.h"


int main() {
    std::string filename = "test.txt";
    std::optional<std::vector<std::string>> text = {};
    Parser p(filename);
    try {
        p.parse();
    }catch (const FileBeginningException& ex){
        std:: cout << ex.what();
        return 1;
    }catch (const SequenceSyntaxError& ex){
        std:: cout << ex.what();
        return 1;
    }
    auto b = p.getBlocks();
    auto s = p.getSequence();
    for (auto x : s){
        b[x]->execute(text);
    }
    return 0;
}
