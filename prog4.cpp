#include <GL/glut.h>
#include <math.h>

float angle = 0;

/* ---------- Cylinder (Circle Extrusion) ---------- */
void drawCylinder()
{
    float r = 0.5, h = 1.0;
    int slices = 50;

    glBegin(GL_QUAD_STRIP);
    for(int i = 0; i <= slices; i++)
    {
        float theta = 2 * 3.14 * i / slices;
        float x = r * cos(theta);
        float y = r * sin(theta);

        glVertex3f(x, y, 0);
        glVertex3f(x, y, h);
    }
    glEnd();
}

/* ---------- Parallelepiped (Quadrilateral Extrusion) ---------- */
void drawParallelepiped()
{
    float z = 0.5;

    glBegin(GL_QUADS);

    // Front face
    glVertex3f(-0.5,-0.5,0);
    glVertex3f( 0.5,-0.5,0);
    glVertex3f( 0.5, 0.5,0);
    glVertex3f(-0.5, 0.5,0);

    // Back face
    glVertex3f(-0.5,-0.5,z);
    glVertex3f( 0.5,-0.5,z);
    glVertex3f( 0.5, 0.5,z);
    glVertex3f(-0.5, 0.5,z);

    // Sides
    glVertex3f(-0.5,-0.5,0); glVertex3f(-0.5, 0.5,0);
    glVertex3f(-0.5, 0.5,z); glVertex3f(-0.5,-0.5,z);

    glVertex3f(0.5,-0.5,0); glVertex3f(0.5, 0.5,0);
    glVertex3f(0.5, 0.5,z); glVertex3f(0.5,-0.5,z);

    glVertex3f(-0.5,-0.5,0); glVertex3f(0.5,-0.5,0);
    glVertex3f(0.5,-0.5,z); glVertex3f(-0.5,-0.5,z);

    glVertex3f(-0.5,0.5,0); glVertex3f(0.5,0.5,0);
    glVertex3f(0.5,0.5,z); glVertex3f(-0.5,0.5,z);

    glEnd();
}

/* ---------- Display Window 1 (Cylinder) ---------- */
void display1()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0,0,-3);
    glRotatef(angle,1,1,0);
    glColor3f(0,0,1);
    drawCylinder();
    glutSwapBuffers();
}

/* ---------- Display Window 2 (Parallelepiped) ---------- */
void display2()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0,0,-3);
    glRotatef(angle,1,1,0);
    glColor3f(1,0,0);
    drawParallelepiped();
    glutSwapBuffers();
}

/* ---------- Animation ---------- */
void spin()
{
    angle += 0.5;
    glutPostRedisplay();
}

/* ---------- Initialization ---------- */
void init()
{
    glClearColor(1,1,1,1);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,1,1,10);
    glMatrixMode(GL_MODELVIEW);
}

/* ---------- Main ---------- */
int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    /* Window 1: Cylinder */
    glutInitWindowSize(400,400);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Cylinder");
    init();
    glutDisplayFunc(display1);

    /* Window 2: Parallelepiped */
    glutInitWindowPosition(550,100);
    glutCreateWindow("Parallelepiped");
    init();
    glutDisplayFunc(display2);
    glutIdleFunc(spin);

    glutMainLoop();
    return 0;
}
