#pragma once
#include "SceneBase.h"
class CreditScene:public SceneBase
{
private:
	int back_image;
public:
	CreditScene();
	virtual ~CreditScene();

	virtual void  Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};

