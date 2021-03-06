macro(SetBuildSettings)
	set(CMAKE_CXX_STANDARD 11)
	set(CMAKE_BUILD_TYPE Release)
	set(CMAKE_CXX_FLAGS "-Wall -fno-rtti")
endmacro()

macro(GetFiles GLOB_TYPE VARIABLE RELATIVE_ROOT_PATH)
	file(${GLOB_TYPE} files ${RELATIVE_ROOT_PATH})
	list(APPEND ${VARIABLE} ${files})
endmacro()