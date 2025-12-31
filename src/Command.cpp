#include "Command.hpp"
#include "Calculator.hpp"
#include "Utils.hpp"

void BinaryCommand::undo() {
    auto& s = Calculator::getInstance().getStack();
    s.pop();
    s.push(operand1);
    s.push(operand2);
}

void UnaryCommand::undo() {
    auto& s = Calculator::getInstance().getStack();
    s.pop();
    s.push(operand1);
}

void AddCommand::execute() {
    auto& s = Calculator::getInstance().getStack();
    popOperands(s);
    result = operand1 + operand2;
    s.push(result);
}
std::string AddCommand::getFullExpression() const {
    return formatRes(operand1) + " + " + formatRes(operand2) + " = " + formatRes(result);
}

void SubCommand::execute() {
    auto& s = Calculator::getInstance().getStack();
    popOperands(s);
    result = operand1 - operand2;
    s.push(result);
}
std::string SubCommand::getFullExpression() const {
    return formatRes(operand1) + " - " + formatRes(operand2) + " = " + formatRes(result);
}

void MulCommand::execute() {
    auto& s = Calculator::getInstance().getStack();
    popOperands(s);
    result = operand1 * operand2;
    s.push(result);
}
std::string MulCommand::getFullExpression() const {
    return formatRes(operand1) + " * " + formatRes(operand2) + " = " + formatRes(result);
}

void DivCommand::execute() {
    auto& s = Calculator::getInstance().getStack();
    popOperands(s);
    if (operand2 == 0) {
        s.push(operand1); s.push(operand2);
        throw std::runtime_error("Division by zero");
    }
    result = operand1 / operand2;
    s.push(result);
}
std::string DivCommand::getFullExpression() const {
    return formatRes(operand1) + " / " + formatRes(operand2) + " = " + formatRes(result);
}

void SqrtCommand::execute() {
    auto& s = Calculator::getInstance().getStack();
    popOperand(s);
    result = Utils::custom_sqrt(operand1);
    s.push(result);
}
std::string SqrtCommand::getFullExpression() const {
    return "sqrt(" + formatRes(operand1) + ") = " + formatRes(result);
}

void SinCommand::execute() {
    auto& s = Calculator::getInstance().getStack();
    popOperand(s);
    result = Utils::custom_sin(operand1);
    s.push(result);
}
std::string SinCommand::getFullExpression() const { return "sin(" + formatRes(operand1) + ") = " + formatRes(result); }

void CosCommand::execute() {
    auto& s = Calculator::getInstance().getStack();
    popOperand(s);
    result = Utils::custom_cos(operand1);
    s.push(result);
}
std::string CosCommand::getFullExpression() const { return "cos(" + formatRes(operand1) + ") = " + formatRes(result); }

void TanCommand::execute() {
    auto& s = Calculator::getInstance().getStack();
    popOperand(s);
    result = Utils::custom_tan(operand1);
    s.push(result);
}
std::string TanCommand::getFullExpression() const { return "tan(" + formatRes(operand1) + ") = " + formatRes(result); }

void LogCommand::execute() {
    auto& s = Calculator::getInstance().getStack();
    popOperand(s);
    result = Utils::custom_log(operand1);
    s.push(result);
}
std::string LogCommand::getFullExpression() const { return "log(" + formatRes(operand1) + ") = " + formatRes(result); }

void ExpCommand::execute() {
    auto& s = Calculator::getInstance().getStack();
    popOperand(s);
    result = Utils::custom_exp(operand1);
    s.push(result);
}
std::string ExpCommand::getFullExpression() const { return "exp(" + formatRes(operand1) + ") = " + formatRes(result); }

void PowCommand::execute() {
    auto& s = Calculator::getInstance().getStack();
    popOperands(s);
    result = Utils::custom_pow(operand1, static_cast<int>(operand2));
    s.push(result);
}
std::string PowCommand::getFullExpression() const { return formatRes(operand1) + " ^ " + formatRes(operand2) + " = " + formatRes(result); }

void AndCommand::execute() {
    auto& s = Calculator::getInstance().getStack();
    popOperands(s);
    long long res = Utils::custom_and(static_cast<long long>(operand1), static_cast<long long>(operand2));
    result = static_cast<double>(res);
    s.push(result);
}
std::string AndCommand::getFullExpression() const { return formatRes(operand1) + " AND " + formatRes(operand2) + " = " + formatRes(result); }

void OrCommand::execute() {
    auto& s = Calculator::getInstance().getStack();
    popOperands(s);
    long long res = Utils::custom_or(static_cast<long long>(operand1), static_cast<long long>(operand2));
    result = static_cast<double>(res);
    s.push(result);
}
std::string OrCommand::getFullExpression() const { return formatRes(operand1) + " OR " + formatRes(operand2) + " = " + formatRes(result); }

void XorCommand::execute() {
    auto& s = Calculator::getInstance().getStack();
    popOperands(s);
    long long res = Utils::custom_xor(static_cast<long long>(operand1), static_cast<long long>(operand2));
    result = static_cast<double>(res);
    s.push(result);
}
std::string XorCommand::getFullExpression() const { return formatRes(operand1) + " XOR " + formatRes(operand2) + " = " + formatRes(result); }

void NotCommand::execute() {
    auto& s = Calculator::getInstance().getStack();
    popOperand(s);
    long long res = Utils::custom_not(static_cast<long long>(operand1));
    result = static_cast<double>(res);
    s.push(result);
}
std::string NotCommand::getFullExpression() const { return "NOT(" + formatRes(operand1) + ") = " + formatRes(result); }

void LShiftCommand::execute() {
    auto& s = Calculator::getInstance().getStack();
    popOperands(s);
    long long res = Utils::custom_shift_left(static_cast<long long>(operand1), static_cast<int>(operand2));
    result = static_cast<double>(res);
    s.push(result);
}
std::string LShiftCommand::getFullExpression() const { return formatRes(operand1) + " << " + formatRes(operand2) + " = " + formatRes(result); }

void RShiftCommand::execute() {
    auto& s = Calculator::getInstance().getStack();
    popOperands(s);
    long long res = Utils::custom_shift_right(static_cast<long long>(operand1), static_cast<int>(operand2));
    result = static_cast<double>(res);
    s.push(result);
}
std::string RShiftCommand::getFullExpression() const { return formatRes(operand1) + " >> " + formatRes(operand2) + " = " + formatRes(result); }