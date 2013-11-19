#pragma once

#include "../defines.h"
#include <vector>

#ifdef DESKTOP
	#include "SDL.h"
	#include "SDL_mixer.h"
#else
	#include "android_native_app_glue.h"
	#include  <SLES/OpenSLES.h>
	#include  <SLES/OpenSLES_Android.h>
	#include  <SLES/OpenSLES_AndroidConfiguration.h>
#endif

namespace star
{
	class BaseSound
	{
	public:
		virtual ~BaseSound();

		virtual void Play(int32 loopTime = 0);
		virtual void Stop();
		virtual void Pause();
		virtual void Resume();

		bool IsStopped() const;
		bool IsPlaying() const;
		bool IsPaused() const;
		bool IsLooping() const;

		void SetCompleteVolume(
			float volume,
			float channelVolume,
			float masterVolume
			);
		void SetBaseVolume(
			float volume
			);
		void SetChannelVolume(
			float volume
			);
		void SetMasterVolume(
			float volume
			);

		float GetBaseVolume() const;

		void IncreaseVolume(float volume);
		void DecreaseVolume(float volume);

		virtual void SetMuted(bool muted) = 0;
		virtual bool IsMuted() const = 0;

		virtual void SetChannel(uint8 channel);
		virtual void UnsetChannel();

		uint8 GetChannel() const;

	protected:
#ifdef ANDROID
		virtual void SetVolume(float volume) = 0;
#else
		void SetVolume(float volume);
#endif
		virtual float GetVolume() const = 0;

		BaseSound(uint8 channel);
#ifdef ANDROID
		static const SLuint32 PLAYER_ID_COUNT = 3;
		static const SLInterfaceID PLAYER_ID_ARR[];
		static const SLboolean PLAYER_REQ_ARR[];

		virtual void CreateSoundDetails();
		virtual void RegisterCallback(SLPlayItf & player) = 0;

		void CreateSound(
			SLObjectItf & sound,
			SLEngineItf & engine,
			SLPlayItf & player,
			const tstring & path
			);

		void DestroySound(
			SLObjectItf & sound,
			SLPlayItf & player
			);

		void ResumeSound(SLPlayItf & player);

		void SetSoundVolume(
			SLObjectItf & sound,
			SLPlayItf & player,
			float volume
			);

		bool GetVolumeInterface(
			const SLObjectItf & sound,
			const SLPlayItf & player,
			void * pInterface
			) const;

		float GetSoundVolume(
			const SLObjectItf & sound,
			const SLPlayItf & player
			) const;

		void SetSoundMuted(
			SLObjectItf & sound,
			SLPlayItf & player,
			bool muted
			);

		bool GetSoundMuted(
			const SLObjectItf & sound,
			const SLPlayItf & player
			) const;

#else
		bool mIsMuted;
		float mVolume;

		virtual void SetSoundVolume(int32 volume) = 0;
		void SetSoundMuted(bool muted);
#endif

		bool mbIsLooping;
		bool mNoChannelAssigned;
		uint8 mChannel;

	private:
		struct SoundVolume
		{
			float Volume;
			float ChannelVolume;
			float MasterVolume;

			SoundVolume();
			float GetVolume() const;
		};

		enum class SoundState : byte
		{
			playing = 0,
			paused = 1,
			stopped = 2
		};

		SoundVolume mSoundVolume;
		SoundState mSoundState;

		BaseSound(const BaseSound& yRef);
		BaseSound(BaseSound&& yRef);
		BaseSound& operator=(const BaseSound& yRef);
		BaseSound& operator=(BaseSound&& yRef);
	};
}
