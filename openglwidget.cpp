#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}
void OpenGLWidget::initializeGL()
{

    initializeOpenGLFunctions();
    qDebug ("OpenGL version : %s", glGetString(GL_VERSION));
    qDebug ("GLSL %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
    glEnable (GL_DEPTH_TEST);
    openFileOff();

    time =  new QTime();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(rotateNtranslate()));
    timer->start(250);
    time->start();

}

void OpenGLWidget::resizeGL( int w , int h )
{
    glViewport(0 ,0 ,w , h);
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(!pig1 || !pig2 || !pig3)
        return;
    pig1->drawModel();
    pig2->drawModel();
    pig3->drawModel();


}

void OpenGLWidget::openFileOff()
{
    QDir tempDir;
    QString fileName;

    tempDir.cd("..");
    tempDir.cd("screensaver");

    fileName =  tempDir.absoluteFilePath("pig.off");

    if (!fileName.isEmpty())
    {

            pig1 = std::make_shared<Model>(this);
            pig1->yTransform = 60;
            pig1->readOFFFile(fileName);
            pig1->invDiag = pig1->invDiag  / 2;

            pig2 = std::make_shared<Model>(this);
            pig2->yTransform = 90;
            pig2->readOFFFile(fileName);
            pig2->invDiag = pig2->invDiag  / 2;


            pig3 = std::make_shared<Model>(this);
            pig3->yTransform = 90;
            pig3->readOFFFile(fileName);
            pig3->invDiag = pig3->invDiag  / 2;

            pigs.push_back(pig1);
            pigs.push_back(pig2);
            pigs.push_back(pig3);



    }
    update();


}

void OpenGLWidget::rotateNtranslate(){


    for (unsigned int i = 0; i < 3; ++i){
        int x = QRandomGenerator::global()->bounded(-10, 10);
        int y = QRandomGenerator::global()->bounded(-10, 10);
        int z = QRandomGenerator::global()->bounded(-10, 10);

        pigs[i].get()->zTransform = time->msec();
        pigs[i].get()->midPoint = QVector3D(x, y, z);
    }


    update();

    time->restart();
}

