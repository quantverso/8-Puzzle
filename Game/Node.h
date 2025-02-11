#ifndef QUANTVERSO_NODE_H
#define QUANTVERSO_NODE_H

//--------------------------------------------------------------------------------------------------

#include <vector>
#include <memory>
#include <unordered_set>
#include <cassert>

class Node;
using NodePtr = std::shared_ptr<Node>;

//--------------------------------------------------------------------------------------------------

class Node
{
public:
	enum Status
	{
		Unvisited,
		Visited
	};

	Node(size_t size);

	void SetStatus(Status status) const;
	void SetDistance(unsigned distance);
	void SetParent(NodePtr parent);
	void Move(size_t index);

	constexpr size_t Size() const;
	Status GetStatus() const;
	const unsigned& GetDistance() const;
	NodePtr GetParent();
	void GetAdjacent(std::vector<NodePtr>& adjacent);

	static unsigned VisitedNodes();
	static void Reset();

	Node& operator=(const Node& other);
	bool operator==(const Node& other) const;

private:
	class Reference
	{
	public:
		Reference(Node& node, size_t index) :
			node{ node },
			index{ index }
		{
		}

		Reference& operator=(unsigned value)
		{
			if (value == 0)
				node.m_IndexOfZero = index;

			// Limpa os bits existentas na posição
			node.m_Data &= ~(uint64_t(0b1111) << (index * 4));

			// Define os novos bits
			node.m_Data |= (uint64_t(value) << (index * 4));

			return *this;
		}

		operator int() const
		{
			return (node.m_Data >> (index * 4)) & 0b1111;
		}

	private:
		Node&	     node;
		const size_t index;
	};
	
	inline static std::unordered_set<uint64_t> visited;

	uint64_t m_Data;
	size_t	 m_Size;
	int		 m_Columns;
	size_t	 m_IndexOfZero;
	unsigned m_Distance;
	NodePtr	 m_Parent;

public:
	Reference operator[](size_t index);
};

//--------------------------------------------------------------------------------------------------

inline void Node::SetStatus(Status status) const
{
	if (status == Visited)
		visited.insert(m_Data);
	else
		visited.erase(m_Data);
}

//--------------------------------------------------------------------------------------------------

inline void Node::SetDistance(unsigned distance)
{
	m_Distance = distance;
}

//--------------------------------------------------------------------------------------------------

inline void Node::SetParent(NodePtr parent)
{
	m_Parent = parent;
}

//--------------------------------------------------------------------------------------------------

inline constexpr size_t Node::Size() const
{
	return m_Size;
}

//--------------------------------------------------------------------------------------------------

inline Node::Status Node::GetStatus() const
{
	return visited.find(m_Data) == visited.end() ? Unvisited : Visited;
}

//--------------------------------------------------------------------------------------------------

inline const unsigned& Node::GetDistance() const
{
	return m_Distance;
}

//--------------------------------------------------------------------------------------------------

inline NodePtr Node::GetParent()
{
	return m_Parent;
}

//--------------------------------------------------------------------------------------------------

inline unsigned Node::VisitedNodes()
{
	return unsigned(visited.size());
}

//--------------------------------------------------------------------------------------------------

inline void Node::Reset()
{
	visited.clear();
}

//--------------------------------------------------------------------------------------------------

inline Node& Node::operator=(const Node& other)
{
	if (this != &other)
	{
		m_Data = other.m_Data;
		m_Size = other.m_Size;
		m_Columns = other.m_Columns;
		m_IndexOfZero = other.m_IndexOfZero;
	}

	return *this;
}

//--------------------------------------------------------------------------------------------------

inline bool Node::operator==(const Node& other) const
{
	return m_Data == other.m_Data;
}

//--------------------------------------------------------------------------------------------------

inline Node::Reference Node::operator[](size_t index)
{
	assert(index < m_Size && "Index fora dos limites do nodo!");
	return Reference(*this, index);
}

//--------------------------------------------------------------------------------------------------

#endif
