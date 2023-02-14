# CMakeList.txt : CMake project for test, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.1)
project(Swagger)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_CLANG_TIDY
  clang-tidy;
  -header-filter=.;
  -checks=*;
  -warnings-as-errors=*;)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS Core REQUIRED)





set(Includes
container/List
SwaggerObject
OperationFactory
OpenApi/Schema/SchemaList
OpenApi/Schema/Schema
OpenApi/Schema/Object/Object
OpenApi/Schema/Object/OneOf
OpenApi/Schema/Object/AnyOf
OpenApi/Schema/Object/AllOf
OpenApi/Schema/Factory/SchemaFactory
OpenApi/Schema/Factory/FieldFactory
OpenApi/Schema/DynamicField/FieldList
OpenApi/Schema/DynamicField/Field/WriteOnly
OpenApi/Schema/DynamicField/Field/Summary
OpenApi/Schema/DynamicField/Field/Type
OpenApi/Schema/DynamicField/Field/ReadOnly
OpenApi/Schema/DynamicField/Field/Pattern
OpenApi/Schema/DynamicField/Field/MinLength
OpenApi/Schema/DynamicField/Field/MultipleOf
OpenApi/Schema/DynamicField/Field/MaxLength
OpenApi/Schema/DynamicField/Field/Min
OpenApi/Schema/DynamicField/Field/Max
OpenApi/Schema/DynamicField/Field/Items
OpenApi/Schema/DynamicField/Field/Enum
OpenApi/Schema/DynamicField/Field/Format
OpenApi/Schema/DynamicField/Field/Description
OpenApi/Schema/DynamicField/Field/Default
OpenApi/Schema/DynamicField/DynamicField
OpenApi/Schema/ConvertError
OpenApi/Schema/Array
OpenApi/Response/Responses
OpenApi/Response/ResponsesFactory
OpenApi/Response/ResponseFactory
OpenApi/Response/Response
OpenApi/RequestBody/RequestBodyFactory
OpenApi/RequestBody/RequestBody
OpenApi/Path/PathRoute
OpenApi/Path/Paths
OpenApi/Path/PathFragment
OpenApi/Path/Path
OpenApi/Path/PathFactory
OpenApi/Path/EventFactory
OpenApi/Path/Event
OpenApi/Path/Callbacks
OpenApi/Parameter/Query
OpenApi/Parameter/PathParameter
OpenApi/Parameter/ParameterFactory
OpenApi/Parameter/Header
OpenApi/Parameter/Parameter
OpenApi/Parameter/Cookie
OpenApi/Operation
OpenApi/OpenApi
OpenApi/Information/Server
OpenApi/Information/License
OpenApi/Information/Info
OpenApi/Information/Contact
OpenApi/Components
IJson
container/Map
)

foreach(file IN LISTS Includes)
	get_filename_component(dir "${file}" PATH) 
    source_group(${dir} FILES "${file}.h")
    source_group(${dir} FILES "${file}.cpp")

    list(APPEND includes "${file}.h" ) 

	if(EXISTS "${PROJECT_SOURCE_DIR}/${file}.cpp")
       list(APPEND includes "${file}.cpp" ) 
	endif()
endforeach()

add_library(${PROJECT_NAME} SHARED 
    ${includes}
)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Library")

if (WIN32)
    target_compile_options(
        ${PROJECT_NAME}
        PRIVATE
        /bigobj
    )
endif()

target_link_libraries(
    ${PROJECT_NAME} PUBLIC
        Qt6::Core
        Qt6::CorePrivate
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ../
)

install(DIRECTORY ./
        DESTINATION include/${PROJECT_NAME}
        FILES_MATCHING # install only matched files
        PATTERN "*.h"
)

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

add_subdirectory(test)