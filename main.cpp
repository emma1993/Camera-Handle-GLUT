/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
#include <algorithm>
#include <stdlib.h>
#define Cos(th) cos(M_PI/180*(th))
#define Sin(th) sin(M_PI/180*(th))
#define DEF_D 5
#include "Camara.h"
static GLfloat light0_position[] = {1.0,1.0,1.0,0.0};
static GLfloat mat_specular[] = {0.2,0.2,0.2,0.2};
static GLfloat mat_shininess[] = {50.0};
Camara cam;
bool tecla[256];
bool shift = false;
bool activar = false;
const float velocidad = 0.005;
const float velocidadRot = M_PI/180*0.2;
bool mouseIzq = false;
bool mouseDer = false;
GLint ancho=1200;
GLint alto=500;
void DrawSphere(GLfloat fRadius, GLint iSlices, GLint iStacks)
{
    GLfloat drho = (GLfloat)(3.141592653589) / (GLfloat) iStacks;
    GLfloat dtheta = 2.0f * (GLfloat)(3.141592653589) / (GLfloat) iSlices;
    GLfloat ds = 1.0f / (GLfloat) iSlices;
    GLfloat dt = 1.0f / (GLfloat) iStacks;
    GLfloat t = 1.0f;
    GLfloat s = 0.0f;
    GLint i, j;     // Looping variables

    for (i = 0; i < iStacks; i++)
        {
        GLfloat rho = (GLfloat)i * drho;
        GLfloat srho = (GLfloat)(sin(rho));
        GLfloat crho = (GLfloat)(cos(rho));
        GLfloat srhodrho = (GLfloat)(sin(rho + drho));
        GLfloat crhodrho = (GLfloat)(cos(rho + drho));
        glBegin(GL_TRIANGLE_STRIP);
        s = 0.0f;
        for ( j = 0; j <= iSlices; j++)
            {
            GLfloat theta = (j == iSlices) ? 0.0f : j * dtheta;
            GLfloat stheta = (GLfloat)(-sin(theta));
            GLfloat ctheta = (GLfloat)(cos(theta));

            GLfloat x = stheta * srho;
            GLfloat y = ctheta * srho;
            GLfloat z = crho;

            glTexCoord2f(s, t);
            glNormal3f(x, y, z);
            glVertex3f(x * fRadius, y * fRadius, z * fRadius);

            x = stheta * srhodrho;
            y = ctheta * srhodrho;
            z = crhodrho;
            glTexCoord2f(s, t - dt);
            s += ds;
            glNormal3f(x, y, z);
            glVertex3f(x * fRadius, y * fRadius, z * fRadius);
            }
        glEnd();

        t -= dt;
        }
}
void keyboard(unsigned char key, int x, int y)
{
    if(key == 27)
    {
        exit(0);
    }

    if(key == ' ')
    {
        activar = !activar;

        if(activar)
        {
            glutSetCursor(GLUT_CURSOR_NONE);
            glutWarpPointer(ancho/2, alto/2);
        }
        else
        {
            glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        }
    }

    if(glutGetModifiers() == GLUT_ACTIVE_SHIFT)
    {
        shift = true;
    }
    else
    {
        shift = false;
    }

    tecla[key] = true;
}

void keyboardUp(unsigned char key, int x, int y)
{
    tecla[key] = false;
}

void timer(int value)
{
    if(activar)
    {
        if(tecla['w'] || tecla['W'])
        {
            cam.mover(velocidad);
        }
        else if(tecla['s'] || tecla['S'])
        {
            cam.mover(-velocidad);
        }
        else if(tecla['a'] || tecla['A'])
        {
            cam.lateral(velocidad);
        }
        else if(tecla['d'] || tecla['D'])
        {
            cam.lateral(-velocidad);
        }
        else if(mouseIzq)
        {
            cam.volar(-velocidad);
        }
        else if(mouseDer)
        {
            cam.volar(velocidad);
        }
    }

    glutTimerFunc(1, timer, 0);
}
void mouse(int button, int state, int x, int y)
{
    if(state == GLUT_DOWN)
    {
        if(button == GLUT_LEFT_BUTTON)
        {
            mouseIzq = true;
        }
        else if(button == GLUT_RIGHT_BUTTON)
        {
            mouseDer = true;
        }
    }
    else if(state == GLUT_UP)
    {
        if(button == GLUT_LEFT_BUTTON)
        {
            mouseIzq = false;
        }
        else if(button == GLUT_RIGHT_BUTTON)
        {
            mouseDer = false;
        }
    }
}

