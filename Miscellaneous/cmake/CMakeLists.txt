#GH_MISC_5
#Specifies minimum cmake vesions required for build
cmake_minimum_required(VERSION 3.5)

project (myProject)

#set Source files
set(V6_SOURCE_FILE
    src/cppFile.cpp
)

message(STATUS "My include dir: ${PROJECT_SOURCE_DIR}")

#Create an executable same name as project name for cppFile.cpp file
add_executable(${PROJECT_NAME} ${V6_SOURCE_FILE})


#It will be included as -I../inc in the make file
target_include_directories(${PROJECT_NAME}
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/inc/
)   
