#!/bin/bash

echo "设置STM32G4开发环境..."

# 使用环境变量
PROJECT_ROOT="${PROJECT_ROOT:-/workspace}"
HOME_DIR="${HOME:-/home/developer}"

# 创建必要的目录
mkdir -p ${PROJECT_ROOT}/{build,config,logs,bin}

# 配置GDB初始化
cat > ${HOME_DIR}/.gdbinit << EOF
set confirm off
set architecture arm
target extended-remote :3333
EOF

# 配置OpenOCD - 移除sudo，使用容器内路径
mkdir -p /etc/openocd
# 检查文件是否存在再复制
if [ -f "/opt/STM32CubeG4/Drivers/BSP/STM32G4xx_Nucleo/stm32g4xx_nucleo.cfg" ]; then
    cp /opt/STM32CubeG4/Drivers/BSP/STM32G4xx_Nucleo/stm32g4xx_nucleo.cfg /etc/openocd/
    echo "OpenOCD配置文件已配置"
else
    echo "警告: STM32CubeG4配置文件未找到"
fi

# 安装VSCode Cortex-Debug配置
mkdir -p ${HOME_DIR}/.vscode
cat > ${HOME_DIR}/.vscode/launch.json << EOF
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Cortex Debug STM32G4",
            "cwd": "\${workspaceRoot}",
            "executable": "\${workspaceRoot}/build/stm32g4-motor-project-ex.elf",
            "request": "launch",
            "type": "cortex-debug",
            "servertype": "openocd",
            "device": "STM32G474RE",
            "configFiles": [
                "interface/stlink.cfg",
                "target/stm32g4x.cfg"
            ],
            "svdFile": "/opt/STM32CubeG4/Drivers/CMSIS/Device/ST/STM32G4xx/SVD/STM32G474xx.svd",
            "runToEntryPoint": "main",
            "showDevDebugOutput": true
        }
    ]
}
EOF

echo "环境设置完成!"