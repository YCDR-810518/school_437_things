#!/bin/bash
# test-windows.sh
# 检查 Windows 可执行文件

EXE_FILE="build-windows/bin/chess.exe"

if [ ! -f "$EXE_FILE" ]; then
    echo "❌ 未找到 Windows 可执行文件，请先运行 ./build-windows.sh"
    exit 1
fi

echo "✅ 找到 Windows 可执行文件: $EXE_FILE"
echo ""

echo "📊 文件信息:"
file "$EXE_FILE"
echo ""

echo "📏 文件大小:"
ls -lh "$EXE_FILE" | awk '{print $5}'
echo ""

echo "🔍 依赖检查:"
echo "（如果显示 'statically linked' 则为独立可执行文件）"
x86_64-w64-mingw32-objdump -p "$EXE_FILE" | grep -i "dll" || echo "未发现 DLL 依赖（良好）"
echo ""

echo "💡 使用说明:"
echo "  1. 将此文件复制到 Windows 电脑"
echo "  2. 在 Windows 上双击 chess.exe 运行"
echo "  3. 或通过命令行运行: chess.exe"
