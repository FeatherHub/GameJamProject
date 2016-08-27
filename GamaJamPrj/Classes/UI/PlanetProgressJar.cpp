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
	percent = 0;

	generateJar();
	generateLabel();
	return true;
}

void PlanetProgressJar::generateJar()
{
	jar = Sprite::create(PATH::JAR_BASE + ".png");
	jar->setPosition(Vec2(0, 290));
	this->addChild(jar);

	light = Sprite::create("UI/Jar/light.png");
	light->setPosition(Vec2(0, 290));
	light->setOpacity(0);
	this->addChild(light);
}

void PlanetProgressJar::generateLabel()
{
	std::string str = StringUtils::toString(m_curHeart).c_str();
	str += "/" + StringUtils::toString(m_aimHeart);

	label = Label::createWithTTF(str, "Font/arial.ttf", 30);
	label->setPosition(0, 230);
	this->addChild(label);
}

void PlanetProgressJar::FindHeart()
{
	m_curHeart++;
	percent = (m_curHeart / (float)m_aimHeart) * 255;
	light->setOpacity(percent);

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(PATH2::GOT_HEART.c_str());
}
