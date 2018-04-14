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

#ifndef Aeon2D_Utils_DebugLogger_H_
#define Aeon2D_Utils_DebugLogger_H_

#include <vector>

namespace ae
{
	/// <summary>
	/// Static class that logs debug info to the console<para/>
	///
	/// It can also be used by the engine user for application-specific debug info.<br/>
	/// The debug info is only logged automatically to the console in debug mode.
	/// </summary>
	class DebugLogger
	{
	public:
		/// <summary>
		/// Deleted default constructor<para/>
		///
		/// No instance of this class may be created.
		/// </summary>
		DebugLogger() = delete;
	public:
		/// <summary>Caches a new debug <paramref name="message"/></summary>
		/// <param name="message">String containing the debug message</param>
		/// <code>
		/// ae::DebugLogger::cacheMessage("...");
		/// ae::DebugLogger::cacheMessage(std::to_string(5) + "...");
		/// </code>
		/// <seealso cref="getCachedMessages"/>
		static void cacheMessage(const std::string& message);
		/// <summary>
		/// Retrieves the cached messages and clears out the cached contents<para/>
		///
		/// The cached messages are retrieved and displayed in the console automatically in debug mode.
		/// </summary>
		/// <returns>The cached messages</returns>
		/// <code>
		/// std::vector&lt;string&gt; messages = ae::DebugLogger::getCachedMessages();
		/// for (const std::string&amp; message : messages) {
		///		std::cout &lt;&lt; message &lt;&lt; std::endl;
		/// }
		/// </code>
		/// <seealso cref="cacheMessage"/>
		static std::vector<std::string> getCachedMessages();

	private:
		static std::vector<std::string> messages_; ///< The cached debug messages
	};
}
#endif