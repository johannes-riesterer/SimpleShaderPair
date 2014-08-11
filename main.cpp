/* 
 * File:   main.cpp
 * Author: johannes
 *
 * Created on 11. August 2014, 16:15
 */

#include <GL/glew.h>

#include <GL/glut.h>

#include <stdio.h>

#include "ShaderUtils.h"


#define window_width  1280              
#define window_height 1024

GLhandleARB program;
static float angle = .0;
static float dt = 0.0;

using namespace ShaderUtils;

void display() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    
    glUseProgram(program);
    
    GLint uniformDt = glGetUniformLocation(program, "dt");
    glUniform1f(uniformDt, dt);
    GLint uniformDdt = glGetUniformLocation(program, "ddt");
    glUniform1f(uniformDdt, 0.5);
    
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glPushMatrix();
    glRotatef(angle, 0.0, 1.0, 0.0);
    glutSolidTorus(1, 5, 150, 150);

    glPopMatrix();
 //   glUniform1f(uniformDt, dt + .1);
//    glUniform1f(uniformDdt, 4.0);
 //   glutSolidSphere(4,150,150);
//    glUseProgram(0);

    angle += 1.1;
    dt += 0.01;

    glutSwapBuffers();
    glutPostRedisplay();

}

void keyboard(unsigned char key, int mousePositionX, int mousePositionY) {

}

void GL_Setup(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
    gluPerspective(45, (float) width / height, .1, 100);
    program = createStandardShaderPairFromFiles("vertexShaderOne", "fragmentShaderOne");

}

void reshape(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, width, height);
    glLoadIdentity();
    gluPerspective(45, (float) width / height, .1, 100);
}

// Initialize GLUT and start main loop

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(window_width, window_height);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow("opengl_test");
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    GL_Setup(window_width, window_height);
    glutMainLoop();
    
    return 0;
}




