cmake_minimum_required(VERSION 3.21)

project(dqcg)
set(CMAKE_CXX_STANDARD 11)
set(SOURCES main.cpp  bmpimage.h bmpimage.cpp)

add_executable(dqcg ${SOURCES})