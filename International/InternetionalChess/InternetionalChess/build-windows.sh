#!/bin/bash
# build-windows.sh
# 在 macOS 上构建 Windows 可执行文件

echo "正在为 Windows 构建可执行文件..."

# 创建构建目录
mkdir -p build-windows
cd build-windows

# 使用 MinGW 工具链进行交叉编译
echo "配置 CMake 进行交叉编译..."
cmake .. \
    -DCMAKE_TOOLCHAIN_FILE=../mingw-w64-toolchain.cmake \
    -DCMAKE_BUILD_TYPE=Release

# 开始构建
echo "开始构建..."
make -j$(sysctl -n hw.logicalcpu)

# 检查是否成功
if [ -f "./bin/chess.exe" ]; then
    echo ""
    echo "✅ 构建成功！"
    echo "🎮 Windows 可执行文件：./build-windows/bin/chess.exe"
    echo ""
    echo "📦 文件信息："
    file ./bin/chess.exe
    echo ""
    echo "💡 提示：将此 .exe 文件复制到 Windows 系统即可运行！"
else
    echo "❌ 构建失败！"
    exit 1
fi

# 回到项目根目录
cd ..
