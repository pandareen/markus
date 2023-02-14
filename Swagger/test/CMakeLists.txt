# CMakeList.txt : CMake project for test, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.1)
project(SwaggerTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(GTest CONFIG REQUIRED)

include_directories(../)

add_executable(${PROJECT_NAME} test.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Swagger GTest::gtest GTest::gtest_main)

include(GoogleTest)
#gtest_discover_tests(Swagger_test)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION Debug/bin
    LIBRARY DESTINATION Debug/lib
    ARCHIVE DESTINATION Debug/lib
    CONFIGURATIONS Debug
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION Release/bin
    LIBRARY DESTINATION Release/lib
    ARCHIVE DESTINATION Release/lib
    CONFIGURATIONS Release
)
