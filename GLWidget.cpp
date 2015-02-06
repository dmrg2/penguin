/*************************************************************************
    CSC418/2504, Winter 20l5
    Assignment 1

    Instructions:
        See main.cpp for more instructions.

        This file contains the class OpenGL portion of the main window.
**************************************************************************/

#include "GLWidget.h"
#include <iostream>

static QGLFormat createQGLFormat()
{
    // Return a QGLFormat object that tells Qt information about what
    // OpenGL context we would like.
    QGLFormat format(QGL::SampleBuffers);
    if (supportsNewOpenGL())
    {
	// Choose a version of OpenGL that supports vertex array objects and
	// tell it that we do not want support for deprecated functions.
        format.setVersion(3, 3);
        format.setProfile(QGLFormat::CoreProfile);
    }
    return format;
}

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(createQGLFormat(), parent)
    , m_is_animating(false)
    , m_animation_frame(0)
    , m_joint_angle(0)
{
    // Start a timer that will call the timerEvent method every 50ms.
    startTimer(/*milliseconds=*/50);
}

void GLWidget::initializeGL()
{
    m_gl_state.initializeGL();

    // To aid with troubleshooting, print out which version of OpenGL we've
    // told the driver to use.
    std::cout << "Using OpenGL: " << glGetString(GL_VERSION) << std::endl;

    // Copy the data for the shapes we'll draw into the video card's memory.
    // Set segments 300 for better image
    m_unit_square.initialize(m_gl_state.VERTEX_POSITION_SHADER_LOCATION);
    m_unit_circle.initialize(
	m_gl_state.VERTEX_POSITION_SHADER_LOCATION,
	/*num_circle_segments=*/300);

    // Set all objects initialization
    m_body_square.initialize(m_gl_state.VERTEX_POSITION_SHADER_LOCATION);
    m_body_square2.initialize(m_gl_state.VERTEX_POSITION_SHADER_LOCATION);
    m_unit_square2.initialize(m_gl_state.VERTEX_POSITION_SHADER_LOCATION);
    m_arm_square.initialize(m_gl_state.VERTEX_POSITION_SHADER_LOCATION);
    m_head_square.initialize(m_gl_state.VERTEX_POSITION_SHADER_LOCATION);
    m_head_square2.initialize(m_gl_state.VERTEX_POSITION_SHADER_LOCATION);
    m_upper_mouth_square.initialize(m_gl_state.VERTEX_POSITION_SHADER_LOCATION);
    m_lower_mouth_square.initialize(m_gl_state.VERTEX_POSITION_SHADER_LOCATION);

    // Tell OpenGL what color to fill the background to when clearing.
    glClearColor(/*red=*/0.7f, /*green=*/0.7f, /*blue=*/0.9f, /*alpha=*/1.0f);

}

void GLWidget::resizeGL(int width, int height)
{
    // Respond to the window being resized by updating the viewport and
    // projection matrices.

    checkForGLErrors();

    // Setup projection matrix for new window
    m_gl_state.setOrthographicProjectionFromWidthAndHeight(width, height);

    // Update OpenGL viewport and internal variables
    glViewport(0, 0, width, height);
    checkForGLErrors();
}

void GLWidget::timerEvent(QTimerEvent *)
{
    // Respond to a timer going off telling us to update the animation.
    if (!m_is_animating)
        return;

    // increment the frame number.
    m_animation_frame++;

    // Update joint angles.
    const double joint_rot_speed = 0.1;
    double joint_rot_t =
        (sin(m_animation_frame * joint_rot_speed) + 1.0) / 2.0;
    // Joint angle for left upper leg    
    m_joint_angle = joint_rot_t * JOINT_MIN + (1 - joint_rot_t) * JOINT_MAX;
    // Joint angle for right upper leg
    m_joint_angle2 = joint_rot_t * JOINT_MIN2 + (1 - joint_rot_t) * JOINT_MAX2;

    // Joint angle for left lower leg
    m_joint_angle_lower_leg = joint_rot_t * LOWER_JOINT_MIN + (1 - joint_rot_t) * LOWER_JOINT_MAX;
    // Joint angle for right lower leg
    m_joint_angle_lower_leg2 = joint_rot_t * LOWER_JOINT_MIN2 + (1 - joint_rot_t) * LOWER_JOINT_MAX2;
    
    // Arm angle
    m_joint_angle_arm = joint_rot_t * JOINT_MIN_ARM + (1 - joint_rot_t) * JOINT_MAX_ARM;
    // Head angle
    m_joint_angle_head = joint_rot_t * JOINT_MIN_HEAD + (1 - joint_rot_t) * JOINT_MAX_HEAD;

    // Rot for movements (body and lib)
    double movement_rot = (sin(m_animation_frame * 0.05) + 1.0) / 2.0;
    double movement_rot2 = (sin(m_animation_frame * 0.2) + 1.0) / 2.0;
    // Body movement, movement (x), movement2 (y)
    movement = movement_rot * MOVE_MIN + (1 - movement_rot) * MOVE_MAX;
    movement2 = movement_rot2 * MOVE_MIN2 + (1 - movement_rot2) * MOVE_MAX2;
    // Lower lib movement    
    mouth_movement = movement_rot * MOUTH_MOVE_MIN + (1 - movement_rot) * MOUTH_MOVE_MAX;

    //////////////////////////////////////////////////////////////////////////
    // TODO:
    //   Modify this function to animate the character's joints
    //   Note: Nothing should be drawn in this function!
    //////////////////////////////////////////////////////////////////////////
    // Added all angles and movements

    // Tell this widget to redraw itself.
    update();
}

