# CMakeList.txt : CMake project for test, include source and define
# project specific logic here.
#
project(Test)
        
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
cmake_minimum_required (VERSION 3.1)

find_package(GTest CONFIG REQUIRED)

find_package(Qt6 COMPONENTS Core Gui Sql Network Test REQUIRED)

include_directories(${CMAKE_INSTALL_PREFIX}/include)

string(REPLACE ${CMAKE_PROJECT_NAME} "Framework" FrameworkPath ${CMAKE_INSTALL_PREFIX})

add_executable(${PROJECT_NAME} 
                test.cpp
                Api.cpp
                RestApiOperationTest.h
                Environment.h
                pch.cpp
)

if (WIN32)
    target_compile_options(
        ${PROJECT_NAME}
        PRIVATE
        /bigobj
    )
endif()

target_link_libraries(
    ${PROJECT_NAME} 
    PUBLIC 
	Qt6::Core
    Qt6::Gui
    Qt6::Sql
    Qt6::Test
	Domain
	Service
    GTest::gtest GTest::gtest_main)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        include
)

target_include_directories(${PROJECT_NAME} PRIVATE ${FrameworkPath}/include)

include(GoogleTest)

install(
    TARGETS ${PROJECT_NAME}
    RUNTIME
        DESTINATION "bin"
)
		
