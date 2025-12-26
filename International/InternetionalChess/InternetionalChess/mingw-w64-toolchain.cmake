# mingw-w64-toolchain.cmake
# Windows 交叉编译工具链配置

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

# 指定交叉编译器路径
set(CMAKE_C_COMPILER /usr/local/bin/x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER /usr/local/bin/x86_64-w64-mingw32-g++)
set(CMAKE_RC_COMPILER /usr/local/bin/x86_64-w64-mingw32-windres)

# 设置静态链接（避免 DLL 依赖）
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")

# 搜索设置
set(CMAKE_FIND_ROOT_PATH /usr/local/x86_64-w64-mingw32)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Windows 特定定义
add_definitions(-DWIN32 -D_WIN32 -D_WINDOWS)