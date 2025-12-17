#include "raylib.h"
#include "stdio.h"

int main(void)
{
    int screenWidth = 640;
    int screenHeight = 360;
    
   	SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
   	SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(screenWidth, screenHeight, "shaderWall");

    // Load shader (no vertex shader = raylib default)
    Shader shader = LoadShader(0, "shader.frag");
    int timeLoc = GetShaderLocation(shader, "time");
    int resLoc  = GetShaderLocation(shader, "resolution");
    int mouseLoc = GetShaderLocation(shader, "mouse");
    
    

    // Render texture to apply shader to
    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
    	screenWidth = GetScreenWidth();
    	screenHeight = GetScreenHeight();
    	if (IsKeyPressed(KEY_U)){
    		shader = LoadShader(0, "shader.frag");
    	}
    	Vector2 mousePos = GetMousePosition();
    	Vector2 mouseNorm = { mousePos.x / screenWidth, mousePos.y / screenHeight };
    	mouseNorm.x -= 0.5f;
    	mouseNorm.y -= 0.5f;
    	
    	// Optional: scale to keep magnitude 1 max
    	mouseNorm.x *= 2.0f;
    	mouseNorm.y *= 2.0f;
    	
    	SetShaderValue(shader, mouseLoc, &mouseNorm, SHADER_UNIFORM_VEC2);
    	
    	float t = GetTime();
    	SetShaderValue(shader, timeLoc, &t, SHADER_UNIFORM_FLOAT);
    	
    	Vector2 res = { (float)screenWidth, (float)screenHeight };
    	SetShaderValue(shader, resLoc, &res, SHADER_UNIFORM_VEC2);

    	//screenWidth = GetScreenWidth();
    	//screenHeight = GetScreenHeight();

        // Draw scene to texture
        BeginTextureMode(target);
            ClearBackground(BLANK);
            DrawText("Hello Shader", 200, 200, 40, WHITE);
        EndTextureMode();

        // Draw texture with shader
        BeginDrawing();
            ClearBackground(BLANK);
            BeginShaderMode(shader);
                // NOTE: RenderTexture is flipped vertically
                DrawTextureRec(
                    target.texture,
                    (Rectangle){ 0, 0, (float)screenWidth, -(float)screenHeight },
                    (Vector2){ 0, 0 },
                    WHITE
                );
            EndShaderMode();
            DrawFPS(0, 0);
        EndDrawing();
    }

    UnloadRenderTexture(target);
    UnloadShader(shader);
    CloseWindow();

    return 0;
}
