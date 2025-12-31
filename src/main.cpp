#include <iostream>
#include <string>
#include <vector>
#include <clocale>

#include "Calculator.hpp"
#include "Modes.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

#ifdef _WIN32
#include <windows.h>
#endif

/**
 * @brief Настройка системы логирования spdlog.
 */
void setupLogging(const std::string& logLevel, bool logToFile) {
    try {
        std::vector<spdlog::sink_ptr> sinks;
        sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        
        if (logToFile) {
            sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/calc_app.log", true));
        }

        auto logger = std::make_shared<spdlog::logger>("multi_sink", sinks.begin(), sinks.end());
        spdlog::set_default_logger(logger);

        if (logLevel == "DEBUG") spdlog::set_level(spdlog::level::debug);
        else if (logLevel == "INFO") spdlog::set_level(spdlog::level::info);
        else if (logLevel == "ERROR") spdlog::set_level(spdlog::level::err);
        
        spdlog::info("Application started");
    } catch (const spdlog::spdlog_ex& ex) {
        std::cout << "Log initialization failed: " << ex.what() << std::endl;
    }
}

int main(int argc, char* argv[]) {
    #ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    #endif

    std::string startMode = "menu";
    std::string logLevel = "INFO";
    std::string historyFile = "";
    std::string expression = "";

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg.find("--mode=") == 0) {
            startMode = arg.substr(7);
        } else if (arg.find("--log-level=") == 0) {
            logLevel = arg.substr(12);
        } else if (arg.find("--load-history=") == 0) {
            historyFile = arg.substr(15);
        } else if (arg.find("--calculate=") == 0) {
            expression = arg.substr(12);
        }
    }

    setupLogging(logLevel, !historyFile.empty());

    auto& calc = Calculator::getInstance();
    if (!historyFile.empty()) {
        calc.loadHistory(historyFile);
    }

    ModeManager manager;

    if (!expression.empty()) {
        spdlog::info("Direct calculation: {}", expression);
        std::cout << "Result: (Logic for RPN calculation of " << expression << ")\n";
        return 0;
    }

    if (startMode == "programmer") {
        spdlog::info("Starting directly in Programmer Mode");
    }

    manager.run();

    spdlog::info("Application finished");
    return 0;
}