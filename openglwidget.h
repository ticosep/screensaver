#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include "model.h"

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>


class OpenGLWidget : public QOpenGLWidget , protected QOpenGLExtraFunctions
{
    Q_OBJECT



    public:
        std::shared_ptr<Model> pig1 = nullptr;
        std::shared_ptr<Model> pig2 = nullptr;
        std::shared_ptr<Model> pig3 = nullptr;

        std::vector<std::shared_ptr<Model>> pigs;

        QTimer *timer;
        QTime *time;
        OpenGLWidget(QWidget * parent = 0);
        void openFileOff();


    protected:
        void initializeGL();
        void resizeGL(int width , int height);
        void paintGL();

    public slots:
            void rotateNtranslate();

};

#endif // OPENGLWIDGET_H
