#include <memory>

#include "raylib.h"

namespace NoSFX
{
	struct Volume
	{
		float master = 0.2f;
		float sfx = 1.0f;
		float music = 1.0f;
	};
	
	struct Pitch
	{
		float sfx = 1.0f;
		float music = 1.0f;
	};
	
	class AudioManager
	{
	protected:
		Volume volume;
		Pitch pitches;
		std::shared_ptr< Music > track = nullptr;
		
	public:
		AudioManager(std::shared_ptr< Music > music=nullptr, float vol=0.2f, float pitch=1.0f, bool play=false);
		AudioManager(std::shared_ptr< Music > music, const Volume& vol, const Pitch& pitch, bool play=false);
		virtual ~AudioManager() {}
		virtual void update();
		void play(std::shared_ptr< Sound > sound);
		void play(std::shared_ptr< Sound > sound, float vol, float pitch);
		void stream(std::shared_ptr< Music >, bool loop=true);
		void stream(std::shared_ptr< Music >, float vol, float pitch, bool loop=true);
		void adjustVolume(const Volume& vol);
		void adjustPitch(const Pitch& pitch);
		void adjustTrackVolume(float vol);
		void adjustMusicVolume(float vol);
		void adjustSFXVolume(float vol);
		void adjustSoundVolume(std::shared_ptr< Sound > sound, float vol);
		void adjustSoundPitch(std::shared_ptr< Sound > sound, float pitch);
		void adjustMaster(float vol);
		void adjustTrackPitch(float vol);
		void adjustMusicPitch(float vol);
		void adjustSFXPitch(float vol);
		void pauseTrack();
		void resumeTrack();
		void stopTrack();
		void seekTrack(float pos);
		bool trackPlaying();
		float trackLength();
		float trackPlayed();
	};
}