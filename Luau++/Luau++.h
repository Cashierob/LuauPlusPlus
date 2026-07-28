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

//This header is only compliable from C++ version 20 to above
//Compile your CPP file with "g++ -std=c++20 Yourfilename.cpp -o Name"


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

inline std::string typefl(const auto& input) {
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
    inline void waitl(double duration) {
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
    inline int randoml(int min, int max) {
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

    inline double absl(double value) {
        return std::abs(value);
    }

    inline int ceill(double value) {
        return static_cast<int>(std::ceil(value));
    }

    inline int floorl(double value) {
        return static_cast<int>(std::floor(value));
    }

    inline double roundl(double value) {
        return std::round(value);
    }

    inline double sqrtl(double value) {
        return std::sqrt(value);
    }

    inline double powl(double base, double exponent) {
        return std::pow(base, exponent);
    }

    inline double fmodl(double value, int num) {
        return std::fmod(value, static_cast<double>(num));
    }

    inline double clampl(double value, double min, double max) {
        if (value < min) {
            return min;
        } else if (value > max) {
            return max;
        }
        return value;
    }

    inline double sinl(double value) {
        return std::sin(value);
    }

    inline double cosl(double value) {
        return std::cos(value);
    }

    inline double tan(double value) {
        return std::tan(value);
    }

    template<typename... Args>
    auto max(Args... args)
    {
        return std::max({args...});
    }

    template<typename... Args>
    auto min(Args... args)
    {
        return std::min({args...});
    }
};

namespace LocalDataStoreService {
    inline void GetLocalDataStore(const std::string& name) {
        std::filesystem::path Database = "./LocalDataStore";
        std::error_code ec;
        if (!(std::filesystem::exists(Database))) {
            std::filesystem::create_directory(Database, ec);
            std::filesystem::path dir = "./LocalDataStore/" + name;
            if (!(std::filesystem::exists(dir))) {
                std::ofstream file(dir);
            }
        } else {
            std::filesystem::path dir = "./LocalDataStore/" + name;
            if (!(std::filesystem::exists(dir))) {
                std::ofstream file(dir);
            }
        }
    }

    inline void SetAsync(const std::string& DataStoreName, const auto& str) {
        std::filesystem::path dir = "./LocalDataStore/" + DataStoreName;
        if (std::filesystem::exists(dir) && std::filesystem::is_regular_file(dir)) {
            std::ofstream file(dir);
            if (file.is_open()) {
                file << str;
                file.close();
            }
        }
    }

    inline std::string GetAsync(const std::string& DataStoreName) {
        std::filesystem::path dir = "./LocalDataStore/" + DataStoreName;
        if (std::filesystem::exists(dir) && std::filesystem::is_regular_file(dir)) {
            std::ifstream input(dir);
            if (input.is_open()) {
                std::string line;
                std::getline(input, line);
                return line;
            }
        }
        return "";
    }

    inline void RemoveAsync(const std::string& DataStoreName) {
        std::filesystem::path dir = "./LocalDataStore/" + DataStoreName;
        if (std::filesystem::exists(dir) && std::filesystem::is_regular_file(dir)) {
            std::filesystem::remove(dir);
        }
    }
};

#endif
