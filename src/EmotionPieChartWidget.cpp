#include "EmotionPieChartWidget.h"

#include <QPainter>
#include <QtMath>

EmotionPieChartWidget::EmotionPieChartWidget(QWidget *parent)
    : QWidget(parent)
{
    m_legendFont = font();
    initDefaultData();
    updateHintFromMap();
    setMinimumSize(320, 220);
}

void EmotionPieChartWidget::initDefaultData()
{
    // 默认数据与颜色，符合用户截图配色
    m_values = {
        {"平静", 35},
        {"开心", 30},
        {"悲伤", 5},
        {"惊讶", 5},
        {"恐惧", 5},
        {"愤怒", 10},
        {"轻蔑", 5},
        {"厌恶", 5}
    };

    m_colors = {
        {"平静", QColor(148, 177, 222)},   // 淡蓝
        {"开心", QColor(252, 208, 89)},    // 亮黄
        {"悲伤", QColor(79, 129, 189)},    // 灰蓝
        {"惊讶", QColor(237, 125, 49)},    // 橙色
        {"恐惧", QColor(112, 48, 160)},    // 紫色
        {"愤怒", QColor(192, 0, 0)},       // 红色
        {"轻蔑", QColor(118, 146, 60)},    // 橄榄绿
        {"厌恶", QColor(89, 150, 95)}      // 褐绿
    };
}

void EmotionPieChartWidget::setEmotionValue(const QString &emotion, double value)
{
    if (value < 0)
        return;
    m_values[emotion] = value;
    updateHintFromMap();
    update();
    emit dataChanged();
}

void EmotionPieChartWidget::setEmotionValues(const QMap<QString, double> &values)
{
    if (values.isEmpty())
        return;
    m_values = values;
    updateHintFromMap();
    update();
    emit dataChanged();
}

QMap<QString, double> EmotionPieChartWidget::emotionValues() const
{
    return m_values;
}

void EmotionPieChartWidget::setCalmColor(const QColor &color)
{
    m_colors["平静"] = color;
    update();
    emit paletteChanged();
}

void EmotionPieChartWidget::setHappyColor(const QColor &color)
{
    m_colors["开心"] = color;
    update();
    emit paletteChanged();
}

void EmotionPieChartWidget::setSadColor(const QColor &color)
{
    m_colors["悲伤"] = color;
    update();
    emit paletteChanged();
}

void EmotionPieChartWidget::setSurprisedColor(const QColor &color)
{
    m_colors["惊讶"] = color;
    update();
    emit paletteChanged();
}

void EmotionPieChartWidget::setFearColor(const QColor &color)
{
    m_colors["恐惧"] = color;
    update();
    emit paletteChanged();
}

void EmotionPieChartWidget::setAngryColor(const QColor &color)
{
    m_colors["愤怒"] = color;
    update();
    emit paletteChanged();
}

void EmotionPieChartWidget::setContemptColor(const QColor &color)
{
    m_colors["轻蔑"] = color;
    update();
    emit paletteChanged();
}

void EmotionPieChartWidget::setDisgustColor(const QColor &color)
{
    m_colors["厌恶"] = color;
    update();
    emit paletteChanged();
}

void EmotionPieChartWidget::setShowLegend(bool on)
{
    if (m_showLegend == on)
        return;
    m_showLegend = on;
    update();
    emit legendSettingChanged();
}

void EmotionPieChartWidget::setLegendWidth(int width)
{
    m_legendWidth = qMax(80, width);
    update();
    emit legendSettingChanged();
}

void EmotionPieChartWidget::setLegendFont(const QFont &font)
{
    m_legendFont = font;
    update();
    emit legendSettingChanged();
}

void EmotionPieChartWidget::setStartAngle(int angle)
{
    m_startAngle = angle;
    update();
    emit appearanceChanged();
}

void EmotionPieChartWidget::setHoleSize(int size)
{
    m_holeSize = qMax(0, size);
    update();
    emit appearanceChanged();
}

QString EmotionPieChartWidget::valueHint() const
{
    return m_valueHint;
}

