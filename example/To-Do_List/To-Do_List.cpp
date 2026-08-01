#include <iostream>
#include "../LuauPlusPlus/LuauPlusPlus.h"

// Compile with: g++ -std=c++20 To-Do_List.cpp -o To_Do_List

int main() {
    Luau::Print("Note name: "); 
    std::string name = Luau::Read::ReadString();
    //Get User Input in string only, repeats if invalid until success.
    
    auto note = Luau::Instance::NewFile(name + ".txt");
    //Create txt file for saving.
    if (!note.found) {
        Luau::Print("Failed to create note.");
        return 0;
    }

    Luau::Print("Note created: " + name + ".txt");
    //Just printing, that's all (std::cout << message << std::endl;).
    Luau::Print("Type your notes (type 'exit' to quit):\n");

    while (true) {
        std::string content = Luau::Read::ReadString(); 
        //Get user input (Only accepts string and will repeat until success.)

        if (content == "exit") break;
        //Inputting content until the user types "exit"

        note.WriteData(content); 
        //Write Data (Not overwrite) into the file.
        Luau::Print("Saved.");
    }

    Luau::Print("Goodbye!");
    Luau::SystemWait(); // Basically std::cin.get();
    return 0;
}