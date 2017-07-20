#pragma once

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtx/rotate_vector.hpp>

class CameraInterface
{
public :

	glm::mat4 Projection;
	glm::mat4 View;
	glm::mat4 VP;

	float near;
	float far;

	bool ProjectionChanged;
	bool ViewChanged;

	virtual glm::mat4 getViewProj() = 0;
};

class Camera : public CameraInterface
{
public :

	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 up;
	glm::vec3 right;

	float ratio;

	float fov;

	Camera();
   ~Camera();

   void translate(glm::vec3 translation);
   void translate(float x, float y, float z);

   void rotate(glm::vec3 anglesVec);
   void rotate(float x, float y, float z);
   void rotate(glm::vec3 axis, float angle);

   void setPosition(glm::vec3 pos);

   void lookAt(glm::vec3 point);

   void setPosTarg(glm::vec3 pos, glm::vec3 targ);

   void setFov(float FOV);
   void setRatio(float RATIO);

   void zoom(float z);										// Its more like changing FOV than zooming
	
	glm::mat4 getViewProj();
};

class CameraOrtho : public CameraInterface
{
private:

	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 up;

	float width;
	float height;

public:

	CameraOrtho();
	~CameraOrtho();

	void translate(glm::vec3 translation);
	void translate(float x, float y, float z);

	void rotate(glm::vec3 anglesVec);
	void rotate(float x, float y, float z);
	void rotate(glm::vec3 axis, float angle);

	void zoom(float z);

	void setViewDimmension(float w, float h);

	void setPosition(glm::vec3 pos);

	void lookAt(glm::vec3 point);

	void setPosTarg(glm::vec3 pos, glm::vec3 targ);

	glm::mat4 getViewProj();
};

class Camera2D : public CameraInterface
{
private :

	glm::vec2 position;
	glm::vec2 up;

	float width;
	float height;

public :

	Camera2D();
   ~Camera2D();

	void translate(glm::vec2 translation);
	void translate(float x, float y);

	void rotate(float angle);

	void zoom(float z);

	void setPosition(glm::vec2 pos);
	void setPosition(float x, float y);

	void setViewRegion(float left, float right, float top, float bottom);
	void setViewRegion(glm::vec2 a, glm::vec2 b);									// Left up corner , right down corner

	void setViewDimmension(float w, float h);

	glm::mat4 getViewProj();
};

