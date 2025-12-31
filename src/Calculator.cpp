#include "Calculator.hpp"
#include "Command.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "spdlog/spdlog.h"

Calculator& Calculator::getInstance() {
    static Calculator instance;
    return instance;
}

void Calculator::executeCommand(std::shared_ptr<Command> cmd) {
    try {
        cmd->execute();
        history.push(cmd);
        
        std::cout << ">>> " << cmd->getFullExpression() << std::endl;
        
        spdlog::info("Executed: {}", cmd->getFullExpression());
    }
    catch (const std::exception& e) {
        spdlog::error("Error: {}", e.what());
        std::cout << "[!] Ошибка: " << e.what() << std::endl;
    }
}

void Calculator::undo() {
    if (history.isEmpty()) {
        spdlog::warn("Undo attempted on empty history");
        return;
    }
    std::shared_ptr<Command> lastCmd = history.top();
    spdlog::info("Undoing command: {}", lastCmd->getName());
    lastCmd->undo();
    history.pop();
}

MyStack<double>& Calculator::getStack() {
    return dataStack;
}

std::vector<std::shared_ptr<Command>> Calculator::getHistoryAsVector() const {
    std::vector<std::shared_ptr<Command>> v;
    MyStack<std::shared_ptr<Command>> tempStack = history;

    while (!tempStack.isEmpty()) {
        v.push_back(tempStack.top());
        tempStack.pop();
    }
    std::reverse(v.begin(), v.end());
    return v; 
}

void Calculator::clear() {
    while(!dataStack.isEmpty()) dataStack.pop();
    while(!history.isEmpty()) history.pop(); 
    spdlog::info("Calculator state cleared");
}

void Calculator::saveHistory(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Cannot open file");

    auto historyVec = getHistoryAsVector();
    
    file << "--- Full Calculation History ---" << std::endl;
    for (const auto& cmd : historyVec) {
        file << cmd->getFullExpression() << std::endl;
    }
    
    std::cout << "История сохранена в " << filename << std::endl;
    
    spdlog::info("History saved to {}", filename);
}

void Calculator::loadHistory(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        spdlog::error("Failed to load history from {}", filename);
        return;
    }
    spdlog::info("History loaded from {}", filename);
}

bool Calculator::hasHistory() const {
    return !history.isEmpty();
}

void Calculator::undoLastCommand() {
    undo();
}