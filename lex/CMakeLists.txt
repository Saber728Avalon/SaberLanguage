project ( SaberLanguage 
		LANGUAGES C CXX )
cmake_minimum_required ( VERSION 2.8 )

include_directories(../src)


#生成调试用exe
OPTION(BUILD_TEST_EXECUTABLES "build exe" ON)

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
    add_definitions(-D_CRT_NONSTDC_NO_DEPRECATE)
endif()

IF(CMAKE_COMPILER_IS_GNUCXX)
	add_compile_options(-std=c++11)
	add_compile_options(-fPIC)
	add_compile_options(-fPIE)
	message(STATUS "option:-std=c++11")
ENDIF()

#设置lib的查找路径
IF(CMAKE_BUILD_TYPE MATCHES "Release")
	LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/bin/Release)
ELSE()
	LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/bin/Debug)
ENDIF() 

set(LEX_HDRS
	lex.h
	lex_header.h
)

# 添加文件
set(LEX_SRC 
	lex.cpp
	lex_main.cpp
)


#调试用exe
if(BUILD_TEST_EXECUTABLES)
	add_executable(test_lex ${LEX_SRC})
endif()