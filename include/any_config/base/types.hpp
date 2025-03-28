/**
 * vim: set ts=4 sw=4 tw=99 noet :
 * ======================================================
 * Source 2 util to read a config of any format.
 * Written by Wend4r (2024).
 * ======================================================

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef _INCLUDE_ANY_CONFIG_BASE_TYPES_HPP_
#define _INCLUDE_ANY_CONFIG_BASE_TYPES_HPP_

#pragma once

class CUtlBuffer;
class CUtlString;
struct KV3ID_t;
class CKeyValues3Context;
class KeyValues3;

namespace AnyConfig
{
	struct Empty_t
	{
		Empty_t() {};
	}; // Empty_t

	template<typename T>
	struct ConstExpr_t
	{
	private:
		T m_aValue;

	public:
		constexpr ConstExpr_t(T aInit)
		 :  m_aValue(aInit)
		{
		}

		operator T() const
		{
			return m_aValue;
		}
	}; // ConstExpr_t<T>

	using String_t = ConstExpr_t<const char *>;

	template<class T>
	struct LoadTo_t
	{
		T m_aContext;
	}; // LoadTo_t<T>

	struct Error_t
	{
		CUtlString *m_psMessage;
	}; // Error_t

	struct LoadRoot_t
	{
		const char *m_pszName;
	}; // LoadRoot_t

	template<class T>
	struct IO_t
	{
		T m_aData;
	}; // IO_t<T>

	template<class T>
	struct Input_t : public IO_t<T>
	{
		using Base_t = IO_t<T>;

		Input_t(const T &aInit)
		 :  Base_t{aInit}
		{
		}
	}; // Input_t<T>

	struct Format_t
	{
		const KV3ID_t &m_aFormat; // = g_KV3Format_General;
	}; // Format_t

	struct FileSystemPath_t
	{
		const char *m_pszFilename;
		const char *m_pszPathID;
	}; // FileSystemPath_t

	struct Encode_t
	{
		const KV3ID_t &m_aEncoding; // = g_KV3Encoding_Text;
	}; // Encode_t

	template<class T>
	struct SaveFrom_t : public IO_t<const T>
	{
		using Base_t = IO_t<const T>;

		SaveFrom_t(const T &aInit)
		 :  Base_t{aInit}
		{
		}
	}; // CSaveFrom_t<T>

	template<class T>
	struct Output_t : public IO_t<T>
	{
		using Base_t = IO_t<T>;

		Output_t(const T &aInit)
		 :  Base_t{aInit}
		{
		}
	}; // Output_t<T>

	struct SaveText_t
	{
		unsigned int m_uFlags; // KV3_SAVE_TEXT_NONE;
	}; // SaveText_t

	template<class T>
	class INoContext
	{
	public:
		virtual ~INoContext() = default;
	}; // INoContext<T>

	template<class T>
	class CNoContextBase : public INoContext<T>, 
	                       public T
	{
	public:
		using Base_t = T;

		CNoContextBase(const Base_t &aInit)
		 :  Base_t(aInit)
		{
		}
	}; // CNoContextBase<T>

	template<class T>
	class IGeneral
	{
	public:
		virtual T ToBase() const = 0;
	}; // IGeneral<T>

	template<class T>
	class CGeneralBase : public IGeneral<T>, 
	                     public T
	{
	public:
		using Base_t = T;

		CGeneralBase(const Base_t &aInit)
		 :  Base_t(aInit)
		{
		}

		template<typename P>
		P To() const
		{
			return static_cast<P>(*this);
		}

		T ToBase() const
		{
			return To<T>();
		}
	}; // CGeneralBase<T>
}; // AnyConfig

#endif // _INCLUDE_ANY_CONFIG_BASE_TYPES_HPP_
