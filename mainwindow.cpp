#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPainter"
#include <QDebug>
#include <QTime>
#include <QVector2D>




MainWindow::MainWindow(QWidget *parent)                 //constructor for MainWindow class
    : QMainWindow(parent), ui(new Ui::MainWindow),
    pixmap(":/tubeclock.png"), spritesheet(":/LCD_Numbers.png"), timestring{"0"},globalScale(1.0)
{
    ui->setupUi(this);

    this->move(800,50);
    setWindowFlags(Qt::FramelessWindowHint);        //create the frameless/transparent window
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(300,300);
    setWindowFlags(windowFlags() & ~Qt::WindowSystemMenuHint);

    mytimer= new QTimer(this);
    connect(mytimer, SIGNAL(timeout()), this, SLOT(myfunction()));  //create and connect slot
    mytimer->start(100);
    timestring="000000";    //initialize timestring to prevent errors

    tubecoord.push_back({1.0,2.0});
    ui->SettingsButton->move(0,0);  //place the settings button in upper left



    //manually load up the coord table

    tubecoord[0]=(QVector2D(23.0,60.0));
    tubecoord.push_back(QVector2D(75.0,60.0));
    tubecoord.push_back(QVector2D(136.0,60.0));
    tubecoord.push_back(QVector2D(190.0,60.0));
    tubecoord.push_back(QVector2D(246.0,60.0));
    tubecoord.push_back(QVector2D(292.0,60.0));



    //load the number images from the sprite sheet
    for(int i=0;i<10;i++)
    {
        QRect source={165*i, 0, 165,245};
        tube_nums.push_back(spritesheet.copy(source));

    }





}
//=======================================================
MainWindow::~MainWindow()
{
    delete ui;
}
//=======================================================


void MainWindow::myfunction()
{
    // Get The Current Time into a string and parse it

    QTime  time=QTime::currentTime();
    timestring=time.toString();
    timestring.remove(':');     //pull the colon out to get 6 digits

    //ui->Time_label->setText(timestring);


    this->update();







    return;

}

//***********************************************************
//              Paint Routine !!!!!!!

void MainWindow::paintEvent(QPaintEvent *event)
{



    QPainter painter(this); //create a paint object
    QPen pen;

    float scaleX=0.5f*globalScale;
    float scaleY=0.5f*globalScale;

    //*****************************************
    //      Draw the base of the tube clock
    //*****************************************

    QPixmap scaledPixmap = pixmap.scaled(pixmap.width() * scaleX,
                                    pixmap.height() * scaleY, Qt::KeepAspectRatio);

    if (!pixmap.isNull()) {
        painter.drawPixmap(0,0,scaledPixmap);

    } else {
        painter.setPen(Qt::red);
        painter.drawText(rect(), Qt::AlignHCenter, "Image not found!");

    }
    QBrush mybrush={Qt::SolidPattern};
    painter.setPen(Qt::NoPen);  //removes the outline
    QColor flare={235,134,5,rand()%255};
    pen.setColor(flare);
    mybrush.setColor(flare);
    painter.setBrush(mybrush);
    //flicker the dots
    painter.drawEllipse(122*globalScale,76*globalScale,5,5);
    painter.drawEllipse(122*globalScale,91*globalScale,5,5);

    painter.drawEllipse(235*globalScale,76*globalScale,5,5);
    painter.drawEllipse(235*globalScale,91*globalScale,5,5);



    //*****************************************
    //    Decode and draw the tubes in
    //*****************************************


    //scaleX=0.25;
    //scaleY=0.25;
    int clockdigit;


    for (int i=0;i<6;i++)
    {
        clockdigit=timestring[i].toLatin1()-48;
        //qDebug()<<timestring;
        //int r=rand()%10;


        //***currently only drawing zeros********
            QPixmap tube=tube_nums[clockdigit].scaled(tube_nums[2].width()*scaleX/2.0,
                        tube_nums[2].height()*scaleY/2.0, Qt::KeepAspectRatio);


            painter.drawPixmap(tubecoord[i].x()*globalScale,tubecoord[i].y()*globalScale,tube);


    }

}
//=======================================================

void MainWindow::on_horizontalScrollBar_valueChanged(int value)
{
    globalScale=0.25*value;    //change the globalscale factor and move the radio button
    ui->SettingsButton->move(ui->SettingsButton->pos().x()*globalScale,
                             ui->SettingsButton->pos().y()*globalScale);
    this->update();

    qDebug()<<"X="<<ui->SettingsButton->pos().x()*globalScale<<
        "  Y="<<ui->SettingsButton->pos().y()*globalScale;


}

//=======================================================
//    Toggling the Settings Button


//git testing again

void MainWindow::on_SettingsButton_pressed()
{

}


void MainWindow::on_SettingsButton_clicked()
{
    //get the value
    if(ui->SettingsButton->isChecked())
    {
        ui->horizontalScrollBar->setVisible(true);
        QRect currentGeometry = geometry(); // Save the current geometry

        setWindowFlags(Qt::Window);
        setGeometry(currentGeometry); // Restore the geometry

        this->show();

    }
    else
    {
        ui->horizontalScrollBar->setVisible(false);
        QRect currentGeometry = geometry(); // Save the current geometry

        setWindowFlags(Qt::FramelessWindowHint);
        setGeometry(currentGeometry); // Restore the geometry

        this->show();
    }
    this->update();
}

