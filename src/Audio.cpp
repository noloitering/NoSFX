#include "Audio.h"

using namespace NoSFX;

AudioManager::AudioManager(std::shared_ptr< Music > music, float vol, float pitch, bool play)
{
	InitAudioDevice();
	if ( vol >= 1 )
	{
		volume.master = 1;
	}
	else if ( vol > 0 )
	{
		volume.master = vol;
	}
	else
	{
		volume.master = 0;
	}
	SetMasterVolume(volume.master);
	if ( music )
	{
		SetMusicPitch(*(music), pitch);
		track = music;
		if ( play )
		{
			PlayMusicStream(*(track));
		}
	}
}

AudioManager::AudioManager(std::shared_ptr< Music > music, const Volume& vol, const Pitch& pitch, bool play)
{
	InitAudioDevice();
	SetMasterVolume(vol.master);
	volume = vol;
	pitches = pitch;
	if ( music )
	{
		track = music;
		SetMusicPitch(*(track), pitch.music);
		SetMusicVolume(*(track), vol.music);
		if ( play )
		{
			PlayMusicStream(*(track));
		}
	}
}

void AudioManager::update()
{
	if ( track )
	{
		UpdateMusicStream(*(track));
		float timePlayed = GetMusicTimePlayed(*(track))/GetMusicTimeLength(*(track));
		if ( timePlayed > 1 )
		{
			StopMusicStream(*(track));
		}
	}
}

void AudioManager::play(std::shared_ptr< Sound > sound)
{
	SetSoundVolume(*(sound), volume.sfx);
	SetSoundPitch(*(sound), pitches.sfx);
	PlaySoundMulti(*(sound));
}

void AudioManager::play(std::shared_ptr< Sound > sound, float vol, float pitch)
{
	SetSoundVolume(*(sound), vol);
	SetSoundPitch(*(sound), pitch);
	PlaySoundMulti(*(sound));
}

void AudioManager::stream(std::shared_ptr< Music > music, bool loop)
{
	music->looping = loop;
	SetMusicVolume(*(music), volume.music);
	SetMusicPitch(*(music), pitches.music);
	track = music;
	PlayMusicStream(*(music));
}

void AudioManager::stream(std::shared_ptr< Music > music, float vol, float pitch, bool loop)
{
	music->looping = loop;
	SetMusicVolume(*(music), vol);
	SetMusicPitch(*(music), pitch);
	track = music;
	PlayMusicStream(*(music));
}

void AudioManager::adjustVolume(const Volume& vol)
{
	volume = vol;
	SetMasterVolume(volume.master);
	if ( track )
	{
		SetMusicVolume(*(track), volume.music);
	}
}

void AudioManager::adjustPitch(const Pitch& pitch)
{
	pitches = pitch;
	if ( track )
	{
		SetMusicVolume(*(track), pitches.music);
	}
}

void AudioManager::adjustTrackVolume(float vol)
{
	if ( vol >= 1 )
	{
		vol = 1;
	}
	else if ( vol < 0 )
	{
		vol = 0;
	}
	if ( track )
	{
		SetMusicVolume(*(track), vol);
	}
}

void AudioManager::adjustMusicVolume(float vol)
{
	if ( vol >= 1 )
	{
		vol = 1;
	}
	else if ( vol < 0 )
	{
		vol = 0;
	}
	volume.music = vol;
	if ( track )
	{
		SetMusicVolume(*(track), volume.music);
	}
}

void AudioManager::adjustSFXVolume(float vol)
{
	if ( vol >= 1 )
	{
		vol = 1;
	}
	else if ( vol < 0 )
	{
		vol = 0;
	}
	volume.sfx = vol;
}

void AudioManager::adjustSoundVolume(std::shared_ptr< Sound > sound, float vol)
{
	SetSoundVolume(*(sound), vol);
}

void AudioManager::adjustMaster(float vol)
{
	if ( vol >= 1 )
	{
		vol = 1;
	}
	else if ( vol < 0 )
	{
		vol = 0;
	}
	volume.master = vol;
	SetMasterVolume(volume.master);
}

void AudioManager::adjustTrackPitch(float pitch)
{
	if ( track )
	{
		SetMusicPitch(*(track), pitch);
	}
}

void AudioManager::adjustMusicPitch(float pitch)
{
	pitches.music = pitch;
	adjustTrackPitch(pitch);
}

void AudioManager::adjustSFXPitch(float pitch)
{
	pitches.sfx = pitch;
}

void AudioManager::adjustSoundPitch(std::shared_ptr< Sound > sound, float pitch)
{
	SetSoundPitch(*(sound), pitch);
}

void AudioManager::pauseTrack()
{
	PauseMusicStream(*(track));
}

void AudioManager::resumeTrack()
{
	if ( trackPlayed() >= 1 )
	{
		ResumeMusicStream(*(track));
	}
	else
	{
		PlayMusicStream(*(track));
	}
}

void AudioManager::stopTrack()
{
	StopMusicStream(*(track));
}

void AudioManager::seekTrack(float pos)
{
	SeekMusicStream(*(track), pos);
}

bool AudioManager::trackPlaying()
{
	
	return IsMusicStreamPlaying(*(track));
}

float AudioManager::trackLength()
{
	
	return GetMusicTimeLength(*(track));
}

float AudioManager::trackPlayed()
{
	
	return GetMusicTimePlayed(*(track));
}