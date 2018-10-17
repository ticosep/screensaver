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
    timer->start(300);
    time->start();

}

void OpenGLWidget::resizeGL( int w , int h )
{
    glViewport(0 ,0 ,w , h);
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(!pigs[0])
        return;
    for(unsigned int i =0; i < 3; ++i) {
        pigs[i].get()->drawModel();
    }



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
        for(unsigned int i =0; i < 3; ++i) {
            std::shared_ptr<Model> pig (new Model(this));
            pig->yTransform = 60;
            pig->readOFFFile(fileName);
            pig->invDiag = pig->invDiag  / 2;
            pigs.push_back(pig);
        }

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

