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
#include <type_traits>


inline void printl(const auto& message) {
    std::cout << message << std::endl;
}

inline std::string UserInput() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

inline std::string typefl(const auto& input) noexcept {
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

namespace taskl {
    inline void waitl(double duration) noexcept {
        if (typefl(duration) == "double") {
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<unsigned int>(std::floor(duration) * 1000)));
        } else if (typefl(duration) == "int") {
            std::this_thread::sleep_for(std::chrono::seconds(static_cast<unsigned int>(duration)));
        }
    }
}

namespace stringl {
    inline std::string lowerl(const std::string& str) {
        std::string result = str;
        for (char& c : result) {
            c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        }
        return result;
    }

    inline std::string upperl(const std::string& str) {
        std::string result = str;
        for (char& c : result) {
            c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        }
        return result;
    }

    inline std::string findl(const std::string& str, const std::string& substr) {
        std::size_t pos = str.find(substr);
        if (pos != std::string::npos) {
            return std::to_string(pos);
        }
        return std::string{};
    }
};

namespace mathl {
    inline int random(int min, int max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }

    inline double pil() {
        return 3.14159265358979323846;
    }

    inline double hugel() {
        return std::numeric_limits<double>::infinity();
    }

    inline double absl(double value) noexcept {
        return std::abs(value);
    }

    inline int ceill(double value) noexcept {
        return static_cast<int>(std::ceil(value));
    }

    inline int floorl(double value) noexcept {
        return static_cast<int>(std::floor(value));
    }

    inline double roundl(double value) noexcept {
        return std::round(value);
    }

    inline double sqrtl(double value) noexcept {
        return std::sqrt(value);
    }

    inline double powl(double base, double exponent) noexcept {
        return std::pow(base, exponent);
    }

    inline double fmodl(double value, int num) noexcept {
        return std::fmod(value, static_cast<double>(num));
    }

    inline double clampl(double value, double min, double max) noexcept {
        if (value < min) {
            return min;
        } else if (value > max) {
            return max;
        }
        return value;
    }

    inline double sinl(double value) noexcept {
        return std::sin(value);
    }

    inline double cosl(double value) noexcept {
        return std::cos(value);
    }

    inline double tanl(double value) noexcept {
        return std::tan(value);
    }

    template<typename... Args>
    auto maxl(Args... args) noexcept
    {
        return std::max({args...});
    }

    template<typename... Args>
    auto minl(Args... args) noexcept
    {
        return std::min({args...});
    }
};

namespace LocalDataStoreService {
    inline bool GetLocalDataStore(const std::string& name) {
        try {
            std::filesystem::path Database = "./LocalDataStore";
            std::error_code ec;
            if (!(std::filesystem::exists(Database))) {
                std::filesystem::create_directory(Database, ec);
                std::filesystem::path dir = "./LocalDataStore/" + name;
                if (!(std::filesystem::exists(dir))) {
                    std::ofstream file(dir);
                    return true;
                }
            } else {
                std::filesystem::path dir = "./LocalDataStore/" + name;
                if (!(std::filesystem::exists(dir))) {
                    std::ofstream file(dir);
                    return true;
                }
            }
            return false;
        } catch(...) {
            return false;
        }
    }

    inline bool SetAsync(const std::string& DataStoreName, const auto& str) {
        try {
            std::filesystem::path dir = "./LocalDataStore/" + DataStoreName;
            if (std::filesystem::exists(dir) && std::filesystem::is_regular_file(dir)) {
                std::ofstream file(dir);
                if (file.is_open()) {
                    file << str;
                    file.close();
                    return true;
                }
            }
            return false;
        } catch (...) {
            return false;
        }
    }

    struct GetAsyncResult {
        bool found;
        std::string data;
    };
    inline GetAsyncResult GetAsync(const std::string& DataStoreName) {
        std::filesystem::path dir = "./LocalDataStore/" + DataStoreName;
        if (std::filesystem::exists(dir) && std::filesystem::is_regular_file(dir)) {
            std::ifstream input(dir);
            if (input.is_open()) {
                std::string line;
                std::getline(input, line);
                return {true,line};
            }
        }
        return {false,""};
    }

    inline bool RemoveAsync(const std::string& DataStoreName) {
        try {
            std::filesystem::path dir = "./LocalDataStore/" + DataStoreName;
            if (std::filesystem::exists(dir) && std::filesystem::is_regular_file(dir)) {
                std::filesystem::remove(dir);
                return true;
            }
            return false;
        } catch(...) {
            return false;
        }
    }
    inline bool RenameAsync(const std::string& DataStoreName, const std::string& Renamestring) {
         try {
            std::filesystem::path dir = "./LocalDataStore/" + DataStoreName;
            std::filesystem::path renamed = "./LocalDataStore/" + Renamestring;
            if (std::filesystem::exists(dir) && std::filesystem::is_regular_file(dir)) {
                std::filesystem::rename(dir, renamed);
                return true;
            }
            return false;
        } catch(...) {
            return false;
        }
    }
};

namespace filel {
    struct FindFirstChildResult {
        bool found;
        std::filesystem::path path;
    };

    inline FindFirstChildResult FindFirstChild(const std::filesystem::path& Parentfolder, const std::string& Filename) {
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
    
}

#endif
