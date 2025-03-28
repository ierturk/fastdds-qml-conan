cmake_minimum_required(VERSION 3.15)
project(FastDDS_QML_Example VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt configuration
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find dependencies (installed by Conan)
find_package(fastdds REQUIRED)
find_package(Qt6 COMPONENTS Core Quick Qml REQUIRED)

# QML resources
qt_add_resources(QML_RESOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc
)

# Add source files
set(SOURCES
    # src/HelloWorld.cxx
    # src/HelloWorldPubSubTypes.cxx
    src/DDSManager.cpp
    src/main.cpp
)

# Add custom command for fastddsgen
set(FASTDDSGEN_IDL_FILE ${CMAKE_CURRENT_SOURCE_DIR}/src/idl/HelloWorldMsg.idl)
set(FASTDDSGEN_OUTPUT_DIR ${CMAKE_BINARY_DIR}/fastdds-gen)

add_custom_command(
    OUTPUT ${FASTDDSGEN_OUTPUT_DIR}/HelloWorldMsg.cxx ${FASTDDSGEN_OUTPUT_DIR}/HelloWorldMsgPubSubTypes.cxx
    COMMAND fastddsgen -d ${FASTDDSGEN_OUTPUT_DIR} ${FASTDDSGEN_IDL_FILE}
    DEPENDS ${FASTDDSGEN_IDL_FILE}
    COMMENT "Generating Fast DDS code from ${FASTDDSGEN_IDL_FILE}"
    VERBATIM
)

# Add generated files to the sources
list(APPEND SOURCES
    ${FASTDDSGEN_OUTPUT_DIR}/HelloWorldMsg.cxx
    ${FASTDDSGEN_OUTPUT_DIR}/HelloWorldMsgPubSubTypes.cxx
)

# Add custom target to force generation
# add_custom_target(generate_fastdds_code
#     DEPENDS ${FASTDDSGEN_OUTPUT_DIR}/HelloWorldMsg.cxx ${FASTDDSGEN_OUTPUT_DIR}/HelloWorldMsgPubSubTypes.cxx
# )

# Create GUI application
add_executable(fastdds_qml 
    ${SOURCES}
    ${QML_RESOURCES}
)

# Ensure the custom target runs before building the executable
# add_dependencies(fastdds_qml generate_fastdds_code)

# Link with Fast DDS and Qt libraries
target_link_libraries(fastdds_qml PRIVATE
    fast-dds::fast-dds
    Qt6::Core
    Qt6::Quick
    Qt6::Qml
)

# Include directories
target_include_directories(fastdds_qml PRIVATE src ${FASTDDSGEN_OUTPUT_DIR})

# Installation rules
install(TARGETS fastdds_qml DESTINATION bin)

# Windows-specific deployment
if(WIN32)
    # Copy Qt plugins for deployment
    get_target_property(_qmake_executable Qt6::qmake IMPORTED_LOCATION)
    get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
    
    add_custom_command(TARGET fastdds_qml POST_BUILD
        COMMAND "${_qt_bin_dir}/windeployqt.exe"
                --qmldir "${CMAKE_CURRENT_SOURCE_DIR}/src/qml"
                "$<TARGET_FILE:fastdds_qml>"
        COMMENT "Deploying Qt dependencies..."
    )
endif()