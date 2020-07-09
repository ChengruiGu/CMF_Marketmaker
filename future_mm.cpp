#include "future_mm.h"
#include <QtWidgets>

future_mm::future_mm(QWidget *parent) : QWidget(parent)
{
    QLabel *serverLabel = new QLabel("Server:");
     QHBoxLayout *serverLayout = new QHBoxLayout;
     serverLayout->addWidget(serverLabel);
     setLayout(serverLayout);
}
