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
	/// <summary>Virtual destructor</summary>
	template <typename T>
	AudioPlayer<T>::~AudioPlayer()
	{
	}

	/// <summary>
	/// Sets the position of the listener (i.e. the player position)<para/>
	///
	/// The listener's position is the same for both the <see cref="MusicPlayer"/> and the <see cref="SoundPlayer"/>.
	/// </summary>
	/// <param name="pos">The listener's new position</param>
	/// <seealso cref="getListenerPosition"/>
	template <typename T>
	void AudioPlayer<T>::setListenerPosition(const sf::Vector2f& pos)
	{
		sf::Listener::setPosition(pos.x, -pos.y, sf::Listener::getPosition().z);
	}

	/// <summary>Retrieves the listener's position</summary>
	/// <returns>The listener's position</returns>
	/// <seealso cref="setListenerPosition"/>
	template <typename T>
	sf::Vector2f AudioPlayer<T>::getListenerPosition() const
	{
		sf::Vector3f pos = sf::Listener::getPosition();
		return sf::Vector2f(pos.x, -pos.y);
	}

	/// <summary>Retrieves the audio player's global volume</summary>
	/// <returns>The audio player's global volume</returns>
	/// <seealso cref="setGlobalVolume"/>
	template <typename T>
	float AudioPlayer<T>::getGlobalVolume() const
	{
		return globalVolume_;
	}

	/// <summary>
	/// Sets the audio player's global volume (0% - 100%)<para/>
	///
	/// A global volume of 50% will reduce the audio player's resources' volume by half of their current volume.
	/// </summary>
	/// <param name="globalVolume">The audio player's global volume</param>
	/// <seealso cref="getGlobalVolume"/>
	template <typename T>
	void AudioPlayer<T>::setGlobalVolume(float globalVolume)
	{
		// Verifies that the global volume is within the range [0, 100]
		globalVolume_ = fmaxf(fminf(globalVolume, 100.f), 0.f);
	}

	/// <summary>
	/// Default constructor<para/>
	///
	/// The global volume is set to 100% and the listener's position to (0, 0, 300).<br/>
	/// The listener's position is the same for both the <see cref="MusicPlayer"/> and the <see cref="SoundPlayer"/>.
	/// </summary>
	template <typename T>
	AudioPlayer<T>::AudioPlayer()
		: globalVolume_(100.f)
	{
		sf::Listener::setPosition(0.f, 0.f, 300.f);
	}
}