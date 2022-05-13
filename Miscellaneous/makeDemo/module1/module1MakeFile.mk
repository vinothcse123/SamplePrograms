CCC=g++
BUILD_DIR=./debug/
BIN_DIR=./bin/


ALL_CPP_SOURCE_FILES=$(wildcard src/*.cpp)
SOURCE_DIR=./src/
OBJ_FILES=$(addprefix $(BUILD_DIR)/, $(notdir $(ALL_CPP_SOURCE_FILES:.cpp=.o)))
DEPENDENCY_RULE_FILES=$(addprefix $(BUILD_DIR)/, $(notdir $(ALL_CPP_SOURCE_FILES:.cpp=.d)))


#Includes all dependency rules(.d files) generated using -MM command
-include $(OBJ_FILES:.o=.d) 

logDetails:
        @echo "Generating dependency rules and redirecting to .d file"

        @echo "List of object files : $(OBJ_FILES)"

        @echo "List of all CPP source files : $(ALL_CPP_SOURCE_FILES)"


$(BUILD_DIR)/%.d:$(SOURCE_DIR)/%.cpp

        @set -e; rm -f $@; \

        @#generate dependency rule file(.d) for each object file
        @#-MM is command line option by gnu to generate dependency rules. Passing -M includes system include files and -MM ignores the system include files
        @#Generates the .d file for each object file
        @$(CCC) -MM $< > $*.d.tmp

        @#sed command is used here to make .d files depend on the any of the file change in cpp file For example: myFile.o myFile.d : myHeaderFile.h
        @sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $*.d.tmp > $(BUILD_DIR)/$*.d; \

        #remove temp .d files
        @rm -f $*.d.tmp


#Hey compiler, if you want to generate object files, refer respective cpp files and execute the below commands
$(BUILD_DIR)/%.o:$(SOURCE_DIR)/%.cpp
        @#compiling individual files
        @echo $<
        @echo $@
        $(CCC) -c $< -o $@

clean:
        rm *.o *.d

.PHONY: all clean

#Starting point of make
all: logDetails $(DEPENDENCY_RULE_FILES) $(OBJ_FILES)
        @$(CCC) -o $(BIN_DIR)/myBinaryFile $(OBJ_FILES)
