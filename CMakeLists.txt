cmake_minimum_required(VERSION 3.6)
project(hybrid_alns)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/TabuMove.cpp src/TabuMove.h src/DestroyMethod.cpp src/DestroyMethod.h src/Instance.cpp src/Instance.h src/RepairMethod.cpp src/RepairMethod.h src/Params.cpp src/Params.h src/AcceptanceCriterion.cpp src/AcceptanceCriterion.h src/Solution.cpp src/Solution.h src/PartialSolution.cpp src/PartialSolution.h src/ALNSSolver.cpp src/ALNSSolver.h src/LocalSearchOperator.cpp src/LocalSearchOperator.h)
add_executable(hybrid_alns ${SOURCE_FILES})