#include <GL/glut.h>
#include <stdio.h>
#include <algorithm>
#include <windows.h>

#define MAX 100

int n, W = 500, H = 500;
float x[MAX], y[MAX], inter[MAX];
int m;

/* Draw a horizontal line */
void drawLine(float x1, float y1, float x2, float y2)
{
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
    glFlush();
}

/* Find intersection with scan line */
void edgeDetect(float x1, float y1, float x2, float y2, int yscan)
{
    if (y2 < y1) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    if (yscan > y1 && yscan < y2)
        inter[m++] = x1 + (yscan - y1) * (x2 - x1) / (y2 - y1);
}

/* Scan-line filling */
void scanFill()
{
    for (int yscan = 0; yscan <= H; yscan++)
    {
        m = 0;
        for (int i = 0; i < n; i++)
            edgeDetect(x[i], y[i],
                       x[(i + 1) % n], y[(i + 1) % n],
                       yscan);

        std::sort(inter, inter + m);

        for (int i = 0; i < m; i += 2)
            drawLine(inter[i], yscan, inter[i + 1], yscan);
    }
}

/* Display */
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw polygon boundary
    glColor3f(0, 0, 1);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < n; i++)
        glVertex2f(x[i], y[i]);
    glEnd();

    // Fill polygon
    glColor3f(1, 0, 0);
    scanFill();
}

/* Initialization */
void init()
{
    glClearColor(1,1,1,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, W, 0, H);
}

/* Main */
int main(int argc, char** argv)
{
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("Enter vertex %d (x y): ", i + 1);
        scanf("%f%f", &x[i], &y[i]);
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(W, H);
    glutCreateWindow("Scan-Line Polygon Fill");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
