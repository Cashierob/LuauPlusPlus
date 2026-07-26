#ifndef LUAU_H
#define LUAU_H

#include <cmath>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <random>
#include <string>
#include <fstream>
#include <filesystem>
#include <type_traits>

//compile with "g++ -std=c++20 Main.cpp -o Main.exe"

inline void print(const auto& message) {
    std::cout << message << std::endl;
}

std::string UserInput() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

std::string type(const auto& input) {
    if constexpr (std::is_same_v<std::decay_t<decltype(input)>, bool>) {
        return "bool";
    } else if constexpr (std::is_integral_v<std::decay_t<decltype(input)>>) {
        return "int";
    } else if constexpr (std::is_floating_point_v<std::decay_t<decltype(input)>>) {
        return "double";
    } else if constexpr (std::is_same_v<std::decay_t<decltype(input)>, std::string>) {
        return "string";
    } else if constexpr (std::is_same_v<std::decay_t<decltype(input)>, const char*>) {
        return "string";
    } else {
        return "unknown";
    }
}

class STR {
public:
    std::string stringlower(const std::string& str) {
        std::string result = str;
        for (char& c : result) {
            c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        }
        return result;
    }

    std::string stringupper(const std::string& str) {
        std::string result = str;
        for (char& c : result) {
            c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        }
        return result;
    }

    std::string find(const std::string& str, const std::string& substr) {
        std::size_t pos = str.find(substr);
        if (pos != std::string::npos) {
            return std::to_string(pos);
        };
        return std::string{};
    };
};

class MTH {
public:
    int random(int min, int max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }

    double pi() {
        return 3.14159265358979323846;
    }

    double huge() {
        return 1e9;
    }

    double abs(double value) {
        return std::abs(value);
    }

    double ceil(double value) {
        return std::ceil(value);
    }

    double floor(double value) {
        return std::floor(value);
    }

    double round(double value) {
        return std::round(value);
    }

    double sqrt(double value) {
        return std::sqrt(value);
    }

    double pow(double base, double exponent) {
        return std::pow(base, exponent);
    }
    double mods(double value, int num) {
        return std::fmod(value, static_cast<double>(num));
    }
};

class LDTS {
public:
    void GetDataStore(const std::string& name){
        std::filesystem::path Database = "./DataStore";
        std::error_code ec;
        if(!(std::filesystem::exists(Database))) {
            std::filesystem::create_directory(Database, ec);
            std::filesystem::path dir = "./DataStore/" + name;
            if(!(std::filesystem::exists(dir))) {
                std::ofstream file(dir);
            }
        } else {
            std::filesystem::path dir = "./DataStore/" + name;
            if(!(std::filesystem::exists(dir))) {
                std::ofstream file(dir);
            }
        }
    }
    void SetAsync(const std::string& DataStoreName, const auto& str) {
        std::filesystem::path dir = "./DataStore/" + DataStoreName;
        if(std::filesystem::exists(dir) && std::filesystem::is_regular_file(dir)) {
            std::ofstream file(dir);
            if(file.is_open()) {
                file << str;
                file.close();
            }
        }
    }
    std::string GetAsync(const std::string& DataStoreName) {
        std::filesystem::path dir = "./DataStore/" + DataStoreName;
        if(std::filesystem::exists(dir) && std::filesystem::is_regular_file(dir)) {
            std::ifstream input(dir);
            if(input.is_open()) {
                std::string line;
                std::getline(input, line);
                return line;
            }
        }
        return "";
    }
    void RemoveAsync(const std::string& DataStoreName) {
        std::filesystem::path dir = "./DataStore/" + DataStoreName;
        if(std::filesystem::exists(dir) && std::filesystem::is_regular_file(dir)) {
           std::filesystem::remove(dir);
        }
    }
};

#endif
