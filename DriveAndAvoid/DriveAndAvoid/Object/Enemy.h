#pragma once

#include "../Utility/Vector2D.h"

class Enemy
{private:
public:
	Enemy();
	~Enemy();

	void Initialize();            //����������
	//void Updata(float speed);     //�X�V����
	void Updata(float speed);     //�X�V����
	void Draw()const;             //�`�揈��
	void Finalize();              //�I��������

	//int GetType()const;           //�^�C�v�擾
	//Vector2D GetLocation()const;  //�ʒu���̎擾
	//Vector2D GetBoxSize()const;   //�����蔻��̑傫�����擾
};

