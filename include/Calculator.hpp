#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <vector>
#include <memory>
#include <string>
#include "Templates.hpp"

class Command;

class Calculator {
public:
    Calculator(const Calculator&) = delete;
    Calculator& operator=(const Calculator&) = delete;

    static Calculator& getInstance();

    void executeCommand(std::shared_ptr<Command> cmd);
    void undo();
    void clear();

    MyStack<double>& getStack();

    void saveHistory(const std::string& filename);
    void loadHistory(const std::string& filename);

    void undoLastCommand();
    bool hasHistory() const;
    
    std::vector<std::shared_ptr<Command>> getHistoryAsVector() const;

private:
    Calculator() = default;
    ~Calculator() = default;

    MyStack<double> dataStack;
    MyStack<std::shared_ptr<Command>> history; 
};

#endif