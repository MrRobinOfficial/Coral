#pragma once

#include "Memory.hpp"

namespace Coral {
	/// @brief Lorem Ipsun
	/// @tparam TValue 
	template<typename TValue>
	class alignas(8) Array
	{
	public:
		/// @brief Creates a new array of the specified length. Creates on the managed heap. Required to be freed with Array::Free
		/// @param InLength The length
		/// @return A new array
		static Array New(size_t InLength)
		{
			Array<TValue> result;
			if (InLength > 0)
			{
				result.m_Ptr = static_cast<TValue*>(Memory::AllocHGlobal(InLength * sizeof(TValue)));
				result.m_Length = static_cast<int32_t>(InLength);
			}
			return result;
		}

		/// @brief Creates a new array from from the specified values. Creates on the managed heap. Required to be freed with Array::Free
		/// @param InValues The values
		/// @return A new array
		static Array New(const std::vector<TValue>& InValues)
		{
			Array<TValue> result;

			if (!InValues.empty())
			{
				result.m_Ptr = static_cast<TValue*>(Memory::AllocHGlobal(InValues.size() * sizeof(TValue)));
				result.m_Length = static_cast<int32_t>(InValues.size());
				memcpy(result.m_Ptr, InValues.data(), InValues.size() * sizeof(TValue));
			}

			return result;
		}

		/// @brief Creates a new array from the specified buffer
		/// @param buffer The buffer
		/// @param size The size of the buffer
		/// @return A new array
		static Array New(const void* buffer, size_t size)
		{
			Array<TValue> result;

			if (buffer)
			{
				result.m_Ptr = static_cast<TValue*>(Memory::AllocHGlobal(size));
				result.m_Length = static_cast<int32_t>(size);
				memcpy(result.m_Ptr, buffer, size);
			}

			return result;
		}

		/// @brief Creates a new array from the specified initializer list
		/// @param InValues The values
		/// @return A new array
		static Array New(std::initializer_list<TValue> InValues)
		{
			Array result;
			
			if (InValues.size() > 0)
			{
				result.m_Ptr = static_cast<TValue*>(Memory::AllocHGlobal(InValues.size() * sizeof(TValue)));
				result.m_Length = static_cast<int32_t>(InValues.size());
				memcpy(result.m_Ptr, InValues.begin(), InValues.size() * sizeof(TValue));
			}

			return result;
		}

		/// @brief Frees the array
		/// @param InArray The array
		static void Free(Array InArray)
		{
			if (!InArray.m_Ptr || InArray.m_Length == 0)
				return;

			Memory::FreeHGlobal(InArray.m_Ptr);
			InArray.m_Ptr = nullptr;
			InArray.m_Length = 0;
		}

		/// @brief Re-assigns the array
		/// @param InOther The other array
		void Assign(const Array& InOther)
		{
			memcpy(m_Ptr, InOther.m_Ptr, InOther.m_Length * sizeof(TValue));
		}

		bool IsEmpty() const { return m_Length == 0 || m_Ptr == nullptr; }

		TValue& operator[](size_t InIndex) { return m_Ptr[InIndex]; }
		const TValue& operator[](size_t InIndex) const { return m_Ptr[InIndex]; }

		size_t Length() const { return m_Length; }
		size_t ByteLength() const { return m_Length * sizeof(TValue); }

		TValue* Data() { return m_Ptr; }
		const TValue* Data() const { return m_Ptr; }

		TValue* begin() { return m_Ptr; }
		TValue* end() { return m_Ptr + m_Length; }

		const TValue* begin() const { return m_Ptr; }
		const TValue* end() const { return m_Ptr + m_Length; }

		const TValue* cbegin() const { return m_Ptr; }
		const TValue* cend() const { return m_Ptr + m_Length; }

	public:
		alignas(8) TValue* m_Ptr = nullptr;
		alignas(8) TValue* m_ArrayHandle = nullptr;
		alignas(8) int32_t m_Length = 0;
		alignas(8) Bool32 m_IsDisposed = false;
	};

	static_assert(offsetof(Array<char>, m_Ptr) == 0);
	static_assert(offsetof(Array<char>, m_ArrayHandle) == 8);
	static_assert(offsetof(Array<char>, m_Length) == 16);
	static_assert(offsetof(Array<char>, m_IsDisposed) == 24);
	static_assert(sizeof(Array<char>) == 32);
}
