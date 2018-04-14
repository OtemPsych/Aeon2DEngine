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

#ifndef Aeon2D_Utils_ResourceHolder_H_
#define Aeon2D_Utils_ResourceHolder_H_

#include <map>
#include <memory>

#ifdef _DEBUG
#include "DebugLogger.h"
#endif

// Forward Declaration(s)
namespace sf {
	class Texture;
	class Image;
	class Font;
	class SoundBuffer;
	class Shader;
}

namespace ae
{
	/// <summary>
	/// Used to store SFML resources by providing a filename and an ID (an enum value)<para/>
	///
	/// Available typedefs: TextureHolder, ImageHolder, FontHolder, SoundBufferHolder, and ShaderHolder.<br/>
	/// Only the ID has to be provided if a typedef is used.
	/// </summary>
	/// <param name="ID">The ID type (i.e. an enumeration type)</param>
	/// <param name="Res">The SFML resource type (sf::Texture, sf::Image, etc.)</param>
	template <typename ID, typename Res>
	class ResourceHolder
	{
	public:
		/// <summary>Default constructor</summary>
		/// <code>
		/// enum class ID { ID1, ID2, ID3 };<br/>
		/// ae::ResourceHolder&lt;ID, sf::Texture&gt; textureHolder;
		/// </code>
		ResourceHolder() = default;
		/// <summary>Deleted copy constructor</summary>
		/// <param name="copy">The <see cref="ResourceHolder"/> to be copied</param>
		ResourceHolder(const ResourceHolder<ID, Res>& copy) = delete;
	public:
		/// <summary>Deleted assignment operator</summary>
		/// <param name="other">The <see cref="ResourceHolder"/> to be copied</param>
		/// <returns>The caller <see cref="ResourceHolder"/></returns>
		ResourceHolder<ID, Res>& operator=(const ResourceHolder<ID, Res>& other) = delete;
	public:
		/// <summary>Loads in a resource by providing a <paramref name="filepath"/> and an <paramref name="id"/> to associate it with</summary>
		/// <param name="filepath">String containing the resource's filepath</param>
		/// <param name="id">The id with which to associate the resource</param>
		/// <code>
		/// enum class ID { ID1, ID2, ID3 };
		/// ae::TextureHolder&lt;ID&gt; textureHolder;
		/// textureHolder.load("Assets/Textures/Player.png", ID::ID1);
		/// </code>
		/// <seealso cref="unload"/>
		/// <seealso cref="get"/>
		void load(const std::string& filepath, ID id);
		/// <summary>
		/// Loads in a resource by providing a <paramref name="filepath"/>, an extra parameter <paramref name="t"/>, and an <paramref name="id"/> to associate it with<para/>
		///
		/// The extra parameter will almost always be used for loading in a shader.
		/// </summary>
		/// <param name="filepath">String containing the resource's filepath</param>
		/// <param name="t">The extra parameter</param>
		/// <param name="id">The id with which to associate the resource</param>
		/// <code>
		/// // Example usage for a shader
		/// enum class ShaderID { ID1, ID2, ID3 };
		/// ae::ShaderHolder&lt;ShaderID&gt; shaderHolder;
		/// shaderHolder.load("Assets/Shaders/GaussianBlur.frag", sf::Shader::Fragment, ShaderID::ID1);
		/// </code>
		/// <seealso cref="unload"/>
		/// <seealso cref="get"/>
		template <typename T>
		void load(const std::string& filepath, const T& t, ID id);
		/// <summary>
		/// Loads in a resource by providing a <paramref name="filepath"/>, 2 extra parameters <paramref name="t"/> and <paramref name="k"/>, and an <paramref name="id"/> to associate it with<para/>
		///
		/// The extra parameters will almost always be used for loading in a shader.
		/// </summary>
		/// <param name="filepath">String containing the resource's filepath</param>
		/// <param name="t">The first extra parameter</param>
		/// <param name="k">The second extra parameter</param>
		/// <param name="id">The id with which to associate the resource</param>
		/// <code>
		/// // Example usage for a shader
		/// enum class ShaderID { ID1, ID2, ID3 };
		/// ae::ShaderHolder&lt;ShaderID&gt; shaderHolder;
		/// shaderHolder.load("Assets/Shaders/VertShader.vert", "Assets/Shaders/GeomShader.geom", "Assets/Shaders/FragShader.frag", ShaderID::ID1);
		/// </code>
		/// <seealso cref="unload"/>
		/// <seealso cref="get"/>
		template <typename T, typename K>
		void load(const std::string& filepath, const T& t, const K& k, ID id);
		/// <summary>Unloads a loaded-in resource by providing the associated <paramref name="id"/></summary>
		/// <param name="id">The id associated with the resource to unload</param>
		/// <code>
		/// enum class ID { ID1, ID2, ID3 };
		/// ae::TextureHolder&lt;ID&gt; textureHolder;
		/// ...
		/// textureHolder.unload(ID::ID1);
		/// </code>
		/// <seealso cref="load"/>
		void unload(ID id);
		/// <summary>Retrieves a stored resource by providing the associated <paramref name="id"/></summary>
		/// <param name="id">The id associated to the resource to retrieve</param>
		/// <returns>The pointer to the resource associated with the <paramref name="id"/> provided</returns>
		/// <code>
		/// enum class TextureID { ID1, ID2, ID3 };
		/// ae::TextureHolder&lt;TextureID&gt; textureHolder;
		/// ...
		/// sf::Texture* const spaceshipTexture = textureHolder.get(TextureID::ID2);
		/// </code>
		/// <seealso cref="load"/>
		Res* const get(ID id);
		/// <summary>Retrieves a stored resource by providing the associated <paramref name="id"/></summary>
		/// <param name="id">The id associated to the resource to retrieve</param>
		/// <returns>The pointer to the resource associated with the <paramref name="id"/> provided</returns>
		/// <code>
		/// enum class TextureID { ID1, ID2, ID3 };
		/// ae::TextureHolder&lt;TextureID&gt; textureHolder;
		/// ...
		/// const sf::Texture* const spaceshipTexture = textureHolder.get(TextureID::ID2);
		/// </code>
		/// <seealso cref="load"/>
		const Res* const get(ID id) const;

	private:
		std::map<ID, std::unique_ptr<Res>> resourceMap_; ///< The list of sfml resources that have been loaded in
	};

	// Typedef(s)
	template <typename ID>
	using TextureHolder = ResourceHolder<ID, sf::Texture>;
	template <typename ID>
	using ImageHolder = ResourceHolder<ID, sf::Image>;
	template <typename ID>
	using FontHolder = ResourceHolder<ID, sf::Font>;
	template <typename ID>
	using SoundBufferHolder = ResourceHolder<ID, sf::SoundBuffer>;
	template <typename ID>
	using ShaderHolder = ResourceHolder<ID, sf::Shader>;
}
#include "ResourceHolder.inl"
#endif