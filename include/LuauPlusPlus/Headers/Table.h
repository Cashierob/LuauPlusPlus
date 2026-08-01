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
#ifndef LUAU_TABLE_H
#define LUAU_TABLE_H

#include <cctype>
#include <cmath>
#include <filesystem>
#include <iostream>
#include <limits>
#include <string>
#include <thread>
#include <type_traits>
#include <vector>
#include <variant>

namespace Luau {
    //--------------------------//
    //     Table functions      //
    //--------------------------//
    namespace Table {
    struct TableHandle {
        using Varianttype = std::variant<int, double, std::string, bool, std::filesystem::path>;
        std::vector<Varianttype> ArrayTable;
        class TableDetail {
            public:
            inline std::string ToString(const Varianttype& value) {
                return std::visit([](const auto& v) -> std::string {
                using T = std::decay_t<decltype(v)>;
                if constexpr (std::is_same_v<T, std::string>)
                    return v;
                else if constexpr (std::is_same_v<T, std::filesystem::path>)
                    return v.string();
                else if constexpr (std::is_same_v<T, bool>)
                    return v ? "true" : "false";
                else
                    return std::to_string(v);
                }, value);
            }
        };
        TableDetail TD;
        inline std::string Tostring(const int index) {
            return TD.ToString(ArrayTable[index - 1]);
        }
        auto begin() {return ArrayTable.begin();}
        auto end() {return ArrayTable.end();}
        auto begin() const {return ArrayTable.begin();}
        auto end() const {return ArrayTable.end();}
        Varianttype operator[](const int index) {
            try {
                if (index > ArrayTable.size() || index == 0) {std::cout << "Invalid Luau index." << std::endl; return {};}
                return ArrayTable[index - 1];
            } catch(...) {std::cout << "Error" << std::endl; return {};}
        }
        template<typename T>
        inline bool Insert(const T& input){
            try {
            if constexpr (std::is_convertible_v<T, std::string>) {
                ArrayTable.emplace_back(std::string(input));
            }
            else {
                ArrayTable.emplace_back(input);
            }
                return true;
            }catch (...) {return false;}
        }
        inline bool Remove(const std::size_t index) {
            try {
                if (index > ArrayTable.size() || index == 0) return false;
                ArrayTable.erase(ArrayTable.begin() + (index - 1));
                return true;
            } catch (...) {return false;}
        }
        inline int Size() {
            return ArrayTable.size();
        }
        inline bool Print(const int index) {
            if (index > 0 && index <= ArrayTable.size()) {
                std::cout << TD.ToString(ArrayTable[index - 1]) << std::endl;
                return true;
            }
            return false;
        }
    };

    inline TableHandle NewArray() {
        return {};
    }
}
}

#endif