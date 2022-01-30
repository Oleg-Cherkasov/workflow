#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "workers.h"
#include "factories.h"
#include "exceptions.h"

enum ParserState{
    DEFUNK,
    DEFOPEN,
    DEFCLOSE,
    DEFEND
};

class Parser{
private:
    std::ifstream fin;
    std::string buffer;
    std::vector<int> commandSequence;
    std::map<int, std::shared_ptr<Worker>> blocks;
    std::shared_ptr<WorkerFactory>   WrdFactory;
    std::shared_ptr<WorkerFactory>   WwtFactory;
    std::shared_ptr<WorkerFactory>    WgpFactory;
    std::shared_ptr<WorkerFactory>    WstFactory;
    std::shared_ptr<WorkerFactory> WrcFactory;
    std::shared_ptr<WorkerFactory>    WdpFactory;

    std::vector<std::string> parseBlock(std::string const &currentString);
    std::vector<int> parseCommandSequence(std::string const &currentString);

public:

    Parser(std::string const &filename);
    void parse();
    std::vector<int> getSequence();
    std::map<int, std::shared_ptr<Worker>> getBlocks();
};
