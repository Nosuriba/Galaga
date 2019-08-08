#pragma once

#include <memory>
#include "../Game.h"
#include "../Input.h"
#include "../AudioMng.h"
#include "../Common/ImageMng.h"

enum class SCN_ID
{
	TITLE,
	MAIN,
	RESULT,
	MAX
};

class Scene
{
public:
	Scene() {};
	virtual ~Scene() {};
	virtual void Init() = 0;
	virtual unique_scene Update(unique_scene scene, const Input& p) = 0;
	virtual const SCN_ID GetSceneID() const = 0;
};

