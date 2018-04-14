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

#ifndef Aeon2D_Utils_Math_H_
#define Aeon2D_Utils_Math_H_

// Forward Declaration(s)
namespace std {
	template <typename T>
	class allocator;

	template <typename T, typename Allocator = allocator<T>>
	class vector;
}
namespace sf {
	template <typename T>
	class Vector2;

	using Vector2f = Vector2<float>;
}

namespace ae
{
	/// <summary>Static utility class that provides various math-related utility functions</summary>
	class Math
	{
	public:
		static const float PI; ///< The mathematical constant of pi

	public:
		/// <summary>
		/// Deleted default constructor<para/>
		///
		/// No instance of this class may be created.
		/// </summary>
		Math() = delete;
	public:
		/// <summary>Converts <paramref name="radians"/> to degrees</summary>
		/// <param name="radians">Value in radians</param>
		/// <returns>Value in degrees</returns>
		/// <code>
		/// float degrees = ae::Math::toDegrees(1.0472f);
		/// </code>
		/// <seealso cref="toRadians"/>
		static float toDegrees(float radians);
		/// <summary>Converts <paramref name="degrees"/> to radians</summary>
		/// <param name="degrees">Value in degrees</param>
		/// <returns>Value in radians</returns>
		/// <code>
		/// float radians = ae::Math::toRadians(60.f);
		/// </code>
		/// <seealso cref="toDegrees"/>
		static float toRadians(float degrees);
		/// <summary>
		/// Normalizes the <paramref name="vec"/> provided<para/>
		///
		/// The process of normalization means that a vector will be converted to a unit vector which is a vector with a magnitude of 1.<br/>
		/// Normalizing a vector can be useful for retrieving the direction of said vector.
		/// </summary>
		/// <param name="vec">The sf::Vector2f that will be normalized</param>
		/// <returns>The unit <paramref name="vec"/></returns>
		/// <code>
		/// sf::Vector2f vec(5.f, 10.f);
		/// sf::Vector2f unitVec = ae::Math::normalize(vec);
		/// </code>
		static sf::Vector2f normalize(const sf::Vector2f& vec);
		/// <summary>
		/// Normalizes a segment formed by <paramref name="vec1"/> and <paramref name="vec2"/><para/>
		///
		/// The process of normalization means that a segment will be converted to a unit segment which is a segment with a magnitude of 1.<br/>
		/// Normalizing a segment can be useful for retrieving the direction of said segment.
		/// </summary>
		/// <param name="vec1">The first sf::Vector2f forming the segment</param>
		/// <param name="vec2">The second sf::Vector2f forming the segment</param>
		/// <returns>The unit segment formed by <paramref name="vec1"/> and <paramref name="vec2"/></returns>
		/// <code>
		/// sf::Vector2f vec1(5.f, 10.f);
		/// sf::Vector2f vec2(8.f, 4.f);
		/// sf::Vector2f unitSeg = ae::Math::normalize(vec1, vec2);
		/// </code>
		static sf::Vector2f normalize(const sf::Vector2f& vec1, const sf::Vector2f& vec2);
		/// <summary>
		/// Calculates the dot product of <paramref name="vec1"/> and <paramref name="vec2"/><para/>
		///
		/// The dot product of two vectors is also called the inner product and is equal to the cosine angle between the two vectors.
		/// </summary>
		/// <param name="vec1">The first sf::Vector2f</param>
		/// <param name="vec2">The second sf::Vector2f</param>
		/// <returns>The dot product (the cosine angle between the two vectors)</returns>
		/// <code>
		/// sf::Vector2f vec1(5.f, 10.f);
		/// sf::Vector2f vec2(8.f, 4.f);22
		/// float dotProduct = ae::Math::dotProduct(vec1, vec2);
		/// </code>
		static float dotProduct(const sf::Vector2f& vec1, const sf::Vector2f& vec2);
		/// <summary>Calculates the row specified of the pascal triangle</summary>
		/// <param name="n">The row to retrieve</param>
		/// <returns>The array of values at the specified row</returns>
		/// <code>
		/// std::vector&lt;int&gt; row22 = ae::Math::pascalTriangle(22);
		/// </code>
		static std::vector<int> pascalTriangle(int n);
	};
}
#endif