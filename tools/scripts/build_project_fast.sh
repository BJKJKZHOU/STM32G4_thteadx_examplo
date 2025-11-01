#!/bin/bash

PROJECT_ROOT="${PROJECT_ROOT:-/workspace}"
BUILD_DIR="${PROJECT_ROOT}/build"

# 默认使用增量编译
MODE="incremental"

# 解析命令行参数
while [[ $# -gt 0 ]]; do
    case $1 in
        -c|--clean)
            MODE="clean"
            shift
            ;;
        -f|--fast)
            MODE="fast"
            shift
            ;;
        -i|--incremental)
            MODE="incremental"
            shift
            ;;
        -h|--help)
            echo "用法: $0 [选项]"
            echo "选项:"
            echo "  -c, --clean        完整清理并重新构建"
            echo "  -f, --fast         快速构建（仅编译改动文件）"
            echo "  -i, --incremental  增量构建（默认）"
            echo "  -h, --help         显示帮助信息"
            exit 0
            ;;
        *)
            echo "未知选项: $1"
            echo "使用 -h 查看帮助"
            exit 1
            ;;
    esac
done

echo "构建STM32G4电机控制固件..."
echo "模式: $MODE"

# 设置正确的编译器路径
export ARM_GCC_ROOT="${ARM_GCC_ROOT:-/opt/STM32CubeCLT/GNU-tools-for-STM32}"

# 检查编译器是否存在
if [ ! -d "${ARM_GCC_ROOT}" ]; then
    echo "警告: ARM GCC工具链路径不存在: ${ARM_GCC_ROOT}"
    echo "尝试使用系统默认路径..."
    export ARM_GCC_ROOT="/usr/bin"
fi

cd ${PROJECT_ROOT}

case $MODE in
    "clean")
        echo "执行完整清理构建..."
        rm -rf ${BUILD_DIR}
        mkdir -p ${BUILD_DIR}
        cd ${BUILD_DIR}
        
        # 配置CMake
        cmake -G "Ninja" \
            -DCMAKE_BUILD_TYPE=Debug \
            -DCMAKE_TOOLCHAIN_FILE=${PROJECT_ROOT}/cmake/gcc-arm-none-eabi.cmake \
            -DTHREADX_ROOT=/opt/threadx \
            -DSTM32CUBEG4_DIR=/opt/STM32CubeG4 \
            -DCMAKE_TRY_COMPILE_TARGET_TYPE=STATIC_LIBRARY \
            ${PROJECT_ROOT}
        ;;
    "fast")
        echo "执行快速构建..."
        if [ ! -d "${BUILD_DIR}" ] || [ ! -f "${BUILD_DIR}/build.ninja" ]; then
            echo "构建目录不存在，先执行完整配置..."
            rm -rf ${BUILD_DIR}
            mkdir -p ${BUILD_DIR}
            cd ${BUILD_DIR}
            
            cmake -G "Ninja" \
                -DCMAKE_BUILD_TYPE=Debug \
                -DCMAKE_TOOLCHAIN_FILE=${PROJECT_ROOT}/cmake/gcc-arm-none-eabi.cmake \
                -DTHREADX_ROOT=/opt/threadx \
                -DSTM32CUBEG4_DIR=/opt/STM32CubeG4 \
                -DCMAKE_TRY_COMPILE_TARGET_TYPE=STATIC_LIBRARY \
                ${PROJECT_ROOT}
        else
            cd ${BUILD_DIR}
        fi
        ;;
    "incremental")
        echo "执行增量构建..."
        if [ ! -d "${BUILD_DIR}" ] || [ ! -f "${BUILD_DIR}/build.ninja" ]; then
            echo "首次构建或构建目录不存在，执行完整配置..."
            rm -rf ${BUILD_DIR}
            mkdir -p ${BUILD_DIR}
            cd ${BUILD_DIR}
            
            cmake -G "Ninja" \
                -DCMAKE_BUILD_TYPE=Debug \
                -DCMAKE_TOOLCHAIN_FILE=${PROJECT_ROOT}/cmake/gcc-arm-none-eabi.cmake \
                -DTHREADX_ROOT=/opt/threadx \
                -DSTM32CUBEG4_DIR=/opt/STM32CubeG4 \
                -DCMAKE_TRY_COMPILE_TARGET_TYPE=STATIC_LIBRARY \
                ${PROJECT_ROOT}
        else
            cd ${BUILD_DIR}
        fi
        ;;
esac

# 构建项目
echo "开始编译..."
start_time=$(date +%s)
ninja
build_result=$?
end_time=$(date +%s)
build_time=$((end_time - start_time))

if [ $build_result -eq 0 ]; then
    echo "构建成功! 耗时: ${build_time}秒"
    echo "输出文件:"
    ls -la ${BUILD_DIR}/*.elf ${BUILD_DIR}/*.bin ${BUILD_DIR}/*.hex 2>/dev/null || echo "未找到输出文件"
    
    # 显示构建统计信息
    echo "构建统计:"
    ninja -t targets | grep -E "\.(o|obj)$" | wc -l | xargs echo "编译的目标文件数量:"
else
    echo "构建失败!"
    exit 1
fi