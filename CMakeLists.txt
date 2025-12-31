cmake_minimum_required(VERSION 3.10)
project(CalculatorApp VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем путь к spdlog (относительно этого файла)
set(SPDLOG_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/external/spdlog/include")

# Собираем все .cpp файлы из папки src
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(CalculatorApp ${SOURCES})

# Передаем компилятору пути к заголовочным файлам
# Указываем путь к заголовкам spdlog
target_include_directories(CalculatorApp PRIVATE 
    "src"
    "include"  # Добавляем папку с вашими .hpp
    "external/spdlog/include"
)

message(STATUS "Build configuration complete for CalculatorApp")