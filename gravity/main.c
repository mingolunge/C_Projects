#include "raylib.h"
#include "math.h"

typedef struct{
    Vector2 pos;
    Vector2 vel;
    float mass;
    float pull;
    float r;
} Planet;

int main(void)
{
    int screenWidth = 1280;//GetScreenWidth();
    int screenHeight = 720;//GetScreenHeight();
    //SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
    InitWindow(screenWidth, screenHeight, "raylib - gravity bouncing ball");
    SetTargetFPS(60);
    /////////////////////////////////////////////////////////////////////////////////

    Planet a = {{200, 50}, {100, -40}, 5, 200, 20};
    Planet b = {{500, 300}, {10,20}, 5, 5000000000000, 10};
    Vector2 dir;
    float distance;
    bool dragging = false;

    while (!WindowShouldClose())
    {
    	screenWidth = 1280;//GetScreenWidth();
    	screenHeight = 720;//GetScreenHeight();
    	Vector2 mousePos = GetMousePosition();
    	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
    		dragging = true;
    	}

    	if (dragging){
    		b.pos.x = mousePos.x;
    		b.pos.y = mousePos.y;
    	}

    	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
    		dragging = false;
    	}
        
        dir.x = b.pos.x - a.pos.x;
        dir.y = b.pos.y - a.pos.y;

        distance = sqrtf(dir.x*dir.x + dir.y*dir.y);

        Vector2 dir_norm = { dir.x / distance, dir.y / distance };
        a.vel.x += dir_norm.x * a.pull * GetFrameTime();
        a.vel.y += dir_norm.y * a.pull * GetFrameTime();
		a.pos.x += a.vel.x * GetFrameTime();
		a.pos.y += a.vel.y * GetFrameTime();
        // --- DRAW ---
        BeginDrawing();
            ClearBackground(BLANK);
            DrawCircle(a.pos.x, a.pos.y, a.r, GREEN);
            DrawCircle(b.pos.x, b.pos.y, b.r, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
