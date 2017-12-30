cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
set(Boost_USE_STATIC_LIBS ON) 
set(BOOST_TEST_LOG_LEVEL all)
project(ip_filter VERSION 0.0.1)

find_package(Boost 1.65.1 COMPONENTS unit_test_framework REQUIRED)

#configure_file(version.h.in version.h)

add_executable(ip_filter main.cpp)

add_library(split split.cpp)

add_library(ip ip.cpp)

add_executable(test_split test_split.cpp)

set_target_properties(ip_filter split PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
	COMPILE_OPTIONS -Wpedantic -Wall -Wextra
	COMPILE_FLAGS -std=c++1z
)

set_target_properties(test_split PROPERTIES
	#COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
	INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(ip_filter
	split
	ip
)

target_link_libraries(test_split
	${Boost_LIBRARIES}
	split
)

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT __shurik@list.ru)

include(CPack)

enable_testing()

add_test(test_split test_split --log_level=message)
