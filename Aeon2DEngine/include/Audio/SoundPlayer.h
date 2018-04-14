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

#ifndef Aeon2D_Audio_SoundPlayer_H_
#define Aeon2D_Audio_SoundPlayer_H_

#include <list>

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include "../Utils/ResourceHolder.h"
#include "AudioPlayer.h"

namespace ae
{
	/// <summary>Class that facilitates loading in sound effects, playing them, and generally managing them</summary>
	/// <param name="T">The ID type (i.e. an enumeration type)</param>
	template <typename T>
	class SoundPlayer : public AudioPlayer<T>
	{
	public:
		/// <summary>
		/// Default constructor<para/>
		///
		/// The global volume is set to 100% and the listener's position to (0, 0, 300).<br/>
		/// The listener's position is the same for both the <see cref="SoundPlayer"/> and the <see cref="MusicPlayer"/>.
		/// </summary>
		SoundPlayer() = default;
		/// <summary>Deleted copy constructor</summary>
		/// <param name="copy">The <see cref="SoundPlayer"/> to be copied</param>
		SoundPlayer(const SoundPlayer<T>& copy) = delete;
	public:
		/// <summary>Deleted assignment operator</summary>
		/// <param name="other">The <see cref="SoundPlayer"/> to be copied</param>
		/// <returns>The caller <see cref="SoundPlayer"/></returns>
		SoundPlayer<T>& operator=(const SoundPlayer<T>& other) = delete;
	public:
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
		void play(T id);
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
		void play(const sf::Vector2f& position, T id);
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
		void pause(bool flag);
		/// <summary>Stops all active sound effects (the sound effects will be removed)</summary>
		/// <code>
		/// enum class SoundID { ID1, ID2, ID3 };
		/// ae::SoundPlayer&lt;SoundID&gt; soundPlayer;
		/// ...
		/// soundPlayer.stop();
		/// </code>
		/// <seealso cref="pause"/>
		/// <seealso cref="play"/>
		void stop();
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
		virtual void setGlobalVolume(float globalVolume) override final;
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
		virtual void load(const std::string& filepath, T id) override final;
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
		virtual void load(const std::string& filepath, const AudioProperties& properties, T id) override final;
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
		virtual void unload(T id) override final;
	private:
		/// <summary>
		/// Removes all stopped sound effects<para/>
		///
		/// This method is called every time a new sound effect is played.
		/// </summary>
		void removeStoppedSounds();

	private:
		/// <summary>Struct used to represent a sound effect</summary>
		struct SoundEffect {
			sf::Sound sound; ///< The sf::Sound object
			T         id;    ///< The ID associated with the sound effect

			/// <summary>Constructs the <see cref="SoundEffect"/> by providing a sound buffer and an ID</summary>
			/// <param name="buffer">The sound effect's buffer</param>
			/// <param name="id">The ID with which the sound effect will be associated with</param>
			SoundEffect(const sf::SoundBuffer& buffer, T id);
		};
	private:
		SoundBufferHolder<T>         soundBuffers_;    ///< The loaded-in sound effects' buffers
		std::map<T, AudioProperties> soundProperties_; ///< The loaded-in sound effects' properties
		std::list<SoundEffect>       sounds_;          ///< The list of all active sound effects
	};
}
#include "SoundPlayer.inl"
#endif