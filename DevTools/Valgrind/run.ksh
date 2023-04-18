g++ -g myCppFile.cpp -std=c++11


valgrind --leak-check=full --verbose --log-file=MyvalgrindOutput.txt ./a.out  

#Attaching to gdb server
#valgrind --leak-check=full --vgdb=full --vgdb-error=0 --num-callers=20 --error-exitcode=1 --error-limit=no myProgram
