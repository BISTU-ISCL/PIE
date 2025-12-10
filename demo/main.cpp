#include <QApplication>
#include <QVBoxLayout>
#include <QWidget>
#include "EmotionPieChartWidget.h"

// Demo: 展示 EmotionPieChartWidget 的常规使用方式
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle(QObject::tr("情绪占比饼状图 Demo"));

    auto *chart = new EmotionPieChartWidget;

    // 通过 API 设置数据和样式，方便用户理解调用方式
    QMap<QString, double> values{{"平静", 40}, {"开心", 25}, {"悲伤", 5}, {"惊讶", 8}, {"恐惧", 5}, {"愤怒", 7}, {"轻蔑", 5}, {"厌恶", 5}};
    chart->setEmotionValues(values);
    chart->setHoleSize(30);          // 圆环效果
    chart->setStartAngle(90 * 16);   // 从顶部开始

    // 自定义颜色示例：用户可自由替换
    chart->setHappyColor(QColor(255, 215, 0));

    QVBoxLayout *layout = new QVBoxLayout(&window);
    layout->addWidget(chart);
    window.setLayout(layout);
    window.resize(720, 420);

    window.show();
    return app.exec();
}

