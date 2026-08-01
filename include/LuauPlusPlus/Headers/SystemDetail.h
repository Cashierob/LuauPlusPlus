
#pragma once
#ifndef LUAU_SYSTEM_H
#define LUAU_SYSTEM_H

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

namespace LuauSystem {
    //--------------------------//
    //     Detail(System)       //
    //--------------------------//
    namespace Detail {
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
    struct InstanceHandle {
        bool found;
        std::filesystem::path path;

        struct Get_Data_Status {
            bool success;
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
        inline bool Rename(const std::string& Newname) 
        { try {
            if(!std::filesystem::exists(path)) {return false;}
            std::filesystem::path newPath = path.parent_path() / (Newname + path.extension().string());
            std::filesystem::rename(path, newPath);
            path = newPath; 
            return true;} catch (...) {
            return false;
        }
        }
        inline std::string Name() {
            if(!std::filesystem::exists(path)) {return "";}
            return path.filename().string();
        }
        inline bool SetParent(const std::filesystem::path Folderpath) { try {
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
        //WriteData,DeleteData,ReadData only works with txt files.
        inline bool WriteData(const std::string& datainput) {
            if(!std::filesystem::exists(path)) {return false;} 
            else {
                if(path.extension().string() == ".txt") {
                    std::ifstream filetxt(path);
                    if(filetxt.is_open()) {
                        std::string content;
                        std::ostringstream ss;
                        ss << filetxt.rdbuf();
                        content = ss.str();
                        filetxt.close();
                        std::ofstream filetxtwritten(path);
                        filetxtwritten << content << '\n';
                        filetxtwritten << datainput;
                        filetxtwritten.close();
                        return true;
                    }
                }
            }
            return false;
        }
        inline bool DeleteData() {
            if(!std::filesystem::exists(path)) {return false;}
            else {
                if (path.extension().string() == ".txt") {
                    std::ofstream textfile(path);
                    if(textfile.is_open()) {textfile.close(); return true;}
                }
                return false;
            }
        }
        inline Get_Data_Status ReadData() {
            if(!std::filesystem::exists(path)) {return {false, ""};}
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
        inline Detail::InstanceHandle FindFirstChild(const std::string& Filename) {
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
        
        inline Luau::Table::TableHandle GetChildren() {
            if(!std::filesystem::path(path).has_extension()) {return {};}
            auto children = Luau::Table::NewArray();
            for(auto& entry : std::filesystem::directory_iterator(path)) {
                if(!entry.is_regular_file()) continue;
                children.Insert(entry.path());
            }
            return children;
        }

        inline Detail::InstanceHandle Parent() {
            if(!std::filesystem::exists(path)) {return {false,{}};}
            if(!std::filesystem::exists(path.parent_path())) {return {false,{}};}
            return {true, path.parent_path()};
        }
    };
}
}

#endif