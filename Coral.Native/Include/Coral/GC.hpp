#pragma once

namespace Coral {

	enum class GCCollectionMode
	{
		// Default is the same as using Forced directly
		Default,

		// Forces the garbage collection to occur immediately
		Forced,

		// Allows the garbage collector to determine whether it should reclaim objects right now
		Optimized,

		// Requests that the garbage collector decommit as much memory as possible
		Aggressive
	};
	
	/// @brief Controls the system garbage collector, a service that automatically reclaims unused memory
	class GC
	{
	public:
		/// @brief Forces garbage collection
		static void Collect();

		/// @brief Forces a garbage collection from generation 0 through a specified generation, at a time specified by a GCCollectionMode value, with values that specify whether the collection should be blocking and compacting
		/// @param InGeneration The number of the oldest generation to be garbage collected
		/// @param InCollectionMode An enumeration value that specifies whether the garbage collection is forced (Default or Forced) or optimized (Optimized)
		/// @param InBlocking True to perform a blocking garbage collection, otherwise perform a background garbage collection where possible
		/// @param InCompacting True to compact the small object heap, otherwise sweep only
		static void Collect(int32_t InGeneration, GCCollectionMode InCollectionMode = GCCollectionMode::Default, bool InBlocking = true, bool InCompacting = false);

		/// @brief Suspends the current thread until the thread that is processing the queue of finalizers has emptied that queue
		static void WaitForPendingFinalizers();
	};
	
}

