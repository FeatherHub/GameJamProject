#include "PlanetProgressJar.h"
#include "SimpleAudioEngine.h"
#include "Data/Constants.h"
#include "Data\/Constants2.h"

bool PlanetProgressJar::init(int pAimHeart)
{
	if (Node::init() == false)
	{
		return false;
	}
	m_aimHeart = pAimHeart;
	m_curHeart = 0;
	m_percent = 0;

	generateJar();
	generateLabel();
	return true;
}

void PlanetProgressJar::generateJar()
{
	m_sprJar = Sprite::create(PATH::JAR_BASE + ".png");
	m_sprJar->setPosition(Vec2(0, 290));
	this->addChild(m_sprJar);

	m_sprLight = Sprite::create("UI/Jar/light.png");
	m_sprLight->setPosition(Vec2(0, 290));
	m_sprLight->setOpacity(0);
	this->addChild(m_sprLight);
}

void PlanetProgressJar::generateLabel()
{
	std::string str = StringUtils::toString(m_curHeart).c_str();
	str += "/" + StringUtils::toString(m_aimHeart);

	m_label = Label::createWithTTF(str, "Font/arial.ttf", 30);
	m_label->setPosition(0, 230);
	this->addChild(m_label);
}

void PlanetProgressJar::FindHeart()
{
	m_curHeart++;

	m_percent = m_curHeart / (float)m_aimHeart * 255;
	m_sprLight->setOpacity(m_percent);

	std::string str = StringUtils::toString(m_curHeart).c_str();
	str += "/" + StringUtils::toString(m_aimHeart);
	m_label->setString(str);

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(PATH2::GOT_HEART.c_str());
}
