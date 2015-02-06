/*************************************************************************
    CSC418/2504, Winter 20l5
    Assignment 1

    Instructions:
        See main.cpp for more instructions.

        This file contains the OpenGL portion of the main window.
**************************************************************************/

#ifndef __GLWidget_h__
#define __GLWidget_h__

#include "include_gl.h"
#include "GLState.h"
#include "GLShape.h"
#include <QtOpenGL/QtOpenGL>

// Before transformed, this class displays a unit square centered at the
// origin.
// Used UnitSquare for legs
class UnitSquare : public GLShape
{
public:
    using GLShape::initialize;

    void initialize(int shader_input_location)
    {
	// Use two triangles to create the square.
        GLfloat square_vertices[][2] =
        {
            { -0.5, -0.5 },  // Triangle 1
            {  0.5, -0.5 },
            {  0.5,  0.5 },
            { -0.5, -0.5 },  // Triangle 2
            {  0.5,  0.5 },
            { -0.5,  0.5 },
        };

        initialize(
	    shader_input_location,
            reinterpret_cast<const GLfloat *>(square_vertices),
            /*num_vertices=*/6,
	    GL_TRIANGLES); // Each group of three coordinates is a triangle
    }
};

// Before transformed, this class displays a unit circle centered at the
// origin.
// UnitCircle is used for all circles like eyes and hinges
class UnitCircle : public GLShape
{
public:
    using GLShape::initialize;

    void initialize(int shader_input_location, int num_circle_segments)
    {
        // We will draw a circle as a triangle fan.  We are careful to send
	// the second coordinate twice to properly close the circle.
        //        3     2     1
        //         +----+----+
        //        / \   |   /
        //       /   \  |  /
        //      /     \ | /
        //     /       \|/
        //   4+---------+ 0
        //        ...
        std::vector<GLfloat> circle_vertices;
        circle_vertices.push_back(0.0);
        circle_vertices.push_back(0.0);
        for (int i=0; i<=num_circle_segments; ++i)
        {
            double angle = (2 * M_PI * i) / num_circle_segments;
            circle_vertices.push_back(cos(angle));
            circle_vertices.push_back(sin(angle));
        }

        initialize(
	    shader_input_location,
            &circle_vertices[0],
            num_circle_segments + 1,
	    GL_TRIANGLE_FAN);
    }
};

////////////////////////////////////////////////////////////////////////
// Following classes are added
//////////////////////////////////////////////////////////////////////////

// BodySquare is used for drawing body (polygon)
// BodySquare and BodySquare2 form body together
class BodySquare : public GLShape
{
public:
    using GLShape::initialize;

    void initialize(int shader_input_location)
    {
    // Use two triangles to create the square.
        GLfloat square_vertices[][2] =
        {
            { -1.0,  0.0 },  // Triangle 1
            { -0.5,  2.0 },
            {  0.5,  2.0 },
            { -1.0,  0.0 },  // Triangle 2
            { -0.4, -1.0 },
            {  0.5,  2.0 },
        };

        initialize(
        shader_input_location,
            reinterpret_cast<const GLfloat *>(square_vertices),
            /*num_vertices=*/6,
        GL_TRIANGLES); // Each group of three coordinates is a triangle
    }
};
class BodySquare2 : public GLShape
{
public:
    using GLShape::initialize;

    void initialize(int shader_input_location)
    {
    // Use two triangles to create the square.
        GLfloat square_vertices[][2] =
        {
            { -0.4, -1.0 },  // Triangle 3
            {  0.4, -1.1 },
            {  0.5,  2.0 },
            {  0.4, -1.1 },  // Triangle 4
            {  1.2, -0.2 },
            {  0.5,  2.0 },
        };

        initialize(
        shader_input_location,
            reinterpret_cast<const GLfloat *>(square_vertices),
            /*num_vertices=*/6,
        GL_TRIANGLES); // Each group of three coordinates is a triangle
    }
};

// UnitSquare2 is used for leg
class UnitSquare2 : public GLShape
{
public:
    using GLShape::initialize;

