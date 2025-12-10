#include "EmotionPieChartPlugin.h"
#include "EmotionPieChartWidget.h"

#include <QtPlugin>

EmotionPieChartPlugin::EmotionPieChartPlugin(QObject *parent)
    : QObject(parent)
{
}

QIcon EmotionPieChartPlugin::icon() const
{
    return QIcon();
}

QString EmotionPieChartPlugin::domXml() const
{
    // 在 Qt Designer 中显示的 XML 定义，包含中文说明与默认几何信息
    return R"(<ui language="c++">
 <widget class="EmotionPieChartWidget" name="emotionPieChart">
  <property name="geometry">
   <rect>
    <x>0</x>
    <y>0</y>
    <width>320</width>
    <height>240</height>
   </rect>
  </property>
  <property name="toolTip" >
   <string>情绪占比饼状图控件</string>
  </property>
  <property name="whatsThis" >
   <string>用于展示情绪分布的饼状图，支持自定义颜色与占比。</string>
  </property>
 </widget>
 <customwidgets>
  <customwidget>
   <class>EmotionPieChartWidget</class>
   <extends>QWidget</extends>
   <header>EmotionPieChartWidget.h</header>
  </customwidget>
 </customwidgets>
</ui>)";
}

QString EmotionPieChartPlugin::group() const
{
    return QStringLiteral("情绪可视化");
}

QString EmotionPieChartPlugin::includeFile() const
{
    return QStringLiteral("EmotionPieChartWidget.h");
}

QString EmotionPieChartPlugin::name() const
{
    return QStringLiteral("EmotionPieChartWidget");
}

QString EmotionPieChartPlugin::toolTip() const
{
    return QStringLiteral("情绪占比饼状图控件");
}

QString EmotionPieChartPlugin::whatsThis() const
{
    return QStringLiteral("可拖拽到 Qt Designer 的情绪饼图，支持颜色、占比、图例等丰富配置。");
}

QWidget *EmotionPieChartPlugin::createWidget(QWidget *parent)
{
    return new EmotionPieChartWidget(parent);
}

void EmotionPieChartPlugin::initialize(QDesignerFormEditorInterface *core)
{
    if (m_initialized)
        return;
    Q_UNUSED(core);
    m_initialized = true;
}

