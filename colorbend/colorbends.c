#include "raylib.h"

int main(void)
{
    const int W = 800, H = 450;
    InitWindow(W, H, "Simple Gradient + Mouse");
    SetTargetFPS(60);

    // vertex shader must use Raylib's attribute names
    const char *vs =
        "#version 330\n"
        "in vec3 vertexPosition;"
        "in vec2 vertexTexCoord;"
        "out vec2 uv;"
        "void main(){"
        "    uv = vertexTexCoord;"
        "    gl_Position = vec4(vertexPosition, 1.0);"
        "}";

    // fragment shader must output 'finalColor'
    const char *fs =
        "#version 330\n"
        "in vec2 uv;"
        "out vec4 finalColor;"
        "uniform vec2 mouse;"
        "void main(){"
        "    vec3 col = vec3(uv.x, uv.y, 1.0-uv.x);"
        "    col += vec3(mouse, 0.0)*0.5;"     // react to mouse
        "    finalColor = vec4(col, 1.0);"
        "}";

    Shader sh = LoadShaderFromMemory(vs, fs);
    int locMouse = GetShaderLocation(sh, "mouse");

    while (!WindowShouldClose())
    {
        // mouse normalized
        Vector2 m = GetMousePosition();
        m.x /= W;
        m.y /= H;

        // upload
        SetShaderValue(sh, locMouse, &m, SHADER_UNIFORM_VEC2);

        BeginDrawing();
            ClearBackground(BLACK);
            BeginShaderMode(sh);
                DrawRectangle(0, 0, W, H, WHITE);
            EndShaderMode();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
