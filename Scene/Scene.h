#pragma once

enum class SCN_ID
{
	TITLE,
	MAIN,
	RESULT,
	MAX
};

#include <memory>
#include "../Input.h"

class Scene
{
public:
	Scene() {};
	virtual ~Scene() {};
	virtual void Init() = 0;
	virtual void Update(const Input& p) = 0;
	virtual const SCN_ID GetSceneID() const = 0;
};

