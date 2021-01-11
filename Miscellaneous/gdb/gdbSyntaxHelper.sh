#Master gdb starting command
gdb -q -x v6gdbInit.gdb --args ./myProgram arg1 arg2 


#passing arguments
gdb --args ./myProgram arg1 arg2


#Run default commands at startup
gdb -x v6gdbInit.gdb --args ./myProgram arg1 arg2

#Python core dump analysis
gdb python3 coreFile

#Thread info 
#Current active thread is marked as *.
info threads


