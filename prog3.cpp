#include <GL/glut.h>

float angle = 0.0;

/* Draw Rectangle with 4 colors */
void drawRect()
{
    glBegin(GL_QUADS);
    glColor3f(1,0,0); glVertex2f(-0.5,-0.5);  // Red
    glColor3f(0,1,0); glVertex2f( 0.5,-0.5);  // Green
    glColor3f(0,0,1); glVertex2f( 0.5, 0.5);  // Blue
    glColor3f(1,1,0); glVertex2f(-0.5, 0.5);  // Yellow
    glEnd();
}

/* First Window: Static Rectangle */
void display1()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    drawRect();
    glutSwapBuffers();
}

/* Second Window: Rotating Rectangle */
void display2()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(angle, 0, 0, 1);
    drawRect();
    glutSwapBuffers();
}

/* Animation */
void spin()
{
    angle += 1.0;
    if (angle > 360) angle -= 360;
    glutPostRedisplay();
}

/* Initialization */
void init()
{
    glClearColor(1,1,1,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1,1,-1,1);
    glMatrixMode(GL_MODELVIEW);
}

/* Main */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    /* Window 1 */
    glutInitWindowSize(400,400);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Static Rectangle");
    init();
    glutDisplayFunc(display1);

    /* Window 2 */
    glutInitWindowPosition(550,100);
    glutCreateWindow("Rotating Rectangle");
    init();
    glutDisplayFunc(display2);
    glutIdleFunc(spin);

    glutMainLoop();
    return 0;
}
