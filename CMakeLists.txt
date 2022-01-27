#NOTE: copy to /usr/local/include and /usr/local/lib when done
cmake_minimum_required(VERSION 3.16)
project(libDateTime)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# MOVE copy compile_commands.json TO BASE DIR
IF ( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" )
	EXECUTE_PROCESS ( COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
		${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
)
ENDIF()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CMAKE_BUILD_TYPE DEBUG)
#set(CMAKE_BUILD_TYPE RELEASE)

# CREATE STATIC LIBRARY
add_library(dt STATIC 
	src/CTime.cpp
	src/dt_tools.cpp
	)

# CREATE TESTING EXECUTABLE
add_executable(testCTime
	src/dt_test.cpp
	src/dt_tools.cpp
	src/CTime.cpp
	)

#file(GLOB HEADERS "include/*.hpp")
set (HEADERS 
	include/dt_tools.hpp
	include/CTime.hpp
	)

#EXECUTE_PROCESS ( COMMAND ${CMAKE_COMMAND} -E copy_directory
#	${CMAKE_SOURCE_BINARY_DIR}/include
#	/usr/local/include/dt
#	)
file(COPY ${HEADERS} DESTINATION /usr/local/include)

# TO COMPLETE, RUN cmake install TO PLACE LIBRARY IN lib DIRECTORY
install(TARGETS dt DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/lib)

