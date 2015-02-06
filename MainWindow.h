/*************************************************************************
    CSC418/2504, Winter 20l5
    Assignment 1
  
  
    Instructions:
        See main.cpp for more instructions.

        This file contains the class for the main window of the program.
**************************************************************************/

#ifndef __MainWindow_h__
#define __MainWindow_h__

#include <QtGui/QtGui>
#include "GLWidget.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow()
    {
        // Create a GLWidget to hold the OpenGL viewport.
        m_gl_widget = new GLWidget();

        // Create a checkbox to turn animation on and off, and make it
        // call GLWidget::onPressAnimate when checked.
        m_animate_checkbox = new QCheckBox("Animate", this);
        connect(
            m_animate_checkbox, SIGNAL(stateChanged(int)),
            m_gl_widget, SLOT(onPressAnimate(int)));

        // Create a button to quit the program.
        m_quit_button = new QPushButton("Quit", this);
        connect(
            m_quit_button, SIGNAL(clicked(bool)),
            this, SLOT(onPressQuit(bool)));

        m_main_layout = new QVBoxLayout();
        m_main_layout->addWidget(m_gl_widget);

        // Create a slider to control the joint angle, and make it call
        // GLWidget::setJointAngle when the slider value changes.
	// Slider for left upper leg joint
        m_slider = create_joint_angle_slider(
	    "Joint (left upper leg)", GLWidget::JOINT_MIN, GLWidget::JOINT_MAX);
        connect(
            m_slider, SIGNAL(valueChanged(int)),
            m_gl_widget, SLOT(setJointAngle(int)));

        //////////////////////////////////////////////////////
        // TODO: Add additional joint sliders here
        //////////////////////////////////////////////////////
	// Slider for right upper leg joint
	m_slider2 = create_joint_angle_slider(
	    "Joint (right upper leg)", GLWidget::JOINT_MIN2, GLWidget::JOINT_MAX2);
        connect(
            m_slider2, SIGNAL(valueChanged(int)),
            m_gl_widget, SLOT(setJointAngle2(int)));

        // Slider for left lower leg joint
        m_slider3 = create_joint_angle_slider(
	    "Joint (left lower leg)", GLWidget::LOWER_JOINT_MIN, GLWidget::LOWER_JOINT_MAX);
        connect(
            m_slider3, SIGNAL(valueChanged(int)),
            m_gl_widget, SLOT(setJointAngle_lower_leg(int)));

        // Slider for right lower leg joint
        m_slider4 = create_joint_angle_slider(
	    "Joint (right lower leg)", GLWidget::LOWER_JOINT_MIN2, GLWidget::LOWER_JOINT_MAX2);
        connect(
            m_slider4, SIGNAL(valueChanged(int)),
            m_gl_widget, SLOT(setJointAngle_lower_leg2(int)));
        
        // Slider for arm
        m_slider5 = create_joint_angle_slider(
	    "Joint (arm)", GLWidget::JOINT_MIN_ARM, GLWidget::JOINT_MAX_ARM);
        connect(
            m_slider5, SIGNAL(valueChanged(int)),
            m_gl_widget, SLOT(setJointAngle_arm(int)));

        // Slider for head
        m_slider6 = create_joint_angle_slider(
	    "Joint (head)", GLWidget::JOINT_MIN_HEAD, GLWidget::JOINT_MAX_HEAD);
        connect(
            m_slider6, SIGNAL(valueChanged(int)),
            m_gl_widget, SLOT(setJointAngle_head(int)));

        // Slider for mouth
        m_slider7 = create_joint_angle_slider(
	    "Mouth movement", GLWidget::MOUTH_MOVE_MIN, GLWidget::MOUTH_MOVE_MAX);
        connect(
            m_slider7, SIGNAL(valueChanged(int)),
            m_gl_widget, SLOT(setMovement_Mouth(int)));
        
        // Slider for body (X)
        m_slider8 = create_joint_angle_slider(
	    "Body movement(X)", GLWidget::MOVE_MIN, GLWidget::MOVE_MAX);
        connect(
            m_slider8, SIGNAL(valueChanged(int)),
            m_gl_widget, SLOT(setMovement_Body_X(int)));

        // Slider for body (Y)
        m_slider9 = create_joint_angle_slider(
	    "Body movement(Y)", GLWidget::MOVE_MIN2, GLWidget::MOVE_MAX2);
        connect(
            m_slider9, SIGNAL(valueChanged(int)),
            m_gl_widget, SLOT(setMovement_Body_Y(int)));


        m_main_layout->addWidget(m_animate_checkbox);
        m_main_layout->addWidget(m_quit_button);
        setLayout(m_main_layout);

        m_slider->setValue(0);
        m_slider2->setValue(0);
        m_slider3->setValue(0);
        m_slider4->setValue(0);
        m_slider5->setValue(0);
        m_slider6->setValue(0);
        m_slider7->setValue(0);
        m_slider8->setValue(0);
        m_slider9->setValue(0);
        setWindowTitle("CSC418/2504 Assignment 1");
    }

public slots:
    void onPressQuit(bool)
    {
        exit(0);
    }

private:
    QSlider *create_joint_angle_slider(
	const char *label, int min_angle, int max_angle)
    {
        QSlider *slider = new QSlider(Qt::Horizontal, this);
        slider->setRange(min_angle, max_angle);
        slider->setSingleStep(1);
        slider->setPageStep(5);
        slider->setTickInterval(5);
        slider->setTickPosition(QSlider::TicksBelow);

	QBoxLayout *layout = new QHBoxLayout();
	layout->addWidget(new QLabel(label));
	layout->addWidget(slider);
	m_main_layout->addLayout(layout);

        return slider;
    }

    GLWidget *m_gl_widget;
    QCheckBox *m_animate_checkbox;
    QPushButton *m_quit_button;
    QSlider *m_slider;
    QSlider *m_slider2;
    QSlider *m_slider3;
    QSlider *m_slider4;
    QSlider *m_slider5;
    QSlider *m_slider6;
    QSlider *m_slider7;
    QSlider *m_slider8;
    QSlider *m_slider9;
    QVBoxLayout *m_main_layout;
};

#endif
