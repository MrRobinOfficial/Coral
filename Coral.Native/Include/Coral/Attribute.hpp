#pragma once

#include "Core.hpp"
#include "String.hpp"

namespace Coral {

	class Type;

	/// @brief Lorem Ipsun
	class Attribute
	{
	public:
		/// @brief Gets the type
		/// @return The type
		Type& GetType();

		/// @brief Gets the field's value
		/// @tparam TReturn The return type
		/// @param InFieldName The name of the field
		/// @return The value
		template<typename TReturn>
		TReturn GetFieldValue(std::string_view InFieldName)
		{
			TReturn result;
			GetFieldValueInternal(InFieldName, &result);
			return result;
		}

	private:
		void GetFieldValueInternal(std::string_view InFieldName, void* OutValue) const;

	private:
		ManagedHandle m_Handle = -1;
		Type* m_Type = nullptr;

		friend class Type;
		friend class MethodInfo;
		friend class FieldInfo;
		friend class PropertyInfo;
	};

}
