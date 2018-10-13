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
    connect(timer, SIGNAL(timeout()), this, SLOT(rotateNColor()));
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

    if(!model)
        return;
    model->drawModel();


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

        model = std::make_shared<Model>(this);
        model->yTransform = 90;
        model->readOFFFile(fileName);

    }
    update();


}

void OpenGLWidget::rotateNColor(){

    qDebug() << time->msec();
    model->zTransform = time->msec();
    update();

    time->restart();
}

