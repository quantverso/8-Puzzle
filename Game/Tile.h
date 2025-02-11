#ifndef QUANTVERSO_TILE_H
#define QUANTVERSO_TILE_H

//--------------------------------------------------------------------------------------------------

#include "Entity.h"

class EightPuzzle;

//--------------------------------------------------------------------------------------------------

class Tile : public Entity
{
public:
	Tile();

	void Awake() override;
	void Update() override;
	void Draw() override;
	
	static const size_t& Clicked();

private:
	inline static float  s_Size;
	inline static size_t s_Clicked;

	const size_t m_Index;
};

//--------------------------------------------------------------------------------------------------

inline const size_t& Tile::Clicked()
{
	return s_Clicked;
}

//--------------------------------------------------------------------------------------------------

#endif
