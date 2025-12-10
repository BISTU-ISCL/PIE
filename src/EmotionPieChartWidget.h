#pragma once

#include <QColor>
#include <QFont>
#include <QMap>
#include <QPointF>
#include <QVariant>
#include <QWidget>

// 情绪占比饼状图控件，支持颜色和数据配置，可用于 Qt Designer 拖拽使用
class EmotionPieChartWidget : public QWidget
{
    Q_OBJECT

    // 每个情绪对应的颜色属性，方便在 Designer 内直接调整
    Q_PROPERTY(QColor calmColor READ calmColor WRITE setCalmColor NOTIFY paletteChanged)
    Q_PROPERTY(QColor happyColor READ happyColor WRITE setHappyColor NOTIFY paletteChanged)
    Q_PROPERTY(QColor sadColor READ sadColor WRITE setSadColor NOTIFY paletteChanged)
    Q_PROPERTY(QColor surprisedColor READ surprisedColor WRITE setSurprisedColor NOTIFY paletteChanged)
    Q_PROPERTY(QColor fearColor READ fearColor WRITE setFearColor NOTIFY paletteChanged)
    Q_PROPERTY(QColor angryColor READ angryColor WRITE setAngryColor NOTIFY paletteChanged)
    Q_PROPERTY(QColor contemptColor READ contemptColor WRITE setContemptColor NOTIFY paletteChanged)
    Q_PROPERTY(QColor disgustColor READ disgustColor WRITE setDisgustColor NOTIFY paletteChanged)

    Q_PROPERTY(bool showLegend READ showLegend WRITE setShowLegend NOTIFY legendSettingChanged)
    Q_PROPERTY(int legendWidth READ legendWidth WRITE setLegendWidth NOTIFY legendSettingChanged)
    Q_PROPERTY(QFont legendFont READ legendFont WRITE setLegendFont NOTIFY legendSettingChanged)
    Q_PROPERTY(int startAngle READ startAngle WRITE setStartAngle NOTIFY appearanceChanged)
    Q_PROPERTY(int holeSize READ holeSize WRITE setHoleSize NOTIFY appearanceChanged)

    // 允许在属性面板快速设置占比数据，格式："平静:35;开心:30;..."
    Q_PROPERTY(QString valueHint READ valueHint WRITE setValueHint DESIGNABLE true)

public:
    explicit EmotionPieChartWidget(QWidget *parent = nullptr);

    // 数据操作
    void setEmotionValue(const QString &emotion, double value);
    void setEmotionValues(const QMap<QString, double> &values);
    QMap<QString, double> emotionValues() const;

    // 颜色操作
    QColor calmColor() const { return m_colors.value("平静"); }
    QColor happyColor() const { return m_colors.value("开心"); }
    QColor sadColor() const { return m_colors.value("悲伤"); }
    QColor surprisedColor() const { return m_colors.value("惊讶"); }
    QColor fearColor() const { return m_colors.value("恐惧"); }
    QColor angryColor() const { return m_colors.value("愤怒"); }
    QColor contemptColor() const { return m_colors.value("轻蔑"); }
    QColor disgustColor() const { return m_colors.value("厌恶"); }

    void setCalmColor(const QColor &color);    
    void setHappyColor(const QColor &color);
    void setSadColor(const QColor &color);
    void setSurprisedColor(const QColor &color);
    void setFearColor(const QColor &color);
    void setAngryColor(const QColor &color);
    void setContemptColor(const QColor &color);
    void setDisgustColor(const QColor &color);

    // 外观与图例
    bool showLegend() const { return m_showLegend; }
    void setShowLegend(bool on);

    int legendWidth() const { return m_legendWidth; }
    void setLegendWidth(int width);

    QFont legendFont() const { return m_legendFont; }
    void setLegendFont(const QFont &font);

    int startAngle() const { return m_startAngle; }
    void setStartAngle(int angle);

    int holeSize() const { return m_holeSize; }
    void setHoleSize(int size);

    QString valueHint() const;
    void setValueHint(const QString &hint);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

signals:
    void dataChanged();
    void paletteChanged();
    void legendSettingChanged();
    void appearanceChanged();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void initDefaultData();
    void drawPie(QPainter &painter, const QRectF &rect);
    void drawLegend(QPainter &painter, const QRectF &rect);
    void updateHintFromMap();

    QMap<QString, double> m_values;
    QMap<QString, QColor> m_colors;

    bool m_showLegend = true;
    int m_legendWidth = 160;
    QFont m_legendFont;
    int m_startAngle = 90 * 16;   // Qt 坐标角度使用 1/16 度
    int m_holeSize = 0;           // 0 表示普通饼图，大于 0 表示圆环孔径像素
    QString m_valueHint;
};

