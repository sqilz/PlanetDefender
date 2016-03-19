#include "pch.h"
#include "AudioClass.h"
using namespace DirectX;

AudioClass::AudioClass()
{
}


AudioClass::~AudioClass()
{
	if (m_audio)
	{
		m_audio->Suspend();
	}
	m_bgAudioLoop.reset();
}

void AudioClass::AudioInit()
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
void AudioClass::AudioUpdate()
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
void AudioClass::AudioSuspend()
{
	// for pausing when window minimized
	m_audio->Suspend();
}
void AudioClass::AudioResume()
{
	// resuming sound when coming back from minimized window
	m_audio->Resume();
	explodeDelay = 2.f;
}