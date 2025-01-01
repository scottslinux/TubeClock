#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QVector2D>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:


    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void myfunction();    //slot for handling the timeout


    virtual void paintEvent(QPaintEvent *event);   //overriding paint function


private:
    Ui::MainWindow *ui;
    QPixmap pixmap;     //pixmap variable
    QPixmap spritesheet;
    QTimer *mytimer;    //timer object
    QString timestring; //timestring is global now

    float globalScale; //for resizing the entire clock and tubes--user adjustable
                        //at runtime

    std::vector<QPixmap> tube_nums; //the vector to hold the glowing numbers
    std::vector<QVector2D> tubecoord; //coordinates for the tubes to be drawn **hand calculated :(
public:



private slots:
    void on_horizontalScrollBar_valueChanged(int value);
    void on_SettingsButton_pressed();
    void on_SettingsButton_clicked();
};
#endif // MAINWINDOW_H
