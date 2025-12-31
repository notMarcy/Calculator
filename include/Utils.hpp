#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <stdexcept>

class Utils {
public:
    static double custom_sqrt(double val);
    static double add(double a, double b) { return a + b; }
    static double sub(double a, double b) { return a - b; }
    static double mul(double a, double b) { return a * b; }
    static double div(double a, double b);

    static double custom_sin(double x);
    static double custom_cos(double x);
    static double custom_tan(double x);
    static double custom_exp(double x);
    static double custom_log(double x); 
    static double custom_pow(double base, int exp);

    static std::string decToSystem(long long decimal, int base);
    static long long custom_and(long long a, long long b) { return a & b; }
    static long long custom_or(long long a, long long b) { return a | b; }
    static long long custom_xor(long long a, long long b) { return a ^ b; }
    static long long custom_not(long long a);
    static long long custom_shift_left(long long a, int bits);
    static long long custom_shift_right(long long a, int bits);

    static int sumOfDigits(long long n);
    static long long reverseNumber(long long n);
    static std::string reverseString(std::string s);
    static bool isPalindrome(const std::string& s);

    static bool isLeapYear(int year);
    static int dateToDays(int d, int m, int y);
    static int daysBetween(int d1, int m1, int y1, int d2, int m2, int y2);

    static long long gcd(long long a, long long b); // НОД
    static bool isPrime(int n);

    static std::string toUpper(std::string s);

    static long long dateDiffInDays(int d1, int m1, int y1, int d2, int m2, int y2);


    static int getPriority(char op);
    
    static void saveArrayToFile(const std::vector<double>& arr, const std::string& filename);

    template<typename T>
    static void customSort(std::vector<T>& arr) {
        for (size_t i = 1; i < arr.size(); ++i) {
            T key = arr[i];
            int j = static_cast<int>(i) - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

template<typename T>
static void bubbleSort(std::vector<T>& arr) {
    for (size_t i = 0; i < arr.size(); ++i)
        for (size_t j = 0; j < arr.size() - 1 - i; ++j)
            if (arr[j] > arr[j + 1]) std::swap(arr[j], arr[j + 1]);
}

template<typename T>
static void quickSort(std::vector<T>& arr, int low, int high) {
    if (low < high) {
        T pivot = arr[high];
        int i = (low - 1);
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        int pi = i + 1;
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

    template<typename T>
    static void merge(std::vector<T>& arr, int l, int m, int r) {
        int n1 = m - l + 1;
        int n2 = r - m;

        std::vector<T> L(n1), R(n2);

        for (int i = 0; i < n1; i++) L[i] = arr[l + i];
        for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

        int i = 0, j = 0, k = l;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = L[i];
            i++; k++;
        }

        while (j < n2) {
            arr[k] = R[j];
            j++; k++;
        }
    }

    template<typename T>
    static void mergeSort(std::vector<T>& arr, int l, int r) {
        if (l >= r) return;

        int m = l + (r - l) / 2;
        
        mergeSort(arr, l, m);   
        mergeSort(arr, m + 1, r); 
        
        merge(arr, l, m, r);   
    };
};

#endif 