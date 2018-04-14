#include "../../include/Utils/DebugLogger.h"

namespace ae
{
	std::vector<std::string> DebugLogger::messages_;

	void DebugLogger::cacheMessage(const std::string& message)
	{
		messages_.push_back(message);
	}

	std::vector<std::string> DebugLogger::getCachedMessages()
	{
		std::vector<std::string> messages(messages_);
		messages_.clear();

		return messages;
	}
}