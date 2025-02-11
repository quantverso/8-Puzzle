#ifndef QUANTVERSO_PATHFINDER_H
#define QUANTVERSO_PATHFINDER_H

//--------------------------------------------------------------------------------------------------

#include "EightPuzzle.h"
#include "Node.h"
#include <stack>

//--------------------------------------------------------------------------------------------------

class Pathfinder
{
public:
	Pathfinder(Node& root);
	virtual ~Pathfinder();
	virtual void Search(std::stack<NodePtr>& solution) = 0;

protected:
	NodePtr			     m_Root;
	NodePtr			     m_Target;
	std::vector<NodePtr> m_Adjacent;

	void GetPath(std::stack<NodePtr>& solution, NodePtr target);
};

//--------------------------------------------------------------------------------------------------

#endif
