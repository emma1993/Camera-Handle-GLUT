#ifndef CAMARA_H
#define CAMARA_H

struct Point3D
{
    float x,y,z;

    Point3D(float x,float y,float z)
    {
        this->x=x;
        this->y=y;
        this->z=z;
    }
    Point3D()
    {
        this->x=0;
        this->y=0;
        this->z=0;
    }
};

class Camara
{
public:
	Camara() { init(); }
	~Camara(){}

	void init();
	void refresh();
	void setPos(Point3D& p);
    Point3D getPos();
    Point3D getDireccion();
	void setYaw(float angulo);
	void setPitch(float angulo);

	// Navigation
	void mover(float incr);
	void lateral(float incr);
	void volar(float incr);
	void rotarYaw(float angulo);
	void rotarPitch(float angulo);

private:
	Point3D posicion;
    Point3D direccion;
	float yaw, pitch;
	float lateralX,lateralZ;
};

#endif
