#
# Compiles all CPP examples
#
# Remark: you must download first the archive (zip/tar) of these examples
#
cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#
# Building all the Marmote examples
#
foreach( EXAMPLE_NUMBER IN ITEMS 1 2 3 4 5 6 7 )
    set(PROJ_N "example")
    string(APPEND PROJ_N ${EXAMPLE_NUMBER})
    set(PROJ_MAIN "example")
    string(APPEND PROJ_MAIN ${EXAMPLE_NUMBER}.cpp)
    message( "Building project ${PROJ_N} from source ${PROJ_MAIN}" )
    project(${PROJ_N})
    find_package(marmote REQUIRED COMPONENTS marmoteCore marmoteMarkovChain marmoteMDP)
    add_executable(${PROJECT_NAME} ${PROJ_MAIN})
    target_link_libraries(${PROJECT_NAME} PUBLIC marmoteCore marmoteMarkovChain)
endforeach()

#
# Building the MarmoteMDP examples
#
foreach( EXAMPLE_NUMBER IN ITEMS 10 11 20 21 22 30 31 40)
    set(PROJ_N "exampleMDP")
    string(APPEND PROJ_N ${EXAMPLE_NUMBER})
    set(PROJ_MAIN "exampleMDP")
    string(APPEND PROJ_MAIN ${EXAMPLE_NUMBER}.cpp)
    message( "Building project ${PROJ_N} from source ${PROJ_MAIN}" )
    project(${PROJ_N})
    find_package(marmote REQUIRED COMPONENTS marmoteCore marmoteMarkovChain marmoteMDP)
    add_executable(${PROJECT_NAME} ${PROJ_MAIN})
    target_link_libraries(${PROJECT_NAME} PUBLIC marmoteCore marmoteMDP)
endforeach()
