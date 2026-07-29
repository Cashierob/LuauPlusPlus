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
Print(str);

//Print the input.

Typeof(str/int);

//Return corresponding variable type.

Some basic Read functions.
------------------------
Read::Read_String();

//Repeats if integer, returns a string.

Read::Read_Number();

//Repeats if string, returns an integer (Mostly double);

Some stringl functions.
----------------------
stringl::lower(str);

//Return a string with all downcase.

stringl::upper(str);

//Return a string with all uppercase.

stringl::find(str, substr);

Some mathl functions.
----------------------
mathl.randoml(min,max);

//randomize a number between min and max.

mathl::pi();

//Return pi.

mathl::huge();

//Return infinity;

mathl::absl(value);

//Return abs of the input value.

LocalDataStoreService Instructions.
----------------------------
//LocalDataStoreService is an idea of mine to match with the computer environment   
as it saves file locally on your computer, where the header is.

LocalDataStoreService::GetDataStore(name);

//Make the DataSave file if not existing and then the txt to store the data.

LocalDataStoreService::SetAsync(keyname, value);

//Replace data, rewrite data.

LocalDataStoreService::GetAsync(keyname);

//Return Data that's present in the file.

LocalDataStoreService::RemoveAsync(keyname);

//Remove the Async;

LocalDataStoreService::RenameAsync(keyname);

//Rename the Async;

filel Instructions.
----------------------------
//File manipulations.

filel::FindFirstChild(parent_folder_path,filename);

//Return filename path/true if found.

filel::Name(File_path, New_file_name);

//Changes name of a file/directory.

filel::Destroy(File_path);

//Remove a directory/File and return true if success.

and many more.

(Soon there will be an example folder for showcasing codes.)
