#!/bin/bash
# build-all.sh
# 构建所有平台的可执行文件

echo "=== 国际象棋游戏构建脚本 ==="
echo ""

# 1. 为当前平台（macOS）构建
echo "1. 构建 macOS 版本..."
mkdir -p build-macos
cd build-macos
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(sysctl -n hw.logicalcpu)
if [ -f "./bin/chess" ]; then
    echo "✅ macOS 版本构建成功"
    cp ./bin/chess ../chess-macos
fi
cd ..

echo ""

# 2. 为 Windows 构建
echo "2. 构建 Windows 版本..."
if ! command -v x86_64-w64-mingw32-g++ &> /dev/null; then
    echo "❌ 未找到 MinGW-w64，请先安装：brew install mingw-w64"
else
    ./build-windows.sh
    if [ -f "./build-windows/bin/chess.exe" ]; then
        cp ./build-windows/bin/chess.exe ./chess-windows.exe
    fi
fi

echo ""

# 3. 显示构建结果
echo "=== 构建完成 ==="
echo ""
echo "生成的可执行文件："
if [ -f "./chess-macos" ]; then
    echo "  • chess-macos    - macOS 可执行文件"
fi
if [ -f "./chess-windows.exe" ]; then
    echo "  • chess-windows.exe - Windows 可执行文件"
fi

echo ""
echo "📦 打包建议："
echo "  1. 将 chess-windows.exe 发送到 Windows 电脑运行"
echo "  2. 可以在 Windows 上直接双击运行"
echo "  3. 如果需要，可以创建 ZIP 包："
echo "     zip chess-windows.zip chess-windows.exe README.md"
