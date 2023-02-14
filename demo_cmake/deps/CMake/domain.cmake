function(create_includes_and_vsfilter  folderName output objects)
    set(includes)

    foreach(loopVar IN LISTS objects)
        set(OBJECT_PATH "Types/${folderName}/${loopVar}")

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

function(setup_domain_project ProjectName ValueObjects Entities)

     if(NOT Entities)
       message("No Entities defined!")
     endif()

    set(CMAKE_CXX_STANDARD 20 PARENT_SCOPE)
    set(CMAKE_CXX_STANDARD_REQUIRED ON PARENT_SCOPE)

    set(CMAKE_AUTOMOC ON PARENT_SCOPE)
    set(CMAKE_AUTORCC ON PARENT_SCOPE)
    set(CMAKE_AUTOUIC ON PARENT_SCOPE)

    string(REPLACE ${CMAKE_PROJECT_NAME} "Framework" FrameworkPath ${CMAKE_INSTALL_PREFIX})

    find_package(Qt6 COMPONENTS Core REQUIRED)
    message("${FrameworkPath}/${CMAKE_BUILD_TYPE}/lib")
    find_library(DomainCore DomainCore HINTS ${FrameworkPath}/${CMAKE_BUILD_TYPE}/lib REQUIRED)
    find_library(jsonserializer jsonserializer HINTS ${FrameworkPath}/${CMAKE_BUILD_TYPE}/lib REQUIRED)

    set(ValueObjects_includes)
    set(Entities_includes)

    create_includes_and_vsfilter( ValueObject ValueObjects_includes "${ValueObjects}")
    create_includes_and_vsfilter( Entity Entities_includes "${Entities}")

    source_group(Domain FILES "Domain.h")
    source_group(Domain FILES "Domain.cpp")

    set(includesOut ${ValueObjects_includes} ${Entities_includes} global.h Domain.h Domain.cpp PARENT_SCOPE)
    set(librariesOut Qt6::Core ${DomainCore} ${jsonserializer} PARENT_SCOPE)
    set(includeDirOut "${FrameworkPath}/include" "${FrameworkPath}/include/jsonserializer" PARENT_SCOPE)
endfunction()


#setup_domain_project to keyword function would be cool #todo
function(func)
    # Define the supported set of keywords
    set(prefix ARG)
    set(noValues)
    set(singleValues TARGET)
    set(multiValues SOURCES IMAGES)
    # Process the arguments passed in
    include(CMakeParseArguments)
    cmake_parse_arguments(
            ${prefix}
            "${noValues}" "${singleValues}" "${multiValues}"
            ${ARGN}
    )
    # Log details for each supported keyword
    message("Option summary:")
    foreach(arg IN LISTS noValues)
        if(${prefix}_${arg})
            message(" ${arg} enabled")
        else()
            message(" ${arg} disabled")
        endif()
    endforeach()

    foreach(arg IN LISTS singleValues multiValues)
    # Single argument values will print as a string
    # Multiple argument values will print as a list
    message(" ${arg} = ${${prefix}_${arg}}")
    endforeach()
endfunction()

