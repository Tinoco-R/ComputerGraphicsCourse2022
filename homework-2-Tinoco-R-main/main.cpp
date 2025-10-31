/*******************************************************
 * Homework 2: OpenGL                                  *
 *-----------------------------------------------------*
 * First, you should fill in problem1(), problem2(),   *
 * and problem3() as instructed in the written part of *
 * the problem set.  Then, express your creativity     *
 * with problem4()!                                    *
 *                                                     *
 * Note: you will only need to add/modify code where   *
 * it says "TODO".                                     *
 *                                                     *
 * The left mouse button rotates, the right mouse      *
 * button zooms, and the keyboard controls which       *
 * problem to display.                                 *
 *                                                     *
 * For Linux/OS X:                                     *
 * To compile your program, just type "make" at the    *
 * command line.  Typing "make clean" will remove all  *
 * computer-generated files.  Run by typing "./hw2"    *
 *                                                     *
 * For Visual Studio:                                  *
 * You can create a project with this main.cpp and     *
 * build and run the executable as you normally would. *
 *******************************************************/

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "./freeglut-3.4.0/include/GL/freeglut.h"

using namespace std;

bool leftDown = false, rightDown = false;
int lastPos[2];
float cameraPos[4] = {0, 1, 4, 1};
int windowWidth = 640, windowHeight = 480;
double xRot = 0;
double yRot = 0;
int curProblem = 1; // TODO: change this number to try different examples

float specular[] = {1.0, 1.0, 1.0, 1.0};
float shininess[] = {50.0};

void problem1() {
  glMatrixMode(GL_MODELVIEW);

  // 8 Matrixes For 8 teapots
  glPushMatrix();
  glPushMatrix();
  glPushMatrix();
  glPushMatrix();
  glPushMatrix();
  glPushMatrix();
  glPushMatrix();
  glPushMatrix();
  // Top Teapot
  glTranslatef (0, 1, 0);
  glRotatef(180, 0, 1, 0);
  glRotatef(180, 1, 0, 0);
  glutSolidTeapot(.125);
  glPopMatrix();
  // Top-Right Teapot
  glTranslatef (0.5, 0.5, 0);
  glRotatef(135, 0, 0, 1);
  glutSolidTeapot(0.125);
  glPopMatrix();
  // Right Teapot
  glTranslatef (1, 0, 0);
  glRotatef(90, 0, 0, 1);
  glutSolidTeapot(0.125);
  glPopMatrix();
  // Bottom-Right Teapot
  glTranslatef (0.5, -0.5, 0);
  glRotatef(45, 0, 0, 1);
  glutSolidTeapot(0.125);
  glPopMatrix();
  // Bottom Teapot
  glTranslatef (0, -1, 0);
  glutSolidTeapot(0.125);
  glPopMatrix();
  // Bottom-Left Teapot
  glTranslatef (-0.5, -0.5, 0);
  glRotatef(45, 0, 0, -1);
  glutSolidTeapot(0.125);
  glPopMatrix();
  // Left Teapot
  glTranslatef (-1, 0, 0);
  glRotatef(90, 0, 0, -1);
  glutSolidTeapot(0.125);
  glPopMatrix();
  // Top-Left Teapot
  glTranslatef (-0.5, 0.5, 0);
  glRotatef(135, 0, 0, -1);
  glutSolidTeapot(0.125);
  glPopMatrix();
}

void problem2() {
  double xPos, yPos, zPos;
  double xzScale, yScale;
  xPos = 0;
  zPos = 1;
  yPos = 1.5;

  // Pyramid Idea: Height scale stays the same, but x and z components increase
  xzScale = -0.5;
  yScale = 1;  

  // Loops for each step downwards
  for (int i = 0; i < 11; i++) {
    yPos -= 0.125;
    xzScale += 1.75;
    
    glPushMatrix();
    glTranslatef (xPos, yPos, zPos);
    glScalef(xzScale, yScale, xzScale);
    glutSolidCube(0.125);
    glPopMatrix();
  }
}

void problem3() {
  glMatrixMode(GL_MODELVIEW);

  // Initialize x and y as doubles to get coordinate of correct location in " reverse pyramid"
  double y = -1.5;
  double x = 0;

  /*  Nested for loop; iterates through each column [teapot] (j) for each row (i) in pyramid
   * Number of teapots/ current row = i
   * Current teapot = j
   * At each row, initializes x to 0, then to the left most position in row (-.3 * i)
   * Also, raises y to correct height [range: -1.1 to 0.9]
   * Delta y = .4
   * Delta x = .6
   * Once in inner loop, pushes a matrix to stack, translates according to current x and y, places a 
   * teapot object at location, and removes matrix from stack
   * Increments x for next teapot in row.
   */
  for (int i = 0; i < 6; i++) {
    x = 0;
    y += 0.4;
    x = -0.3 * i;
    for (int j = 0; j < i + 1; j++) {
      glPushMatrix();
      glTranslatef (x, y, 0);
      glutSolidTeapot(0.2);
      glPopMatrix();
      x += 0.6;
    }
  }
}

