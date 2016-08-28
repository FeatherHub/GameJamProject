#pragma once

/*
	2016. 8. 27.
	������ 
*/

#include "cocos2d.h"
#include "Utils\/Macro.h"

USING_NS_CC;

// �ϴ� ���Ƿ� ���ؼ� �±װ��� �ְڽ��ϴ�.

#define POS0 0
#define POS1 1
#define POS2 2
#define POS3 3

#define START_POS_1 Vec2 ( - 300, - 200 ) // ȭ�� ����
#define START_POS_2 Vec2 ( -100, -90 )	// ���� ũ�� ���̴� ���� �̰�
#define START_POS_3 Vec2 ( 40, -10 )
#define START_POS_4 Vec2 ( 150, 10 )
#define START_POS_5 Vec2 ( 200, 40 )

#define P_PATH1 "SelectScene/stage1.png"
#define P_PATH2 "SelectScene/stage2.png"
#define P_PATH3 "SelectScene/stage3.png"
#define P_PATH4 "SelectScene/stage4.png"
#define P_PATH5 "SelectScene/stage5.png"

class Stars : public Node
{
public:
	bool init();
	CREATE_FUNC_ARGS(Stars);
	void FadeOut();
	void FadeIn();
	void Disable() { m_stars->setEnabled(false); }
	void Enable() { m_stars->setEnabled(true); }
private:
	void generateStars();
	void MoveStar();
	void CallStar(Ref* sender);
	void CallRenew(Ref* sender);
private:
	CREATEWINSIZE
	ccMenuCallback m_callBack;
	Menu* m_stars;
};