void mouseMov(int x, int y)
{
    static bool just_warped = false;
    if(just_warped)
    {
        just_warped = false;
        return;
    }

    if(activar)
    {
        int dx = x - ancho/2;
        int dy = y - alto/2;

        if(dx)
        {
            cam.rotarYaw(velocidadRot*dx);
        }

        if(dy)
        {
            cam.rotarPitch(velocidadRot*dy);
        }

        glutWarpPointer(ancho/2, alto/2);

        just_warped = true;
    }
}
void cilindro(float x,float y,float z,int slices,float HEIGHT,float r){
    glBegin(GL_TRIANGLE_FAN);
    // bottom circle
     glNormal3f(x,y,z);
    glVertex3f(x,y,z);
    for(int i=0 ; i<=slices; i++){
        glNormal3f(x + cos((float)i/slices * 2 *M_PI)*r,y, z+sin((float)i/slices * 2 * M_PI)*r);
        glVertex3f(x + cos((float)i/slices * 2 *M_PI)*r,y, z+sin((float)i/slices * 2 * M_PI)*r);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    //top circle
    glVertex3f(x,y + HEIGHT,z);
    for(int i=0; i<=slices; i++){
        glNormal3f(x + cos((float)i/slices * 2 *M_PI)*r,y+ HEIGHT, z+sin((float)i/slices * 2 * M_PI)*r);
        glVertex3f(x + cos((float)i/slices * 2 *M_PI)*r,y+ HEIGHT, z+sin((float)i/slices * 2 * M_PI)*r);
    }
    glEnd();
    // the rest
    glBegin(GL_TRIANGLE_STRIP);
    for(int i=0; i<=slices; i++)
    {
        glNormal3f(x + cos((float)i/slices * 2 *M_PI)*r,y, z+sin((float)i/slices * 2 * M_PI)*r);
        glVertex3f(x + cos((float)i/slices * 2 *M_PI)*r,y, z+sin((float)i/slices * 2 * M_PI)*r);
        glNormal3f(x + cos((float)i/slices * 2 *M_PI)*r,y+ HEIGHT, z+sin((float)i/slices * 2 *M_PI)*r);
        glVertex3f(x + cos((float)i/slices * 2 *M_PI)*r,y+ HEIGHT, z+sin((float)i/slices * 2 *M_PI)*r);
    }
    glEnd();
}
void cono(float x,float x1,float y,float y1){
    glBegin(GL_TRIANGLES);
    for (int k=0;k<=360;k+=DEF_D){
      glColor3f(0.0,0.0,1.0);
      glNormal3f(0,0,1);
      glVertex3f(0,0,1);
      glColor3f(0.0,1.0,1.0);
      glNormal3f(Cos(k),Sin(k),0);
      glVertex3f(Cos(k),Sin(k),0);
      glColor3f(1.0,0.0,0.0);
      glNormal3f(Cos(k+DEF_D),Sin(k+DEF_D),0);
      glVertex3f(Cos(k+DEF_D),Sin(k+DEF_D),0);
    }
    glEnd();

    /* bottom circle */
    /* rotate back */
    glRotated(90,1,0,0);
    glBegin(GL_TRIANGLES);
    for (int k=0;k<=360;k+=DEF_D) {
      glColor3f(1.0,0.0,0.0);
      glNormal3f(0,0,0);
      glVertex3f(0,0,0);
      glColor3f(1.0,0.0,1.0);
      glNormal3f(Cos(k),0,Sin(k));
      glVertex3f(Cos(k),0,Sin(k));
      glColor3f(1.0,1.0,0.0);
      glNormal3f(Cos(k+DEF_D),0,Sin(k+DEF_D));
      glVertex3f(Cos(k+DEF_D),0,Sin(k+DEF_D));
    }
    glEnd();
}

void drawTorus(float R, float r, int N, int n)
{
    int maxn= 1000; // max precision
    n=std::min(n,maxn-1);
    N=std::min(N,maxn-1);
    float rr=1.5f*r;
    double dv=2*M_PI/n;
    double dw=2*M_PI/N;
    double v=0.0f;
    double w=0.0f;
    // outer loop
    while(w<2*M_PI+dw)
    {
        v=0.0f;
        glBegin(GL_TRIANGLE_STRIP);
        // inner loop
        while(v<2*M_PI+dv)
        {
            glNormal3d(
                    (R+rr*cos(v))*cos(w)-(R+r*cos(v))*cos(w),
                    (R+rr*cos(v))*sin(w)-(R+r*cos(v))*sin(w),
                    (rr*sin(v)-r*sin(v)));
            glVertex3d((R+r*cos(v))*cos(w),
                       (R+r*cos(v))*sin(w),
                        r*sin(v));
            glNormal3d(
                    (R+rr*cos(v+dv))*cos(w+dw)-(R+r*cos(v+dv))*cos(w+dw),
                    (R+rr*cos(v+dv))*sin(w+dw)-(R+r*cos(v+dv))*sin(w+dw),
                    rr*sin(v+dv)-r*sin(v+dv));
            glVertex3d((R+r*cos(v+dv))*cos(w+dw),
                       (R+r*cos(v+dv))*sin(w+dw),
                        r*sin(v+dv));
            v+=dv;
        } // inner loop
        glEnd();
        w+=dw;
    } //outer loop
}
/* GLUT callback Handlers */
void DrawEllipsoid(unsigned int uiStacks, unsigned int uiSlices, float fA, float fB, float fC)
{
	float tStep = (M_PI) / (float)uiSlices;
	float sStep = (M_PI) / (float)uiStacks;
	glPolygonMode(GL_FRONT, GL_LINE);
	glNormal3f(0,0,-1);
	for(float t = -M_PI/2; t <= (M_PI/2)+.0001; t += tStep)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for(float s = -M_PI; s <= M_PI+.0001; s += sStep)
		{
		    glNormal3f(fA * cos(t) * cos(s), fB * cos(t) * sin(s),fC * sin(t));
			glVertex3f(fA * cos(t) * cos(s), fB * cos(t) * sin(s), fC * sin(t));
			glNormal3f(fA * cos(t+tStep) * cos(s),  fB * cos(t+tStep) * sin(s),fC * sin(t+tStep));
			glVertex3f(fA * cos(t+tStep) * cos(s), fB * cos(t+tStep) * sin(s), fC * sin(t+tStep));
		}
		glEnd();
	}
}
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    cam.refresh();
    glColor3d(1,0,0);

    glPushMatrix();
    //glRotatef(90,1.0,0.0,0.0);
    glTranslatef(0,0,-20);
    //glScalef(0.2,0.2,0.2);
    //`drawTorus(3,1,7,7);
    //cilindro(0,0,0,10,4,4);
    //cono(10,10,10,10);
    //DrawSphere(5,10,10);
    DrawEllipsoid(5,5,5,1,2);
    //glutSolidSphere(10,5,5);
    glPopMatrix();
    glutSwapBuffers();
}

static void resize(int width, int height)
{
    ancho = width;
    alto = height;

    glViewport(0,0,(GLsizei)width,(GLsizei)height);
    glMatrixMode (GL_PROJECTION);

    glLoadIdentity ();
    gluPerspective(60.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);
    glMatrixMode (GL_MODELVIEW);
}
void initgl()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0,0.0,0.0,1.0);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);

}
static void idle(void)
{
    glutPostRedisplay();
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Bodegon");
    initgl();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMov);
    glutPassiveMotionFunc(mouseMov);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutIdleFunc(idle);

    glutTimerFunc(1, timer, 0);
    glutMainLoop();

    return EXIT_SUCCESS;
}
