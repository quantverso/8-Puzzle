#include "Node.h"
#include "EightPuzzle.h"
#include <algorithm>
#include <cmath>

//--------------------------------------------------------------------------------------------------

Node::Node(size_t size) :
    m_Data{},
    m_Size{ size },
    m_Columns{ int(std::sqrt(size)) },
    m_IndexOfZero{},
    m_Distance{},
    m_Parent{}
{
}

//--------------------------------------------------------------------------------------------------

void Node::Move(size_t index)
{
    int offset{ int(index) - int(m_IndexOfZero) };

    if ((offset == -1 && m_IndexOfZero % m_Columns == 0) ||
        (offset == 1 && m_IndexOfZero % m_Columns == m_Columns - 1))
        return;

    if (abs(offset) == 1 || abs(offset) == m_Columns)
    {
        int temp{ (*this)[m_IndexOfZero] };
        (*this)[m_IndexOfZero] = unsigned((*this)[index]);
        (*this)[index] = temp;
    }
}

//--------------------------------------------------------------------------------------------------

void Node::GetAdjacent(std::vector<NodePtr>& adjacent)
{
    adjacent.clear();
    for (int offset{ -m_Columns }; offset <= m_Columns; offset += m_Columns - 1)
    {
        // Calcula o índice de um nó adjacente
        size_t adjacentIndex{ m_IndexOfZero + offset };
        if (adjacentIndex >= m_Size)
            continue;

        // Guarda o índice atual do elemento 0
        size_t oldIndexOfZero{ m_IndexOfZero };

        // Move elemento para gerar um nó adjacente
        Move(adjacentIndex);

        if (m_IndexOfZero != oldIndexOfZero)
        {
            // Instancia nó vizinho
            NodePtr neighbour{ std::make_shared<Node>(*this) };

            // Restaura o estado do nó
            Move(oldIndexOfZero);

            if (neighbour->GetStatus() == Unvisited)
                adjacent.push_back(neighbour);
        }
    }
}

//--------------------------------------------------------------------------------------------------
