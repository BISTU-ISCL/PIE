# EmotionPieChart Qt 控件

适用于 Windows + Qt 6.10.0 + MSVC 2022 64bit 的情绪占比饼状图控件，支持 Qt Designer 拖拽使用并提供示例 Demo。

## 主要特性
- 内置 8 种情绪占比：平静、开心、悲伤、惊讶、恐惧、愤怒、轻蔑、厌恶，对应颜色可在属性面板或代码中调整。
- 支持显示/隐藏图例、图例宽度与字体、起始角度、圆环孔径等丰富外观配置。
- `valueHint` 属性允许直接在 Qt Designer 的属性面板批量输入占比数据（格式示例：`平静:35;开心:30;悲伤:5`）。
- 提供 Qt Designer 自定义控件插件，编译后可复制到 `Qt\Tools\QtDesigner\plugins\designer` 目录即可拖拽使用。
- Demo 展示了如何通过代码设置数据、修改颜色以及启用圆环效果。

## 构建步骤（Windows + Qt Creator 18.0.0）
1. 打开 Qt Creator，使用 **Open Project** 选择本目录下的 `CMakeLists.txt`。
2. 确保工具链选择 **MSVC 2022 64bit**，Qt 版本选择 **Qt 6.10.0**。
3. 生成并编译项目，会得到以下目标：
   - `EmotionPieChartWidget`：静态库，可供业务项目直接链接。
   - `EmotionPieChartDesignerPlugin`：自定义控件插件，输出到构建目录的 `designer/` 下。
   - `EmotionPieChartDemo`：可运行示例程序。
4. 将生成的 `EmotionPieChartDesignerPlugin.dll` 复制到 Qt Designer 插件目录（例如 `C:/Qt/6.10.0/msvc2022_64/plugins/designer/`），重新启动 Qt Designer 后即可在 “情绪可视化” 分组看到控件。
5. 运行 `EmotionPieChartDemo` 可快速预览效果。

