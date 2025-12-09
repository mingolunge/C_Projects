#include "raylib.h"

int main() {
    SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    InitWindow(screenWidth, screenHeight, "Raylib Shader Art");

    Shader shader = LoadShader(0, "shader.fs");

    int timeLoc = GetShaderLocation(shader, "time");
    int resLoc  = GetShaderLocation(shader, "resolution");

    Vector2 resolution = {1920, 1080};

    SetTargetFPS(30);

    while (!WindowShouldClose()) {

        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();
        float time = GetTime();

        SetShaderValue(shader, timeLoc, &time, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shader, resLoc, &resolution, SHADER_UNIFORM_VEC2);

        BeginDrawing();
        ClearBackground(BLACK);

        BeginShaderMode(shader);
        DrawRectangle(0, 0, screenWidth, screenHeight, WHITE);
        EndShaderMode();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
