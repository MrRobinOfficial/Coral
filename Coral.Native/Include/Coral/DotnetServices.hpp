#pragma once

#include <string>

namespace Coral
{
	/// @brief Lorem Ipsun
	class DotnetServices
	{
	public:
		/// @brief Run MSBuild on the specified solution
		/// @param InSolutionPath The path to the solution
		/// @param InBuildDebug True to build in debug mode, otherwise release mode
		/// @return True if the build was successful
		static bool RunMSBuild(const std::string& InSolutionPath, bool InBuildDebug = true);
	};
}
