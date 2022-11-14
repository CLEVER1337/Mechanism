#include <QOpenGLWidget>
#include <QtDebug>

#include "MainOpenGLClass.h"

MainOpenGLClass::MainOpenGLClass(QWidget* parent) : QOpenGLWidget(parent)
{

}

MainOpenGLClass::~MainOpenGLClass()
{

}

void MainOpenGLClass::initializeGL()
{

}

void MainOpenGLClass::resizeGL(int w, int h)
{
    qDebug() << "loh";
}

void MainOpenGLClass::paintGL()
{

}
