# 使用现有的STM32G4电机控制开发镜像
# 镜像名称: zhouhengai/stm32g4-motor-dev:latest
# 此文件保留作为参考，实际使用在devcontainer.json中配置的镜像
FROM zhouhengai/stm32g4-motor-dev:latest

# 原始构建配置已注释，使用现存的本地镜像 zhouhengai/stm32g4-motor-dev
# 以下为原始构建代码，已注释掉：
# FROM zhouhengai/stm32cubeclt-base:latest AS base

# # 构建参数
# ARG THREADX_VERSION=6.4.0
# ARG DEBIAN_FRONTEND=noninteractive

# # 安装STM32CubeG4
# RUN git clone --recursive 1 https://github.com/STMicroelectronics/STM32CubeG4.git /opt/STM32CubeG4

# # 安装 Eclipse ThreadX - 使用实际存在的版本 v6.4.3.202503_rel
# RUN git clone --branch v6.4.3.202503_rel --depth 1 \
#     https://github.com/eclipse-threadx/threadx.git /opt/threadx

# # 验证安装
# RUN if [ ! -d "/opt/threadx" ]; then \
#     echo "ThreadX installation failed, trying alternative method..." && \
#     git clone --branch main --depth 1 \
#         https://github.com/eclipse-threadx/threadx.git /opt/threadx; \
#     fi && \
#     echo "ThreadX installed successfully"

# # 安装STM32CubeProgrammer的依赖库
# RUN apt-get update && apt-get install -y \
#     libusb-1.0-0 \
#     libusb-1.0-0-dev \
#     libglib2.0-0 \
#     libglib2.0-dev \
#     locales \
#     && rm -rf /var/lib/apt/lists/*
# # 安装电机控制相关工具
# RUN pip3 install --no-cache-dir \
#     pyocd \
#     stm32pio \
#     intelhex \
#     pyyaml \
#     numpy \
#     scipy \
#     matplotlib \
#     jupyter
 

# # 创建开发用户（如果基础镜像中不存在）
# RUN if ! id developer >/dev/null 2>&1; then \
#     groupadd -r developer && \
#     useradd -r -g developer -G plugdev,users -m -d /home/developer -s /bin/bash developer && \
#     echo "developer ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers; \
#     fi

# # 设置环境变量
# ENV STM32CUBEG4_DIR=/opt/STM32CubeG4
# ENV THREADX_ROOT=/opt/threadx
# ENV LANG=C.UTF-8
# ENV LC_ALL=C.UTF-8

# # 切换到开发用户
# USER developer
# WORKDIR /workspace

# # 复制初始化脚本
# COPY --chown=developer:developer tools/scripts/ /tmp/scripts/
# RUN chmod +x /tmp/scripts/*.sh

# CMD ["/bin/bash"]