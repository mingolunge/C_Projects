#include "stdio.h"
#include "raylib.h"
#include "math.h"

Vector2 add(Vector2 a, Vector2 b){
	Vector2 result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return result;
}

Vector2 sub(Vector2 a, Vector2 b){
	Vector2 result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	return result;
}

float VDist(Vector2 a, Vector2 b){
	Vector2 subbed = sub(a, b);
	return sqrt(pow(subbed.x, 2) + pow(subbed.y, 2));
}

struct Obj{
	Vector2 pos;
	float s;	
	bool alive;
};


int main(){
	struct Obj a = {{2, 4}, 8, true};
	int width = 1280;
	int height = 720;
	SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
	InitWindow(width, height, "fluid sim");
	SetTargetFPS(60);

	 while (!WindowShouldClose()){
	 	width = GetScreenWidth();
	 	height = GetScreenHeight();
	 	Vector2 ray = {width / 2, height / 2};
	 	BeginDrawing();
	 		ClearBackground(BLANK);
	 		DrawCircleV(a.pos, 50, WHITE);
	 		DrawLineV(a.pos, ray, WHITE);
	 	EndDrawing();
	 }
	 CloseWindow();
	 return 0;
}
