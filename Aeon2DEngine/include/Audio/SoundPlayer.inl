// Aeon2DEngine - 2D Game Engine Powered by SFML
// Copyright (C) 2018 Filippos Gleglakos (gleglakos.filippos@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.

namespace ae
{
	/// <summary>
	/// Plays a pre-loaded sound effect by providing an <paramref name="id"/> associated with the desired sound effect<para/>
	///
	/// The sound effect's source will be the position of the listener.
	/// </summary>
	/// <param name="id">The id associated with the desired sound effect</param>
	/// <code>
	/// enum class SoundID { ID1, ID2, ID3 };
	/// ae::SoundPlayer&lt;SoundID&gt; soundPlayer;
	/// ...
	/// soundPlayer.play(SoundID::ID1);
	/// </code>
	/// <seealso cref="pause"/>
	/// <seealso cref="stop"/>
	/// <seealso cref="load"/>
	template <typename T>
	void SoundPlayer<T>::play(T id)
	{
		play(AudioPlayer<T>::getListenerPosition(), id);
	}

	/// <summary>Plays a pre-loaded sound effect by providing a <paramref name="position"/> indicating the sound effect's source, and an <paramref name="id"/> associated with the desired sound effect</summary>
	/// <param name="position">The position of the sound effect's source</param>
	/// <param name="id">The id associated with the desired sound effect</param>
	/// <code>
	/// enum class SoundID { ID1, ID2, ID3 };
	/// ae::SoundPlayer&lt;SoundID&gt; soundPlayer;
	/// ...
	/// soundPlayer.play(sf::Vector2f(250.f, 100.f), SoundID::ID1);
	/// </code>
	/// <seealso cref="pause"/>
	/// <seealso cref="stop"/>
	/// <seealso cref="load"/>
	template <typename T>
	void SoundPlayer<T>::play(const sf::Vector2f& position, T id)
	{
		// Remove all stopped sound effects before playing the new one
		removeStoppedSounds();

		// Construct the new sound effect
#ifdef _DEBUG
		auto found = soundProperties_.find(id);
		if (found == soundProperties_.end()) {
			DebugLogger::cacheMessage("ae::SoundPlayer<T>::play - Unable to find sound effect");
			return;
		}
		const AudioProperties& props = found->second;
#else
		const AudioProperties& props = soundProperties_.find(id)->second;
#endif
		sounds_.emplace_back(*soundBuffers_.get(id), id);
		SoundEffect& effect = sounds_.back();
		effect.sound.setPosition(position.x, -position.y, 0.f);
		effect.sound.setVolume(AudioPlayer<T>::getGlobalVolume() * props.getVolume() / 100.f);
		effect.sound.setAttenuation(props.getAttenuation());
		effect.sound.setPitch(props.getPitch());
		effect.sound.setMinDistance(props.getMinDistance3D());
		effect.sound.setRelativeToListener(props.isRelativeToListener());
		effect.sound.play();
	}

	/// <summary>
	/// (Un)Pauses all active sound effects<para/>
	///
	/// Pausing the sound effects can be useful when you wish to resume playing them from the point where they were previously paused.
	/// </summary>
	/// <param name="flag">True to pause them, false otherwise</param>
	/// <code>
	/// enum class SoundID { ID1, ID2, ID3 };
	/// ae::SoundPlayer&lt;SoundID&gt; soundPlayer;
	/// ...
	/// soundPlayer.pause(true);
	/// </code>
	/// <seealso cref="stop"/>
	/// <seealso cref="play"/>
	template <typename T>
	void SoundPlayer<T>::pause(bool flag)
	{
		if (flag)
			for (SoundEffect& effect : sounds_)
				effect.sound.pause();
		else
			for (SoundEffect& effect : sounds_)
				if (effect.sound.getStatus() == sf::SoundSource::Status::Paused)
					effect.sound.play();
	}

	/// <summary>Stops all active sound effects (the sound effects will be removed)</summary>
	/// <code>
	/// enum class SoundID { ID1, ID2, ID3 };
	/// ae::SoundPlayer&lt;SoundID&gt; soundPlayer;
	/// ...
	/// soundPlayer.stop();
	/// </code>
	/// <seealso cref="pause"/>
	/// <seealso cref="play"/>
	template <typename T>
	void SoundPlayer<T>::stop()
	{
		for (SoundEffect& effect : sounds_)
			effect.sound.stop();

		removeStoppedSounds();
	}

