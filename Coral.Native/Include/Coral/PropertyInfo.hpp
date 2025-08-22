#pragma once

#include "Core.hpp"
#include "String.hpp"

namespace Coral {

	class Type;
	class Attribute;

	/// @brief Lorem Ipsun
	class PropertyInfo
	{
	public:
		/// @brief Gets the name
		/// @return A string containing the name
		String GetName() const;

		/// @brief Gets the type of the property
		/// @return A reference to the type
		Type& GetType();

		/// @brief Get vector of attributes
		/// @return A vector of attributes
		std::vector<Attribute> GetAttributes() const;

	private:
		ManagedHandle m_Handle = -1;
		Type* m_Type = nullptr;

		friend class Type;
	};
	
}
