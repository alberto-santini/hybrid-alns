cmake_minimum_required(VERSION 3.5)
project(hybrid_alns)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -m64 -Wall -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG -O3 -flto")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(Exactcolors)
include_directories(SYSTEM ${EXACTCOLORS_INCLUDE_DIR})

find_package(Cplex)
include_directories(SYSTEM ${CPLEX_INCLUDE_DIRS})

set(SOURCE_FILES src/main.cpp src/TabuMove.h src/DestroyMethod.h src/RepairMethod.h src/Params.cpp src/Params.h src/AcceptanceCriterion.h src/Solution.h src/PartialSolution.h src/ALNSSolver.cpp src/ALNSSolver.h src/LocalSearchOperator.h src/DRMethod.h src/vcp/VCInstance.cpp src/vcp/VCInstance.h src/vcp/Colouring.cpp src/vcp/Colouring.h src/acceptance/WorseAccept.cpp src/acceptance/WorseAccept.h src/vcp/GreedyColour.cpp src/vcp/GreedyColour.h src/vcp/DestroyMethods.h src/vcp/DestroyMethods.cpp src/vcp/RepairMethods.h src/vcp/VCTabuMove.h src/vcp/RepairMethods.cpp src/vcp/VCTabuMove.cpp src/vcp/VCLocalSearch.cpp src/vcp/VCLocalSearch.h src/vcp/VCParams.cpp src/vcp/VCParams.h src/vcp/MWSS.cpp src/vcp/MWSS.h src/SuppressOutput.h src/Column.h src/ColumnOptimiser.h src/vcp/VCColumnOptimiser.cpp src/vcp/VCColumnOptimiser.h)

add_executable(hybrid_alns ${SOURCE_FILES})
target_link_libraries(hybrid_alns ${SEWELL_LIBRARY})
target_link_libraries(hybrid_alns ${CPLEX_LIBRARIES})