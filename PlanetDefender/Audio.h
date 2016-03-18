#pragma once
using namespace DirectX;
class Audio
{
public:
	Audio();
	~Audio();
	void AudioInit();
	void AudioUpdate();
	void AudioSuspend();
	void AudioResume();
	void OnNewAudioDevice() { m_retryAudio = true; }
private:
	std::unique_ptr<DirectX::AudioEngine> m_audio;
	bool m_retryAudio;
	float explodeDelay;
	std::unique_ptr<DirectX::SoundEffect> m_bgAudio;
	std::unique_ptr<DirectX::SoundEffectInstance> m_bgAudioLoop;
};

