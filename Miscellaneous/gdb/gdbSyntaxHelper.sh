#Master gdb starting command
gdb -q -x v6gdbInit.gdb --args ./myProgram arg1 arg2 

#passing arguments
gdb --args ./myProgram arg1 arg2

#Analyze core without binary name
gdb -c core.335343

#Run default commands at startup
gdb -x v6gdbInit.gdb --args ./myProgram arg1 arg2

#Python core dump analysis
gdb python3 coreFile

#Python debugging
gdb --args  python3 myPythonFile.py

#Thread info 
#Current active thread is marked as *.
info threads


#Backtrace of all threads
thread apply all backtrace

#Catch exception
catch throw

#Debug running process
gdb -p <processId>

#Execute shell commands
shell ./compile.ksh

#Run gdb commands automatically
gdb --command=listOfCommands.gdb binaryFile
