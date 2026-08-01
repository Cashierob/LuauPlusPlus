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

#pragma once
#ifndef LDSS_H
#define LDSS_H

#include <chrono>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <thread>
#include <sstream>
#include <vector>

namespace Luau {
    //--------------------------//
    //     LDSS functions       //
    //--------------------------//

    //Mostly used for saves for game projects.

    namespace LocalDataStoreService {
    const std::string Location = "./LocalDataStore/";
    inline bool GetLocalDataStore(const std::string& name) {
        try {
            std::filesystem::path Database = "./LocalDataStore";
            std::error_code ec;
            if (!(std::filesystem::exists(Database))) {
                std::filesystem::create_directory(Database, ec);
                std::filesystem::path dir = Location + name;
                if (!(std::filesystem::exists(dir))) {
                    std::ofstream file(dir);
                    return true;
                }
            } else {
                std::filesystem::path dir = Location + name;
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
            std::filesystem::path dir = Location + DataStoreName;
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
        std::filesystem::path dir = Location + DataStoreName;
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
            std::filesystem::path dir = Location + DataStoreName;
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
            std::filesystem::path dir = Location + DataStoreName;
            std::filesystem::path renamed = Location + Renamestring;
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
}

#endif