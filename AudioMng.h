#pragma once
#include <map>
#include <memory>
#include <mutex>
#include <vector>

#define LpAudioMng (AudioMng::GetInstance())

class AudioMng
{
public:
	static AudioMng & GetInstance()
	{
		return *s_Instance;
	}

	void PlaySE(std::string f_name);
	void PlayBGM(std::string f_name);
	void RepeatBGM(std::string f_name);
	void ChangeVolume(int vol, std::string f_name);	
	bool CheckSound(std::string f_name);
	void StopBGM();
private:
	void SetAudio(std::string f_name);
	struct AudioMngDeleter
	{
		void operator()(AudioMng * musMng) const
		{
			delete musMng;
		}
	};

	AudioMng();

	int nowBGM;

	static std::unique_ptr<AudioMng, AudioMngDeleter> s_Instance;

	std::map<std::string, int> musMap;
};

