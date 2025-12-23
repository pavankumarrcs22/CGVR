#include <GL/glut.h>
#include <math.h>

#define PI 3.14159

/* Draw Sphere using latitude-longitude method */
void drawSphere()
{
    int lat, lon;
    float radius = 1.0;

    for(lat = -80; lat <= 80; lat += 20)
    {
        float lat1 = PI * lat / 180.0;
        float lat2 = PI * (lat + 20) / 180.0;

        glBegin(GL_QUAD_STRIP);
        for(lon = -180; lon <= 180; lon += 20)
        {
            float lonRad = PI * lon / 180.0;

            glVertex3f(radius * cos(lat1) * sin(lonRad),
                       radius * sin(lat1),
                       radius * cos(lat1) * cos(lonRad));

            glVertex3f(radius * cos(lat2) * sin(lonRad),
                       radius * sin(lat2),
                       radius * cos(lat2) * cos(lonRad));
        }
        glEnd();
    }
}

/* Display */
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0, 0, -3);
    glRotatef(30, 1, 1, 0);
    glColor3f(0, 0, 1);

    drawSphere();

    glFlush();
}

/* Initialization */
void init()
{
    glClearColor(1,1,1,1);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 10);

    glMatrixMode(GL_MODELVIEW);
}

/* Main */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("3D Sphere Approximation");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
