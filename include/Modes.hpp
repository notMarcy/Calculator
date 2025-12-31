#ifndef MODES_HPP
#define MODES_HPP

#include <string>
#include <memory>
#include <vector>
#include <sstream>
#include "Command.hpp"
#include "Templates.hpp"

enum class CalcMode {
    Standard,
    Engineering,
    Programmer,
    RPN,
    ArrayProcessing,
    History,
    Exit
};

class ModeManager {
public:
    ModeManager();
    ~ModeManager() = default;

    void run();

private:
    CalcMode currentMode;
    bool running;

    void enterStandardMode();
    void enterEngineeringMode();
    void enterProgrammerMode();
    void enterRPNMode();
    void enterArrayMode();
    void showHistory();
    void enterNumberMode();
    void enterStringMode();
    void enterDateMode();
    void displayMainMenu();
    void processChoice(int choice);
    std::string infixToRPN(const std::string& infix);

    double evaluateRPN(const std::string& expression);
};

#endif