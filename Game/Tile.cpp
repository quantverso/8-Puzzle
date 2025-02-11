#include "Tile.h"
#include "EightPuzzle.h"

//--------------------------------------------------------------------------------------------------

Tile::Tile() :
	m_Index{ []()
		{
			static size_t index{};
			return index++;
		}()
	}
{
}

//--------------------------------------------------------------------------------------------------

void Tile::Awake()
{
	auto game{ GetScene<EightPuzzle>() };

	// Calcula o tamanho da peça
	s_Size = (window.GetSize().width - game->m_BorderSize * 2) / 3;

	// Carrega a textura da peça
	static Texture texture("Resources/tiles.png");
	sprite.SetTexture(&texture);
	
	// Define tamanho e posição da peça
	transform.SetSize(s_Size, s_Size);

	float x{ game->m_Tiles[m_Index] % 3 * s_Size + game->m_BorderSize };
	float y{ float(game->m_Tiles[m_Index] / 3) * s_Size + game->m_BorderSize };
	transform.Position(x, y);
}

//--------------------------------------------------------------------------------------------------

void Tile::Update()
{
	Node& tiles{ GetScene<EightPuzzle>()->m_Tiles };
	if (tiles[m_Index] != 0)
	{
		sprite.SetRect({ (tiles[m_Index] - 1) * 334, 0, 334, 334 });

		if (window.IsEventTriggered(Window::MouseButtonDown))
		{
			Point point{ Mouse::GetPosition() };
			if (transform.CheckCollision(&point))
				s_Clicked = m_Index;
		}
	}
}

//--------------------------------------------------------------------------------------------------

void Tile::Draw()
{
	if (GetScene<EightPuzzle>()->m_Tiles[m_Index] != 0)
		Entity::Draw();
}

//--------------------------------------------------------------------------------------------------
