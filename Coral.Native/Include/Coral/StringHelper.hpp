#pragma once

#include "Core.hpp"

namespace Coral {

	/// @brief Lorem Ipsun
	class StringHelper
	{
	public:
		/// @brief Converts a UTF-8 string to a wide string
		/// @param InString The string
		/// @return A wide string
		static UCString ConvertUtf8ToWide(std::string_view InString);

		/// @brief Converts a wide string to a UTF-8 string
		/// @param InString The string
		/// @return A UTF-8 string
		static std::string ConvertWideToUtf8(UCStringView InString);
	};

}
