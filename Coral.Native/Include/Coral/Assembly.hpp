#pragma once

#include "Type.hpp"

#include "StableVector.hpp"

namespace Coral {

	enum class AssemblyLoadStatus
	{
		Success,
		FileNotFound,
		FileLoadFailure,
		InvalidFilePath,
		InvalidAssembly,
		UnknownError
	};

	class HostInstance;

	/// @brief Lorem Ipsun
	class ManagedAssembly
	{
	public:
		/// @brief Gets the assembly id
		/// @return A integer containing the assembly id
		int32_t GetAssemblyID() const { return m_AssemblyId; }

		/// @brief Gets the load status
		/// @return A enum containing the load status
		AssemblyLoadStatus GetLoadStatus() const { return m_LoadStatus; }

		/// @brief Get the name of the assembly
		/// @return A string containing the assembly name
		std::string_view GetName() const { return m_Name; }

		/// @brief Adds an internal call to the assembly. Similar to the `AddInternalCall` function in Mono
		/// @param InClassName The name of the class
		/// @param InVariableName The name of the variable
		/// @param InFunctionPtr The function pointer
		void AddInternalCall(std::string_view InClassName, std::string_view InVariableName, void* InFunctionPtr);

		/// @brief Uploads the internal calls to the assembly
		void UploadInternalCalls();

		[[deprecated(CORAL_GLOBAL_ALC_MSG)]]
		Type& GetType(std::string_view InClassName) const;

		/// @brief Gets a local type
		/// @param InClassName The name of the class
		/// @return The type
		Type& GetLocalType(std::string_view InClassName) const;

		/// @brief Gets a local type
		/// @param InTypeId The type id
		/// @return The type
		Type& GetLocalType(TypeId InTypeId) const;

		[[deprecated(CORAL_GLOBAL_ALC_MSG)]]
		const std::vector<Type*>& GetTypes() const;

		/// @brief Get vector of local types
		/// @return A vector of local types
		const std::vector<Type>& GetLocalTypes() const;

	private:
		HostInstance* m_Host = nullptr;
		int32_t m_AssemblyId = -1;
		int32_t m_OwnerContextId = 0;
		AssemblyLoadStatus m_LoadStatus = AssemblyLoadStatus::UnknownError;
		std::string m_Name;

		std::vector<UCString> m_InternalCallNameStorage;

		std::vector<InternalCall> m_InternalCalls;

		std::vector<Type*> m_Types;

		// NOTE(Emily): Doesn't need to be a `StableVector` since it's static post-init.
		std::vector<Type> m_LocalTypes;
		std::unordered_map<std::string, Type*> m_LocalTypeNameCache;
		std::unordered_map<TypeId, Type*> m_LocalTypeIdCache;

		friend class HostInstance;
		friend class AssemblyLoadContext;
	};

	/// @brief Lorem Ipsun
	class AssemblyLoadContext
	{
	public:
		/// @brief Loads an assembly from a file
		/// @param InFilePath The path to the assembly
		/// @return A managed assembly object
		ManagedAssembly& LoadAssembly(std::string_view InFilePath);

		/// @brief Loads an assembly from memory
		/// @param data The data
		/// @param dataLength The length of the data
		/// @return A managed assembly object
		ManagedAssembly& LoadAssemblyFromMemory(const std::byte* data, int64_t dataLength);

		/// @brief Get vector of loaded assemblies
		/// @return A vector of loaded assemblies
		const StableVector<ManagedAssembly>& GetLoadedAssemblies() const { return m_LoadedAssemblies; }

	private:
		int32_t m_ContextId;
		StableVector<ManagedAssembly> m_LoadedAssemblies;

		HostInstance* m_Host = nullptr;

		friend class HostInstance;
	};

}
