//Copyright 2026 @Cashierob

//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at

   // http://www.apache.org/licenses/LICENSE-2.0

//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.

//Project inception date: 7/26/2026.
//Last modified 7/31/2026.

//Only compatible with C++ Version 20 or above.
//Compile your CPP file with "g++ -std=c++20 Yourfilename.cpp -o Name".

#pragma once
#ifndef LUAU_H
#define LUAU_H

#include <algorithm>
#include <chrono>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <thread>
#include <sstream>
#include <vector>
#include <variant>
#include <utility>
#include <functional>
#include "Headers/Table.h"
#include "Headers/LocalDataStoreService.h"
#include "Headers/SystemDetail.h"
#include "Headers/Task.h"


namespace Luau {
//--------------------------//
//     Basic Functions      //
//--------------------------//
template<typename T>
inline void Print(const T& message) {
    try {std::cout << message << std::endl;} catch (...) {std::cout << "Printing Error." << std::endl;}
}

template<typename... Types>
inline void Print(const std::variant<Types...>& message) {
    try {
        std::visit([](const auto& value) {
        std::cout << value << std::endl;
        }, message);
    } catch (...) {std::cout << "Printing Error." << std::endl;}
}

inline void SystemWait() {std::cin.get();}

inline std::string Typeof(const auto& input) noexcept {
    if constexpr (std::is_same_v<std::decay_t<decltype(input)>, bool>) {return "bool";}
    else if constexpr (std::is_integral_v<std::decay_t<decltype(input)>>) {return "int";} 
    else if constexpr (std::is_floating_point_v<std::decay_t<decltype(input)>>) {return "double";} 
    else if constexpr (std::is_same_v<std::decay_t<decltype(input)>, std::string>) {return "string";} 
    else if constexpr (std::is_same_v<std::decay_t<decltype(input)>, const char*>) {return "string";} 
    else {return "unknown";}
}
//--------------------------//
//     Read functions       //
//--------------------------//
namespace Read {
    inline std::string ReadString() {
        std::string input;
        std::getline(std::cin,input);
        while(LuauSystem::Detail::isNumber(input)) {
            std::cout << "Must be a string." << std::endl;
            std::getline(std::cin,input);
        }
        return input;
    }

    inline double ReadNumber() {
        std::string value;
        std::getline(std::cin,value);
        while(!(LuauSystem::Detail::isNumber(value))) {
            std::cout << "Must be an integer." << std::endl;
            std::getline(std::cin,value);
        }
        return std::stod(value);
    }
}
//--------------------------//
//     String functions     //
//--------------------------//
namespace String {
    inline std::string Lower(const std::string& str) {
        std::string result = str;
        for (char& c : result) {
            c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        }
        return result;
    }

    inline std::string Upper(const std::string& str) {
        std::string result = str;
        for (char& c : result) {
            c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        }
        return result;
    }

    inline std::string Find(const std::string& str, const std::string& substr) {
        std::size_t pos = str.find(substr);
        if (pos != std::string::npos) {
            return std::to_string(pos);
        }
        return std::string{};
    }
    template<typename T>
    inline std::string Tostring(const T& Value) {
        try {return to_string(Value);} catch (...) {return "";}
    }
};

//--------------------------//
//     Math functions       //
//--------------------------//

namespace Math {
    inline int Random(int min, int max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }
    inline double Pi() {return 3.14159265358979323846;}
    inline double Huge() {return std::numeric_limits<double>::infinity();}
    inline double Abs(double value) noexcept {return std::abs(value);}
    inline int Ceil(double value) noexcept {return static_cast<int>(std::ceil(value));}
    inline int Floor(double value) noexcept {return static_cast<int>(std::floor(value));}
    inline double Round(double value) noexcept {return std::round(value);}
    inline double Sqrt(double value) noexcept {return std::sqrt(value);}
    inline double Pow(double base, double exponent) noexcept {return std::pow(base, exponent);}
    inline double Fmod(double value, int num) noexcept {return std::fmod(value, static_cast<double>(num));}
    inline double Clamp(double value, double min, double max) noexcept {
        if (value < min) {return min;} else if (value > max) {return max;} return value;}
    inline double Sin(double value) noexcept {return std::sin(value);}
    inline double Cos(double value) noexcept {return std::cos(value);}
    inline double Tan(double value) noexcept {return std::tan(value);}
    template<typename... Args>
    auto Max(Args... args) noexcept{return std::max({args...});}
    template<typename... Args>
    auto Min(Args... args) noexcept{return std::min({args...});}
};
//--------------------------//
//     File functions       //
//--------------------------//
namespace File {

    inline LuauSystem::Detail::InstanceHandle FindFirstChild(const std::filesystem::path& Parentfolder, const std::string& Filename) {
        if (!std::filesystem::exists(Parentfolder)) {
            return {false,{}};
        }
        std::filesystem::path Childfile = Parentfolder / Filename;
        if(std::filesystem::exists(Childfile)) {
            return {true, Childfile};
        }

        return {false,{}};
    }

    inline bool Name(const std::filesystem::path& Filepath, const std::string NewName) {
        if(!std::filesystem::exists(Filepath)) {
            return false;
        }
        std::filesystem::path NewnameFile = Filepath.parent_path() / NewName;
        std::filesystem::rename(Filepath, NewnameFile);
        return true;
    }
    inline bool Destroy(const std::filesystem::path& Filepath) {
        if(!std::filesystem::exists(Filepath)) {
            return false;
        }
        if(std::filesystem::is_regular_file(Filepath)) {
            std::filesystem::remove(Filepath);
            return true;
        } else if (std::filesystem::is_directory(Filepath)) {
            std::filesystem::remove_all(Filepath);
            std::filesystem::remove(Filepath);
            return true;
        }
        return false;
    }
    inline bool Parent(const std::filesystem::path CurrentFilePath, const std::filesystem::path NewFilePath) {
        if(!std::filesystem::exists(CurrentFilePath)) {
            return false;
        }
        std::filesystem::rename(CurrentFilePath,NewFilePath);
        return true;
    }
}

//--------------------------//
//     Instance functions   //
//--------------------------//
namespace Instance {
    inline LuauSystem::Detail::InstanceHandle NewFile(const std::string& Filename) {
        std::filesystem::path tempfold = ".";
        std::filesystem::path Filepath = tempfold / Filename;

        if (!std::filesystem::exists(Filepath)) {
            if(!std::filesystem::path(Filepath).has_extension()) {
                std::filesystem::create_directory(Filepath);
                return {true, Filepath};
            } else {
                std::ofstream newfilel(Filepath);
                if (newfilel.is_open()) {
                newfilel.close();
                return {true, Filepath};
            }
            }
        } else {
            std::cout << "error: Familiar name detected." << std::endl;
        }
        return {false,{}};
    }
}

}
#endif