g++ -g myCppFile.cpp -std=c++11

valgrind --leak-check=full --verbose --log-file=MyvalgrindOutput.txt ./a.out  
