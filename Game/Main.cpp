#include "Engine.h"
#include "EightPuzzle.h"

//--------------------------------------------------------------------------------------------------

int main(int argc, char** argv)
{
    Engine::window.SetSize(600, 600);
    Engine::window.SetTitle("8-Puzzle");
    Engine::Run(new EightPuzzle);

    return 0;
}

//--------------------------------------------------------------------------------------------------
