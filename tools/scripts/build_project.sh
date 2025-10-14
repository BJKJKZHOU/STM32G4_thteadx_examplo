#!/bin/bash

PROJECT_ROOT="${PROJECT_ROOT:-/workspace}"
BUILD_DIR="${PROJECT_ROOT}/build"

echo "构建STM32G4电机控制固件..."

# 设置正确的编译器路径 - 根据实际容器环境调整
export ARM_GCC_ROOT="${ARM_GCC_ROOT:-/opt/STM32CubeCLT/GNU-tools-for-STM32}"

# 检查编译器是否存在
if [ ! -d "${ARM_GCC_ROOT}" ]; then
    echo "警告: ARM GCC工具链路径不存在: ${ARM_GCC_ROOT}"
    echo "尝试使用系统默认路径..."
    export ARM_GCC_ROOT="/usr/bin"
fi

cd ${PROJECT_ROOT}

# 清理并创建构建目录
rm -rf ${BUILD_DIR}
mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}

# 配置CMake - 使用正确的工具链文件路径
cmake -G "Ninja" \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_TOOLCHAIN_FILE=${PROJECT_ROOT}/cmake/gcc-arm-none-eabi.cmake \
    -DTHREADX_ROOT=/opt/threadx \
    -DSTM32CUBEG4_DIR=/opt/STM32CubeG4 \
    -DCMAKE_TRY_COMPILE_TARGET_TYPE=STATIC_LIBRARY \
    ${PROJECT_ROOT}

# 构建项目
ninja

if [ $? -eq 0 ]; then
    echo "构建成功!"
    echo "输出文件:"
    ls -la ${BUILD_DIR}/*.elf ${BUILD_DIR}/*.bin ${BUILD_DIR}/*.hex 2>/dev/null || echo "未找到输出文件"
else
    echo "构建失败!"
    exit 1
fi