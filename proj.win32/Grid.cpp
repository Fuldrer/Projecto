#include "Grid.h"
#include "Creature.h"

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

void Grid::setupTouchHandling()
{
	auto touchListener = EventListenerTouchOneByOne::create();

	touchListener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		Sprite* gridSprite = this->getChildByName<Sprite*>("grid");

		Vec2 gridTouchLocation = gridSprite->convertTouchToNodeSpace(touch);

		Creature* touchedCreature = this->creatureForTouchLocation(gridTouchLocation);

		if (touchedCreature)
		{
			touchedCreature->setIsAlive(!touchedCreature->getIsAlive());
		}

		return true;
	};

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

Creature* Grid::creatureForTouchLocation(Vec2 touchLocation)
{
	if (touchLocation.x < 0.0f || touchLocation.y < 0.0f)
	{
		return nullptr;
	}

	int row = touchLocation.y / cellHeight;
	int col = touchLocation.x / cellWidth;

	if (this->isValidIndex(row, col))
	{
		return gridArray.at(this->indexForRowColumn(row, col));
	}
	else
	{
		return nullptr;
	}
}

bool Grid::isValidIndex(int row, int col)
{
	return (row >= 0 && row < ROWS) && (col >= 0 && col < COLUMNS);
}

int Grid::indexForRowColumn(int row, int col)
{
	return row * COLUMNS + col;
}