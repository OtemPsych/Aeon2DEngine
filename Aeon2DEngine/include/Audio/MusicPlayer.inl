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
	template <typename T>
	void MusicPlayer<T>::play(T id, bool loop)
	{
		play(AudioPlayer<T>::getListenerPosition(), id, loop);
	}

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
	template <typename T>
	void MusicPlayer<T>::play(const sf::Vector2f& position, T id, bool loop)
	{
#ifdef _DEBUG
		auto found = tracks_.find(id);
		if (found == tracks_.end()) {
			DebugLogger::cacheMessage("ae::MusicPlayer<T>::play - Unable to find music track");
			return;
		}
		MusicTrack& track = found->second;
#else
		MusicTrack& track = tracks_.find(id)->second;
#endif
		track.music.setPosition(position.x, -position.y, 0.f);
		track.music.setLoop(loop);
		track.music.setVolume(AudioPlayer<T>::getGlobalVolume() * track.VOLUME / 100.f);
		track.music.play();
	}

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
	template <typename T>
	void MusicPlayer<T>::pause(bool flag)
	{
		if (flag)
			for (auto& track : tracks_) {
				if (track.second.music.getStatus() == sf::SoundSource::Status::Playing)
					track.second.music.pause();
			}
		else
			for (auto& track : tracks_) {
				if (track.second.music.getStatus() == sf::SoundSource::Status::Paused)
					track.second.music.play();
			}
	}

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
	template <typename T>
	void MusicPlayer<T>::pause(T id, bool flag)
	{
#ifdef _DEBUG
		auto found = tracks_.find(id);
		if (found == tracks_.end()) {
			DebugLogger::cacheMessage("ae::MusicPlayer<T>::pause - Unable to find music track");
			return;
		}
		sf::Music& music = found->second.music;
#else
		sf::Music& music = tracks_.find(id)->second.music;
#endif
		if (flag && music.getStatus() == sf::SoundSource::Status::Playing)
			music.pause();
		else if (!flag && music.getStatus() == sf::SoundSource::Status::Paused)
			music.play();
	}

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
	template <typename T>
	void MusicPlayer<T>::stop()
	{
		for (auto& track : tracks_)
			track.second.music.stop();
	}

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
	template <typename T>
	void MusicPlayer<T>::stop(T id)
	{
#ifdef _DEBUG
		auto found = tracks_.find(id);
		if (found == tracks_.end()) {
			DebugLogger::cacheMessage("ae::MusicPlayer<T>::stop - Unable to find music track");
			return;
		}
		found->second.music.stop();
#else
		tracks_.find(id)->second.music.stop();
#endif
	}

	/// <summary>Sets the <paramref name="position"/> of the specified music track's source</summary>
	/// <param name="position">The new position of the specified music track's source</param>
	/// <param name="id">The id associated with the desired music track</param>
	/// <code>
	/// enum class MusicID { ID1, ID2, ID3 };
	/// ae::MusicPlayer&lt;MusicID&gt; musicPlayer;
	/// ...
	/// musicPlayer.setMusicSourcePosition(boomboxZombie.getPosition(), MusicID::ID1);
	/// </code>
	template <typename T>
	void MusicPlayer<T>::setMusicSourcePosition(const sf::Vector2f& position, T id)
	{
#ifdef _DEBUG
		auto found = tracks_.find(id);
		if (found == tracks_.end()) {
			DebugLogger::cacheMessage("ae::MusicPlayer<T>::setMusicSourcePosition - Unable to find music track");
			return;
		}
		found->second.music.setPosition(position.x, -position.y, 0.f);
#else
		tracks_.find(id)->second.music.setPosition(position.x, -position.y, 0.f);
#endif
	}

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
	template <typename T>
	sf::SoundSource::Status MusicPlayer<T>::getMusicStatus(T id) const
	{
#ifdef _DEBUG
		auto found = tracks_.find(id);
		if (found == tracks_.end()) {
			DebugLogger::cacheMessage("ae::MusicPlayer<T>::getMusicStatus - Unable to find music track");
			return sf::SoundSource::Status::Stopped;
		}
		return found->second.music.getStatus();
#else
		return tracks_.find(id)->second.music.getStatus();
#endif
	}

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
	template <typename T>
	void MusicPlayer<T>::setGlobalVolume(float globalVolume)
	{
		AudioPlayer<T>::setGlobalVolume(globalVolume);

		const float GLOBAL_VOLUME = AudioPlayer<T>::getGlobalVolume();
		for (auto& track : tracks_)
			track.second.music.setVolume(GLOBAL_VOLUME * track.second.VOLUME / 100.f);
	}

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
	template <typename T>
	void MusicPlayer<T>::load(const std::string& filepath, T id)
	{
		if (tracks_.find(id) == tracks_.end()) {
			AudioProperties properties;
			tracks_.insert(std::make_pair(id, MusicTrack(properties.getVolume())));
			setupTrack(properties, filepath);
		}
#ifdef _DEBUG
		else {
			DebugLogger::cacheMessage("ae::MusicPlayer<T>::load - Attempt to load in music track that's already loaded in");
		}
#endif
	}

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
	template <typename T>
	void MusicPlayer<T>::load(const std::string& filepath, const AudioProperties& properties, T id)
	{
		if (tracks_.find(id) == tracks_.end()) {
			tracks_.insert(std::make_pair(id, MusicTrack(properties.getVolume())));
			setupTrack(properties, filepath);
		}
#ifdef _DEBUG
		else {
			DebugLogger::cacheMessage("ae::MusicPlayer<T>::load - Attempt to load in music track that's already loaded in");
		}
#endif
	}

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
	template <typename T>
	void MusicPlayer<T>::unload(T id)
	{
#ifdef _DEBUG
		auto found = tracks_.find(id);
		if (found == tracks_.end()) {
			DebugLogger::cacheMessage("ae::MusicPlayer<T>::unload - The ID provided isn't associated with any music track");
			return;
		}
		tracks_.erase(found);
#else
		tracks_.erase(tracks_.find(id));
#endif
	}

	/// <summary>Sets up the new music track by providing the <see cref="AudioProperties"/> and the <paramref name="filepath"/> of the music track</summary>
	/// <param name="properties">The <see cref="AudioProperties"/> that contain the music track's properties</param>
	/// <param name="filepath">The music track's filepath</param>
	template <typename T>
	void MusicPlayer<T>::setupTrack(const AudioProperties& properties, const std::string& filepath)
	{
		// Retrieve the newly inserted music track and configure its properties
		sf::Music& music = tracks_.rbegin()->second.music;
		if (music.openFromFile(filepath)) {
			music.setAttenuation(properties.getAttenuation());
			music.setPitch(properties.getPitch());
			music.setMinDistance(properties.getMinDistance3D());
			music.setRelativeToListener(properties.isRelativeToListener());
		}
		else {
#ifdef _DEBUG
			DebugLogger::cacheMessage("ae::MusicPlayer<T>::loadTrack - Failed to open \"" + filepath + '"');
#endif
			tracks_.erase(tracks_.rbegin()->first);
		}
	}

	/// <summary>Constructs the <see cref="MusicTrack"/> by providing the original <paramref name="volume"/></summary>
	/// <param name="volume">The original volume of the music track</param>
	template <typename T>
	MusicPlayer<T>::MusicTrack::MusicTrack(float volume)
		: music()
		, VOLUME(volume)
	{
	}

	/// <summary>Move constructor</summary>
	/// <param name="other">The <see cref="MusicTrack"/> to be moved</param>
	template <typename T>
	MusicPlayer<T>::MusicTrack::MusicTrack(MusicTrack&& other)
		: music()
		, VOLUME(std::move(other.VOLUME))
	{
	}
}