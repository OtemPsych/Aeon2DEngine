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

#ifndef Aeon2D_Audio_AudioProperties_H_
#define Aeon2D_Audio_AudioProperties_H_

namespace ae
{
	/// <summary>
	/// A container class for a specific audio's (sound or music) properties<para/>
	///
	/// Audio properties include volume, attenuation, pitch, minimum 2D distance and listener relativity.
	/// </summary>
	class AudioProperties
	{
	public:
		/// <summary>
		/// Constructs the <see cref="AudioProperties"/> by providing a <paramref name="volume"/>, an <paramref name="attenuation"/>, a <paramref name="pitch"/>, a minimum 2D distance where the audio is heard at full volume, and if the audio source is relative to the listener<para/>
		///
		/// All the parameters are optional and can be modified later.
		/// </summary>
		/// <param name="volume">
		/// The volume is a value between 0 (mute) and 100 (full volume)<para/>
		///
		/// The default value for the volume is 100.
		/// </param>
		/// <param name="attenuation">
		/// The attenuation is a multiplicative factor which makes an audio more or less loud according to its distance from the listener.<br/>
		/// An attenuation of 0 will produce a non-attenuated audio, i.e. its volume will always be the same whether it is heard from near or from far.<br/>
		/// On the other hand, an attenuation value such as 100 will make an audio fade out very quickly as it gets further from the listener.<para/>
		///
		/// The default value of the attenuation is 1.
		/// </param>
		/// <param name="pitch">
		/// The pitch represents the perceived fundamental frequency of an audio; thus you can make it more acute or grave by changing its pitch.<br/>
		/// A side effect of changing the pitch is to modify the playing speed of an audio as well.<para/>
		///
		/// The default value for the pitch is 1.
		/// </param>
		/// <param name="minDistance2d">
		/// The "minimum distance" of an audio is the maximum distance at which it is heard at its maximum volume.<br/>
		/// Further than the minimum distance, it will start to fade out according to its attenuation factor.<br/>
		/// A value of 0 ("inside the head of the listener") is an invalid value and is forbidden.<para/>
		///
		/// The default value for the minimum distance is 1.
		/// </param>
		/// <param name="relativeToListener">
		/// Making an audio relative to the listener will ensure that it will always be played the same way regardless of the position of the listener.<br/>
		/// This can be useful for non-spatialized audios, that are produced by the listener, or that are attached to it.<para/>
		///
		/// The default value is false (position is absolute).
		/// </param>
		/// <code>
		/// ae::AudioProperties props1;       // all the properties are set to their default values
		/// ae::AudioProperties props2(65.f); // volume is set to 65%, all the other properties are set to their default values
		/// </code>
		explicit AudioProperties(float volume = 100.f, float attenuation = 1.f, float pitch = 1.f,
			                     float minDistance2d = 1.f, bool relativeToListener = false);
		/// <summary>Copy constructor</summary>
		/// <param name="copy">The <see cref="AudioProperties"/> to be copied</param>
		/// <code>
		/// ae::AudioProperties props1;
		/// ae::AudioProperties props2(props1);
		/// </code>
		AudioProperties(const AudioProperties& copy);
		/// <summary>Move constructor</summary>
		/// <param name="other">The <see cref="AudioProperties"/> to be moved</param>
		/// <code>
		/// ae::AudioProperties props1;
		/// ...
		/// ae::AudioProperties props2(std::move(props1));
		/// </code>
		AudioProperties(AudioProperties&& other);
	public:
		/// <summary>
		/// Assignment operator overload<para/>
		///
		/// Assigns the <paramref name="other"/> <see cref="AudioProperties"/>'s attributes to the caller <see cref="AudioProperties"/>'s attributes.
		/// </summary>
		/// <param name="other">The <see cref="AudioProperties"/> of which its attributes will be copied</param>
		/// <returns>The caller <see cref="AudioProperties"/></returns>
		/// <code>
		/// ae::AudioProperties props1;
		/// ae::AudioProperties props2(5.f);
		/// props1 = props2;
		/// </code>
		/// <seealso cref="operator=="/>
		/// <seealso cref="operator!="/>
		AudioProperties& operator=(const AudioProperties& other);
		/// <summary>
		/// Move assignment operator overload<para/>
		///
		/// Moves the <paramref name="other"/> <see cref="AudioProperties"/>'s attributes to the caller <see cref="AudioProperties"/>'s attributes.
		/// </summary>
		/// <param name="other">The <see cref="AudioProperties"/> of which its attributes will be moved</param>
		/// <returns>The caller <see cref="AudioProperties"/></returns>
		/// <code>
		/// ae::AudioProperties props1;
		/// ae::AudioProperties props2(5.f);
		/// props1 = std::move(props2);
		/// </code>
		/// <seealso cref="operator=="/>
		/// <seealso cref="operator!="/>
		AudioProperties& operator=(AudioProperties&& other);
		/// <summary>
		/// Equality operator overload<para/>
		///
		/// Checks if the two <see cref="AudioProperties"/> objects are equal.
		/// </summary>
		/// <param name="ap1">The first <see cref="AudioProperties"/> object</param>
		/// <param name="ap2">The second <see cref="AudioProperties"/> object</param>
		/// <returns>True if the two <see cref="AudioProperties"/> objects are equal, false otherwise</returns>
		/// <code>
		/// ae::AudioProperties props1(5.f);
		/// ae::AudioProperties props2;
		/// if (props1 == props2) {
		///		...
		/// }
		/// </code>
		/// <seealso cref="operator!="/>
		friend bool operator==(const AudioProperties& ap1, const AudioProperties& ap2);
		/// <summary>
		/// Inequality operator overload<para/>
		///
		/// Checks if the two <see cref="AudioProperties"/> objects are inequal.
		/// </summary>
		/// <param name="ap1">The first <see cref="AudioProperties"/> object</param>
		/// <param name="ap2">The second <see cref="AudioProperties"/> object</param>
		/// <returns>True if the two <see cref="AudioProperties"/> objects are inequal, false otherwise</returns>
		/// <code>
		/// ae::AudioProperties props1(5.f);
		/// ae::AudioProperties props2;
		/// if (props1 != props2) {
		///		...
		/// }
		/// </code>
		/// <seealso cref="operator=="/>
		friend bool operator!=(const AudioProperties& ap1, const AudioProperties& ap2);
	public:
		/// <summary>
		/// Sets the volume to a value between 0 (mute) and 100 (full volume)<para/>
		///
		/// Values under 0 are set to 0 and values higher than 100 are set to 100.
		/// </summary>
		/// <param name="volume">The new volume value</param>
		/// <code>
		/// ae::AudioProperties props;
		/// props.setVolume(50.f);                   // sets volume to 50%
		/// props.setVolume(props.getVolume() / 2.f) // sets volume to half of 50%, meaning 25%
		/// </code>
		/// <seealso cref="getVolume"/>
		void setVolume(float volume);
		/// <summary>
		/// Sets the minimum 2d distance of the audio<para/>
		///
		/// The "minimum distance" of an audio is the maximum distance at which it is heard at its maximum volume.<br/>
		/// Further than the minimum distance, it will start to fade out according to its attenuation factor.<br/>
		/// A value of 0 ("inside the head of the listener") is an invalid value and is forbidden.<para/>
		///
		/// Values under 1 are set to 1.
		/// </summary>
		/// <param name="minDistance2d">The new minimum 2d distance</param>
		/// <code>
		/// ae::AudioProperties props;
		/// props.setMinDistance2D(500.f); // the maximum distance in which the audio is heard at full volume is set to 500
		/// </code>
		/// <seealso cref="getMinDistance2D"/>
		/// <seealso cref="getMinDistance3D"/>
		void setMinDistance2D(float minDistance2d);
		/// <summary>
		/// Sets the attenuation factor of the audio<para/>
		///
		/// The attenuation is a multiplicative factor which makes an audio more or less loud according to its distance from the listener.<br/>
		/// An attenuation of 0 will produce a non-attenuated audio, i.e. its volume will always be the same whether it is heard from near or from far.<br/>
		/// On the other hand, an attenuation value such as 100 will make an audio fade out very quickly as it gets further from the listener.<para/>
		///
		/// Values under 0 are set to 0.
		/// </summary>
		/// <param name="attenuation">The new attenuation factor</param>
		/// <code>
		/// ae::AudioProperties props;
		/// props.setAttenuation(20.f); // the audio will start fading out once it's out of the minimum 2d distance by multiplicative factor of 20
		/// </code>
		/// <seealso cref="getAttenuation"/>
		inline void setAttenuation(float attenuation) { attenuation_ = fmaxf(attenuation, 0.f); }
		/// <summary>
		/// Sets the pitch frequency of the audio<para/>
		///
		/// The pitch represents the perceived fundamental frequency of an audio; thus you can make it more acute or grave by changing its pitch.<br/>
		/// A side effect of changing the pitch is to modify the playing speed of an audio as well.
		/// </summary>
		/// <param name="pitch">The new pitch frequency</param>
		/// <code>
		/// ae::AudioProperties props;
		/// props.setPitch(10.f); // sets the pitch to a more acute frequency
		/// </code>
		/// <seealso cref="getPitch"/>
		inline void setPitch(float pitch) { pitch_ = pitch; }
		/// <summary>
		/// (De)Activates the audio's source as relative to the listener<para/>
		///
		/// Making an audio relative to the listener will ensure that it will always be played the same way regardless of the position of the listener.<br/>
		/// This can be useful for non-spatialized audios, that are produced by the listener, or that are attached to it.<para/>
		/// </summary>
		/// <param name="flag">True to make the audio relative to the listener, false otherwise</param>
		/// <code>
		/// ae::AudioProperties props;
		/// props.setRelativeToListener(true); // the audio will now always be heard at full volume no matter how far the audio's source is from the listener
		/// </code>
		/// <seealso cref="isRelativeToListener"/>
		inline void setRelativeToListener(bool flag) { relativeToListener_ = flag; }
		/// <summary>Retrieves the volume value</summary>
		/// <returns>The volume value</returns>
		/// <code>
		/// ae::AudioProperties props(25.f); // sets the volume to 25%
		/// float volume = props.getVolume();
		/// </code>
		/// <seealso cref="setVolume"/>
		inline float getVolume() const { return volume_; }
		/// <summary>Retrieves the attenuation factor</summary>
		/// <returns>The attenuation factor</returns>
		/// <code>
		/// ae::AudioProperties props(25.f, 20.f); // sets the attenuation factor to 20
		/// float attenuation = props.getAttenuation();
		/// </code>
		/// <seealso cref="setAttenuation"/>
		inline float getAttenuation() const { return attenuation_; }
		/// <summary>Retrieves the pitch frequency</summary>
		/// <returns>The pitch frequency</returns>
		/// <code>
		/// ae::AudioProperties props(25.f, 20.f, 3.f); // sets the pitch frequency to 3
		/// float pitch = props.getPitch();
		/// </code>
		/// <seealso cref="setPitch"/>
		inline float getPitch() const { return pitch_; }
		/// <summary>Retrieves the minimum 2d distance where the audio is heard at full volume</summary>
		/// <returns>The minimum 2d distance</returns>
		/// <code>
		/// ae::AudioProperties props(25.f, 20.f, 3.f, 350.f); // sets the minimum 2d distance to 350px
		/// float minDistance2d = props.getMinDistance2D();
		/// </code>
		/// <seealso cref="setMinDistance2D"/>
		/// <seealso cref="getMinDistance3D"/>
		inline float getMinDistance2D() const { return minDistance2d_; }
		/// <summary>
		/// Retrieves the minimum 3d distance where the audio is heard at full volume<para/>
		///
		/// The minimum 3d distance is calculated automatically when providing the minimum 2d distance.
		/// </summary>
		/// <returns>The minimum 3d distance</returns>
		/// <code>
		/// ae::AudioProperties props(25.f, 20.f, 3.f, 350.f); // sets the minimum 2d distance to 350px
		/// float minDistance3d = props.getMinDistance3D();    // retrieves the hypotenuse of the minimum 2d distance and the listener's z position
		/// </code>
		/// <seealso cref="getMinDistance2D"/>
		/// <seealso cref="setMinDistance2D"/>
		inline float getMinDistance3D() const { return minDistance3d_; }
		/// <summary>Checks if the audio is relative to the listener or not</summary>
		/// <returns>True if the audio is relative to the listener, false otherwise</returns>
		/// <code>
		/// ae::AudioProperties props(25.f, 20.f, 3.f, 350.f, true); // sets the audio as relative to the listener
		/// bool relativeToListener = props.isRelativeToListener();
		/// </code>
		/// <seealso cref="setRelativeToListener"/>
		inline bool isRelativeToListener() const { return relativeToListener_; }

	private:
		float volume_;             ///< The volume
		float attenuation_;        ///< The attenuation factor
		float pitch_;              ///< The pitch frequency
		float minDistance2d_;      ///< The minimum 2d distance where the audio is heard at full volume
		float minDistance3d_;      ///< The minimum 3d distance where the audio is heard at full volume
		bool  relativeToListener_; ///< Is the audio source relative to the listener?
	};
}
#endif