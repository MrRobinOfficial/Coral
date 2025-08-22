#pragma once

#include "Core.hpp"
#include "String.hpp"

namespace Coral {

	class Type;
	class Attribute;

	/// @brief Lorem Ipsun
	class MethodInfo
	{
	public:
		/// @brief Gets the name
		/// @return A string containing the name
		String GetName() const;

		/// @brief Gets the return type
		/// @return A reference to the return type
		Type& GetReturnType();

		/// @brief Get vector of parameter types
		/// @return A vector of parameter types
		const std::vector<Type*>& GetParameterTypes();

		/// @brief Gets the accessibility (public, private, etc.)
		/// @return A enum containing the accessibility
		TypeAccessibility GetAccessibility() const;

		/// @brief Get vector of attributes
		/// @return A vector of attributes
		std::vector<Attribute> GetAttributes() const;

	private:
		ManagedHandle m_Handle = -1;
		Type* m_ReturnType = nullptr;
		std::vector<Type*> m_ParameterTypes;

		friend class Type;
	};

}
