#include <GL/glut.h>
#include <stdlib.h>

int x1, y1, x2, y2;
int click = 0;
int W = 500, H = 500;

/* Draw a pixel */
void drawPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

/* Bresenham Line Algorithm */
void bresenham(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while (true)
    {
        drawPixel(x1, y1);

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

/* Mouse Input */
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        x1 = x;
        y1 = H - y;
        click = 1;
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        x2 = x;
        y2 = H - y;
        click = 2;
        glutPostRedisplay();
    }
}

/* Display */
void display()
{
    if (click == 2)
    {
        glColor3f(0, 0, 0);
        bresenham(x1, y1, x2, y2);
        click = 0;   // allow multiple lines
    }
    glFlush();
}

/* Initialization */
void init()
{
    glClearColor(1, 1, 1, 1);
    glColor3f(0, 0, 0);
    glPointSize(2.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, W, 0, H);
}

/* Main */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(W, H);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Line Drawing");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
