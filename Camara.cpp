#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "Camara.h"

void Camara::init()
{
	yaw = 0.0;
	pitch = 0.0;
	posicion.x = 0;
	posicion.y = 0;
	posicion.z = 0;
}

void Camara::refresh()
{
	direccion.x = cos(yaw)*cos(pitch);
	direccion.y = sin(pitch);
	direccion.z = sin(yaw)*cos(pitch);

	lateralX = cos(yaw - M_PI_2);
	lateralZ = sin(yaw - M_PI_2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(posicion.x, posicion.y, posicion.z,
           posicion.x + direccion.x, posicion.y + direccion.y, posicion.z + direccion.z,
           0.0,1.0,0.0);
}

void Camara::setPos(Point3D& p)
{
	posicion.x = p.x;
	posicion.y = p.y;
	posicion.z = p.z;
	refresh();
}

Point3D Camara::getPos()
{
    return posicion;
}

Point3D Camara::getDireccion()
{
    return direccion;
}

void Camara::mover(float incr)
{
    float lx = cos(yaw)*cos(pitch);
    float ly = sin(pitch);
    float lz = sin(yaw)*cos(pitch);

	posicion.x = posicion.x + incr*lx;
	posicion.y = posicion.y + incr*ly;
	posicion.z = posicion.z + incr*lz;
	refresh();
}

void Camara::lateral(float incr)
{
	posicion.x = posicion.x + incr*lateralX;
	posicion.z = posicion.z + incr*lateralZ;
	refresh();
}

void Camara::volar(float incr)
{
	posicion.y = posicion.y + incr;
	refresh();
}

void Camara::rotarYaw(float angulo)
{
	yaw += angulo;
	refresh();
}

void Camara::rotarPitch(float angulo)
{
    const float limit = 89.0 * M_PI/180.0;
	pitch += angulo;

    if(pitch < -limit)
        pitch = -limit;

    if(pitch > limit)
        pitch = limit;

	refresh();
}

void Camara::setYaw(float angulo)
{
	yaw = angulo;
	refresh();
}

void Camara::setPitch(float angulo)
{
    pitch = angulo;
    refresh();
}
