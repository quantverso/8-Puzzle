#include "EightPuzzle.h"
#include "Tile.h"
#include "BFS.h"
#include "Clock.h"
#include <random>

//--------------------------------------------------------------------------------------------------

EightPuzzle::EightPuzzle() :
	m_BorderSize{ window.GetSize().width / 37 },
	m_Tiles{ 9 },
	m_Pathfinder{}
{
}

//--------------------------------------------------------------------------------------------------

void EightPuzzle::Start()
{
	SetBackground("Resources/base.png");

	for (unsigned i{}; i < m_Tiles.Size(); ++i)
	{
		m_Tiles[i] = i;
		CreateObject<Tile>();
	}

	Shuffle();
}

//--------------------------------------------------------------------------------------------------

void EightPuzzle::Update()
{
	// Embaralha o quebra-cabeça
	if (Keyboard::IsKeyPressed(Keyboard::Num0))
		Shuffle();

	// Move com o mouse
	if (window.IsEventTriggered(Window::MouseButtonDown))
		m_Tiles.Move(Tile::Clicked());

	// BFS
	if (!m_Pathfinder)
	{
		if (Keyboard::IsKeyDown(Keyboard::Return))
			m_Pathfinder = new BFS{ m_Tiles };
	}
	else
	{
		m_Pathfinder->Search(m_Solution);
		delete m_Pathfinder;
		m_Pathfinder = nullptr;
	}

	// Monta o quebra-cabeça
	if (!m_Solution.empty())
	{
		static Clock clock;

		if (clock.Count() > 0.5f)
		{
			m_Tiles = *m_Solution.top();

			m_Solution.pop();

			clock.Reset();
		}		
	}

	Scene::Update();
}

//--------------------------------------------------------------------------------------------------

void EightPuzzle::Shuffle()
{
	// Embaralha até surgir uma configuração solúvel
	while (true)
	{
		// Gerador de números aleatórios
		static std::mt19937 mt{ std::random_device{}() };
		static std::uniform_int_distribution<> dist{ 0, 8 };

		for (size_t i{}; i < m_Tiles.Size(); ++i)
		{
			int randomIndex{ dist(mt) };
			int temp{ m_Tiles[i] };
			m_Tiles[i] = int(m_Tiles[randomIndex]);
			m_Tiles[randomIndex] = temp;
		}

		// Contagem de inversões
		unsigned inversions{};
		for (size_t i{}; i < m_Tiles.Size() - 1; ++i)
		{
			for (size_t j{ i + 1 }; j < m_Tiles.Size(); ++j)
			{
				if (m_Tiles[i] != 0 && m_Tiles[j] != 0 && m_Tiles[i] > m_Tiles[j]) // Conta as inversões (ignorando o 0)
					++inversions;
			}
		}

		// Se as inversões forem par, a configuração é solúvel
		if (inversions % 2 == 0)
			break;
	}
}

//--------------------------------------------------------------------------------------------------
