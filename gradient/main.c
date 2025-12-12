#include "stdio.h"
#include "raylib.h"



int main(void)
{
    int screenWidth = 1280;//GetScreenWidth();
    int screenHeight = 720;//GetScreenHeight();
    //SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
    InitWindow(screenWidth, screenHeight, "gradient");
    SetTargetFPS(10);
    /////////////////////////////////////////////////////////////////////////////////

	

    while (!WindowShouldClose())
    {
    	if (IsKeyDown(KEY_Q)){
    		CloseWindow();
    	}
    	if (IsKeyDown(KEY_K)){
    	
		}
    	
        BeginDrawing();
            ClearBackground(BLANK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
