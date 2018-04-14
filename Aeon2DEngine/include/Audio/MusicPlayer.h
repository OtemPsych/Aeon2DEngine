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

#ifndef Aeon2D_Audio_MusicPlayer_H_
#define Aeon2D_Audio_MusicPlayer_H_

#include <map>

#include <SFML/Audio/Music.hpp>

#ifdef _DEBUG
#include "../Utils/DebugLogger.h"
#endif
#include "AudioPlayer.h"

namespace ae
{
	/// <summary>Class that facilitates loading in music tracks, playing them, and generally managing them</summary>
	/// <param name="T">The ID type (i.e. and enumeration type)</param>
	template <typename T>
	class MusicPlayer : public AudioPlayer<T>
	{
	public:
		/// <summary>
		/// Default constructor<para/>
		///
		/// The global volume is set to 100% and the listener's position to (0, 0, 300).<br/>
		/// The listener's position is the same for both the <see cref="MusicPlayer"/> and the <see cref="SoundPlayer"/>.
		/// </summary>
		MusicPlayer() = default;
		/// <summary>Deleted copy constructor</summary>
		/// <param name="copy">The <see cref="MusicPlayer"/> to be copied</param>
		MusicPlayer(const MusicPlayer<T>& copy) = delete;
	public:
		/// <summary>Deleted assignment operator</summary>
		/// <param name="other">The <see cref="MusicPlayer"/> to be copied</param>
		/// <returns>The caller <see cref="MusicPlayer"/></returns>
		MusicPlayer<T>& operator=(const MusicPlayer<T>& other) = delete;
	public:
		/// <summary>
		/// Plays a pre-loaded music track by providing an <paramref name="id"/> associated with the desired music track and if it should be on <paramref name="loop"/><para/>
		///
		/// The music track's source will be the position of the listener.
		/// </summary>
		/// <param name="id">The id associated with the desired music track</param>
		/// <param name="loop">True to put the music track on loop, false otherwise</param>
		/// <code>
		/// enum class MusicID { ID1, ID2, ID3 };
		/// ae::MusicPlayer&lt;MusicID&gt; musicPlayer;
		/// ...
		/// musicPlayer.play(MusicID::ID1, true);
		/// </code>
		/// <seealso cref="pause"/>
		/// <seealso cref="stop"/>
		/// <seealso cref="load"/>
		void play(T id, bool loop);
		/// <summary>Plays a pre-loaded music track by providing a <paramref name="position"/> indicating the music track's source, an <paramref name="id"/> associated with the desired music track, and if it should be on <paramref name="loop"/></summary>
		/// <param name="position">The position of the music track's source</param>
		/// <param name="id">The id associated with the desired music track</param>
		/// <param name="loop">True to put the music track on loop, false otherwise</param>
		/// <code>
		/// enum class MusicID { ID1, ID2, ID3 };
		/// ae::MusicPlayer&lt;MusicID&gt; musicPlayer;
		/// ...
		/// musicPlayer.play(sf::Vector2f(250.f, 100.f), MusicID::ID1, true);
		/// </code>
		/// <seealso cref="pause"/>
		/// <seealso cref="stop"/>
		/// <seealso cref="load"/>
		void play(const sf::Vector2f& position, T id, bool loop);
		/// <summary>
		/// (Un)Pauses all active music tracks<para/>
		///
		/// Pausing the music tracks can be useful when you wish to resume playing them from the point where they were previously paused.
		/// </summary>
		/// <param name="flag">True to pause them, false otherwise</param>
		/// <code>
		/// enum class MusicID { ID1, ID2, ID3 };
		/// ae::MusicPlayer&lt;MusicID&gt; musicPlayer;
		/// ...
		/// musicPlayer.pause(true);
		/// </code>
		/// <seealso cref="stop"/>
		/// <seealso cref="play"/>
		void pause(bool flag);
		/// <summary>
		/// (Un)Pauses an active music track<para/>
		///
		/// Pausing a music track can be useful when you wish to resume playing it from the point where it was previously paused.
		/// </summary>
		/// <param name="id">The id associated with the music track to (un)pause</param>
		/// <param name="flag">True to pause it, false otherwise</param>
		/// <code>
		/// enum class MusicID { ID1, ID2, ID3 };
		/// ae::MusicPlayer&lt;MusicID&gt; musicPlayer;
		/// ...
		/// musicPlayer.pause(MusicID::ID2, true);
		/// </code>
		/// <seealso cref="stop"/>
		/// <seealso cref="play"/>
		void pause(T id, bool flag);
		/// <summary>
		/// Stops all active music tracks<para/>
		///
		/// The music tracks' playing position will be reset (unlike the method '<see cref="pause"/>').
		/// </summary>
		/// <code>
		/// enum class MusicID { ID1, ID2, ID3 };
		/// ae::MusicPlayer&lt;MusicID&gt; musicPlayer;
		/// ...
		/// musicPlayer.stop();
		/// </code>
		/// <seealso cref="pause"/>
		/// <seealso cref="play"/>
		void stop();
		/// <summary>
		/// Stops an active music track<para/>
		///
		/// The music track's playing position will be reset (unlike the method '<see cref="pause"/>').
		/// </summary>
		/// <param name="id">The id associated with the music track to stop</param>
		/// <code>
		/// enum class MusicID { ID1, ID2, ID3 };
		/// ae::MusicPlayer&lt;MusicID&gt; musicPlayer;
		/// ...
		/// musicPlayer.stop(MusicID::ID2);
		/// </code>
		/// <seealso cref="pause"/>
		/// <seealso cref="play"/>
		void stop(T id);
		/// <summary>Sets the <paramref name="position"/> of the specified music track's source</summary>
		/// <param name="position">The new position of the specified music track's source</param>
		/// <param name="id">The id associated with the desired music track</param>
		/// <code>
		/// enum class MusicID { ID1, ID2, ID3 };
		/// ae::MusicPlayer&lt;MusicID&gt; musicPlayer;
		/// ...
		/// musicPlayer.setMusicSourcePosition(boomboxZombie.getPosition(), MusicID::ID1);
		/// </code>
		void setMusicSourcePosition(const sf::Vector2f& position, T id);
		/// <summary>Retrieves the status of the specified music track</summary>
		/// <param name="id">The id associated with the desired music track</param>
		/// <returns>The status of the specified music track</returns>
		/// <code>
		/// enum class MusicID { ID1, ID2, ID3 };
		/// ae::MusicPlayer&lt;MusicID&gt; musicPlayer;
		/// ...
		/// if (musicPlayer.getMusicStatus(MusicID::ID2) == sf::SoundSource::Status::Paused) {
		///		...
		/// }
		/// </code>
		sf::SoundSource::Status getMusicStatus(T id) const;
		/// <summary>
		/// Sets the music player's global volume (0% - 100%)<para/>
		///
		/// A global volume of 50% will reduce the music player's tracks' volume by half of their current volume.
		/// </summary>
		/// <param name="globalVolume">The music player's global volume</param>
		/// <code>
		/// enum class MusicID { ID1, ID2, ID3 };
		/// ae::MusicPlayer&lt;MusicID&gt; musicPlayer;
		/// musicPlayer.setGlobalVolume(50.f);
		/// </code>
		virtual void setGlobalVolume(float globalVolume) override final;
		/// <summary>
		/// Loads in a music track by providing a <paramref name="filepath"/> and an <paramref name="id"/> to associate it with<para/>
		///
		/// The <see cref="AudioProperties"/> of the music track will be those by default.<para/>
		///
		/// Only music tracks with one channel (mono sounds) can be spatialized.
		/// </summary>
		/// <param name="filepath">The music track's filepath</param>
		/// <param name="id">An ID with which to associate the music track (i.e. an enum value)</param>
		/// <code>
		/// enum class MusicID { ID1, ID2, ID3 };
		/// ae::MusicPlayer&lt;MusicID&gt; musicPlayer;
		/// musicPlayer.load("Assets/Music/Soundtrack.wav", MusicID::ID1);
		/// </code>
		/// <seealso cref="unload"/>
		/// <seealso cref="play"/>
		virtual void load(const std::string& filepath, T id) override final;
		/// <summary>
		/// Loads in a music track by providing a <paramref name="filepath"/>, an <see cref="AudioProperties"/> that contain the music track's properties, and an <paramref name="id"/> to associate it with<para/>
		///
		/// Only music tracks with one channel (mono sounds) can be spatialized.
		/// </summary>
		/// <param name="filepath">The music track's filepath</param>
		/// <param name="properties">The <see cref="AudioProperties"/> that contain the music track's properties</param>
		/// <param name="id">An ID with which to associate the music track (i.e. an enum value)</param>
		/// <code>
		/// enum class MusicID { ID1, ID2, ID3 };
		/// ae::MusicPlayer&lt;MusicID&gt; musicPlayer;
		/// musicPlayer.load("Assets/Music/Soundtrack.wav", ae::AudioProperties(100.f, 35.f, 1.f, 250.f), MusicID::ID1);
		/// </code>
		/// <seealso cref="unload"/>
		/// <seealso cref="play"/>
		virtual void load(const std::string& filepath, const AudioProperties& properties, T id) override final;
		/// <summary>
		/// Unloads a loaded-in music track by providing the associated <paramref name="id"/><para/>
		///
		/// The music track associated with this <paramref name="id"/> will be removed (even if it's currently playing).
		/// </summary>
		/// <param name="id">The ID associated with the music track to unload</param>
		/// <code>
		/// enum class MusicID { ID1, ID2, ID3 };
		/// ae::MusicPlayer&lt;MusicID&gt; musicPlayer;
		/// ...
		/// musicPlayer.unload(MusicID::ID1);
		/// </code>
		/// <seealso cref="load"/>
		virtual void unload(T id) override final;
	private:
		/// <summary>Sets up the new music track by providing the <see cref="AudioProperties"/> and the <paramref name="filepath"/> of the music track</summary>
		/// <param name="properties">The <see cref="AudioProperties"/> that contain the music track's properties</param>
		/// <param name="filepath">The music track's filepath</param>
		void setupTrack(const AudioProperties& properties, const std::string& filepath);

	private:
		/// <summary>Struct used to represent a music track along with its original volume</summary>
		struct MusicTrack {
			sf::Music   music;  ///< The sf::Music object
			const float VOLUME; ///< The original volume of the music track

			/// <summary>Constructs the <see cref="MusicTrack"/> by providing the original <paramref name="volume"/></summary>
			/// <param name="volume">The original volume of the music track</param>
			explicit MusicTrack(float volume);
			/// <summary>Move constructor</summary>
			/// <param name="other">The <see cref="MusicTrack"/> to be moved</param>
			MusicTrack(MusicTrack&& other);
		};
	private:
		std::map<T, MusicTrack> tracks_; ///< The list of all loaded-in music tracks
	};
}
#include "MusicPlayer.inl"
#endif