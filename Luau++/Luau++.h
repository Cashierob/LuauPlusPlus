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
#include <chrono>
#include <thread>
#include <cmath>
#include <algorithm>
using namespace std;
namespace fs = filesystem;

//compile your CPP file with "g++ -std=c++20 Yourfilename.cpp -o Name"

inline void printl(const auto& message) {
    cout << message << endl;
}

inline string UserInput() {
    string input;
    getline(cin, input);
    return input;
}

inline string typefl(const auto& input) {
    if constexpr (is_same_v<decay_t<decltype(input)>, bool>) {
        return "bool";
    } else if constexpr (is_integral_v<decay_t<decltype(input)>>) {
        return "int";
    } else if constexpr (is_floating_point_v<decay_t<decltype(input)>>) {
        return "double";
    } else if constexpr (is_same_v<decay_t<decltype(input)>, string>) {
        return "string";
    } else if constexpr (is_same_v<decay_t<decltype(input)>, const char*>) {
        return "string";
    } else {
        return "unknown";
    }
}

namespace taskl {
    inline void waitl(double duration) {
        if (typefl(duration) == "double") {
            this_thread::sleep_for(chrono::milliseconds((static_cast<unsigned int>(floor(duration)*1000))));
        } else if ((typefl(duration) == "int")) {
            this_thread::sleep_for(chrono::seconds((static_cast<unsigned int>(duration))));
        }
    }
}

namespace stringl {
    inline string lowerl(const string& str) {
        string result = str;
        for (char& c : result) {
            c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
        }
        return result;
    }

    inline string upperl(const string& str) {
        string result = str;
        for (char& c : result) {
            c = static_cast<char>(toupper(static_cast<unsigned char>(c)));
        }
        return result;
    }

    inline string findl(const string& str, const string& substr) {
        size_t pos = str.find(substr);
        if (pos != string::npos) {
            return to_string(pos);
        };
        return string{};
    };
};

namespace mathl {
    inline int randoml(int min, int max) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }

    inline double pil() {
        return 3.14159265358979323846;
    }

    inline double hugel() {
        return numeric_limits<double>::infinity();;
    }

    inline double absl(double value) {
        return abs(value);
    }

    inline int ceill(double value) {
        return static_cast<unsigned int>(ceil(value));
    }

    inline int floorl(double value) {
        return static_cast<unsigned int>(floor(value));
    }

    inline double roundl(double value) {
        return round(value);
    }

    inline double sqrtl(double value) {
        return sqrt(value);
    }

    inline double powl(double base, double exponent) {
        return pow(base, exponent);
    }
    inline double fmodl(double value, int num) {
        return fmod(value, static_cast<double>(num));
    }
    inline double clampl(double value, double min, double max) {
        double result;
        if(value < min) {
            return min;
        } else if (value > max){
            return max;
        }
        return value;
    }
    inline double sinl(double value) {
        return sin(value);
    }
    inline double cosl(double value) {
        return cos(value);
    }
    inline double tan(double value) {
        return tan(value);
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
    inline void GetLocalDataStore(const string& name){
        fs::path Database = "./LocalDataStore";
        error_code ec;
        if(!(fs::exists(Database))) {
            fs::create_directory(Database, ec);
            fs::path dir = "./LocalDataStore/" + name;
            if(!(fs::exists(dir))) {
                ofstream file(dir);
            }
        } else {
            fs::path dir = "./LocalDataStore/" + name;
            if(!(fs::exists(dir))) {
                ofstream file(dir);
            }
        }
    }
    inline void SetAsync(const string& DataStoreName, const auto& str) {
        fs::path dir = "./LocalDataStore/" + DataStoreName;
        if(fs::exists(dir) && fs::is_regular_file(dir)) {
            ofstream file(dir);
            if(file.is_open()) {
                file << str;
                file.close();
            }
        }
    }
    inline string GetAsync(const string& DataStoreName) {
        fs::path dir = "./LocalDataStore/" + DataStoreName;
        if(fs::exists(dir) && fs::is_regular_file(dir)) {
            ifstream input(dir);
            if(input.is_open()) {
                string line;
                getline(input, line);
                return line;
            }
        }
        return "";
    }
    inline void RemoveAsync(const string& DataStoreName) {
        fs::path dir = "./LocalDataStore/" + DataStoreName;
        if(fs::exists(dir) && fs::is_regular_file(dir)) {
           fs::remove(dir);
        }
    }
};

#endif
