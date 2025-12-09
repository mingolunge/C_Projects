#include "raylib.h"


int main(void)
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
    InitWindow(screenWidth, screenHeight, "raylib - gravity bouncing ball");

    // Ball properties
    float 1X = screenWidth / 2.0f;
    float 1Y = 50.0f;
    float 2X = 50.0f;
    float 2Y = 50.0f;
    float radius = 50.0f;
    float velocityY = 50.0f;
    float velocityX = 30.0f;

    const float gravity = 0.5f;      // gravity acceleration
    const float bounceFactor = 0.8f; // energy retained after bounce (0-1)

    SetTargetFPS(60);

    float oldx = 0.0f;
    float oldy = 0.0f;
    while (!WindowShouldClose())
    {
    	screenWidth = GetScreenWidth();
    	screenHeight = GetScreenHeight();
    	Vector2 mousePos = GetMousePosition();

        // Bounce on floor
        if (ballY + radius >= screenHeight)
        {
            ballY = screenHeight - radius;   // reset position to floor
            velocityY *= -bounceFactor;      // reverse and reduce velocity
        }

        // Optional: bounce on ceiling
        if (ballY - radius <= 0)
        {
            ballY = radius;
            velocityY *= -bounceFactor;
        }

        if (ballX + radius >= screenWidth)
        {
            ballX = screenWidth - radius;   // reset position to floor
            velocityX *= -bounceFactor;      // reverse and reduce velocity
        }

        // Optional: bounce on ceiling
        if (ballX - radius <= 0)
        {
            ballX = radius;
            velocityX *= -bounceFactor;
        }

        // --- DRAW ---
        BeginDrawing();
            ClearBackground(BLANK);

            DrawCircle((int)ballX, (int)ballY, radius, GREEN);
        EndDrawing();
        oldx = mousePos.x;
        oldy = mousePos.y;
    }

    CloseWindow();
    return 0;
}
