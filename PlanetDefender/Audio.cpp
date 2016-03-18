#include "pch.h"
#include "Audio.h"


Audio::Audio()
{
}


Audio::~Audio()
{
	if (m_audio)
	{
		m_audio->Suspend();
	}
	m_bgAudioLoop.reset();
}

void Audio::AudioInit()
{
	// Initialising Audio
	AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
#ifdef _DEBUG
	eflags = eflags | AudioEngine_Debug;
#endif
	m_audio = std::make_unique<AudioEngine>(eflags);
	m_retryAudio = false;

	m_bgAudio = std::make_unique<SoundEffect>(m_audio.get(), L"sandstorm.wav");
	m_bgAudioLoop = m_bgAudio->CreateInstance();
	m_bgAudioLoop->Play(true);
	explodeDelay = 2.f;
}
void Audio::AudioUpdate()
{
	if (m_retryAudio)
	{
		m_retryAudio = false;
		if (m_audio->Reset())
		{
			// TODO: restart any looped sounds here
			if (m_bgAudioLoop)
				m_bgAudioLoop->Play(true);
		}
	}
	else if (!m_audio->Update())
	{
		if (m_audio->IsCriticalError())
		{
			m_retryAudio = true;
		}
	}
}
void Audio::AudioSuspend()
{
	m_audio->Suspend();
}
void Audio::AudioResume()
{
	m_audio->Resume();
	explodeDelay = 2.f;
}