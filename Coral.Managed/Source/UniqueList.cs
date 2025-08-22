using System;
using System.Collections.Concurrent;
using System.Runtime.CompilerServices;

namespace Coral.Managed;

/// <summary>
/// A list of unique objects
/// </summary>
/// <typeparam name="T">The type of the object</typeparam>
public class UniqueIdList<T>
{
	private readonly ConcurrentDictionary<int, T> m_Objects = new();

	/// <summary>
	/// Checks if the list contains the object
	/// </summary>
	/// <param name="id">The id</param>
	/// <returns>True if the list contains the object</returns>
	public bool Contains(int id)
	{
		return m_Objects.ContainsKey(id);
	}

	/// <summary>
	/// Adds an object
	/// </summary>
	/// <param name="obj">The object</param>
	/// <returns>A unique id</returns>
	/// <exception cref="ArgumentNullException"></exception>
	public int Add(T? obj)
	{
		if (obj == null)
		{
			throw new ArgumentNullException(nameof(obj));
		}

		int hashCode = RuntimeHelpers.GetHashCode(obj);
		_ = m_Objects.TryAdd(hashCode, obj);
		return hashCode;
	}

	/// <summary>
	/// Tries to get the object
	/// </summary>
	/// <param name="id">The id</param>
	/// <param name="obj">The object</param>
	/// <returns>True if the object was found</returns>
	public bool TryGetValue(int id, out T? obj)
	{
		return m_Objects.TryGetValue(id, out obj);
	}

	/// <summary>
	/// Clears the list
	/// </summary>
	public void Clear()
	{
		m_Objects.Clear();
	}
}