	/// <summary>
	/// Sets the sound player's global volume (0% - 100%)<para/>
	///
	/// A global volume of 50% will reduce the sound player's effects' volume by half of their current volume.
	/// </summary>
	/// <param name="globalVolume">The sound player's global volume</param>
	/// <code>
	/// enum class SoundID { ID1, ID2, ID3 };
	/// ae::SoundPlayer&lt;SoundID&gt; soundPlayer;
	/// soundPlayer.setGlobalVolume(50.f);
	/// </code>
	template <typename T>
	void SoundPlayer<T>::setGlobalVolume(float globalVolume)
	{
		AudioPlayer<T>::setGlobalVolume(globalVolume);

		const float GLOBAL_VOLUME = AudioPlayer<T>::getGlobalVolume();
		for (SoundEffect& effect : sounds_) {
#ifdef _DEBUG
			auto found = soundProperties_.find(effect.id);
			if (found == soundProperties_.end()) {
				DebugLogger::cacheMessage("ae::SoundPlayer<T>::setGlobalVolume - Unable to find a sound effect");
				return;
			}
			effect.sound.setVolume(GLOBAL_VOLUME * found->second.getVolume() / 100.f);
#else
			effect.sound.setVolume(GLOBAL_VOLUME * soundProperties_.find(effect.id)->second.getVolume() / 100.f);
#endif
		}
	}

	/// <summary>
	/// Loads in a sound effect by providing a <paramref name="filepath"/> and an <paramref name="id"/> to associate it with<para/>
	///
	/// The <see cref="AudioProperties"/> of the sound effect will be those by default.<para/>
	///
	/// Only sound effects with one channel (mono sounds) can be spatialized.
	/// </summary>
	/// <param name="filepath">The sound effect's filepath</param>
	/// <param name="id">An ID with which to associate the sound effect (i.e. an enum value)</param>
	/// <code>
	/// enum class SoundID { ID1, ID2, ID3 };
	/// ae::SoundPlayer&lt;SoundID&gt; soundPlayer;
	/// soundPlayer.load("Assets/Sounds/KnightAttack.wav", SoundID::ID1);
	/// </code>
	/// <seealso cref="unload"/>
	/// <seealso cref="play"/>
	template <typename T>
	void SoundPlayer<T>::load(const std::string& filepath, T id)
	{
		soundBuffers_.load(filepath, id);
		soundProperties_.insert(std::make_pair(id, AudioProperties()));
	}

	/// <summary>
	/// Loads in a sound effect by providing a <paramref name="filepath"/>, an <see cref="AudioProperties"/> that contain the sound effect's properties, and an <paramref name="id"/> to associate it with<para/>
	///
	/// Only sound effects with one channel (mono sounds) can be spatialized.
	/// </summary>
	/// <param name="filepath">The sound effect's filepath</param>
	/// <param name="properties">The <see cref="AudioProperties"/> that contain the sound effect's properties</param>
	/// <param name="id">An ID with which to associate the sound effect (i.e. an enum value)</param>
	/// <code>
	/// enum class SoundID { ID1, ID2, ID3 };
	/// ae::SoundPlayer&lt;SoundID&gt; soundPlayer;
	/// soundPlayer.load("Assets/Sounds/KnightAttack.wav", ae::AudioProperties(100.f, 35.f, 1.f, 250.f), SoundID::ID1);
	/// </code>
	/// <seealso cref="unload"/>
	/// <seealso cref="play"/>
	template <typename T>
	void SoundPlayer<T>::load(const std::string& filepath, const AudioProperties& properties, T id)
	{
		soundBuffers_.load(filepath, id);
		soundProperties_.insert(std::make_pair(id, properties));
	}

	/// <summary>
	/// Unloads a loaded-in sound effect by providing the associated <paramref name="id"/><para/>
	///
	/// The sound effects associated with this <paramref name="id"/> that are currently being played will be removed.
	/// </summary>
	/// <param name="id">The ID associated with the sound effect to unload</param>
	/// <code>
	/// enum class SoundID { ID1, ID2, ID3 };
	/// ae::SoundPlayer&lt;SoundID&gt; soundPlayer;
	/// ...
	/// soundPlayer.unload(SoundID::ID1);
	/// </code>
	/// <seealso cref="load"/>
	template <typename T>
	void SoundPlayer<T>::unload(T id)
	{
#ifdef _DEBUG
		auto found = soundProperties_.find(id);
		if (found == soundProperties_.end()) {
			DebugLogger::cacheMessage("ae::SoundPlayer<T>::unload - The ID provided isn't associated with any sound effect");
			return;
		}
		soundProperties_.erase(found);
#else
		soundProperties_.erase(soundProperties_.find(id));
#endif
		sounds_.remove_if([&id](const SoundEffect& e) { return e.id == id; });
		soundBuffers_.unload(id);
	}

	/// <summary>
	/// Removes all stopped sound effects<para/>
	///
	/// This method is called every time a new sound effect is played.
	/// </summary>
	template <typename T>
	void SoundPlayer<T>::removeStoppedSounds()
	{
		sounds_.remove_if([](const SoundEffect& e) { return e.sound.getStatus() == sf::Sound::Status::Stopped; });
	}

	/// <summary>Constructs the <see cref="SoundEffect"/> by providing a sound buffer and an ID</summary>
	/// <param name="buffer">The sound effect's buffer</param>
	/// <param name="id">The ID with which the sound effect will be associated with</param>
	template <typename T>
	SoundPlayer<T>::SoundEffect::SoundEffect(const sf::SoundBuffer& buffer, T id)
		: sound(buffer)
		, id(id)
	{
	}
}