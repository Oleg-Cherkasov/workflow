#pragma once

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <optional>
#include "exceptions.h"

class Worker{
public:
    virtual void execute(std::optional<std::vector<std::string>> &text) = 0;
};

class WorkerRead : public Worker{
public:
    std::string filename;
    explicit WorkerRead(std::string const &args);
    void execute(std::optional<std::vector<std::string>> &text) override;
};

class WorkerWrite : public Worker{
public:
    std::string filename;
    explicit WorkerWrite(std::string const &args);
    void execute(std::optional<std::vector<std::string>> &text) override;
};
class WorkerGrep : public Worker{
public:
    std::string word;
    explicit WorkerGrep(std::string const &args);
    void execute(std::optional<std::vector<std::string>> &text) override;
};
class WorkerSort : public Worker{
public:
    explicit WorkerSort(std::string const &args);
    void execute(std::optional<std::vector<std::string>> &text) override;
};
class WorkerReplace : public Worker{
public:
    std::string word1, word2;
    explicit WorkerReplace(std::string const &args);
    void execute(std::optional<std::vector<std::string>> &text) override;
};
class WorkerDump : public Worker{
public:
    std::string filename;
    explicit WorkerDump(std::string const &args);
    void execute(std::optional<std::vector<std::string>> &text) override;
};