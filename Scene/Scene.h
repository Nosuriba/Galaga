#pragma once

#include <memory>
#include "../Game.h"
#include "../AudioMng.h"
#include "../Common/ImageMng.h"
#include "../Input/InputState.h"

class Scene
{
public:
	Scene() {};
	virtual ~Scene() {};
	virtual void Init() = 0;
	virtual unique_scene Update(unique_scene scene, const std::unique_ptr<InputState>& p) = 0;
};

