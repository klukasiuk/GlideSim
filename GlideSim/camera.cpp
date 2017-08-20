#include "camera.h"


Camera::Camera()
{
	position  = glm::vec3(0, 0, 0);
	direction = glm::vec3(0, 0, 1);
	up        = glm::vec3(0, 1, 0);
	right     = glm::vec3(-1, 0, 0);

	fov = 60;
	ratio = 4.0f / 3.0f;

	near = 0.1f;
	far = 3000.0f;

	projectionChanged = false;
	viewChanged       = false;

	Projection = glm::perspective(glm::radians(fov), ratio, near, far);
	View = glm::lookAt(position, position + direction, up);

	VP = Projection * View;
}

Camera::~Camera()
{
}

void Camera::move(float forward, float upward, float to_right)
{
	position = position + forward*direction + upward*up + to_right*right;

	viewChanged = true;
}

void Camera::translate(glm::vec3 translation)
{
	position += translation;

	viewChanged = true;
}

void Camera::translate(float x, float y, float z)
{
	position.x += x;
	position.y += y;
	position.z += z;

	viewChanged = true;
}

void Camera::rotate(glm::vec3 anglesVec)
{
	direction = glm::rotate(direction, glm::radians(anglesVec.y),right);
	direction = glm::rotate(direction, glm::radians(anglesVec.z),up);

	right = -glm::cross(up, direction);

	viewChanged = true;
}

void Camera::rotate(float x, float y, float z)
{
	direction = glm::rotate(direction, glm::radians(y), right);
	direction = glm::rotate(direction, glm::radians(z),up);

	right = -glm::cross(up, direction);

	viewChanged = true;
}

void Camera::rotate(glm::vec3 axis, float angle)
{
	direction =  glm::rotate(direction, glm::radians(angle), axis);

	right = -glm::cross(up, direction);

	viewChanged = true;
}

void Camera::setPosition(glm::vec3 pos)
{
	position = pos;

	viewChanged = true;
}

void Camera::lookAt(glm::vec3 point)
{
	direction = point - position;
	direction = glm::normalize(direction);

	right = -glm::cross(up, direction);

	viewChanged = true;
}

void Camera::setPosTarg(glm::vec3 pos, glm::vec3 targ)
{
	position = pos;

	direction = targ - pos;
	direction = glm::normalize(direction);

	viewChanged = true;
}

void Camera::setFov(float FOV)
{
	fov = FOV;

	projectionChanged = true;
}

void Camera::setRatio(float RATIO)
{
	ratio = RATIO;

	projectionChanged = true;
}

void Camera::zoom(float z)
{
	if (z < 0.0001f && z > -0.0001f)				// Zoom cannot be zero
		z = 1.0f;

	z = 1.0f / z;

	fov *= z;

	projectionChanged = true;
}

glm::vec3 Camera::getPos()
{
	return position;
}

glm::mat4 Camera::getView()
{
	glm::mat4 vp = getViewProj();

	return View;
}

glm::mat4 Camera::getProj()
{
	glm::mat4 vp = getViewProj();

	return Projection;
}

glm::mat4 Camera::getViewProj()
{
	if (projectionChanged == false && viewChanged == false)
		return VP;

	if (projectionChanged)
	{
		Projection = glm::perspective(glm::radians(fov), ratio, near, far);
		projectionChanged = false;
	}

	if (viewChanged)
	{
		View = glm::lookAt(position, position + direction, up);
		viewChanged = false;
	}

	VP = Projection * View;

	return VP;
}



CameraOrtho::CameraOrtho()
{
	position  = glm::vec3(0, 0, 0);
	direction = glm::vec3(0, 0, 1);
	up        = glm::vec3(0, 1, 0);
	right     = glm::vec3(-1, 0, 0);

	width  = 10;
	height = 10;

	near = 0.1f;
	far = 100.0f;

	projectionChanged = false;
	viewChanged = false;

	Projection = glm::ortho(-0.5f*width, 0.5f*width, -0.5f*height, 0.5f*height, near, far);
	View = glm::lookAt(position, direction, up);

	VP = Projection * View;
}

CameraOrtho::~CameraOrtho()
{
}

void CameraOrtho::move(float forward, float upward, float to_right)
{
	position = position + forward*direction + upward*up + to_right*right;

	viewChanged = true;
}

void CameraOrtho::translate(glm::vec3 translation)
{
	position += translation;

	viewChanged = true;
}

void CameraOrtho::translate(float x, float y, float z)
{
	position.x += x;
	position.y += y;
	position.z += z;

	viewChanged = true;
}

void CameraOrtho::rotate(glm::vec3 anglesVec)
{
	direction = glm::rotate(direction, glm::radians(anglesVec.y), right);
	direction = glm::rotate(direction, glm::radians(anglesVec.z), up);

	right = -glm::cross(up, direction);

	viewChanged = true;
}

