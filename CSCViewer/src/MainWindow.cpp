#include "MainWindow.hpp"
#include "./ui_MainWindow.h"

#include "QCanvas.hpp"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_Manager(new Manager())
{
    ui->setupUi(this);

    connect(
        ui->cbType,
        static_cast<void(QComboBox::*)(int)>(&QComboBox::activated),
        m_Manager.get(),
        &Manager::onChangeColorSpaceType);
    connect(
        ui->hsChannel1,
        &QSlider::valueChanged,
        m_Manager.get(),
        &Manager::onChangeChannel1Value);
    connect(
        ui->hsChannel2,
        &QSlider::valueChanged,
        m_Manager.get(),
        &Manager::onChangeChannel2Value);
    connect(
        ui->hsChannel3,
        &QSlider::valueChanged,
        m_Manager.get(),
        &Manager::onChangeChannel3Value);

    connect(
        m_Manager.get(),
        &Manager::inputImageChanged,
        ui->saInput,
        &QScrollableCanvas::onChangeImage);
    connect(
        m_Manager.get(),
        &Manager::channel1ImageChanged,
        ui->saCh1,
        &QScrollableCanvas::onChangeImage);
    connect(
        m_Manager.get(),
        &Manager::channel2ImageChanged,
        ui->saCh2,
        &QScrollableCanvas::onChangeImage);
    connect(
        m_Manager.get(),
        &Manager::channel3ImageChanged,
        ui->saCh3,
        &QScrollableCanvas::onChangeImage);
    connect(
        m_Manager.get(),
        &Manager::outputImageChanged,
        ui->saOutput,
        &QScrollableCanvas::onChangeImage);

    connect(
        ui->pbReset,
        &QPushButton::clicked,
        m_Manager.get(),
        &Manager::onReset);

    connect(
        ui->saOutput,
        &QScrollableCanvas::imageChanged,
        this,
        &MainWindow::resetSliders);

    connect(
        ui->cbType,
        static_cast<void(QComboBox::*)(int)>(&QComboBox::activated),
        this,
        &MainWindow::updateLabels);

    ui->lbChannel1min->setText(
        QString::number(ui->hsChannel1->minimum()));
    ui->lbChannel1max->setText(
        QString::number(ui->hsChannel1->maximum()));
    ui->lbChannel2min->setText(
        QString::number(ui->hsChannel2->minimum()));
    ui->lbChannel2max->setText(
        QString::number(ui->hsChannel2->maximum()));
    ui->lbChannel3min->setText(
        QString::number(ui->hsChannel3->minimum()));
    ui->lbChannel3max->setText(
        QString::number(ui->hsChannel3->maximum()));

    ui->cbType->addItems(
        { "YUV BT.601" , "YUV BT.709", "HSV" });
    updateLabels(ui->cbType->currentIndex());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLoad_image_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Load image"), "",
        tr("All Files (*)"));
    if (fileName.isEmpty()) {
        return;
    }
    bool result = m_Manager->loadImage(fileName);
}

void MainWindow::on_actionSave_image_triggered()
{

}

void MainWindow::on_actionExit_triggered()
{

}

void MainWindow::resetSliders()
{
    ui->hsChannel1->setValue(0);
    ui->hsChannel2->setValue(0);
    ui->hsChannel3->setValue(0);
}

void MainWindow::updateLabels(
    int value)
{
    if (0 == value || 1 == value) {
        ui->lbChannel1->setText("Y");
        ui->lbChannel2->setText("U");
        ui->lbChannel3->setText("V");
    } else if (2 == value) {
        ui->lbChannel1->setText("H");
        ui->lbChannel2->setText("S");
        ui->lbChannel3->setText("V");
    }
}
