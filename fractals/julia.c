#include "stdio.h"
#include "raylib.h"

const Color background = {0,0,0,55};
int iy;
double R = 2;
double cx = -0.7;
double cy = 0.27015;
int screenWidth = 1920;//GetScreenWidth();
int screenHeight = 1080;//GetScreenHeight();
bool pressed;

int in_set(int x, int y) {

    // Scale pixel to complex plane
    double zx = -R + (x / (double)screenWidth)  * (2 * R);
    double zy = -R + (y / (double)screenHeight) * (2 * R);

    for (int i = 0; i < 20; i++) {

        double xtemp = zx*zx - zy*zy;
        zy = 2*zx*zy + cy;
        zx = xtemp + cx;

        // Escape: if |z| > R, it's NOT in the set
        if (zx*zx + zy*zy > R*R) {
            return i;
        }
    }

    // If never escaped after max iterations → likely in the set
    return true;
}

int main(){
	//SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
	InitWindow(screenWidth, screenHeight, "julia set");
	SetTargetFPS(30);
	while (!WindowShouldClose()){
		if (IsKeyPressed(KEY_K)) {
			pressed= true;
		}
		if (pressed){
			R *= 0.9;
		}
		if (IsKeyReleased(KEY_K)){
			pressed = false;
		}
		
		ClearBackground(BLANK);
		BeginDrawing();
			for (int ix = 0; ix<screenWidth; ix++){
				for (int iy = 0; iy<screenHeight; iy++){
					int i = (in_set(ix, iy));
					Color smooth = {i*5, i*5, i*3, 255};
					DrawPixel(ix, iy, smooth);
					//if (in_set(ix, iy)){
					//	DrawPixel(ix, iy, WHITE);
					//}
				}
			}			
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
