#pragma once

#include "Core.hpp"
#include "MessageLevel.hpp"
#include "Assembly.hpp"
#include "ManagedObject.hpp"

#include <functional>

namespace Coral {

	using ExceptionCallbackFn = std::function<void(std::string_view)>;

	struct HostSettings
	{
		/// @brief The file path to Coral.runtimeconfig.json (e.g C:\Dev\MyProject\ThirdParty\Coral)
		std::string CoralDirectory;

		/// @brief Callback for logging
		MessageCallbackFn MessageCallback = nullptr;

		/// @brief Filter for logging
		MessageLevel MessageFilter = MessageLevel::All;

		/// @brief Callback for unhandled exceptions
		ExceptionCallbackFn ExceptionCallback = nullptr;
	};

	enum class CoralInitStatus
	{
		Success,
		CoralManagedNotFound,
		CoralManagedInitError,
		DotNetNotFound,
	};

	/// @brief The Coral host instance
	class HostInstance
	{
	public:
		/// @brief Initializes the Coral host
		/// @param InSettings The settings
		/// @return A enum containing the initialization status
		CoralInitStatus Initialize(HostSettings InSettings);

		/// @brief Shutdowns Coral host
		void Shutdown();

		/// @brief Creates an assembly load context
		/// @param InName The name of the context
		/// @return A assembly load context
		AssemblyLoadContext CreateAssemblyLoadContext(std::string_view InName);

		/// @brief Unloads an assembly load context
		/// @param InLoadContext The assembly load context
		void UnloadAssemblyLoadContext(AssemblyLoadContext& InLoadContext);

		// `InDllPath` is a colon-separated list of paths from which AssemblyLoader will try and resolve load paths at runtime.
		// This does not affect the behaviour of LoadAssembly from native code.

		/// @brief Creates an assembly load context with a custom load .dll path. A load path is a colon-separated list of paths from which AssemblyLoader will try and resolve load paths at runtime
		/// @param InName The name of the context
		/// @param InDllPath The .dll path
		/// @return A assembly load context
		AssemblyLoadContext CreateAssemblyLoadContext(std::string_view InName, std::string_view InDllPath);

	private:
		bool LoadHostFXR() const;
		bool InitializeCoralManaged();
		void LoadCoralFunctions();

		void* LoadCoralManagedFunctionPtr(const std::filesystem::path& InAssemblyPath, const UCChar* InTypeName, const UCChar* InMethodName, const UCChar* InDelegateType = CORAL_UNMANAGED_CALLERS_ONLY) const;

		template<typename TFunc>
		TFunc LoadCoralManagedFunctionPtr(const UCChar* InTypeName, const UCChar* InMethodName, const UCChar* InDelegateType = CORAL_UNMANAGED_CALLERS_ONLY) const
		{
			return (TFunc) LoadCoralManagedFunctionPtr(m_CoralManagedAssemblyPath, InTypeName, InMethodName, InDelegateType);
		}

	private:
		HostSettings m_Settings;
		std::filesystem::path m_CoralManagedAssemblyPath;
		void* m_HostFXRContext = nullptr;
		bool m_Initialized = false;

		friend class AssemblyLoadContext;
	};

}