void problem4() {
  // Left Vertex Coordinates   (-1,  0, -2)
  // Right Vertex Coordinates  (2.5, 0, -2)
  // Bottom Vertex Coordinates (1,  -2, 0)

  // Triangle creation
  glDisable(GL_LIGHTING);
  
  glPushMatrix();
  glBegin(GL_TRIANGLES);
  // Brown
  glColor3f(0.5, 0.3, 0.1);
  glVertex3f(-1, 0, -2);
  glVertex3f(2.5, 0, -2);
  glVertex3f(1, -2, 0);
  glEnd();
  glPopMatrix();
  glEnable(GL_LIGHTING);
  

  
  // Mouse creation
  // First branch of loop creates mouse nose
  // Second branch creates mouse ears (involves nested matrix)
  // Last branch creates mouse eyes (involves nested matrix)
  double x = -2;
  for (int i = 0; i < 5; i++) {
    x += 1;

    // Ears
    if (i == 0 || i == 3) {
      // Bottom third of ear
      glPushMatrix();
      glTranslatef (x + 0.25,  0 + 0.375, -2 - 0.25);
      glScalef(1, 1.5, 1);
      glutSolidCube(0.5);
      
      // Nested matrix
      // Middle third of ear
      glPushMatrix();
      glScalef(1, 1.25, 1);
      glTranslatef (0, 0.3, 0.1);
      glRotatef(30, 10, 0, 0);
      
      glutSolidCube(0.5);  
      // Double nested matrix
      // Top third of ear
      glPushMatrix();
      glTranslatef (0, 0.3, 0.05);
      glRotatef(20, 10, 0, 0);
      glutSolidCube(0.5);
      
      glPopMatrix();
      glPopMatrix();
      glPopMatrix();
    }

    // Eyes
    else if (i == 1 || i == 2) {
      glPushMatrix();
      glTranslatef (x + 0.25, 0.25, -1.6);
      glRotatef(90, 1, 0, 0);
      glScalef(1, 1.5, 1);
      glutSolidCube(0.5);
      
      // Nested matrix
      // Middle third of ear
      glPushMatrix();
      glScalef(1, 1.25, 1);
      glTranslatef (0, 0.3, .1);
      glRotatef(30, 1, 0, 0);
      
      glutSolidCube(0.5);  
      // Double nested matrix
      // Top third of ear
      glPushMatrix();
      glRotatef(75, 1, 0, 0);
      glScalef(1, 2, 0.5);
      glTranslatef (0, 0.15, -0.4);
      glutSolidCube(0.5);
      
      glPopMatrix();
      glPopMatrix();
      glPopMatrix();
    }
    
    // Nose
    else {
      glPushMatrix();
      glTranslatef ((-1 + 2.5) / 2 + .25,  -1.75, -.25);
      glutSolidCube(0.5);
      glPopMatrix();
    }
  }
}

void display() {
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glDisable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
  glBegin(GL_LINES);
  glColor3f(1, 0, 0);
  glVertex3f(0, 0, 0);
  glVertex3f(1, 0, 0); // x axis
  glColor3f(0, 1, 0);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 1, 0); // y axis
  glColor3f(0, 0, 1);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, 1); // z axis
  glEnd(/*GL_LINES*/);

  glEnable(GL_LIGHTING);
  glShadeModel(GL_SMOOTH);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  glEnable(GL_LIGHT0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, windowWidth, windowHeight);

  float ratio = (float)windowWidth / (float)windowHeight;
  gluPerspective(50, ratio, 1, 1000);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);

  glLightfv(GL_LIGHT0, GL_POSITION, cameraPos);

  glRotatef(xRot, 1, 0, 0);
  glRotatef(yRot, 0, 1, 0);

  if (curProblem == 1)
    problem1();
  if (curProblem == 2)
    problem2();
  if (curProblem == 3)
    problem3();
  if (curProblem == 4)
    problem4();

  glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON)
    leftDown = (state == GLUT_DOWN);
  else if (button == GLUT_RIGHT_BUTTON)
    rightDown = (state == GLUT_DOWN);

  lastPos[0] = x;
  lastPos[1] = y;
}

void mouseMoved(int x, int y) {
  if (leftDown) {
    xRot += (y - lastPos[1]) * .1;
    yRot += (x - lastPos[0]) * .1;
  }
  if (rightDown) {
    for (int i = 0; i < 3; i++)
      cameraPos[i] *= pow(1.1, (y - lastPos[1]) * .1);
  }

  lastPos[0] = x;
  lastPos[1] = y;
  glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
  curProblem = key - '0';
  if (key == 'q' || key == 'Q' || key == 27) {
    exit(0);
  }
  glutPostRedisplay();
}

void reshape(int width, int height) {
  windowWidth = width;
  windowHeight = height;
  glutPostRedisplay();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(windowWidth, windowHeight);
  glutCreateWindow("HW2");

  glutDisplayFunc(display);
  glutMotionFunc(mouseMoved);
  glutMouseFunc(mouse);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);

  glutMainLoop();

  return 0;
}
