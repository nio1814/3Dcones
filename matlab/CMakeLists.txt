find_package(Matlab REQUIRED COMPONENTS MEX_COMPILER)
if(Matlab_FOUND AND NOT WIN32)
	#set(MATLAB_MEX "${MATLAB_ROOT}/bin/mex")

	set(CMAKE_C_COMPILER ${Matlab_MEX_COMPILER})
	set(CMAKE_CXX_COMPILER ${Matlab_MEX_COMPILER})
	set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/mex)
	set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)
	set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS)
#		set(CMAKE_C_FLAGS "-Wall -Werror")
	#set(CMAKE_CXX_FLAGS "-Wall -Werror")
	#set(CMAKE_C_FLAGS "-cxx")
	#set(CMAKE_C_FLAGS "-fPIC")
	set(CMAKE_C_FLAGS)

	set(CMAKE_C_COMPILE_OBJECT "<CMAKE_C_COMPILER> <FLAGS> <DEFINES> -c <SOURCE> -outdir <OBJECT_DIR>")
	set(CMAKE_CXX_COMPILE_OBJECT "<CMAKE_CXX_COMPILER> -c <FLAGS> <INCLUDES> <DEFINES> <SOURCE> -outdir <OBJECT_DIR>")
	set(CMAKE_C_LINK_EXECUTABLE "<CMAKE_C_COMPILER> <FLAGS> <LINK_FLAGS> <LINK_LIBRARIES> <OBJECTS> -outdir ${CMAKE_BINARY_DIR} -output <TARGET>")
	set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_CXX_COMPILER> <FLAGS> <LINK_FLAGS> <LINK_LIBRARIES> <OBJECTS> -outdir ${CMAKE_BINARY_DIR} -output <TARGET>")

	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

	set(CONES_SOURCE generateCones.cpp)

#	add_executable(generateCones ${CONES_SOURCE})
#	target_link_libraries(generateCones trajectory)

#	add_executable(generateSpiral generateSpiral.cpp)
#	target_link_libraries(generateSpiral trajectory)

	add_subdirectory(mex)
endif()
