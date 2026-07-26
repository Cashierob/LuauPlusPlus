Made By @cashierob Discord

This is a small A C++ library that lets developers write Luau-like code by providing 
familiar Luau functions and services implemented in C++.
or just a Luau compatibility layer for C++.

Version #1

Before writing a project using this, remember to copy the Luau++ folder into your folder project
and paste:


"#include "LUAU++/Luau++.h""

And

"STR string;
MTH math;
LDTS LocalDataStoreService;"

And you'll have to compile with "g++ -std=c++20 Yourfilename.cpp -o Name"

Here are some working luau that works:
print(str);
UserInput(str); //Return userinput like getline();
type(str/int); //Return corresponding variable type
string.stringlower(str);
string.stringupper(str);
string.find(str, substr);
math.random(min,max);

And etc.

even LocalDataStoreService that saves data in your local folder that you stores your project.

LocalDataSaveService Instructions
----------------------------
LocalDataStoreService.GetDataStore(name); 
//Make the DataSave file if not existing and then the txt to store the data.
LocalDataStoreService.SetAsync(keyname, value);
//Replace data, rewrite data.
LocalDataStoreService.GetAsync(keyname);
//Return Data that's present in the file.
LocalDataStoreService.RemoveAsync(keyname);
//Remove the Async;