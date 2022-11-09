g++ -g myCppFile.cpp -std=c++14

valgrind   --tool=callgrind --log-file=MycalgrindConsoleOutput.txt --callgrind-out-file=callgrindDataFile.dat ./a.out

callgrind_annotate callgrindDataFile.dat &> callgrindAnnotateResult.txt
