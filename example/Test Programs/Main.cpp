#include "../../include/LuauPlusPlus/LuauPlusPlus.h"

using namespace Luau;

int main(){
    local HelloWorld = "Hello World!";
    Print(HelloWorld);
    local Greetings = "Greetings from Luau++, what is your name?";
    Print(Greetings);
    local Name = Read::ReadString();
    Print("Hello, " + Name + "!");
    return 0;
}