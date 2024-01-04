cmake_minimum_required(VERSION 3.25)
project(data-structures)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

set(SOURCES src/main.cpp)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/out.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


set(HEADERS include/My_Single_Linked_List.h include/My_Doubly_Linked_List.h include/Big_Int.h
        include/graph-with-adjacency-matrix.h include/My_bt.h include/My_Bst.h include/AVL.h include/Heap.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)