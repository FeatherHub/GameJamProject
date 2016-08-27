#include "GameManager.h"
#include "Object/Character.h"
#include "Object/CameraMan.h"
#include "Data/Constants.h"
#include "Data/Mapdata.h"
#include "UI\Dig.h"
#include "UI\/Flag.h"
#include "UI/JoyStick.h"

bool GameManager::init()
{
	if (Node::init() == false)
	{
		return false;
	}
	
	return true;
}

void GameManager::update(float delta)
{
	while (m_pRefCharacter->ActionQueueEmpty() == false)
	{
		CHARACTER_ACTION action = m_pRefCharacter->GetCharAction();

		//�̹� �ٸ� action�� �����ϰ� ������ 
		//�Է� ������ �Լ����� �� ��
		if (m_pRefCharacter->IsStatusRunning(CHARACTER_ACTION::DIG) ||
			m_pRefCharacter->IsStatusRunning(CHARACTER_ACTION::FLAG) ||
			m_pRefCharacter->IsStatusRunning(CHARACTER_ACTION::MOVE))
		{
			continue;
		}

		switch (action)
		{
		case CHARACTER_ACTION::DIG:
			CharDig();
			break;
		case CHARACTER_ACTION::FLAG:
			CharFlag();
			break;
		case CHARACTER_ACTION::MOVE:
			CharMove();
			break;
		}
	}
}

void GameManager::CharMove()
{
	const auto& charPos = m_pRefCharacter->getPosition();
	const auto& charDir = m_pRefCharacter->GetDirection();
	const auto& moveDelta = m_pRefdirDeltaPos[(int)charDir];
	const auto& movedPos = charPos + moveDelta;

	//TODO: ������ ��ȿ���� �ʴ� ��Ȳ���� �ִϸ��̼����� ������ ������
	
	//�� �ٱ����� ����������
	if (movedPos.x > m_pRefObjectTypeMap->width ||
		movedPos.y > m_pRefObjectTypeMap->height ||
		movedPos.x < 0 || movedPos.y < 0)
	{
		return;
	}

	//���� �浹 �ߴ�
	int charXPos = m_pRefCharMap->pos.x;
	int charYPos = m_pRefCharMap->pos.y;
	if (m_pRefObjectTypeMap->map[charXPos][charYPos] == MAP_OBJECT_TYPE::WALL)
	{
		return;
	}

	/*
	Note : ĳ������ ��ġ�� ĳ���� �ʿ����� ĳ���� ��ġ�� �����Ѵ�
	*/
	m_pRefCharacter->Move(moveDelta);
	m_pRefCharMap->UpdatePos(charDir);

	m_pCameraMan->Move(moveDelta);
}

void GameManager::CharDig()
{
	int charXPos = m_pRefCharMap->pos.x;
	int charYPos = m_pRefCharMap->pos.y;
	auto objectType = m_pRefObjectTypeMap->map[charXPos][charYPos];

	switch (objectType)
	{
	case MAP_OBJECT_TYPE::ROAD:
		OnRoad();
		break;
	case MAP_OBJECT_TYPE::HEART:
		OnHeart();
		break;
	case MAP_OBJECT_TYPE::NUMBER:
		OnNumber();
		break;
	}
}

void GameManager::CharFlag()
{
	int charXPos = m_pRefCharMap->pos.x;
	int charYPos = m_pRefCharMap->pos.y;
	auto objectType = m_pRefObjectTypeMap->map[charXPos][charYPos];

	if (objectType == MAP_OBJECT_TYPE::FLAG_ON_HEART ||
		objectType == MAP_OBJECT_TYPE::FLAG_ON_NUMBER ||
		objectType == MAP_OBJECT_TYPE::FLAG_ON_ROAD)
	{
		//Character -> ��� �̱� �ִϸ��̼� //���ϰ� �־�
		m_pRefObjectTypeMap->map[charXPos][charYPos] = (MAP_OBJECT_TYPE)
			((int)objectType - (int)MAP_OBJECT_TYPE::FLAG_DELTA);
	}
	else if(objectType == MAP_OBJECT_TYPE::HEART ||
		objectType == MAP_OBJECT_TYPE::NUMBER || 
		objectType == MAP_OBJECT_TYPE::ROAD)
	{
		//Character -> ��� �ű� �ִϸ��̼� //���ϰ� �־�
		m_pRefObjectTypeMap->map[charXPos][charYPos] = (MAP_OBJECT_TYPE)
			((int)objectType + (int)MAP_OBJECT_TYPE::FLAG_DELTA);
	}
}

void GameManager::InitUI()
{
	joyStick = JoyStick::create(CC_CALLBACK_1(GameManager::CallUI, this));
	this->addChild(joyStick);
	dig = Dig::create(CC_CALLBACK_1(GameManager::CallUI, this));
	this->addChild(dig);
	flag = Flag::create(CC_CALLBACK_1(GameManager::CallUI, this));
	this->addChild(flag);
}

/*
	UI �ݹ��� �޾Ƽ� ��Ȳ�� �°� ȣ����
	2016. 8. 27
	�ۼ��� : ������
*/
void GameManager::CallUI(Ref* sender)
{
	auto type = (Menu*)sender;
	switch (type->getTag())
	{
	case Constants::TAG_JOYSTICK_TOP:		m_pRefCharMap->UpdatePos(DIRECTION::UP);	break;
	case Constants::TAG_JOYSTICK_BOTTOM:	m_pRefCharMap->UpdatePos(DIRECTION::DOWN);	break;
	case Constants::TAG_JOYSTICK_LEFT:		m_pRefCharMap->UpdatePos(DIRECTION::LEFT);	break;
	case Constants::TAG_JOYSTICK_RIGHT:		m_pRefCharMap->UpdatePos(DIRECTION::RIGHT);	break;
	case Constants::TAG_FLAG_NUM:			m_pRefCharacter->Flag();					break;
	case Constants::TAG_DIG_NUM:			m_pRefCharacter->Dig();						break;
	}
}