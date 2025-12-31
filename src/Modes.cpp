#include "Modes.hpp"
#include "Calculator.hpp"
#include "Utils.hpp"
#include "spdlog/spdlog.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <fstream>
#include <iterator>
#include "Command.hpp"
#include <vector>
#include <algorithm>
#include <limits>

ModeManager::ModeManager() : currentMode(CalcMode::Standard), running(true) {}

void ModeManager::run() {
    spdlog::info("Application started");
    while (running) {
        displayMainMenu();
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }
        processChoice(choice);
    }
}

void ModeManager::displayMainMenu() {
    int choice = -1;
    while (choice != 10) {
        std::cout << "\n=== ГЛАВНОЕ МЕНЮ (Выбор режима) ===\n"
                  << "1. Стандартный\n2. Инженерный\n3. Программист\n"
                  << "4. Вычисление выражений (RPN)\n5. Работа с числами\n"
                  << "6. Работа со строками\n7. Работа с датами\n"
                  << "8. Сортировки массивов\n9. История\n10. Выход\n"
                  << "Выберите пункт: ";
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        processChoice(choice);
    }
}

void ModeManager::processChoice(int choice) {
    switch (choice) {
        case 1: enterStandardMode(); break;
        case 2: enterEngineeringMode(); break;
        case 3: enterProgrammerMode(); break;
        case 4: enterRPNMode(); break;
        case 5: enterNumberMode(); break;
        case 6: enterStringMode(); break;
        case 7: enterDateMode(); break;
        case 8: enterArrayMode(); break;
        case 9: showHistory(); break;
        case 10: Calculator::getInstance().saveHistory("history.txt"); break;
        case 0: std::cout << "Выход...\n"; break;
        default: std::cout << "Неверный выбор.\n";
    }
}

