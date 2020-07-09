#include "bar.h"

#include <QtWidgets>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>

QT_CHARTS_USE_NAMESPACE

bar::bar(QWidget *parent) : QWidget(parent)
{
    QBarSet *set0 = new QBarSet("Cu2008");
    QBarSet *set1 = new QBarSet("Cu2009");
    *set0 << 0.82;
    *set1 << 0.74;

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);

    QChart *chart = new QChart();
    chart->addSeries(series);

    chart->setTitle("持续报价时间占比");

    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;

    categories << "报价占比";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);


    chart->setMargins(*(new QMargins(2,2,2,2)));

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(chartView);
    setLayout(mainLayout);
}

bar1::bar1(QWidget *parent) : QWidget(parent)
{
    QBarSet *set0 = new QBarSet("Cu2008");
    QBarSet *set1 = new QBarSet("Cu2009");
    *set0 << 0.63;
    *set1 << 0.75;

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);

    QChart *chart = new QChart();
    chart->addSeries(series);

    chart->setTitle("价差报价时间占比");

    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;

    categories << "价差占比";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setMargins(*(new QMargins(2,2,2,2)));

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(chartView);
    setLayout(mainLayout);
}
