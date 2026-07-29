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
//Last modified 7/29/2026.

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
#include <sstream>

namespace {
    bool isNumber(const std::string& input) {
        try {
            std::size_t pos = 0;
            double value = std::stod(input, &pos);
            (void)value;
            return pos == input.size();
        } catch (...) {
            return false;
        }
    }
    struct Instanceactions {
        bool found;
        std::filesystem::path path;

        struct Get_Data_Status {
            bool sucess;
            std::string str;
        };

        inline bool Destroy() {
            try { 
                if(!std::filesystem::path(path).has_extension()) {
                    std::filesystem::remove_all(path);
                    return true;
                } else {
                    std::filesystem::remove(path);
                    return true;
                }
                return false;
            } catch (...) {
                return false;
            }
        }
        inline bool Name(const std::string& Newname) 
        { try {
            if(!std::filesystem::exists(path)) {return false;}
            std::filesystem::path newPath = path.parent_path() / (Newname + path.extension().string());
            std::filesystem::rename(path, newPath);
            path = newPath; 
            return true;} catch (...) {
            return false;
        }
        }
        inline bool Set_Parent(const std::filesystem::path Folderpath) { try {
            std::filesystem::path newPath = Folderpath / path;
                if(!std::filesystem::path(path).has_extension()) {
                    std::filesystem::create_directory(newPath);
                    std::filesystem::remove_all(path);
                    path = newPath;
                    return true;
                } else if (std::filesystem::exists(path)) {
                    std::filesystem::rename(path, newPath);
                    path = newPath;
                    return true;
                }
                return false;
            } catch (...) {
                return false;
            }
        }
        inline bool Write_Data(const std::string& datainput) {
            if(!std::filesystem::exists(path)) {return false;} 
            else {
                if(path.extension().string() == ".txt") {
                    std::ifstream filetxt(path);
                    if(filetxt.is_open()) {
                        std::string content;
                        std::ostringstream ss;
                        ss << filetxt.rdbuf();
                        content = ss.str();
                        std::ofstream filetxtwritten(path);
                        filetxtwritten << content << '\n';
                        filetxtwritten << datainput;
                        filetxt.close();
                        return true;
                    }
                }
            }
            return false;
        }
        inline bool Delete_Data() {
            if(!std::filesystem::exists(path)) {return false;}
            else {
                if (path.extension().string() == ".txt") {
                    std::ofstream textfile(path);
                    if(textfile.is_open()) {textfile.close(); return true;}
                }
                return false;
            }
        }
        inline Get_Data_Status Read_Data() {
            if(!std::filesystem::exists(path)) {}
            else {
                if(path.extension().string() == ".txt") {
                    std::ifstream textfile(path);
                    std::ostringstream ss;
                    ss << textfile.rdbuf();
                    return {true, ss.str()};
                }
            }
            return {false,""};
        }
        inline Instanceactions FindFirstChild(const std::string& Filename) {
            if (!std::filesystem::exists(path)) {
                return {false,{}};
            }
            if (std::filesystem::is_directory(path)) {
                std::filesystem::path ChildFile = path / Filename;
                if(!std::filesystem::exists(ChildFile)) {return {false, {}};}
                return {true, ChildFile};
            }
            return {false,{}};
        }
        inline Instanceactions Parent() {
            if(!std::filesystem::exists(path)) {return {false,{}};}
            if(!std::filesystem::exists(path.parent_path())) {return {false,{}};}
            return {true, path.parent_path()};
        }
    };
}


inline void Print(const auto& message) {
    std::cout << message << std::endl;
}

inline std::string Typeof(const auto& input) noexcept {
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

namespace Read {
    inline std::string Read_String() {
        std::string input;
        std::getline(std::cin,input);
        while(isNumber(input)) {
            std::getline(std::cin,input);
        }
        return input;
    }

    inline double Read_Number() {
        std::string value;
        std::getline(std::cin,value);
        while(!(isNumber(value))) {
            std::getline(std::cin,value);
        }
        return std::stod(value);
    }
}

namespace task {
    inline void wait(double seconds) noexcept {
        if (seconds <= 0.0) return;
        using namespace std::chrono;
        auto dur = duration<double>(seconds);
        std::this_thread::sleep_for(duration_cast<milliseconds>(dur));
    }
}

namespace stringl {
    inline std::string lower(const std::string& str) {
        std::string result = str;
        for (char& c : result) {
            c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        }
        return result;
    }

    inline std::string upper(const std::string& str) {
        std::string result = str;
        for (char& c : result) {
            c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        }
        return result;
    }

    inline std::string find_str(const std::string& str, const std::string& substr) {
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

    inline double pi() {
        return 3.14159265358979323846;
    }

    inline double huge() {
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

    inline double clamp(double value, double min, double max) noexcept {
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
                std::ostringstream ss;
                ss << input.rdbuf();
                return {true,ss.str()};
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

    inline Instanceactions FindFirstChild(const std::filesystem::path& Parentfolder, const std::string& Filename) {
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

namespace Instance {
    inline Instanceactions New_File(const std::string& Filename) {
        std::filesystem::path tempfold = ".";
        std::filesystem::path Filepath = tempfold / Filename;

        if (!std::filesystem::exists(Filepath)) {
            if(!std::filesystem::path(Filepath).has_extension()) {
                std::filesystem::create_directory(Filepath);
            } else {
                std::ofstream newfilel(Filepath);
                if (newfilel.is_open()) {
                newfilel.close();
            }
            }
        }
        return {std::filesystem::exists(Filepath),Filepath};
    }
}

#endif
