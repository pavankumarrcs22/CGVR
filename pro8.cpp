#include <GL/glut.h>
#include <stdio.h>

#define LEFT   1
#define RIGHT  2
#define BOTTOM 4
#define TOP    8

float xmin, ymin, xmax, ymax;          // Clipping window
float vxmin, vymin, vxmax, vymax;      // Viewport

int n;
float line[20][4];

/* Compute region code */
int computeCode(float x, float y)
{
    int code = 0;
    if (x < xmin) code |= LEFT;
    else if (x > xmax) code |= RIGHT;
    if (y < ymin) code |= BOTTOM;
    else if (y > ymax) code |= TOP;
    return code;
}

/* Cohen–Sutherland Algorithm */
int clip(float &x1, float &y1, float &x2, float &y2)
{
    int c1 = computeCode(x1, y1);
    int c2 = computeCode(x2, y2);

    while (1)
    {
        if (!(c1 | c2)) return 1;   // Trivial accept
        if (c1 & c2) return 0;      // Trivial reject

        float x, y;
        int c = c1 ? c1 : c2;

        if (c & TOP)
            x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1), y = ymax;
        else if (c & BOTTOM)
            x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1), y = ymin;
        else if (c & RIGHT)
            y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1), x = xmax;
        else
            y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1), x = xmin;

        if (c == c1) x1 = x, y1 = y, c1 = computeCode(x1, y1);
        else         x2 = x, y2 = y, c2 = computeCode(x2, y2);
    }
}

/* Window to Viewport Mapping */
float mapX(float x) {
    return vxmin + (x - xmin) * (vxmax - vxmin) / (xmax - xmin);
}
float mapY(float y) {
    return vymin + (y - ymin) * (vymax - vymin) / (ymax - ymin);
}

/* Display */
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    /* Clipping Window */
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();

    /* Viewport */
    glColor3f(0, 0, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(vxmin, vymin);
    glVertex2f(vxmax, vymin);
    glVertex2f(vxmax, vymax);
    glVertex2f(vxmin, vymax);
    glEnd();

    /* Clipped Lines */
    glColor3f(0, 1, 0);
    for (int i = 0; i < n; i++)
    {
        float x1 = line[i][0], y1 = line[i][1];
        float x2 = line[i][2], y2 = line[i][3];

        if (clip(x1, y1, x2, y2))
        {
            glBegin(GL_LINES);
            glVertex2f(mapX(x1), mapY(y1));
            glVertex2f(mapX(x2), mapY(y2));
            glEnd();
        }
    }

    glFlush();
}

/* Initialization */
void init()
{
    glClearColor(1,1,1,1);
    gluOrtho2D(0, 500, 0, 500);
}

/* Main */
int main(int argc, char** argv)
{
    printf("Enter clipping window xmin ymin xmax ymax:\n");
    scanf("%f%f%f%f", &xmin, &ymin, &xmax, &ymax);

    printf("Enter viewport xmin ymin xmax ymax:\n");
    scanf("%f%f%f%f", &vxmin, &vymin, &vxmax, &vymax);

    printf("Enter number of lines: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("Enter line %d (x1 y1 x2 y2): ", i + 1);
        scanf("%f%f%f%f",
              &line[i][0], &line[i][1],
              &line[i][2], &line[i][3]);
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Cohen–Sutherland Line Clipping");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
