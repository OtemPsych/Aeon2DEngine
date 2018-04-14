#include <type_traits>
#include <cmath>

#include <SFML/Audio/Listener.hpp>

#include "../../include/Audio/AudioProperties.h"

namespace ae
{
	AudioProperties::AudioProperties(float volume, float attenuation, float pitch,
		                             float minDistance2d, bool relativeToListener)
		: pitch_(pitch)
		, relativeToListener_(relativeToListener)
	{
		setVolume(volume);
		setAttenuation(attenuation);
		setMinDistance2D(minDistance2d);
	}

	AudioProperties::AudioProperties(const AudioProperties& copy)
		: volume_(copy.volume_)
		, attenuation_(copy.attenuation_)
		, pitch_(copy.pitch_)
		, minDistance2d_(copy.minDistance2d_)
		, minDistance3d_(copy.minDistance3d_)
		, relativeToListener_(copy.relativeToListener_)
	{
	}

	AudioProperties::AudioProperties(AudioProperties&& other)
		: volume_(std::move(other.volume_))
		, attenuation_(std::move(other.attenuation_))
		, pitch_(std::move(other.pitch_))
		, minDistance2d_(std::move(other.minDistance2d_))
		, minDistance3d_(std::move(other.minDistance3d_))
		, relativeToListener_(std::move(other.relativeToListener_))
	{
	}

	AudioProperties& AudioProperties::operator=(const AudioProperties& other)
	{
		volume_ = other.volume_;
		attenuation_ = other.attenuation_;
		pitch_ = other.pitch_;
		minDistance2d_ = other.minDistance2d_;
		minDistance3d_ = other.minDistance3d_;
		relativeToListener_ = other.relativeToListener_;

		return *this;
	}

	AudioProperties& AudioProperties::operator=(AudioProperties&& other)
	{
		volume_ = std::move(other.volume_);
		attenuation_ = std::move(other.attenuation_);
		pitch_ = std::move(other.pitch_);
		minDistance2d_ = std::move(other.minDistance2d_);
		minDistance3d_ = std::move(other.minDistance3d_);
		relativeToListener_ = std::move(other.relativeToListener_);

		return *this;
	}

	bool operator==(const AudioProperties& ap1, const AudioProperties& ap2)
	{
		return ap1.volume_ == ap2.volume_ && ap1.attenuation_ == ap2.attenuation_
			&& ap1.pitch_ == ap2.pitch_ && ap1.minDistance2d_ == ap2.minDistance2d_
			&& ap1.minDistance3d_ == ap2.minDistance3d_ && ap1.relativeToListener_ == ap2.relativeToListener_;
	}

	bool operator!=(const AudioProperties& ap1, const AudioProperties& ap2)
	{
		return ap1.volume_ != ap2.volume_ || ap1.attenuation_ != ap2.attenuation_
			|| ap1.pitch_ != ap2.pitch_ || ap1.minDistance2d_ != ap2.minDistance2d_
			|| ap1.minDistance3d_ != ap2.minDistance3d_ || ap1.relativeToListener_ != ap2.relativeToListener_;
	}

	void AudioProperties::setVolume(float volume)
	{
		// Verifies that the volume is within the range [0, 100]
		volume_ = fmaxf(fminf(volume, 100.f), 0.f);
	}

	void AudioProperties::setMinDistance2D(float minDistance2d)
	{
		minDistance2d_ = fmaxf(minDistance2d, 1.f);

		const float LISTENER_POS_Z = sf::Listener::getPosition().z;
		minDistance3d_ = sqrtf(minDistance2d_ * minDistance2d_ + LISTENER_POS_Z * LISTENER_POS_Z);
	}
}