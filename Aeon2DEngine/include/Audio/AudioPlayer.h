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

#ifndef Aeon2D_Audio_AudioPlayer_H_
#define Aeon2D_Audio_AudioPlayer_H_

#include <string>

#include <SFML/System/Vector2.hpp>
#include <SFML/Audio/Listener.hpp>

#include "AudioProperties.h"

namespace ae
{
	/// <summary>
	/// Abstract base class providing a global volume attribute and listener repositioning<para/>
	///
	/// This base class is inherited by the classes <see cref="MusicPlayer"/> and <see cref="SoundPlayer"/> which we recommend using.
	/// </summary>
	/// <param name="T">The ID type (i.e. an enumeration type)</param>
	template <typename T>
	class AudioPlayer
	{
	public:
		/// <summary>Virtual destructor</summary>
		virtual ~AudioPlayer();
	public:
		/// <summary>
		/// Sets the position of the listener (i.e. the player position)<para/>
		///
		/// The listener's position is the same for both the <see cref="MusicPlayer"/> and the <see cref="SoundPlayer"/>.
		/// </summary>
		/// <param name="pos">The listener's new position</param>
		/// <seealso cref="getListenerPosition"/>
		void setListenerPosition(const sf::Vector2f& pos);
		/// <summary>Retrieves the listener's position</summary>
		/// <returns>The listener's position</returns>
		/// <seealso cref="setListenerPosition"/>
		sf::Vector2f getListenerPosition() const;
		/// <summary>Retrieves the audio player's global volume</summary>
		/// <returns>The audio player's global volume</returns>
		/// <seealso cref="setGlobalVolume"/>
		float getGlobalVolume() const;
		/// <summary>
		/// Sets the audio player's global volume (0% - 100%)<para/>
		///
		/// A global volume of 50% will reduce the audio player's resources' volume by half of their current volume.
		/// </summary>
		/// <param name="globalVolume">The audio player's global volume</param>
		/// <seealso cref="getGlobalVolume"/>
		virtual void setGlobalVolume(float globalVolume) = 0;
		/// <summary>
		/// Loads in an audio resource by providng a <paramref name="filepath"/> and an <paramref name="id"/> to associate it with<para/>
		///
		/// The <see cref="AudioProperties"/> of the audio resource will be those by default.<para/>
		///
		/// Only audio tracks with one channel (mono sounds) can be spatialized.
		/// </summary>
		/// <param name="filepath">The audio resource's filepath</param>
		/// <param name="id">An ID with which to associate the audio resource (i.e. an enum value)</param>
		/// <seealso cref="unload"/>
		virtual void load(const std::string& filepath, T id) = 0;
		/// <summary>
		/// Loads in an audio resource by providing a <paramref name="filepath"/>, an <see cref="AudioProperties"/> that contain the audio properties, and an <paramref name="id"/> to associate it with<para/>
		///
		/// Only audio tracks with one channel (mono sounds) can be spatialized.
		/// </summary>
		/// <param name="filepath">The audio resource's filepath</param>
		/// <param name="properties">The <see cref="AudioProperties"/> that contain the audio resource's properties</param>
		/// <param name="id">An ID with which to associate the audio resource (i.e. an enum value)</param>
		/// <seealso cref="unload"/>
		virtual void load(const std::string& filepath, const AudioProperties& properties, T id) = 0;
		/// <summary>Unloads a loaded-in audio resource by providing the associated <paramref name="id"/></summary>
		/// <param name="id">The ID associated with the resource to unload</param>
		/// <seealso cref="load"/>
		virtual void unload(T id) = 0;
	protected:
		/// <summary>
		/// Default constructor<para/>
		///
		/// The global volume is set to 100% and the listener's position to (0, 0, 300).<br/>
		/// The listener's position is the same for both the <see cref="MusicPlayer"/> and the <see cref="SoundPlayer"/>.
		/// </summary>
		AudioPlayer();
		/// <summary>Deleted copy constructor</summary>
		/// <param name="copy">The <see cref="AudioPlayer"/> to be copied</param>
		AudioPlayer(const AudioPlayer<T>& copy) = delete;
	protected:
		/// <summary>Deleted assignment operator</summary>
		/// <param name="other">The <see cref="AudioPlayer"/> of which its attributes will be copied</param>
		/// <returns>The caller <see cref="AudioPlayer"/></returns>
		AudioPlayer<T>& operator=(const AudioPlayer<T>& other) = delete;

	private:
		float globalVolume_; ///< The audio player's global volume
	};
}
#include "AudioPlayer.inl"
#endif