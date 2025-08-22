#pragma once

#include "Core.hpp"
#include "String.hpp"
#include "ManagedObject.hpp"
#include "MethodInfo.hpp"
#include "FieldInfo.hpp"
#include "PropertyInfo.hpp"

#include <optional>

namespace Coral {

	/// @brief Lorem Ipsun
	class Type
	{
	public:
		/// @brief Gets the fully qualified name of the type, including its namespace but not its assembly
		/// @return The fully qualified name
		String GetFullName() const;

		/// @brief Gets the assembly-qualified name of the type, which includes the name of the assembly from which this Type object was loaded
		/// @return The assembly-qualified name
		String GetAssemblyQualifiedName() const;

		/// @brief Gets the base type
		/// @return The base type
		Type& GetBaseType();

		/// @brief Get vector of interface types
		/// @return A vector of interfaces
		std::vector<Type*>& GetInterfaceTypes();

		/// @brief Gets the size of the type
		/// @return The size in bytes
		int32_t GetSize() const;

		/// @brief Determines whether the current type derives from the specified type
		/// @param InOther The type to check
		/// @return True if the current type derives from the specified type
		bool IsSubclassOf(const Type& InOther) const;

		/// @brief Determines whether the current type can be assigned to a variable of the specified type
		/// @param InOther The type to check
		/// @return True if the current type can be assigned to a variable of the specified type
		bool IsAssignableTo(const Type& InOther) const;

		/// @brief Determines whether an instance of a specified type can be assigned to a variable of the current type
		/// @param InOther The type to check
		/// @return True if an instance of a specified type can be assigned to a variable of the current type
		bool IsAssignableFrom(const Type& InOther) const;

		/// @brief Get vector of methods
		/// @return A vector of methods
		std::vector<MethodInfo> GetMethods() const;

		/// @brief Get vector of fields
		/// @return A vector of fields
		std::vector<FieldInfo> GetFields() const;

		/// @brief Get vector of properties
		/// @return A vector of properties
		std::vector<PropertyInfo> GetProperties() const;

		/// @brief Determines whether the current type has the specified attribute
		/// @param InAttributeType The type of the attribute
		/// @return True if the current type has the specified attribute
		bool HasAttribute(const Type& InAttributeType) const;

		/// @brief Get vector of attributes
		/// @return A vector of attributes
		std::vector<Attribute> GetAttributes() const;

		/// @brief Gets the managed type
		/// @return The managed type
		ManagedType GetManagedType() const;

		/// @brief Indicates whether the type is an array type that can represent only a single-dimensional array with a zero lower bound
		/// @return True if the type is an array
		bool IsSZArray() const;

		/// @brief Gets the element type of the array
		/// @return The type of the elements
		Type& GetElementType();

		bool operator==(const Type& InOther) const;

		operator bool() const { return m_Id != -1; }

		TypeId GetTypeId() const { return m_Id; }

	public:
		/// @brief Creates an instance of the type
		/// @tparam ...TArgs The types of the arguments
		/// @param ...InArguments The arguments
		/// @return The created instance of the type
		template<typename... TArgs>
		ManagedObject CreateInstance(TArgs&&... InArguments) const
		{
			constexpr size_t argumentCount = sizeof...(InArguments);

			ManagedObject result;

			if constexpr (argumentCount > 0)
			{
				const void* argumentsArr[argumentCount];
				ManagedType argumentTypes[argumentCount];
				AddToArray<TArgs...>(argumentsArr, argumentTypes, std::forward<TArgs>(InArguments)..., std::make_index_sequence<argumentCount> {});
				result = CreateInstanceInternal(argumentsArr, argumentTypes, argumentCount);
			}
			else
			{
				result = CreateInstanceInternal(nullptr, nullptr, 0);
			}

			return result;
		}

		/// @brief Invokes a static method on the type
		/// @tparam TReturn The return type
		/// @tparam ...TArgs The types of the arguments
		/// @param InMethodName The name of the method
		/// @param ...InParameters The arguments
		/// @return The result of the method
		template <typename TReturn, typename... TArgs>
		TReturn InvokeStaticMethod(std::string_view InMethodName, TArgs&&... InParameters) const
		{
			constexpr size_t parameterCount = sizeof...(InParameters);

			TReturn result;

			if constexpr (parameterCount > 0)
			{
				const void* parameterValues[parameterCount];
				ManagedType parameterTypes[parameterCount];
				AddToArray<TArgs...>(parameterValues, parameterTypes, std::forward<TArgs>(InParameters)..., std::make_index_sequence<parameterCount> {});
				InvokeStaticMethodRetInternal(InMethodName, parameterValues, parameterTypes, parameterCount, &result);
			}
			else
			{
				InvokeStaticMethodRetInternal(InMethodName, nullptr, nullptr, 0, &result);
			}

			return result;
		}

		/// @brief Invokes a static method on the type
		/// @tparam ...TArgs The types of the arguments
		/// @param InMethodName The name of the method
		/// @param ...InParameters The arguments
		template <typename... TArgs>
		void InvokeStaticMethod(std::string_view InMethodName, TArgs&&... InParameters)
		{
			constexpr size_t parameterCount = sizeof...(InParameters);

			if constexpr (parameterCount > 0)
			{
				const void* parameterValues[parameterCount];
				ManagedType parameterTypes[parameterCount];
				AddToArray<TArgs...>(parameterValues, parameterTypes, std::forward<TArgs>(InParameters)..., std::make_index_sequence<parameterCount> {});
				InvokeStaticMethodInternal(InMethodName, parameterValues, parameterTypes, parameterCount);
			}
			else
			{
				InvokeStaticMethodInternal(InMethodName, nullptr, nullptr, 0);
			}
		}

	private:
		ManagedObject CreateInstanceInternal(const void** InParameters, const ManagedType* InParameterTypes, size_t InLength) const;
		void InvokeStaticMethodInternal(std::string_view InMethodName, const void** InParameters, const ManagedType* InParameterTypes, size_t InLength) const;
		void InvokeStaticMethodRetInternal(std::string_view InMethodName, const void** InParameters, const ManagedType* InParameterTypes, size_t InLength, void* InResultStorage) const;

	private:
		TypeId m_Id = -1;
		Type* m_BaseType = nullptr;
		std::optional<std::vector<Type*>> m_InterfaceTypes = std::nullopt;
		Type* m_ElementType = nullptr;

		friend class HostInstance;
		friend class ManagedAssembly;
		friend class AssemblyLoadContext;
		friend class MethodInfo;
		friend class FieldInfo;
		friend class PropertyInfo;
		friend class Attribute;
		friend class ReflectionType;
		friend class ManagedObject;
	};

	/// @brief Lorem Ipsun
	class ReflectionType
	{
	public:
		operator Type&() const;

	public:
		TypeId m_TypeID;
	};

	static_assert(offsetof(ReflectionType, m_TypeID) == 0);
	static_assert(sizeof(ReflectionType) == 4);
}
