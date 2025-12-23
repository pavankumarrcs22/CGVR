#include <GL/glut.h>
#include <stdlib.h>

int n;   // number of recursive steps

/* Initial tetrahedron vertices */
GLfloat v[4][3] = {
    {0.0, 0.0, 1.0},
    {0.0, 0.9428, -0.3333},
    {-0.8165, -0.4714, -0.3333},
    {0.8165, -0.4714, -0.3333}
};

/* Draw one triangle */
void triangle(GLfloat *a, GLfloat *b, GLfloat *c)
{
    glBegin(GL_TRIANGLES);
    glVertex3fv(a);
    glVertex3fv(b);
    glVertex3fv(c);
    glEnd();
}

/* Draw tetrahedron */
void tetra(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d)
{
    glColor3f(1,0,0); triangle(a,b,c);
    glColor3f(0,1,0); triangle(a,c,d);
    glColor3f(0,0,1); triangle(a,d,b);
    glColor3f(1,1,0); triangle(b,d,c);
}

/* Recursive subdivision */
void divideTetra(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, int m)
{
    GLfloat ab[3], ac[3], ad[3], bc[3], bd[3], cd[3];

    if(m > 0)
    {
        for(int i=0;i<3;i++)
        {
            ab[i] = (a[i]+b[i])/2;
            ac[i] = (a[i]+c[i])/2;
            ad[i] = (a[i]+d[i])/2;
            bc[i] = (b[i]+c[i])/2;
            bd[i] = (b[i]+d[i])/2;
            cd[i] = (c[i]+d[i])/2;
        }

        divideTetra(a, ab, ac, ad, m-1);
        divideTetra(ab, b, bc, bd, m-1);
        divideTetra(ac, bc, c, cd, m-1);
        divideTetra(ad, bd, cd, d, m-1);
    }
    else
        tetra(a,b,c,d);
}

/* Display */
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0,0,-2);
    glRotatef(30,1,1,0);

    divideTetra(v[0], v[1], v[2], v[3], n);

    glFlush();
}

/* Initialization */
void init()
{
    glClearColor(1,1,1,1);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,1,1,10);

    glMatrixMode(GL_MODELVIEW);
}

/* Main */
int main(int argc, char** argv)
{
    printf("Enter number of recursive steps: ");
    scanf("%d",&n);

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("3D Sierpinski Gasket");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