    void initialize(int shader_input_location)
    {
	// Use two triangles to create the square.
        GLfloat square_vertices[][2] =
        {
            { -0.5, -0.5 },  // Triangle 1
            {  0.5, -0.5 },
            {  0.5,  0.5 },
            { -0.5, -0.5 },  // Triangle 2
            {  0.5,  0.5 },
            { -0.5,  0.5 },
        };

        initialize(
	    shader_input_location,
            reinterpret_cast<const GLfloat *>(square_vertices),
            /*num_vertices=*/6,
	    GL_TRIANGLES); // Each group of three coordinates is a triangle
    }
};

// ArmSquare is used for arm
class ArmSquare : public GLShape
{
public:
    using GLShape::initialize;

    void initialize(int shader_input_location)
    {
    // Use two triangles to create the square.
        GLfloat square_vertices[][2] =
        {
            { -1.0,  1.2 },  // Triangle 1
            {  1.0,  1.2 },
            { -0.5, -1.2 },
            { -0.5, -1.2 },  // Triangle 2
            {  0.5, -1.2 },
            {  1.0,  1.2 },
        };

        initialize(
        shader_input_location,
            reinterpret_cast<const GLfloat *>(square_vertices),
            /*num_vertices=*/6,
        GL_TRIANGLES); // Each group of three coordinates is a triangle
    }
};

// HeadSquare and HeadSquare2 are used for head
class HeadSquare : public GLShape
{
public:
    using GLShape::initialize;

    void initialize(int shader_input_location)
    {
    // Use two triangles to create the square.
        GLfloat square_vertices[][2] =
        {
            { -0.5, -0.45 },  // Triangle 1
            { -0.1,  0.45 },
            { -0.4,  0.35 },
            { -0.5, -0.45 },  // Triangle 2
            {  0.5, -0.45 },
            { -0.1,  0.45 },
        };

        initialize(
        shader_input_location,
            reinterpret_cast<const GLfloat *>(square_vertices),
            /*num_vertices=*/6,
        GL_TRIANGLES); // Each group of three coordinates is a triangle
    }
};

class HeadSquare2 : public GLShape
{
public:
    using GLShape::initialize;

    void initialize(int shader_input_location)
    {
    // Use two triangles to create the square.
        GLfloat square_vertices[][2] =
        {
            { -0.5, -0.45 },  // Triangle 3
            {  0.5, -0.45 },
            { -0.1,  0.45 },            
            { -0.1,  0.45 },  // Triangle 4
            {  0.5, -0.45 },
            {  0.3,  0.3 },
        };

        initialize(
        shader_input_location,
            reinterpret_cast<const GLfloat *>(square_vertices),
            /*num_vertices=*/6,
        GL_TRIANGLES); // Each group of three coordinates is a triangle
    }
};

// UpperMouthSquare is used for upper lib
class UpperMouthSquare : public GLShape
{
public:
    using GLShape::initialize;

    void initialize(int shader_input_location)
    {
    // Use two triangles to create the square.
        GLfloat square_vertices[][2] =
        {
            { -0.5, -0.2 },  // Triangle 1
            {  0.5, -0.2 },
            { -0.5,  0.0 },            
            { -0.5,  0.0 },  // Triangle 2
            {  0.5, -0.2 },
            {  0.5,  0.2 },
        };

        initialize(
        shader_input_location,
            reinterpret_cast<const GLfloat *>(square_vertices),
            /*num_vertices=*/6,
        GL_TRIANGLES); // Each group of three coordinates is a triangle
    }
};

// LowerMouthSquare is used for lower lib
class LowerMouthSquare : public GLShape
{
public:
    using GLShape::initialize;

    void initialize(int shader_input_location)
    {
    // Use two triangles to create the square.
        GLfloat square_vertices[][2] =
        {
            { -0.5, -0.05 },  // Triangle 1
            {  0.5, -0.05 },
            { -0.5,  0.05 },            
            { -0.5,  0.05 },  // Triangle 2
            {  0.5, -0.05 },
            {  0.5,  0.05 },
        };

        initialize(
        shader_input_location,
            reinterpret_cast<const GLfloat *>(square_vertices),
            /*num_vertices=*/6,
        GL_TRIANGLES); // Each group of three coordinates is a triangle
    }
};



