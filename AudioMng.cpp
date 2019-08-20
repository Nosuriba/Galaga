#include "DxLib.h"
#include "AudioMng.h"

std::unique_ptr<AudioMng, AudioMng::AudioMngDeleter> AudioMng::s_Instance(new AudioMng());

AudioMng::AudioMng()
{
}

void AudioMng::SetAudio(std::string f_name)
{
	if (musMap.find(f_name) == musMap.end())
	{
		musMap[f_name];
		musMap[f_name] = LoadSoundMem(f_name.c_str());
	}
}

void AudioMng::PlaySE(std::string f_name)
{
	SetAudio(f_name);
	PlaySoundMem(musMap[f_name], DX_PLAYTYPE_BACK, true);
}

void AudioMng::PlayBGM(std::string f_name)
{
	SetAudio(f_name);
	if (!CheckSoundMem(musMap[f_name]))
	{
		StopSoundMem(nowBGM);
		nowBGM = musMap[f_name];
		PlaySoundMem(nowBGM, DX_PLAYTYPE_BACK, true);
	}
}

void AudioMng::RepeatBGM(std::string f_name)
{
	SetAudio(f_name);
	if (!CheckSoundMem(musMap[f_name]))
	{
		StopSoundMem(nowBGM);
		nowBGM = musMap[f_name];
		PlaySoundMem(nowBGM, DX_PLAYTYPE_LOOP, true);
	}
}

void AudioMng::ChangeVolume(int vol, std::string f_name)
{
	ChangeVolumeSoundMem(255 * vol / 100, musMap[f_name]);
}

bool AudioMng::CheckSound(std::string f_name)
{
	return CheckSoundMem(musMap[f_name]);
}

void AudioMng::StopBGM()
{
	StopSoundMem(nowBGM);
	nowBGM = 0;
}