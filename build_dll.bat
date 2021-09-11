g++ -m32 -c -DBUILD_CUSTOM_DLL src\time_table\time_table.cpp -o build\object\time_table.o
g++ -m32 -shared -o build\dll\time_table.dll build\object\time_table.o -Wl,--out-implib,build\lib\time_table_lib.a
copy build\dll\time_table.dll bin