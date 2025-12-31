#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include "Templates.hpp"
#include "Calculator.hpp"
#include "Utils.hpp"
#include <iomanip>
#include <sstream>
#include <stdexcept>

inline std::string formatRes(double val) {
    std::ostringstream oss;
    oss << std::setprecision(6) << (val == static_cast<long long>(val) ? static_cast<long long>(val) : val);
    return oss.str();
}

class Command {
protected:
    double operand1 = 0;
    double operand2 = 0;
    double result = 0;
    bool executed = false;

public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual std::string getFullExpression() const = 0;
    virtual std::string getName() const = 0;
};

class BinaryCommand : public Command {
protected:
    void popOperands(MyStack<double>& s) {
        if (s.size() < 2) throw std::runtime_error("Need 2 operands");
        operand2 = s.top(); s.pop();
        operand1 = s.top(); s.pop();
    }
public:
    void undo() override;
};

class UnaryCommand : public Command {
protected:
    void popOperand(MyStack<double>& s) {
        if (s.isEmpty()) throw std::runtime_error("Stack is empty");
        operand1 = s.top(); s.pop();
    }
public:
    void undo() override;
};

class AddCommand : public BinaryCommand {
public:
    void execute() override;
    std::string getName() const override { return "Сложение (+)"; }
    std::string getFullExpression() const override;
};

class SubCommand : public BinaryCommand {
public:
    void execute() override;
    std::string getName() const override { return "Вычитание (-)"; }
    std::string getFullExpression() const override;
};

class MulCommand : public BinaryCommand {
public:
    void execute() override;
    std::string getName() const override { return "Умножение (*)"; }
    std::string getFullExpression() const override;
};

class DivCommand : public BinaryCommand {
public:
    void execute() override;
    std::string getName() const override { return "Деление (/)"; }
    std::string getFullExpression() const override;
};

class SqrtCommand : public UnaryCommand {
public:
    void execute() override;
    std::string getName() const override { return "Корень (sqrt)"; }
    std::string getFullExpression() const override;
};

class SinCommand : public UnaryCommand {
public:
    void execute() override;
    std::string getName() const override { return "Sin"; }
    std::string getFullExpression() const override;
};

class CosCommand : public UnaryCommand {
public:
    void execute() override;
    std::string getName() const override { return "Cos"; }
    std::string getFullExpression() const override;
};

class TanCommand : public UnaryCommand {
public:
    void execute() override;
    std::string getName() const override { return "Tan"; }
    std::string getFullExpression() const override;
};

class LogCommand : public UnaryCommand {
public:
    void execute() override;
    std::string getName() const override { return "Ln"; }
    std::string getFullExpression() const override;
};

class ExpCommand : public UnaryCommand {
public:
    void execute() override;
    std::string getName() const override { return "Exp (e^x)"; }
    std::string getFullExpression() const override;
};

class PowCommand : public BinaryCommand {
public:
    void execute() override;
    std::string getName() const override { return "Степень (x^y)"; }
    std::string getFullExpression() const override;
};

class AndCommand : public BinaryCommand {
public:
    void execute() override;
    std::string getName() const override { return "AND"; }
    std::string getFullExpression() const override;
};

class OrCommand : public BinaryCommand {
public:
    void execute() override;
    std::string getName() const override { return "OR"; }
    std::string getFullExpression() const override;
};

class XorCommand : public BinaryCommand {
public:
    void execute() override;
    std::string getName() const override { return "XOR"; }
    std::string getFullExpression() const override;
};

class NotCommand : public UnaryCommand {
public:
    void execute() override;
    std::string getName() const override { return "NOT"; }
    std::string getFullExpression() const override;
};

class LShiftCommand : public BinaryCommand {
public:
    void execute() override;
    std::string getName() const override { return "Shift L (<<)"; }
    std::string getFullExpression() const override;
};

class RShiftCommand : public BinaryCommand {
public:
    void execute() override;
    std::string getName() const override { return "Shift R (>>)"; }
    std::string getFullExpression() const override;
};

#endif