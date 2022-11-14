#ifndef MAINOPENGLCLASS_H
#define MAINOPENGLCLASS_H

#include <QOpenGLWidget>

class MainOpenGLClass : public QOpenGLWidget
{
public:
    MainOpenGLClass(QWidget* parent = nullptr);
    ~MainOpenGLClass();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
};

#endif // MAINOPENGLCLASS_H