void EmotionPieChartWidget::setValueHint(const QString &hint)
{
    // 支持在属性面板一次性编辑："平静:35;开心:30" 这样的字符串
    if (hint == m_valueHint)
        return;
    m_valueHint = hint;
    QMap<QString, double> parsed;
    const auto parts = hint.split(';', Qt::SkipEmptyParts);
    for (const QString &part : parts) {
        const auto pair = part.split(':');
        if (pair.size() == 2) {
            bool ok = false;
            double value = pair[1].toDouble(&ok);
            if (ok) {
                parsed.insert(pair[0].trimmed(), value);
            }
        }
    }
    if (!parsed.isEmpty()) {
        m_values = parsed;
        update();
        emit dataChanged();
    }
}

QSize EmotionPieChartWidget::minimumSizeHint() const
{
    return {240, 180};
}

QSize EmotionPieChartWidget::sizeHint() const
{
    return {520, 320};
}

void EmotionPieChartWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const QColor background(20, 44, 73);
    painter.fillRect(rect(), background);

    QRectF pieRect = rect();
    if (m_showLegend) {
        pieRect.setWidth(pieRect.width() - m_legendWidth - 12);
        pieRect.adjust(12, 12, -12, -12);
    } else {
        pieRect.adjust(12, 12, -12, -12);
    }

    drawPie(painter, pieRect);

    if (m_showLegend) {
        QRectF legendRect(pieRect.right() + 12, pieRect.top(), m_legendWidth - 12, pieRect.height());
        drawLegend(painter, legendRect);
    }
}

void EmotionPieChartWidget::drawPie(QPainter &painter, const QRectF &rect)
{
    if (m_values.isEmpty())
        return;

    double total = 0.0;
    for (double v : m_values)
        total += v;
    if (qFuzzyIsNull(total))
        return;

    int start = m_startAngle;

    QRectF outerRect = rect;
    QRectF innerRect = rect.adjusted(m_holeSize, m_holeSize, -m_holeSize, -m_holeSize);
    const QColor holeColor(20, 44, 73);

    for (auto it = m_values.constBegin(); it != m_values.constEnd(); ++it) {
        const QString &emotion = it.key();
        double value = it.value();
        int span = static_cast<int>((value / total) * 360 * 16);

        QColor color = m_colors.value(emotion, Qt::gray);
        painter.setPen(Qt::NoPen);
        painter.setBrush(color);
        painter.drawPie(outerRect, start, span);

        // 绘制内圆形成圆环效果
        if (m_holeSize > 0) {
            painter.setBrush(QBrush(holeColor));
            painter.setPen(Qt::NoPen);
            painter.drawEllipse(innerRect);
        }

        start += span;
    }
}

void EmotionPieChartWidget::drawLegend(QPainter &painter, const QRectF &rect)
{
    painter.save();
    painter.setFont(m_legendFont);
    painter.setPen(Qt::white);

    const int itemHeight = 24;
    const int boxSize = 14;
    int y = static_cast<int>(rect.top());

    for (auto it = m_values.constBegin(); it != m_values.constEnd(); ++it) {
        if (y + itemHeight > rect.bottom())
            break;
        const QString &emotion = it.key();
        const QColor color = m_colors.value(emotion, Qt::gray);

        QRect colorBox(rect.left(), y + (itemHeight - boxSize) / 2, boxSize, boxSize);
        painter.fillRect(colorBox, color);
        painter.drawRect(colorBox);

        QString text = QString("%1 %2%").arg(emotion).arg(QString::number(it.value(), 'f', 0));
        painter.drawText(QRectF(rect.left() + boxSize + 8, y, rect.width() - boxSize - 8, itemHeight),
                         Qt::AlignVCenter | Qt::AlignLeft, text);
        y += itemHeight;
    }

    painter.restore();
}

void EmotionPieChartWidget::updateHintFromMap()
{
    QStringList items;
    for (auto it = m_values.constBegin(); it != m_values.constEnd(); ++it) {
        items << QString("%1:%2").arg(it.key()).arg(QString::number(it.value()));
    }
    m_valueHint = items.join(';');
}

