@echo off
if not exist "build" mkdir build
cd build
cmake .. -G "MinGW Makefiles"  # 或者使用 "Visual Studio 16 2019" 等
cmake --build . --config Release
cd ..
echo 构建完成！可执行文件在 .\build\bin\chess.exe