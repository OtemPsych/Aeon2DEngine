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
	template <typename ID, typename Res>
	void ResourceHolder<ID, Res>::load(const std::string& filepath, ID id)
	{
		std::unique_ptr<Res> res = std::make_unique<Res>();
		if (res->loadFromFile(filepath)) {
			resourceMap_.insert(std::make_pair(id, std::move(res)));
		}
#ifdef _DEBUG
		else {
			DebugLogger::cacheMessage("ae::ResourceHolder::load - Failed to load \"" + filepath + '"');
		}
#endif
	}

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
	template <typename ID, typename Res>
	template <typename T>
	void ResourceHolder<ID, Res>::load(const std::string& filepath, const T& t, ID id)
	{
		std::unique_ptr<Res> res = std::make_unique<Res>();
		if (res->loadFromFile(filepath, t)) {
			resourceMap_.insert(std::make_pair(id, std::move(res)));
		}
#ifdef _DEBUG
		else {
			DebugLogger::cacheMessage("ae::ResourceHolder::load<T> - Failed to load \"" + filepath + '"');
		}
#endif
	}

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
	template <typename ID, typename Res>
	template <typename T, typename K>
	void ResourceHolder<ID, Res>::load(const std::string& filepath, const T& t, const K& k, ID id)
	{
		std::unique_ptr<Res> res = std::make_unique<Res>();
		if (res->loadFromFile(filepath, t, k)) {
			resourceMap_.insert(std::make_pair(id, std::move(res)));
		}
#ifdef _DEBUG
		else {
			DebugLogger::cacheMessage("ae::ResourceHolder::load<T,K> - Failed to load \"" + filepath + '"');
		}
#endif
	}

	/// <summary>Unloads a loaded-in resource by providing the associated <paramref name="id"/></summary>
	/// <param name="id">The id associated with the resource to unload</param>
	/// <code>
	/// enum class ID { ID1, ID2, ID3 };
	/// ae::TextureHolder&lt;ID&gt; textureHolder;
	/// ...
	/// textureHolder.unload(ID::ID1);
	/// </code>
	/// <seealso cref="load"/>
	template <typename ID, typename Res>
	void ResourceHolder<ID, Res>::unload(ID id)
	{
#ifdef _DEBUG
		auto found = resourceMap_.find(id);
		if (found == resourceMap_.end()) {
			DebugLogger::cacheMessage("ae::ResourceHolder::unload - Unable to find resource");
			return;
		}
		resourceMap_.erase(found);
#else
		resourceMap_.erase(resourceMap_.find(id));
#endif
	}

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
	template <typename ID, typename Res>
	Res* const ResourceHolder<ID, Res>::get(ID id)
	{
#ifdef _DEBUG
		auto found = resourceMap_.find(id);
		if (found == resourceMap_.end()) {
			DebugLogger::cacheMessage("ae::ResourceHolder::get - Unable to find resource");
			return nullptr;
		}
		return found->second.get();
#else
		return resourceMap_.find(id)->second.get();
#endif
	}

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
	template <typename ID, typename Res>
	const Res* const ResourceHolder<ID, Res>::get(ID id) const
	{
#ifdef _DEBUG
		auto found = resourceMap_.find(id);
		if (found == resourceMap_.end()) {
			DebugLogger::cacheMessage("ae::ResourceHolder::get - Unable to find resource");
			return nullptr;
		}
		return found->second.get();
#else
		return resourceMap_.find(id)->second.get();
#endif
	}
}