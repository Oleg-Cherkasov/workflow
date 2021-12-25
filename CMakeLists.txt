cmake_minimum_required(VERSION 3.21)
project(Workflow)

set(CMAKE_CXX_STANDARD 14)

add_executable(Workflow main.cpp workers.cpp workers.h factories.cpp factories.h parser.cpp parser.h exceptions.cpp exceptions.h)
