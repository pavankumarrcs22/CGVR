#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

int xc, yc, r;
int click = 0;
int W = 500, H = 500;

/* Draw a pixel */
void drawPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

/* Draw all 8 symmetric points */
void plotCircle(int xc, int yc, int x, int y)
{
    drawPixel(xc + x, yc + y);
    drawPixel(xc - x, yc + y);
    drawPixel(xc + x, yc - y);
    drawPixel(xc - x, yc - y);
    drawPixel(xc + y, yc + x);
    drawPixel(xc - y, yc + x);
    drawPixel(xc + y, yc - x);
    drawPixel(xc - y, yc - x);
}

/* Bresenham / Midpoint Circle Algorithm */
void bresenhamCircle(int xc, int yc, int r)
{
    int x = 0, y = r;
    int d = 3 - 2 * r;

    while (x <= y)
    {
        plotCircle(xc, yc, x, y);

        if (d < 0)
            d += 4 * x + 6;
        else
        {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

/* Mouse Input */
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        xc = x;
        yc = H - y;
        click = 1;
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        int xr = x;
        int yr = H - y;
        r = sqrt((xr - xc)*(xr - xc) + (yr - yc)*(yr - yc));
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
        bresenhamCircle(xc, yc, r);
        click = 0;   // allow multiple circles
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
    glutCreateWindow("Bresenham Circle Drawing");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