void ModeManager::enterProgrammerMode() {
    spdlog::info("Entering Programmer Mode");
    int subChoice = -1;
    int currentBase = 10;

    while (subChoice != 0) {
        auto& calc = Calculator::getInstance();
        auto& stack = calc.getStack();

        std::cout << "\n--- [2 уровень] РЕЖИМ ПРОГРАММИСТА ---" << std::endl;
        std::cout << "Текущая база: " << (currentBase == 2 ? "BIN (2)" : (currentBase == 16 ? "HEX (16)" : "DEC (10)")) << std::endl;
        
        if (!stack.isEmpty()) {
            long long val = static_cast<long long>(stack.top());
            std::cout << "Верхнее значение: " << Utils::decToSystem(val, currentBase) << std::endl;
        } else {
            std::cout << "Стек пуст" << std::endl;
        }

        std::cout << "1. Ввести число (DEC)\n"
                  << "2. Изменить базу (2, 10, 16)\n"
                  << "3. Побитовое И (AND)\n"
                  << "4. Побитовое ИЛИ (OR)\n"
                  << "5. Исключающее ИЛИ (XOR)\n"
                  << "6. Побитовое НЕ (NOT)\n"
                  << "7. Сдвиг влево (<<)\n"
                  << "8. Сдвиг вправо (>>)\n"
                  << "9. Отменить (undo)\n"
                  << "0. Назад\n"
                  << "Выберите пункт: ";

        if (!(std::cin >> subChoice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        try {
            switch (subChoice) {
                case 1: {
                    std::string input;
                    std::cout << "Введите целое число: ";
                    std::cin >> input;
                    stack.push(static_cast<double>(std::stoll(input)));
                    break;
                }
                case 2: {
                    std::cout << "Введите новую базу (2, 10, 16): ";
                    int newBase;
                    std::cin >> newBase;
                    if (newBase == 2 || newBase == 10 || newBase == 16) {
                        currentBase = newBase;
                    } else {
                        std::cout << "Ошибка: поддерживаются только базы 2, 10 и 16.\n";
                    }
                    break;
                }
                case 3: calc.executeCommand(std::make_shared<AndCommand>()); break;
                case 4: calc.executeCommand(std::make_shared<OrCommand>()); break;
                case 5: calc.executeCommand(std::make_shared<XorCommand>()); break;
                case 6: calc.executeCommand(std::make_shared<NotCommand>()); break;
                case 7: calc.executeCommand(std::make_shared<LShiftCommand>()); break;
                case 8: calc.executeCommand(std::make_shared<RShiftCommand>()); break;
                case 9: calc.undo(); break;
                case 0: break;
                default: std::cout << "Неверный выбор.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Ошибка выполнения: " << e.what() << std::endl;
        }
    }
}

void ModeManager::enterArrayMode() {
    spdlog::info("Entering Array Mode");
    int subChoice = -1;
    std::vector<double> data;

    while (subChoice != 0) {
        std::cout << "\n--- [2 уровень] СОРТИРОВКА МАССИВОВ ---" << std::endl;
        
        std::cout << "Массив: ";
        if (data.empty()) {
            std::cout << "[пуст]";
        } else {
            for (size_t i = 0; i < std::min(data.size(), size_t(15)); ++i) 
                std::cout << data[i] << " ";
            if (data.size() > 15) std::cout << "... (всего " << data.size() << ")";
        }
        std::cout << "\n--------------------------------------" << std::endl;

        std::cout << "1. Ввести массив вручную\n"
                  << "2. Загрузить массив из файла\n"
                  << "3. Пузырьковая сортировка (Bubble)\n"
                  << "4. Быстрая сортировка (Quick)\n"
                  << "5. Сортировка слиянием (Merge)\n"
                  << "6. Очистить массив\n"
                  << "0. Назад\n"
                  << "Выбор: ";

        if (!(std::cin >> subChoice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        switch (subChoice) {
            case 1: {
                int n;
                std::cout << "Введите количество элементов: ";
                if (!(std::cin >> n) || n <= 0) {
                    std::cout << "Ошибка размера!\n";
                    break;
                }
                data.resize(n);
                std::cout << "Введите " << n << " чисел: ";
                for (int i = 0; i < n; ++i) std::cin >> data[i];
                break;
            }
            case 2: {
                std::string filename;
                std::cout << "Введите имя файла (например, data.txt): ";
                std::cin >> filename;

                std::ifstream file(filename);
                if (!file.is_open()) {
                    std::cout << "Ошибка: Не удалось открыть файл '" << filename << "'\n";
                    break;
                }

                data.clear();
                double value;
                while (file >> value) {
                    data.push_back(value);
                }
                
                if (data.empty()) {
                    std::cout << "Предупреждение: Файл пуст или содержит некорректные данные.\n";
                } else {
                    std::cout << "Успешно загружено " << data.size() << " элементов.\n";
                }
                file.close();
                break;
            }
            case 3:
                if (data.empty()) std::cout << "Массив пуст!\n";
                else {
                    Utils::bubbleSort(data);
                    Utils::saveArrayToFile(data, "sortedArray.txt");
                }
                break;
            case 4:
                if (data.empty()) std::cout << "Массив пуст!\n";
                else {
                    Utils::quickSort(data, 0, static_cast<int>(data.size() - 1));
                    Utils::saveArrayToFile(data, "sortedArray.txt");
                }
                break;
            case 5:
                if (data.empty()) std::cout << "Массив пуст!\n";
                else {
                    Utils::mergeSort(data, 0, static_cast<int>(data.size() - 1));
                    Utils::saveArrayToFile(data, "sortedArray.txt");
                }
                break;
            case 6:
                data.clear();
                std::cout << "Массив очищен.\n";
                break;
            case 0:
                break;
            default:
                std::cout << "Неверный пункт.\n";
        }
    }
}

void ModeManager::showHistory() {
    int subChoice = -1;
    while (subChoice != 0) {
        std::cout << "\n--- [2 уровень] ИСТОРИЯ ОПЕРАЦИЙ ---\n"
                  << "1. Показать\n2. Очистить\n3. Сохранить в файл\n"
                  << "4. Загрузить из файла\n0. Назад\n"
                  << "Выбор: ";
        std::cin >> subChoice;

        if (subChoice == 1) {
            auto history = Calculator::getInstance().getHistoryAsVector();
            for(const auto& cmd : history) std::cout << " - " << cmd->getName() << std::endl;
        }
        else if (subChoice == 2) {
            Calculator::getInstance().clear();
            std::cout << "История и стек очищены.\n";
        }
        else if (subChoice == 3) {
            Calculator::getInstance().saveHistory("history_save.txt");
        }
        else if (subChoice == 4) {
            Calculator::getInstance().loadHistory("history_save.txt");
        }
    }
}

double ModeManager::evaluateRPN(const std::string& expression) {
    MyStack<double> stack;
    std::istringstream ss(expression);
    std::string token;

    while (ss >> token) {
        if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-')) {
            stack.push(std::stod(token));
        } else {
            if (stack.size() < 2) throw std::runtime_error("Invalid expression");
            double op2 = stack.top(); stack.pop();
            double op1 = stack.top(); stack.pop();

            if (token == "+") stack.push(op1 + op2);
            else if (token == "-") stack.push(op1 - op2);
            else if (token == "*") stack.push(op1 * op2);
            else if (token == "/") {
                if (op2 == 0) throw std::runtime_error("Division by zero");
                stack.push(op1 / op2);
            }
            else if (token == "^") {
                stack.push(std::pow(op1, op2));
            }
        }
    }
    return stack.top();
}

void ModeManager::enterStandardMode() {
    spdlog::info("Entering Standard Mode");
    int subChoice = -1;

    while (subChoice != 0) {
        auto& calc = Calculator::getInstance();
        auto& stack = calc.getStack();

        std::cout << "\n--- [2 уровень] СТАНДАРТНЫЙ РЕЖИМ ---" << std::endl;
        std::cout << "Стек: " << (stack.isEmpty() ? "[пуст]" : std::to_string(stack.top()) + " (top)") << std::endl;
        std::cout << "\n------------------------------------" << std::endl;

        std::cout << "1. Ввести число\n"
                  << "2. Сложение (+)\n"
                  << "3. Вычитание (-)\n"
                  << "4. Умножение (*)\n"
                  << "5. Деление (/)\n"
                  << "6. Корень (sqrt)\n"
                  << "7. Отменить последнее действие (undo)\n"
                  << "0. Назад в главное меню\n"
                  << "Выберите пункт: ";

        if (!(std::cin >> subChoice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Ошибка: введите числовой номер команды.\n";
            continue;
        }

        try {
            switch (subChoice) {
                case 1: {
                    double val;
                    std::cout << "Введите число: ";
                    if (std::cin >> val) {
                        stack.push(val);
                    } else {
                        std::cout << "Ошибка ввода числа.\n";
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                    }
                    break;
                }
                case 2: calc.executeCommand(std::make_shared<AddCommand>()); break;
                case 3: calc.executeCommand(std::make_shared<SubCommand>()); break;
                case 4: calc.executeCommand(std::make_shared<MulCommand>()); break;
                case 5: calc.executeCommand(std::make_shared<DivCommand>()); break;
                case 6: calc.executeCommand(std::make_shared<SqrtCommand>()); break;
                case 7: {
                    calc.undo(); 
                    std::cout << "Действие отменено.\n";
                    break;
                }
                case 0: 
                    spdlog::info("Exiting Standard Mode");
                    break;
                default: 
                    std::cout << "Неверный выбор. Попробуйте снова.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "[!] Ошибка: " << e.what() << std::endl;
        }
    }
}

void ModeManager::enterEngineeringMode() {
    spdlog::info("Entering Engineering Mode");
    int subChoice = -1;
    
    while (subChoice != 0) {
        auto& calc = Calculator::getInstance();
        auto& stack = calc.getStack();

        std::cout << "\n--- [2 уровень] ИНЖЕНЕРНЫЙ РЕЖИМ ---" << std::endl;
        std::cout << "Стек: " << (stack.isEmpty() ? "[пуст]" : std::to_string(stack.top()) + " (top)") << std::endl;
        
        std::cout << "1. Ввести число\n"
                  << "2. Синус (sin)\n"
                  << "3. Косинус (cos)\n"
                  << "4. Тангенс (tan)\n"
                  << "5. Натуральный логарифм (ln)\n"
                  << "6. Экспонента (exp)\n"
                  << "7. Квадратный корень (sqrt)\n"
                  << "8. Возведение в степень (x^y)\n"
                  << "9. Отменить (undo)\n"
                  << "0. Назад\n"
                  << "Выберите операцию: ";

        if (!(std::cin >> subChoice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Ошибка: введите числовой пункт меню.\n";
            continue;
        }

        try {
            switch (subChoice) {
                case 1: {
                    double val;
                    std::cout << "Введите число: ";
                    if (std::cin >> val) stack.push(val);
                    break;
                }
                case 2: calc.executeCommand(std::make_shared<SinCommand>()); break;
                case 3: calc.executeCommand(std::make_shared<CosCommand>()); break;
                case 4: calc.executeCommand(std::make_shared<TanCommand>()); break;
                case 5: calc.executeCommand(std::make_shared<LogCommand>()); break;
                case 6: calc.executeCommand(std::make_shared<ExpCommand>()); break;
                case 7: calc.executeCommand(std::make_shared<SqrtCommand>()); break;
                case 8: calc.executeCommand(std::make_shared<PowCommand>()); break;
                case 9: calc.undo(); break;
                case 0: break; 
                default: std::cout << "Неверный пункт меню.\n";
            }
        } catch (const std::exception& e) {
            spdlog::error("Engineering mode error: {}", e.what());
        }
    }
}

void ModeManager::enterRPNMode() {
    std::cout << "\n--- ВЫЧИСЛЕНИЕ ВЫРАЖЕНИЙ (Standard Infix) ---\n";
    std::cout << "Пример: (2 + 3) * 7 ^ 2\n";
    std::cout << "[Expression] > ";
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string input;
    std::getline(std::cin, input);

    if (input == "q" || input.empty()) return;

    try {
        std::string rpn = infixToRPN(input);
        double result = evaluateRPN(rpn);
        
        Calculator::getInstance().getStack().push(result);
        std::cout << "Результат: " << result << std::endl;
        spdlog::info("Infix expression evaluated: {} = {}", input, result);
    } catch (const std::exception& e) {
        std::cout << "[!] Ошибка: " << e.what() << std::endl;
    }
}

void ModeManager::enterNumberMode() {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n--- РАБОТА С ЧИСЛАМИ ---\n1. Найти НОД\n2. Проверка на простоту\n0. Назад\nВыбор: ";
        std::cin >> choice;
        if (choice == 1) {
            long long a, b;
            std::cout << "Введите два числа: "; std::cin >> a >> b;
            std::cout << "НОД: " << Utils::gcd(a, b) << std::endl;
        } else if (choice == 2) {
            int n; std::cout << "Введите число: "; std::cin >> n;
            std::cout << (Utils::isPrime(n) ? "Простое" : "Составное") << std::endl;
        }
    }
}

std::string ModeManager::infixToRPN(const std::string& infix) {
    std::string rpn;
    MyStack<char> operators;
    
    for (size_t i = 0; i < infix.length(); ++i) {
        char c = infix[i];
        if (isspace(c)) continue;

        if (isdigit(c) || c == '.') {
            while (i < infix.length() && (isdigit(infix[i]) || infix[i] == '.')) {
                rpn += infix[i++];
            }
            rpn += " ";
            i--;
        } 
        else if (c == '(') {
            operators.push(c);
        } 
        else if (c == ')') {
            while (!operators.isEmpty() && operators.top() != '(') {
                rpn += operators.top(); rpn += " ";
                operators.pop();
            }
            if (!operators.isEmpty()) operators.pop();
        } 
        else {
            while (!operators.isEmpty() && Utils::getPriority(operators.top()) >= Utils::getPriority(c)) {
                rpn += operators.top(); rpn += " ";
                operators.pop();
            }
            operators.push(c);
        }
    }

    while (!operators.isEmpty()) {
        rpn += operators.top(); rpn += " ";
        operators.pop();
    }
    return rpn;
}

void ModeManager::enterStringMode() {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n--- РАБОТА СО СТРОКАМИ ---\n1. Реверс строки\n2. В ВЕРХНИЙ РЕГИСТР\n0. Назад\nВыбор: ";
        std::cin >> choice;
        if (choice != 0) {
            std::cout << "Введите строку: ";
            std::string s; std::cin.ignore(); std::getline(std::cin, s);
            if (choice == 1) std::cout << "Результат: " << Utils::reverseString(s) << std::endl;
            else if (choice == 2) {
                for (auto &c : s) c = toupper(c);
                std::cout << "Результат: " << s << std::endl;
            }
        }
    }
}

void ModeManager::enterDateMode() {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n--- РАБОТА С ДАТАМИ ---\n1. Разница между датами (в днях)\n0. Назад\nВыбор: ";
        std::cin >> choice;
        if (choice == 1) {
            int d1, m1, y1, d2, m2, y2;
            std::cout << "Дата 1 (ДД ММ ГГГГ): "; std::cin >> d1 >> m1 >> y1;
            std::cout << "Дата 2 (ДД ММ ГГГГ): "; std::cin >> d2 >> m2 >> y2;
            std::cout << "Разница: " << Utils::dateDiffInDays(d1, m1, y1, d2, m2, y2) << " дней" << std::endl;
        }
    }
}