void CameraOrtho::rotate(float x, float y, float z)
{
	direction = glm::rotate(direction, glm::radians(y), right);
	direction = glm::rotate(direction, glm::radians(z), up);

	right = -glm::cross(up, direction);

	viewChanged = true;
}

void CameraOrtho::rotate(glm::vec3 axis, float angle)
{
	direction = glm::rotate(direction, glm::radians(angle), axis);

	right = -glm::cross(up, direction);

	viewChanged = true;
}

void CameraOrtho::zoom(float z)
{
	if (z < 0.0001f && z > -0.0001f)				// Zoom cannot be zero
	z = 1.0f;

	z = 1.0f/ z;

	width  *= z;
	height *= z;

	projectionChanged = true;
}

void CameraOrtho::setViewDimmension(float w, float h)
{
	width = fabs(w);
	height = fabs(h);

	projectionChanged = true;
}

void CameraOrtho::setPosition(glm::vec3 pos)
{
	position = pos;

	viewChanged = true;
}

void CameraOrtho::lookAt(glm::vec3 point)
{
	direction = point - position;
	direction = glm::normalize(direction);

	viewChanged = true;
}

void CameraOrtho::setPosTarg(glm::vec3 pos, glm::vec3 targ)
{
	position = pos;

	direction = targ - pos;
	direction = glm::normalize(direction);

	viewChanged = true;
}

glm::mat4 CameraOrtho::getViewProj()
{
	if (projectionChanged == false && viewChanged == false)
		return VP;

	if (projectionChanged)
	{
		Projection = glm::ortho(-0.5f*width, 0.5f*width, -0.5f*height, 0.5f*height, near, far);
		projectionChanged = false;
	}

	if (viewChanged)
	{
		View = glm::lookAt(position, direction, up);
		viewChanged = false;
	}

	VP = Projection * View;

	return VP;
}


// 2D camera with lefthanded coordinates ( positive z is screen space)
Camera2D::Camera2D()
{
	position = glm::vec2(0, 0);
	up		 = glm::vec2(0, 1);

	width = 10;
	height = 10;

	near = 0.1f;
	far = 100.0f;

	projectionChanged = false;
	viewChanged = false;

	Projection = glm::orthoLH(-0.5f*width, 0.5f*width, -0.5f*height, 0.5f*height, near, far);
	View = glm::lookAtLH(glm::vec3(position.x,position.y,0), glm::vec3(0,0,1), glm::vec3(up.x,up.y, 0));

	VP = Projection * View;
}

Camera2D::~Camera2D()
{
}

void Camera2D::translate(glm::vec2 translation)
{
	position += translation;

	viewChanged = true;
}

void Camera2D::translate(float x, float y)
{
	position.x += x;
	position.y += y;

	viewChanged = true;
}

void Camera2D::rotate(float angle)
{
	up = glm::rotate(up, angle);

	viewChanged = true;
}

void Camera2D::zoom(float z)
{
	if (z < 0.0001f && z > -0.0001f)				// Zoom cannot be zero
		z = 1.0f;

	z = 1.0f / z;

	width  *= z;
	height *= z;

	projectionChanged = true;
}

void Camera2D::setPosition(glm::vec2 pos)
{
	position = pos;

	viewChanged = true;
}

void Camera2D::setPosition(float x, float y)
{
	position.x = x;
	position.y = y;

	viewChanged = true;
}

void Camera2D::setViewRegion(float left, float right, float top, float bottom)
{
	position.x = left + 0.5f*(right - left);
	position.y = bottom + 0.5f*(top - bottom);

	width = right - left;
	height = top - bottom;

	viewChanged = true;
	projectionChanged = true;
}

void Camera2D::setViewRegion(glm::vec2 a, glm::vec2 b)
{
	position.x = a.x + 0.5f*(b.x - a.x);
	position.y = b.y + 0.5f*(a.y - b.y);

	width = fabs(b.x - a.x);
	height = fabs(a.y - b.y);

	viewChanged = true;
	projectionChanged = true;
}

void Camera2D::setViewDimmension(float w, float h)
{
	width  = fabs(w);
	height = fabs(h);

	projectionChanged = true;
}

glm::mat4 Camera2D::getViewProj()
{
	if (projectionChanged == false && viewChanged == false)
		return VP;

	if (projectionChanged)
	{
		Projection = glm::orthoLH(-0.5f*width, 0.5f*width, -0.5f*height, 0.5f*height, near, far);
		projectionChanged = false;
	}

	if (viewChanged)
	{
		View = glm::lookAtLH(glm::vec3(position.x, position.y, 0), glm::vec3(0, 0, 1), glm::vec3(up.x, up.y, 0));
		viewChanged = false;
	}

	VP = Projection * View;

	return VP;
}