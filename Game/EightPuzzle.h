#ifndef QUANTVERSO_EIGHTPUZZLE_H
#define QUANTVERSO_EIGHTPUZZLE_H

//--------------------------------------------------------------------------------------------------

#include "Scene.h"
#include "Node.h"
#include <array>
#include <stack>

class Pathfinder;

//--------------------------------------------------------------------------------------------------

class EightPuzzle : public Scene
{
public:
	EightPuzzle();

	void Start() override;
	void Update() override;
	void Shuffle();

private:
	friend class Tile;

	const float			m_BorderSize;
	Node				m_Tiles;
	Pathfinder*		    m_Pathfinder;
	std::stack<NodePtr> m_Solution;
};

//--------------------------------------------------------------------------------------------------

#endif
