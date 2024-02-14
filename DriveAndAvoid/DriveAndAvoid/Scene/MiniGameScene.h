#pragma once

#include "SceneBase.h"

class MiniGameScene : public SceneBase
{
private:
    int background_image; // �w�i�摜
    int background_image1; // �w�i�摜2
    int currentImage;
 

public:
    MiniGameScene();
    virtual ~MiniGameScene();

    virtual void Initialize() override;
    virtual eSceneType Update() override;
    virtual void Draw() const override;
    virtual void Finalize() override;

    virtual eSceneType GetNowScene() const override;

    void DrawColoredBox(unsigned int color) const;

    
};