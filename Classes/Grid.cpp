#include "Grid.h"

using namespace cocos2d;

const int ROWS = 8;
const int COLUMNS = 10;

bool Grid::init()
{
	if (!Node::init())
	{
		return false;
	}

	generationCount = 0;
	populationCount = 0;

	return true;
}

void Grid::onEnter()
{
	Node::onEnter();

	this->setupGrid();

	this->setupTouchHandling();
}

void Grid::setupGrid()
{
	Sprite* gridSprite = this->getChildByName<Sprite*>("grid");
	cellWidth = gridSprite->getContentSize().width / float(COLUMNS);
	cellHeight = gridSprite->getContentSize().height / float(ROWS);

	gridArray.reserve(ROWS * COLUMNS);

	for (int row = 0; row < ROWS; ++row)
	{
		for (int col = 0; col < COLUMNS; ++col)
		{
			Creature* creature = Creature::create();

			creature->setAnchorPoint(Vec2(0.0f, 0.0f));
			creature->setPosition(cellWidth *  float(col), cellHeight * float(row));

			gridSprite->addChild(creature);

			gridArray.pushBack(creature);
		}
	}
}