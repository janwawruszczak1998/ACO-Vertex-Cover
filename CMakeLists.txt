cmake_minimum_required(VERSION 3.13)
project(AOIN)

set(CMAKE_CXX_STANDARD 17)

add_executable(AOIN main.cpp Graph.h InputOutput.cpp InputOutput.h Algo.cpp Algo.h Randoms.cpp Randoms.h ACO.cpp ACO.h Aprox.cpp Aprox.h AlgorithmContext.cpp AlgorithmContext.h TestsGenerator.cpp TestsGenerator.h)
