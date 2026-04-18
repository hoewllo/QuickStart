# Qt Application CI/CD Pipeline

这个CI/CD流水线为Qt应用程序提供跨平台构建和发布功能。

## 功能特性

- **跨平台构建**: 支持Windows (MSVC/MinGW)、Linux和macOS
- **Qt库支持**: 自动安装和配置Qt 6.5+
- **代码质量检查**: 包含clang-tidy、cppcheck和clang-format
- **自动发布**: 自动创建GitHub Release并打包
- **运行时库收集**: 自动收集Qt和系统运行时库

## 支持的平台

### Windows
- **MSVC**: 使用Visual Studio 2019构建
- **MinGW**: 使用MinGW GCC构建

### Linux
- Ubuntu 20.04+
- 支持DEB包和AppImage格式

### macOS
- macOS 11.0 (Big Sur)+
- 支持DMG和ZIP格式

## 触发条件

流水线在以下情况下自动运行：

1. **推送代码**: 推送到main或master分支时
2. **拉取请求**: 创建或更新拉取请求时
3. **手动触发**: 通过GitHub Actions界面手动触发

## 工作流程

### 1. 构建阶段
- Windows MSVC构建
- Windows MinGW构建  
- Linux构建
- macOS构建

### 2. 代码质量检查
- clang-format格式检查
- clang-tidy静态分析
- cppcheck代码检查

### 3. 发布阶段（仅main/master分支）
- 下载所有构建产物
- 创建跨平台发布包
- 生成GitHub Release

## 环境变量

| 变量名 | 默认值 | 说明 |
|--------|--------|------|
| BUILD_TYPE | Release | 构建类型 |
| QT_VERSION | 6.5.0 | Qt版本 |
| PROJECT_NAME | QtAppLauncher | 项目名称 |

## 自定义配置

### 修改Qt版本
在`.github/workflows/ci.yml`中修改`QT_VERSION`环境变量：
```yaml
env:
  QT_VERSION: "6.5.0"  # 修改为需要的Qt版本
```

### 修改项目名称
在`.github/workflows/ci.yml`中修改`PROJECT_NAME`环境变量：
```yaml
env:
  PROJECT_NAME: "YourAppName"  # 修改为你的应用名称
```

### 添加Qt模块
如果需要额外的Qt模块，修改构建步骤中的Qt组件：
```yaml
- name: Setup Qt for MSVC
  uses: jurplel/install-qt-action@v4
  with:
    version: ${{ env.QT_VERSION }}
    host: windows
    target: desktop
    arch: win64_msvc2019_64
    modules: qtbase qtwidgets qtdeclarative  # 添加需要的模块
    install-deps: true
```

## 产物输出

### 构建产物
- Windows: ZIP包、MSI安装包、可执行文件
- Linux: DEB包、AppImage、tar.gz包
- macOS: DMG镜像、ZIP包、应用程序包

### 代码质量报告
- clang-tidy-report.txt
- cppcheck-report.xml
- cppcheck-htmlreport/

## 本地测试

### 安装依赖
```bash
# Ubuntu/Debian
sudo apt-get install cmake qt6-base-dev clang-tidy cppcheck

# macOS
brew install cmake qt@6 clang-format

# Windows
# 安装Visual Studio或MinGW，然后安装Qt
```

### 本地构建
```bash
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=<path-to-qt>
cmake --build . --config Release
```

## 故障排除

### Qt找不到问题
确保CMake可以找到Qt安装路径：
```bash
# 设置Qt路径
export CMAKE_PREFIX_PATH=/path/to/qt
```

### 运行时库缺失
Windows构建需要收集Qt DLL：
- MSVC: 需要Visual C++ Redistributable
- MinGW: 需要MinGW运行时DLL

### 代码质量检查失败
检查代码格式：
```bash
# 格式化代码
find src include -name "*.cpp" -o -name "*.h" -o -name "*.hpp" | xargs clang-format -i
```

## 相关文件

- `CMakeLists.txt`: CMake构建配置
- `CMakePresets.json`: CMake预设配置
- `.github/workflows/ci.yml`: CI/CD流水线配置

## 许可证

本项目使用MIT许可证。详情请查看LICENSE文件。