function(create_includes_and_vsfilter  folderName output objects)
    set(includes)

    foreach(loopVar IN LISTS objects)
        set(OBJECT_PATH "${folderName}/${loopVar}")

        get_filename_component(dir "${OBJECT_PATH}" PATH) 

        list(APPEND includes "${OBJECT_PATH}.h" ) 
        source_group(${dir} FILES "${OBJECT_PATH}.h")

        if(EXISTS "${PROJECT_SOURCE_DIR}/${OBJECT_PATH}.cpp") #only add cpp if existing
            list(APPEND includes "${OBJECT_PATH}.cpp") 
            source_group(${dir} FILES "${OBJECT_PATH}.cpp")
        endif()
    endforeach()

    set(${output} "${includes}" PARENT_SCOPE)
endfunction()

function(setup_service_project ProjectName ApiPaths Utilities)

     if(NOT ApiPaths)
       message("No ApiPaths defined!")
     endif()

    message("Building = ${CMAKE_PROJECT_NAME}/${PROJECT_NAME}")
    set(CMAKE_CXX_STANDARD 20 PARENT_SCOPE)
    set(CMAKE_CXX_STANDARD_REQUIRED ON PARENT_SCOPE)

	
    set(CMAKE_AUTOMOC ON PARENT_SCOPE)
    set(CMAKE_AUTORCC ON PARENT_SCOPE)
    set(CMAKE_AUTOUIC ON PARENT_SCOPE)
    
    string(REPLACE ${CMAKE_PROJECT_NAME} "Framework" FrameworkPath ${CMAKE_INSTALL_PREFIX})

	message("${FrameworkPath}/${CMAKE_BUILD_TYPE}/lib")
    find_package(Qt6 COMPONENTS Core Gui Sql REQUIRED)
    find_library(DomainCore DomainCore HINTS ${FrameworkPath}/${CMAKE_BUILD_TYPE}/lib REQUIRED)
    find_library(ServiceCore ServiceCore HINTS ${FrameworkPath}/${CMAKE_BUILD_TYPE}/lib REQUIRED REQUIRED) #create package one day
    find_library(Sql Sql HINTS ${FrameworkPath}/${CMAKE_BUILD_TYPE}/lib REQUIRED) #create package one day
    find_library(RestApiServer RestApiServer HINTS ${FrameworkPath}/${CMAKE_BUILD_TYPE}/lib REQUIRED) #create package one day
    find_library(Swagger Swagger HINTS ${FrameworkPath}/${CMAKE_BUILD_TYPE}/lib REQUIRED) #create package one day

    set(ApiPath_includes)
    set(Utility_includes)

    create_includes_and_vsfilter( ApiPath ApiPath_includes "${ApiPaths}")
    create_includes_and_vsfilter( Utility Utility_includes "${Utilities}")

    source_group(Service FILES "ApiPathFactory.h")
    source_group(Service FILES "ApiPathFactory.cpp")

    set(includesOut ${ApiPath_includes} ${Utility_includes} global.h ApiPathFactory.h ApiPathFactory.cpp PARENT_SCOPE)
    set(librariesOut Qt6::Core Qt6::Gui Qt6::Sql ${DomainCore} ${ServiceCore} ${Sql} ${RestApiServer} ${Swagger} PARENT_SCOPE)
    set(includeDirOut "${FrameworkPath}/include" PARENT_SCOPE)

endfunction()