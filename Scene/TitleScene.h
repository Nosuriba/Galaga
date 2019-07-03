#pragma once
#include "Scene.h"

class TitleScene :
	public Scene
{
public:
	TitleScene();
	~TitleScene();

	void Init() override;
	unique_scene Update(unique_scene scene, const Input& p) override;
	const SCN_ID GetSceneID() const override;
};

