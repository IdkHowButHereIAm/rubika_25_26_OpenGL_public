#pragma once

#include "Camera.h"

namespace threshold
{
	void init();
	void update(float deltaTime);
	void updateCamera(float deltaTime, camera::Direction direction);
	void updateCameraRot(float xoffset, float yoffset);
	void updateCameraZoom(float yoffset);
	void draw();
	void destroy();
}
