#include "Utils.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <cmath>

double Utils::custom_sqrt(double val) {
    if (val < 0) throw std::domain_error("Sqrt of negative number");
    if (val == 0) return 0;
    double res = val;
    double precision = 1e-10;
    while (true) {
        double next = 0.5 * (res + val / res);
        if (std::abs(res - next) < precision) break;
        res = next;
    }
    return res;
}

double Utils::custom_sin(double x) {
    double pi = 3.14159265358979323846;
    while (x > pi) x -= 2 * pi;
    while (x < -pi) x += 2 * pi;

    double res = 0;
    double term = x; 
    for (int i = 1; i <= 15; ++i) {
        res += term;
        term *= -x * x / (2 * i * (2 * i + 1));
    }
    return res;
}

double Utils::custom_pow(double base, int exp) {
    if (exp == 0) return 1;
    if (exp < 0) return 1.0 / custom_pow(base, -exp);
    double res = 1;
    for (int i = 0; i < exp; ++i) res *= base;
    return res;
}

std::string Utils::decToSystem(long long decimal, int base) {
    if (base < 2 || base > 16) return "";
    const std::string chars = "0123456789ABCDEF";
    std::string result = "";
    bool isNegative = decimal < 0;
    if (isNegative) decimal = -decimal;

    do {
        result = chars[decimal % base] + result;
        decimal /= base;
    } while (decimal > 0);

    return isNegative ? "-" + result : result;
}

bool Utils::isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

double Utils::custom_cos(double x) {
    double pi = 3.141592653589793;
    while (x > pi) x -= 2 * pi;
    while (x < -pi) x += 2 * pi;

    double res = 1.0;
    double term = 1.0;
    for (int i = 1; i <= 15; ++i) {
        term *= -x * x / ((2 * i - 1) * (2 * i));
        res += term;
    }
    return res;
}

double Utils::custom_exp(double x) {
    double res = 1.0;
    double term = 1.0;
    for (int i = 1; i <= 20; ++i) {
        term *= x / i;
        res += term;
    }
    return res;
}

double Utils::custom_log(double x) {
    if (x <= 0) throw std::domain_error("Logarithm of non-positive number");
    double res = x > 1 ? x / 10.0 : x - 1.0; 
    for (int i = 0; i < 10; ++i) {
        double e_y = custom_exp(res);
        res += 2 * (x - e_y) / (x + e_y);
    }
    return res;
}

long long Utils::custom_not(long long a) {
    return ~a;
}

long long Utils::custom_shift_left(long long a, int bits) {
    return a << bits;
}

long long Utils::custom_shift_right(long long a, int bits) {
    return a >> bits;
}

int Utils::sumOfDigits(long long n) {
    n = n < 0 ? -n : n;
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

std::string Utils::reverseString(std::string s) {
    int n = s.length();
    for (int i = 0; i < n / 2; i++) {
        std::swap(s[i], s[n - i - 1]);
    }
    return s;
}

double Utils::custom_tan(double x) {
    double s = custom_sin(x);
    double c = custom_cos(x);
    if (std::abs(c) < 1e-15) {
        throw std::runtime_error("Math Error: Tangent undefined");
    }
    return s / c;
}

long long Utils::gcd(long long a, long long b) {
    while (b) { a %= b; std::swap(a, b); }
    return std::abs(a);
}

bool Utils::isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) if (n % i == 0) return false;
    return true;
}

long long Utils::dateDiffInDays(int d1, int m1, int y1, int d2, int m2, int y2) {
    auto toDays = [](int d, int m, int y) {
        if (m < 3) { y--; m += 12; }
        return 365LL * y + y / 4 - y / 100 + y / 400 + (153 * m + 8) / 5 + d;
    };
    return std::abs(toDays(d1, m1, y1) - toDays(d2, m2, y2));
}

int Utils::getPriority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

void Utils::saveArrayToFile(const std::vector<double>& arr, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cout << "[!] Ошибка: Не удалось сохранить результат в " << filename << std::endl;
        return;
    }
    for (const auto& val : arr) {
        outFile << val << " ";
    }
    outFile.close();
    std::cout << "[Файл] Результат автоматически сохранен в " << filename << std::endl;
}