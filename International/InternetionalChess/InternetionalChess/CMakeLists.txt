cmake_minimum_required(VERSION 3.15)
project(InternationalChess 
    VERSION 1.0.0 
    DESCRIPTION "国际象棋游戏程序"
    LANGUAGES CXX
)

# 设置项目信息
set(PROJECT_NAME chess)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 区分 Windows 和 macOS 编译
if(CMAKE_SYSTEM_NAME STREQUAL "Windows" OR MINGW)
    # Windows 编译设置
    add_compile_options(-DWIN32_LEAN_AND_MEAN)
    add_definitions(-D_WIN32_WINNT=0x0601)  # Windows 7+
    
    # 如果是交叉编译，添加静态链接标志
    if(CMAKE_CROSSCOMPILING)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
    endif()
elseif(APPLE)
    # macOS 编译设置
    add_compile_options(-Wall -Wextra)
endif()

# 源文件列表
set(SOURCES
    main.cpp
    logic.cpp
    search.cpp
    display.cpp
)

# 头文件列表
set(HEADERS
    logic.h
    search.h
    display.h
)

# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# 包含目录
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# 如果是交叉编译，设置特定的目标属性
if(CMAKE_CROSSCOMPILING)
    # Windows 可执行文件需要 .exe 扩展名
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".exe")
endif()