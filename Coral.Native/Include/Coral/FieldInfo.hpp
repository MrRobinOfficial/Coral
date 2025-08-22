#pragma once

#include "Core.hpp"
#include "String.hpp"

namespace Coral {

	class Type;
	class Attribute;

	/// @brief Lorem Ipsun
	class FieldInfo
	{
	public:
		/// @brief Gets the name
		/// @return A string containing the name
		String GetName() const;

		/// @brief Gets the type
		/// @return The type
		Type& GetType();

		/// @brief Gets the accessibility (public, private, etc.)
		/// @return A enum containing the accessibility
		TypeAccessibility GetAccessibility() const;

		/// @brief Get vector of attributes
		/// @return A vector of attributes
		std::vector<Attribute> GetAttributes() const;

	private:
		ManagedHandle m_Handle = -1;
		Type* m_Type = nullptr;

		friend class Type;
	};
	
}
