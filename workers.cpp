#include "workers.h"

WorkerRead::WorkerRead(std::string const &args) : Worker() {
    int i = 0;
    while (args[i] == ' ' && i < args.size()){
        ++i;
    }
    if (i == args.size()) throw TooFewArgsException("Read");
    filename.clear();
    while (args[i] != ' ' && i < args.size()){
        filename += args[i];
        ++i;
    }
    if (i != args.size()) throw TooMuchArgsException("Read");
}

WorkerWrite::WorkerWrite(std::string const &args) : Worker() {
    int i = 0;
    while (args[i] == ' ' && i < args.size()){
        ++i;
    }
    if (i == args.size()) throw TooFewArgsException("Write");
    filename.clear();
    while (args[i] != ' ' && i < args.size()){
        filename += args[i];
        ++i;
    }
    if (i != args.size()) throw TooMuchArgsException("Write");
    std::ifstream fout(filename, std::ios::out | std::ios::trunc);
    fout.close();
}

WorkerGrep::WorkerGrep(std::string const &args) : Worker() {
    int i = 0;
    while (args[i] == ' ' && i < args.size()){
        ++i;
    }
    if (i == args.size()) throw TooFewArgsException("Grep");
    word.clear();
    while (args[i] != ' ' && i < args.size()){
        word += args[i];
        ++i;
    }
    if (i != args.size()) throw TooMuchArgsException("Grep");
}

WorkerSort::WorkerSort(std::string const &args) : Worker() {
    int i = 0;
    int sz = args.size();
    while (args[i] == ' ' && i < args.size()){
        ++i;
    }

    if (i != args.size()) throw TooMuchArgsException("Sort");
}

WorkerReplace::WorkerReplace(std::string const &args) : Worker() {
    int i = 0;
    while (args[i] == ' ' && i < args.size()){
        ++i;
    }
    if (i == args.size()) throw TooFewArgsException("Replace");
    word1.clear();
    while (args[i] != ' ' && i < args.size()){
        word1 += args[i];
        ++i;
    }
    while (args[i] == ' ' && i < args.size()){
        ++i;
    }
    if (i == args.size()) throw TooFewArgsException("Replace");
    word2.clear();
    while (args[i] != ' ' && i < args.size()){
        word2 += args[i];
        ++i;
    }
    if (i != args.size()) throw TooMuchArgsException("Replace");
}

WorkerDump::WorkerDump(std::string const &args) : Worker() {

    int i = 0;
    while (args[i] == ' ' && i < args.size()){
        ++i;
    }
    if (i == args.size()) throw TooFewArgsException("Dump");
    filename.clear();
    while (args[i] != ' ' && i < args.size()){
        filename += args[i];
        ++i;
    }
    if (i != args.size()) throw TooMuchArgsException("Dump");
    std::ifstream fout(filename, std::ios::out | std::ios::trunc);
    fout.close();
}

void WorkerRead::execute(std::optional<std::vector<std::string>> &text) {
    if(text){
        throw IOTextException("Read block haven`t input");
    }
    text.emplace();
    std::ifstream fin(filename);
    std::string buffer;
    while (!fin.eof()){
        std::getline(fin, buffer);
        (*text).push_back(buffer);
    }
    fin.close();
}

void WorkerWrite::execute(std::optional<std::vector<std::string>> &text) {
    if(!text){
        throw IOTextException("Write block have input");
    }
    std::ofstream fout(filename, std::ios::app);
    for (auto &x : *text){
        fout << x << "\n";
    }
    text.reset();
    fout.close();
}

void WorkerGrep::execute(std::optional<std::vector<std::string>> &text) {
    if(!text){
        throw IOTextException("Grep block have input");
    }
    std::vector<std::string> result;
    std::regex r(word);
    std::smatch sm;
    for (auto const &x: *text){
        if (std::regex_search(x, sm, r)){
            for (auto matched_word : sm){
                result.push_back(matched_word);
            }
        }
    }
    *text = result;
}

void WorkerSort::execute(std::optional<std::vector<std::string>> &text) {
    if(!text){
        throw IOTextException("Sort block have input");
    }
    std::sort((*text).begin(), (*text).end());
}

void WorkerReplace::execute(std::optional<std::vector<std::string>> &text) {
    if(!text){
        throw IOTextException("Replace block have input");
    }
    std::regex r(word1);
    for (auto &x: *text){
        x = std::regex_replace(x, r, word2);
    }
}

void WorkerDump::execute(std::optional<std::vector<std::string>> &text) {
    if(!text){
        throw IOTextException("Dump block have input");
    }
    std::ofstream fout(filename, std::ios::app);
    for (auto &x : *text){
        fout << x << "\n";
    }
    fout.close();
}

