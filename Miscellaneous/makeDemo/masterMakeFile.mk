CCC=g++
BIN_DIR=./bin/

BUILD_DIR_M1=module1/debug/
ALL_CPP_SOURCE_FILES_1=$(wildcard module1/src/*.cpp)
OBJ_FILES_1=$(addprefix $(BUILD_DIR_M1)/, $(notdir $(ALL_CPP_SOURCE_FILES_1:.cpp=.o)))

BUILD_DIR_M2=module2/debug/
ALL_CPP_SOURCE_FILES_2=$(wildcard module2/src/*.cpp)
OBJ_FILES_2=$(addprefix $(BUILD_DIR_M2)/, $(notdir $(ALL_CPP_SOURCE_FILES_2:.cpp=.o)))


#Starting point of make
all: 
        cd module1 && make all -f module1MakeFile.mk
        cd module2 && make all -f module2MakeFile.mk
        echo $(ALL_CPP_SOURCE_FILES_1)
        echo $(OBJ_FILES_1)
        @$(CCC) -o $(BIN_DIR)/myBinaryFile $(OBJ_FILES_1) $(OBJ_FILES_2)
    
