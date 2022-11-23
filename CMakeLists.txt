cmake_minimum_required (VERSION 3.10)

project (ChatServer)

set (CMAKE_CXX_STANDARD 20)

link_directories (${Boost_INCLUDE_DIR}) # root 
link_directories (${Boost_INCLUDE_DIR}/bin/x64/lib) # libs

set (Boost_USE_DEBUG_LIBS ON)
set (Boost_USE_MULTITHREADED ON)
set (BOOST_ALL_DYN_LINK ON)

find_package (Boost)

include_directories(
	"source/" 
	"source/utils/" 
	"source/settings/")

set(SRC_LIST 
	"source/settings/settings.cpp"
	"source/main.cpp" )

if (Boost_FOUND)
	add_executable (${PROJECT_NAME} ${SRC_LIST})
	include_directories (${PROJECT_NAME} ${Boost_INCLUDE_DIR})
	target_link_libraries (${PROJECT_NAME} ${Boost_LIBRARIES})
else ()
	message(STATUS "Boost package was not found")
endif ()

# TODO: tests
