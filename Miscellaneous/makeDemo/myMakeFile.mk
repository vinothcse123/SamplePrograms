CCC=g++
OBJ_FILES=myCppFile.o
DEPENDENCY_RULE_FILES=myCppFile.d


#Includes all dependency rules(.d files) generated using -MM command
-include $(OBJ_FILES:.o=.d) 

%.d:%.cpp

	@set -e; rm -f $@; \

	@#generate dependency rule file(.d) for each object file
	@#-MM is command line option by gnu to generate dependency rules. Passing -M includes system include files and -MM ignores the system include files
	@#Generates the .d file for each object file
	@$(CCC) -MM $< > $*.d.tmp

	@#sed command is used here to make .d files depend on the any of the file change in cpp file For example: myFile.o myFile.d : myHeaderFile.h
	@sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $*.d.tmp > $*.d; \

	#remove temp .d files
	@rm -f $*.d.tmp



%.o:%.cpp
	@echo "Generating dependency rules and redirecting to .d file"
	
	@#compiling individual files
	$(CCC) -c $< 

clean:
	rm *.o *.d

.PHONY: all clean

#Starting point of make
all: $(DEPENDENCY_RULE_FILES) $(OBJ_FILES)
	@$(CCC) -o myBinaryFile $(OBJ_FILES)