void GLWidget::paintGL()
{
    // This method gets called by the event handler to draw the scene, so
    // this is where you need to build your scene -- make your changes and
    // additions here.  All rendering happens in this function.

    checkForGLErrors();

    // Clear the screen with the background colour.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

    // Setup the model-view transformation matrix stack.
    transformStack().loadIdentity();
    checkForGLErrors();

    //////////////////////////////////////////////////////////////////////////
    // TODO:
    //   Modify this function draw the scene.  This should include function
    //   calls to pieces that apply the appropriate transformation matrices
    //   and render the individual body parts.
    //////////////////////////////////////////////////////////////////////////

    // Draw our hinged object
    // Added const for scale
    const float BODY_WIDTH = 55.0f;
    const float BODY_LENGTH = 100.0f;
    const float ARM_LENGTH = 80.0f;
    const float ARM_WIDTH = 20.0f;
    const float ARM2_LENGTH = 50.0f;
    const float ARM2_WIDTH = 25.0f; 
    const float HEAD_WIDTH = 150.0f;
    const float HEAD_LENGTH =120.0f;
    const float MOUTH_WIDTH = 60.0f;
    const float MOUTH_LENGTH = 40.0f;
    const float JOINT_WIDTH = 5.0f;
    const float BIG_EYE = 12.0f;
    const float SMALL_EYE = 10.0f;

    // Note that successive transformations are applied *before* the previous
    // ones.

    // Push the current transformation matrix on the stack
    transformStack().pushMatrix();

	// Back ground - for better quality
	transformStack().pushMatrix();
		transformStack().translate(0,-BODY_LENGTH*2);
		// Ice layer		
		transformStack().pushMatrix();
			transformStack().scale(12*BODY_WIDTH, 6*BODY_WIDTH);
			m_gl_state.setColor(1.0, 1.0, 1.0);			
			m_unit_square.draw();
		transformStack().popMatrix();
		// Snow man
		// Upper black and white, first draw black at the base then draw white circle top on it.
		transformStack().pushMatrix();
			transformStack().translate(-BODY_LENGTH*2,BODY_LENGTH*2);
			transformStack().pushMatrix();
				transformStack().scale(40, 40);
				m_gl_state.setColor(0.0, 0.0, 0.0);
				m_unit_circle.draw();
			transformStack().popMatrix();
			transformStack().pushMatrix();
				transformStack().scale(38, 38);
				m_gl_state.setColor(1.0, 1.0, 1.0);
				m_unit_circle.draw();
			transformStack().popMatrix();
			// Draw eyes (two squares)
			transformStack().pushMatrix();
			transformStack().translate(-5.0,0.0);
			transformStack().pushMatrix();
				transformStack().scale(10,5);
				m_gl_state.setColor(0.0, 0.0, 0.0);
				m_unit_square.draw();
			transformStack().popMatrix();
			transformStack().translate(25.0,0.0);
			transformStack().pushMatrix();
				transformStack().scale(10,5);
				m_gl_state.setColor(0.0, 0.0, 0.0);
				m_unit_square.draw();
			transformStack().popMatrix();
		transformStack().popMatrix();
		transformStack().popMatrix();
		transformStack().translate(0.0,-120);
		// Draw lower snow man as same as upper snow man.
		transformStack().pushMatrix();
			transformStack().translate(-BODY_LENGTH*2,BODY_LENGTH*2);
			transformStack().pushMatrix();
				transformStack().scale(80, 80);
				m_gl_state.setColor(0.0, 0.0, 0.0);
				m_unit_circle.draw();
			transformStack().popMatrix();
			transformStack().pushMatrix();
				transformStack().scale(78, 78);
				m_gl_state.setColor(1.0, 1.0, 1.0);
				m_unit_circle.draw();
			transformStack().popMatrix();
		transformStack().popMatrix();
	transformStack().popMatrix();


        // Whole body moves left and right
        transformStack().translate(movement, -50+movement2);

		// Draw the 'body'
		transformStack().pushMatrix();
			transformStack().scale(2*BODY_WIDTH, BODY_LENGTH);
			m_gl_state.setColor(0.0, 0.0, 1.0);
			// Use two squares to draw body
			m_body_square.draw();
			m_body_square2.draw();
		transformStack().popMatrix();


		// Draw the 'head'
		transformStack().pushMatrix();
			transformStack().translate(0, BODY_LENGTH*2);
			// Set hinge for movement of the head
			transformStack().rotateInDegrees(m_joint_angle_head);
			transformStack().pushMatrix();        
				transformStack().translate(0, HEAD_LENGTH/2-20);
				transformStack().scale(HEAD_WIDTH, HEAD_LENGTH);
				m_gl_state.setColor(0.0, 0.0, 0.5);
				// Use two squares to draw head
				m_head_square2.draw();
				m_head_square.draw();
			transformStack().popMatrix();

			// Draw the 'upper mouth'
			transformStack().pushMatrix();
				transformStack().translate(-HEAD_LENGTH*2/3-18, 20);
				transformStack().scale(MOUTH_WIDTH, MOUTH_LENGTH);
				m_gl_state.setColor(1.0, 1.0, 0.0);
				m_upper_mouth_square.draw();
			transformStack().popMatrix();
			// Draw the 'lower mouth'
			transformStack().pushMatrix();
				transformStack().translate(-HEAD_LENGTH*2/3-18, mouth_movement);
				transformStack().scale(MOUTH_WIDTH, MOUTH_LENGTH);
				m_gl_state.setColor(1.0, 1.0, 0.0);
				m_lower_mouth_square.draw();
			transformStack().popMatrix();
			// Draw joint circle
			transformStack().pushMatrix();
				transformStack().translate(0.0, 0.0);        
				transformStack().scale(JOINT_WIDTH, JOINT_WIDTH);
				m_gl_state.setColor(1.0, 1.0, 1.0);
				m_unit_circle.draw();
			transformStack().popMatrix();
			// Draw the 'outer eye'
			transformStack().pushMatrix();
				transformStack().translate(-HEAD_WIDTH/4, HEAD_LENGTH/2);
				transformStack().scale(BIG_EYE, BIG_EYE);
				m_gl_state.setColor(1.0, 1.0, 1.0);
				m_unit_circle.draw();
			transformStack().popMatrix();
			// Draw the 'inner eye'
			transformStack().pushMatrix();
				transformStack().translate(-HEAD_WIDTH/4-3,HEAD_LENGTH/2);
				transformStack().scale(SMALL_EYE, SMALL_EYE);
				m_gl_state.setColor(0.0, 0.0, 0.0);
				m_unit_circle.draw();
			transformStack().popMatrix();          
		transformStack().popMatrix();

       

		// Draw the 'arm'
		transformStack().pushMatrix();
			transformStack().translate(0, ARM2_LENGTH*2+20);
			transformStack().rotateInDegrees(m_joint_angle_arm);
			transformStack().translate(0, -ARM2_LENGTH);
			transformStack().pushMatrix();
				transformStack().translate(0, 0);
				transformStack().scale(ARM2_WIDTH, ARM2_LENGTH);
				m_gl_state.setColor(0.5, 0.0, 0.5);
				m_arm_square.draw();
			transformStack().popMatrix();
			
			// Draw joint circle
			transformStack().pushMatrix();
				transformStack().translate(0.0, ARM2_LENGTH);        
				transformStack().scale(JOINT_WIDTH, JOINT_WIDTH);
				m_gl_state.setColor(1.0, 1.0, 1.0);
				m_unit_circle.draw();
			transformStack().popMatrix();         
		transformStack().popMatrix();

		// Draw 'left leg'
		transformStack().pushMatrix();
			// Put all leg objects to right place
			transformStack().translate(-BODY_WIDTH/2, -BODY_LENGTH*2/3);
			// Rotate along the hinge
			transformStack().rotateInDegrees(m_joint_angle);
			// Draw 'left upper leg'
			transformStack().rotateInDegrees(-20);        
			transformStack().pushMatrix();
				transformStack().translate(0.0, 10);
				// Scale the size of the leg
				transformStack().scale(ARM_WIDTH, ARM_LENGTH);
				// Move to center location of leg, under previous rotation
				transformStack().translate(0.0, -0.5);
				// Draw the square for the leg
				m_gl_state.setColor(1.0, 0.0, 0.0);
				m_unit_square2.draw();
			transformStack().popMatrix();
			// Draw joint circle
			transformStack().pushMatrix();
				transformStack().scale(JOINT_WIDTH, JOINT_WIDTH);
				m_gl_state.setColor(1.0, 1.0, 1.0);
				m_unit_circle.draw();
			transformStack().popMatrix();        

			// Draw 'left lower leg'
			transformStack().pushMatrix();
				transformStack().translate(0,-ARM_LENGTH+10);
				// Set pivot for joint
				transformStack().rotateInDegrees(m_joint_angle_lower_leg);
				// Rotate lower leg to -80 degree
				transformStack().rotateInDegrees(-80);
				transformStack().pushMatrix();
					transformStack().translate(0,-ARM_LENGTH/2+10);
					// Scale the size of the leg
					transformStack().scale(ARM_WIDTH, ARM_LENGTH);
					// Draw the square for the leg        
					m_gl_state.setColor(1.0, 1.0, 0.0);
					m_unit_square.draw();
				transformStack().popMatrix();
				// Draw joint circle
				transformStack().pushMatrix();
					transformStack().scale(JOINT_WIDTH, JOINT_WIDTH);
					m_gl_state.setColor(1.0, 1.0, 1.0);
					m_unit_circle.draw();
				transformStack().popMatrix();    
			transformStack().popMatrix();
		transformStack().popMatrix();

		// Draw 'right leg'
		transformStack().pushMatrix();
			// Put all leg objects to right place
			transformStack().translate(BODY_WIDTH/2, -BODY_LENGTH*2/3);
			// Rotate along the hinge
			transformStack().rotateInDegrees(m_joint_angle2);
			// Draw 'right upper leg'
			transformStack().rotateInDegrees(20);
			transformStack().pushMatrix();
				transformStack().translate(0.0, 10);
				// Scale the size of the leg
				transformStack().scale(ARM_WIDTH, ARM_LENGTH);
				// Move to center location of leg, under previous rotation
				transformStack().translate(0.0, -0.5);
				// Draw the square for the leg
				m_gl_state.setColor(1.0, 0.0, 0.0);
				m_unit_square2.draw();
			transformStack().popMatrix();			
			// Draw joint circle
			transformStack().pushMatrix();
				transformStack().scale(JOINT_WIDTH, JOINT_WIDTH);
				m_gl_state.setColor(1.0, 1.0, 1.0);
				m_unit_circle.draw();
			transformStack().popMatrix();  

			// Draw 'right lower leg'
			transformStack().pushMatrix();
				transformStack().translate(0,-ARM_LENGTH+10);
				// Set pivot for joint
				transformStack().rotateInDegrees(m_joint_angle_lower_leg2);
				// Rotate lower leg to -80 degree
				transformStack().rotateInDegrees(-80);
				transformStack().pushMatrix();
					transformStack().translate(0,-ARM_LENGTH/2+10);
					// Scale the size of the leg
					transformStack().scale(ARM_WIDTH, ARM_LENGTH);
					// Draw the square for the leg        
					m_gl_state.setColor(1.0, 1.0, 0.0);
					m_unit_square.draw();
				transformStack().popMatrix();		
				// Draw joint circle
				transformStack().pushMatrix();
					transformStack().translate(0.0, 0.4);        
					transformStack().scale(JOINT_WIDTH, JOINT_WIDTH);
					m_gl_state.setColor(1.0, 1.0, 1.0);
					m_unit_circle.draw();
				transformStack().popMatrix(); 
			transformStack().popMatrix();
        	transformStack().popMatrix();

    // Retrieve the previous state of the transformation stack
    transformStack().popMatrix();

    // Execute any GL functions that are in the queue just to be safe
    glFlush();
    checkForGLErrors();
}

