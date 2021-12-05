#pragma once

#include <QMainWindow>
#include <QImage>

#include <memory>

#include "QCanvas.hpp"
#include "Manager.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow
    : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(
        QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionLoad_image_triggered();
    void on_actionSave_image_triggered();
    void on_actionExit_triggered();
    void resetSliders();
    void updateLabels(
        const int value);
private:
    Ui::MainWindow* ui;
    std::unique_ptr<Manager> m_Manager;
};
