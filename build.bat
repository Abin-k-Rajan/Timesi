g++ -c _main.cpp -o build\object\_main.o
g++ -o bin\_main.exe build\object\_main.o -L. -lbuild\dll\time_table