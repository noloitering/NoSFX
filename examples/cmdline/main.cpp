#include "../../src/Audio.h"

Vector2 window = {470, 720};
Vector2 center = {window.x / 2, window.y / 2};
Vector2 scale = {1.0, 1.0};
float size = 35;
int fps = 60;
bool pause = false;

int main(int argc, char ** argv)
{
	InitWindow(window.x, window.y, "Audio Player");
	SetTargetFPS(fps);
	if (argc > 1)
	{
		NoSFX::AudioManager player = NoSFX::AudioManager();
		if ( IsAudioDeviceReady() )
		{
			std::shared_ptr< Music > song =  std::make_shared< Music >(LoadMusicStream(argv[1]));
			player.stream(song, false);
			while (!WindowShouldClose())
			{
				player.update();
				if (IsKeyPressed(KEY_SPACE))
				{
					if ( player.trackPlaying() )
					{
						player.stopTrack();
					}
					else
					{
						player.resumeTrack();
					}
				}
				if (IsKeyPressed(KEY_P))
				{
					pause = !pause;

					if (pause)
					{	
						player.pauseTrack();
					}
					else 
					{
						player.resumeTrack();
					}
				}
				BeginDrawing();
					ClearBackground(RAYWHITE);
				EndDrawing();
			}
			UnloadMusicStream(*(song));
			CloseAudioDevice();
			CloseWindow();
		}
	}
	
	return 0;
}