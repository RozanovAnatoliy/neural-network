cmake_minimum_required(VERSION 2.8)
project(NeuralNetwork)

file(GLOB CPPS "src/*.cpp")
file(GLOB HS "include/*.h")
include_directories(include)

add_executable(${PROJECT_NAME} ${CPPS} ${HS})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BIN_DIR ${ROOT_DIR}/_bin)
add_custom_target(post_binaries ALL DEPENDS NeuralNetwork
                  COMMAND ${CMAKE_COMMAND} -E make_directory ${BIN_DIR}
                  COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:NeuralNetwork>
                                                                ${BIN_DIR}/$<TARGET_FILE_NAME:NeuralNetwork>
                  )
set_target_properties(post_binaries PROPERTIES FOLDER BuildInfrastructure)