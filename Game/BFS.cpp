#include "BFS.h"
#include <iostream>

//--------------------------------------------------------------------------------------------------

BFS::BFS(Node& root) : Pathfinder(root)
{
	m_Queue.push(m_Root); // Coloca o nó raiz na fila
}

//--------------------------------------------------------------------------------------------------

void BFS::Search(std::stack<NodePtr>& solution)
{
	while (!m_Queue.empty())
	{
		auto current{ m_Queue.front() };
		m_Queue.pop();

		if (*current == *m_Target)
		{
			std::cout << "Solucao encontrada na profundidade: " << current->GetDistance() << std::endl
				<< "Nos visitados: " << Node::VisitedNodes() << "\n\n";
			GetPath(solution, current);
			return;
		}

		// Acessa os nós adjacentes
		current->GetAdjacent(m_Adjacent);

		// Visita nós adjacentes, atualiza e coloca na fila
		for (auto& adj : m_Adjacent)
		{
			adj->SetStatus(Node::Visited);
			adj->SetDistance(current->GetDistance() + 1);
			adj->SetParent(current);

			m_Queue.push(adj);
		}	
	}
}

//--------------------------------------------------------------------------------------------------
