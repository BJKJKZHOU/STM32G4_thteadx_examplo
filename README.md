# 简介



## 镜像

[Docker Hub]([zhouhengai/stm32g4-motor-dev general | Docker Hub](https://hub.docker.com/repository/docker/zhouhengai/stm32g4-motor-dev/general))  zhouhengai/stm32g4-motor-dev

```cmd
docker pull zhouhengai/stm32g4-motor-dev:latest
```

这个镜像包含 

- **STM32CubeG4** - STM32G4系列HAL库和示例代码
- **STM32cubeclt**-1.19
- **Eclipse ThreadX RTOS** v6.4.3代码
- **Python 3**

## 开发

1. 安装 Docker Desktop（会安装WSL） 和 VS code Dev Containers插件。

2. clone代码到本地，使用STM32CubeMX配置，选择 Cmake，生成。

3. 在 VS code 打开工作区，右下角会弹窗选项，选择从镜像打开。

4. `.devcontainer`配置会自动安装镜像并自动设置插件，镜像有点大（不知道怎么就10G了）。

5. 在工作区根目录使用脚本 `./tools/scripts/build_project.sh`会开始构建(点击 VS code 下方的“生成”一样效果)，调用Ninja ，生成相关文件。

6. 如果报错或有任何异常，将信息和现象详细的报告给 **AI** 。

   

Drivers，Middlewares 等文件夹未纳入版本管理，STM32CubeMX 会自动生成。

如有报错与 STM32G474RETx_FLASH.ld 相关，可能是 STM32CubeMX 版本问题，生成的 STM32G474RETx_FLASH.ld 会少几个“RAM"字段。

解决方案：使用 STM32CubeMX 前先将 STM32G474RETx_FLASH.ld 文件保存到另一个文件夹，生成后复制回来，覆盖。

