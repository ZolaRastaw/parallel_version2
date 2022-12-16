# CMakeList.txt : CMake project for parallel_version2, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8 FATAL_ERROR)

project ("parallel_version2")


# TODO: Add tests and install targets if needed.


OPTION(BUILD_WITH_OPENMP "Build with OPENMP" OFF)
IF(BUILD_WITH_OPENMP)
# to set the /openmp switch
find_package(OpenMP REQUIRED)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
ENDIF(BUILD_WITH_OPENMP)


SET(parallel_version2-src 
parallel_version2.cpp
)

SET(parallel_version2-header
)

ADD_EXECUTABLE(
    parallel_version2
${parallel_version2-src} 
${parallel_version2-header}
)

IF(BUILD_WITH_OPENMP)
set_target_properties(parallel_version2 PROPERTIES OUTPUT_NAME "parallel_version2_omp")
ENDIF(BUILD_WITH_OPENMP)