class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    // These values control the bounds to display on the joint angle sliders.
    //////////////////////////////////////////////////////////////////////////
    // TODO:
    //   Add different ranges for the different joints.  Use these ranges
    //   when constructing sliders and when animating joints.
    //////////////////////////////////////////////////////////////////////////
    // Upper leg joing angle
    // First one is left leg, second one is right leg    
    static const int JOINT_MIN = -15;
    static const int JOINT_MAX = 15;
    static const int JOINT_MIN2 = -25;
    static const int JOINT_MAX2 = 15;

    // Lower leg joint angle
    // First one is left leg, second one is right leg
    static const int LOWER_JOINT_MIN = -40;
    static const int LOWER_JOINT_MAX = 40;
    static const int LOWER_JOINT_MIN2 = -30;
    static const int LOWER_JOINT_MAX2 = 30;

    // Arm joint angle
    static const int JOINT_MIN_ARM = -80;
    static const int JOINT_MAX_ARM = 80;

    // Head joint angle
    static const int JOINT_MIN_HEAD = -5;
    static const int JOINT_MAX_HEAD = 5;

    // Body movement min and max
    // First one is left and right, second one is up and down
    static const int MOVE_MIN = -80;
    static const int MOVE_MAX = 80;
    static const int MOVE_MIN2 = -50;
    static const int MOVE_MAX2 = 50;

    // Mouth movement min and max
    static const int MOUTH_MOVE_MIN = -5;
    static const int MOUTH_MOVE_MAX = 5;

    GLWidget(QWidget *parent=NULL);

public slots:
    // This method is called when the user changes the joint angle slider.
    //////////////////////////////////////////////////////////////////////////
    // TODO:
    //   There is currently only one joint, but you need to add more.
    //////////////////////////////////////////////////////////////////////////
    // setJointAngle function for left upper leg    
    void setJointAngle(int angle)
    {
        // This method is called when the user changes the slider value.
        m_joint_angle = angle;

        // Call update() to trigger a redraw.
        update();
    }

    // setJointAngle function for right upper leg
    void setJointAngle2(int angle)
    {
        m_joint_angle2 = angle;
        update();
    }

    // setJointAngle for left lower leg
    void setJointAngle_lower_leg(int angle)
    {
        m_joint_angle_lower_leg = angle;
        update();
    }

    // setJointAngle for right lower leg
    void setJointAngle_lower_leg2(int angle)
    {
        m_joint_angle_lower_leg2 = angle;
        update();
    }

    // setJointAngle for arm
    void setJointAngle_arm(int angle)
    {
        m_joint_angle_arm = angle;
        update();
    }

    // setJointAngle for head
    void setJointAngle_head(int angle)
    {
        m_joint_angle_head = angle;
        update();
    }

    // setMovement_Mouth for mouth
    void setMovement_Mouth(int mov)
    {
        mouth_movement = mov;
        update();
    }

    // setMovement_Body_X for body
    void setMovement_Body_X(int mov)
    {
        movement = mov;
        update();
    }

    // setMovement_Body_Y for body
    void setMovement_Body_Y(int mov)
    {
        movement2 = mov;
        update();
    }

    void onPressAnimate(int is_animating)
    {
        // This method is called when the user changes the animation checkbox.
        m_is_animating = (bool)is_animating;
        m_animation_frame = 0;
        update();
    }

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void timerEvent(QTimerEvent *event);

private:
    GLTransformStack &transformStack()
    { return m_gl_state.transformStack(); }

private:
    GLState m_gl_state;
    bool m_is_animating;
    int m_animation_frame;
    UnitSquare m_unit_square;
    UnitCircle m_unit_circle;
    //////////////////////////////////////////////////////////////////////////
    // TODO: Add additional joint parameters.
    //////////////////////////////////////////////////////////////////////////
    BodySquare m_body_square;
    BodySquare2 m_body_square2;
    UnitSquare m_unit_square2;
    ArmSquare m_arm_square;
    HeadSquare m_head_square;
    HeadSquare2 m_head_square2;
    UpperMouthSquare m_upper_mouth_square;
    LowerMouthSquare m_lower_mouth_square;

    double m_joint_angle;
    double m_joint_angle2;
    double m_joint_angle_lower_leg;
    double m_joint_angle_lower_leg2;
    double m_joint_angle_arm;
    double m_joint_angle_head;
    double movement;
    double movement2;
    double mouth_movement;
};

#endif
