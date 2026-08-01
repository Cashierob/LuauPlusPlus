Made By @cashierob Discord

(A very very early project.)

This is a small A C++ library that lets developers write Luau-like code by providing 
familiar Luau functions and services implemented in C++.
or just a Luau compatibility layer for C++.

(Some codes are changed to match the Window environment)

Version #4

Before writing a project using this, remember to copy the header into your folder project
and paste:

"#include "LuauPlusPlus.h"".

//(Most of the original functions got added "l" at the end to avoid name conflicts or gets changed
//completely.) 

Some basic core functions.
------------------------
Luau::Print(str);
//Print the input.
Luau::Typeof(str/int);
//Return the corresponding variable type.

Some basic Luau::Read functions.
------------------------
Luau::Read::ReadString();
//Repeats, if integer, returns a string.
Luau::Read::ReadNumber();
//Repeats, if string, returns an integer (Mostly double);

Some String functions.
----------------------
Luau::String::Lower(str);
//Return a string with all downcase.
Luau::String::Upper(str);
//Return a string with all uppercase.
Luau::String::Find(str, substr);

Some Math functions.
----------------------
Luau::Math::Random(min,max);
//Randomize a number between min and max.
Luau::Math::Pi();
//Return pi.
Luau::Math::Huge();
//Return infinity;
Luau::Math::Abs(value);
//Return abs of the input value.

LocalDataStoreService Instructions.
----------------------------
//LocalDataStoreService is an idea of mine to match with the computer environment   
as it saves file locally on your computer, where the header is.

Luau::LocalDataStoreService::GetDataStore(name); 
//Make the DataSave file if not existing and then the txt to store the data.
Luau::LocalDataStoreService::SetAsync(keyname, value);
//Replace data, rewrite data.
Luau::LocalDataStoreService::GetAsync(keyname);
//Return Data that's present in the file.
Luau::LocalDataStoreService::RemoveAsync(keyname);
//Remove the Async;
Luau::LocalDataStoreService::RenameAsync(keyname);
//Rename the Async;

File Instructions.
----------------------------
//File manipulations.

Luau::File::FindFirstChild(parent_folder_path,filename);
//Return filename path/true if found.
Luau::File::Name(File_path, New_file_name);
//Changes name of a file/directory.
Luau::File::Destroy(File_path);
//Remove a directory/File and return true if success.

and many more.
(Soon there will be an example folder for showcasing codes.)