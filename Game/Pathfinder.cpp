#include "Pathfinder.h"
#include <numeric>

//--------------------------------------------------------------------------------------------------

Pathfinder::Pathfinder(Node& root) :
	m_Root{ std::make_shared<Node>(root) },
	m_Target{ std::make_shared<Node>(root.Size()) }
{
	for (unsigned i{}; i < m_Target->Size(); ++i)
		(*m_Target)[i] = i;
}

//--------------------------------------------------------------------------------------------------

Pathfinder::~Pathfinder()
{
	Node::Reset();
}

//--------------------------------------------------------------------------------------------------

void Pathfinder::GetPath(std::stack<NodePtr>& solution, NodePtr target)
{
	while (target)
	{
		solution.push(target);
		target = target->GetParent();
	}
}

//--------------------------------------------------------------------------------------------------
