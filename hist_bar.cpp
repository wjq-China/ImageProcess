#include "hist_bar.h"
#include "ui_histbar.h"
#include "qcustomplot.h"

HistBar::HistBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistBar)
{
    ui->setupUi(this);
}

void HistBar::PlotBar(QVector<double>hist)
{
    qDebug()<<"22";
    QCPAxis *keyAxis = ui->customPlot->xAxis;
    QCPAxis *valueAxis = ui->customPlot->yAxis;
    QCPBars *fossil = new QCPBars(keyAxis, valueAxis);  // 使用xAxis作为柱状图的key轴，yAxis作为value轴

    fossil->setAntialiased(false); // 为了更好的边框效果，关闭抗齿锯
    fossil->setName("Fossil fuels"); // 设置柱状图的名字，可在图例中显示
    fossil->setPen(QPen(QColor(0, 168, 140).lighter(130))); // 设置柱状图的边框颜色
    fossil->setBrush(QColor(0, 168, 140));  // 设置柱状图的画刷颜色
    // 为柱状图设置一个文字类型的key轴，ticks决定了轴的范围，而labels决定了轴的刻度文字的显示
    QVector<double> ticks;
    //QVector<QString> labels;
    //QVector<double>::iterator iter;
    for(int i=0;i<256;i++)
    {
        ticks.push_back(i);
    }
    //ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7;
    //labels << "USA" << "Japan" << "Germany" << "France" << "UK" << "Italy" << "Canada";
    //QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    //textTicker->addTicks(ticks, labels);

    //keyAxis->setTicker(textTicker);        // 设置为文字轴

    keyAxis->setTickLabelRotation(60);     // 轴刻度文字旋转60度
    keyAxis->setSubTicks(false);           // 不显示子刻度
    keyAxis->setTickLength(0, 4);          // 轴内外刻度的长度分别是0,4,也就是轴内的刻度线不显示
    keyAxis->setRange(0, 256);               // 设置范围
    keyAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);

    valueAxis->setRange(0, 5000);
    valueAxis->setPadding(35);             // 轴的内边距，可以到QCustomPlot之开始（一）看图解
    //valueAxis->setLabel("Power Consumption in\nKilowatts per Capita (2007)");
    valueAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    QVector<double> fossilData = hist;
//    for(int i =0;i<256;i++)
//    {
//        fossilData.push_back(500);
//    }
    //fossilData  << 500 << 500<< 500<< 500 << 0.89*5.2 << 0.90*4.2 << 0.67*11.2;
    fossil->setData(ticks, fossilData);
}
HistBar::~HistBar()
{
    delete ui;
}
