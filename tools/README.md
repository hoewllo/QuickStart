# 工具目录 (tools/)

此目录包含与主程序相关的辅助工具和测试程序。

## 当前工具

### test_icon_generator.cpp

图标生成器测试程序，用于验证IconGenerator类的功能。

**编译和运行：**
```bash
# 需要Qt开发环境
cd tools
# 编译（示例命令，根据您的Qt版本调整）
g++ -std=c++17 -I../include -I/path/to/qt/include -L/path/to/qt/lib -lQt6Widgets test_icon_generator.cpp -o test_icon_generator
# 运行
./test_icon_generator
```

**功能：**
- 测试默认图标生成（基于名称的第一个字母）
- 测试自定义颜色图标生成
- 显示所有预定义颜色的示例

## 添加新工具

1. 将新工具源代码放在此目录下
2. 更新此README文件说明工具的用途和用法
3. 确保工具不依赖于主程序的内部实现细节（保持松耦合）

## 注意事项

- 这些工具不会被包含在主程序的构建系统中
- 工具仅供开发和测试使用
- 请勿将敏感信息或密钥放在工具代码中