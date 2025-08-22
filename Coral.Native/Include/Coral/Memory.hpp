#pragma once

#include "Core.hpp"

namespace Coral {

	/// @brief Lorem Ipsun
	struct Memory
	{
		/// @brief Allocates memory from the unmanaged memory of the process by using the specified number of bytes
		/// @param InSize The required number of bytes in memory
		/// @return A pointer to the newly allocated memory. This memory must be released using the FreeHGlobal(void*) function
		static void* AllocHGlobal(size_t InSize);

		/// @brief Frees memory previously allocated from the unmanaged memory of the process
		/// @param InPtr The handle returned by the original matching call to AllocHGlobal(size_t)
		static void FreeHGlobal(void* InPtr);

		/// @brief Copies the contents of a managed String to a block of memory allocated from the unmanaged COM task allocator
		/// @param InString The string to copy
		/// @return A pointer to the newly allocated memory
		static UCChar* StringToCoTaskMemAuto(UCStringView InString);

		/// @brief Frees a block of memory allocated by the unmanaged COM task memory allocator
		/// @param InMemory The memory to free
		static void FreeCoTaskMem(void* InMemory);

	};

}
