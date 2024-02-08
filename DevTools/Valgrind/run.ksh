g++ -g myCppFile.cpp -std=c++11


valgrind --leak-check=full --log-file=MyvalgrindOutput.txt --show-leak-kinds=all --gen-suppressions=yes --undef-value-errors=no --suppressions=valgrindSupressionList.sup  --num-callers=20 --error-exitcode=1 --error-limit=no ./a.out


#Attaching to gdb server
#valgrind --leak-check=full --vgdb=full --vgdb-error=0 --num-callers=20 --error-exitcode=1 --error-limit=no myProgram
