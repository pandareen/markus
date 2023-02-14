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

function(setup_service_project ProjectName Utilities)

    message("Building = ${CMAKE_PROJECT_NAME}/${PROJECT_NAME}")
    set(CMAKE_CXX_STANDARD 20 PARENT_SCOPE)
    set(CMAKE_CXX_STANDARD_REQUIRED ON PARENT_SCOPE)
	
    string(REPLACE ${CMAKE_PROJECT_NAME} "Framework" FrameworkPath ${CMAKE_INSTALL_PREFIX})
	
	
    set(CMAKE_AUTOMOC ON PARENT_SCOPE)
    set(CMAKE_AUTORCC ON PARENT_SCOPE)
    set(CMAKE_AUTOUIC ON PARENT_SCOPE)
    
    find_package(Qt6 COMPONENTS Core Gui REQUIRED)
	message("${PROJECT_SOURCE_DIR}/../Service/${CMAKE_BUILD_TYPE}/lib")
    #find_library(Service Service HINTS ${PROJECT_SOURCE_DIR}/../Service/${CMAKE_BUILD_TYPE}/lib REQUIRED REQUIRED) #create package one day
    

	
    set(Utility_includes)

    create_includes_and_vsfilter( Utility Utility_includes "${Utilities}")

    source_group(App FILES "App.h")
    source_group(App FILES "App.cpp")

    set(MainFiles global.h App.cpp)

    set(includesOut ${Utility_includes} ${MainFiles} PARENT_SCOPE)

    set(librariesOut Qt6::Core Qt6::Gui PARENT_SCOPE)
    set(includeDirOut "${Service}/include" PARENT_SCOPE)

    qt_standard_project_setup()
endfunction()