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

#ifndef _INCLUDE_ANY_CONFIG_JSON_READER_HPP_
#define _INCLUDE_ANY_CONFIG_JSON_READER_HPP_

#pragma once

#include "types.hpp"

#include <any_config/base/reader.hpp>

#include <tier0/utlbuffer.h>

namespace AnyConfig
{
	template<class T, class I>
	struct CLoadFromJSON_t : public CLoadTo_t<T>, 
	                         public CError_t, 
	                         public CInput_t<I>, 
	                         public CLoadRoot_t
	{
	}; // CLoadFromJSON_t<T, I>

	struct LoadFromJSON_t : public CLoadFromJSON_t<KeyValues3 *, const char *>
	{
	}; // LoadFromJSON_t

	class LoadFromJSON_NoContext_t : public CNoContextBase<CLoadFromJSON_t<CEmpty_t, const char *>>
	{
	public:
		LoadFromJSON_NoContext_t(const Load_Generic_t::Base_t &aInit);
	}; // LoadFromJSON_NoContext_t

	template<class T>
	struct CLoadFromJSONFile_t : public CLoadTo_t<T>, 
	                             public CError_t, 
	                             public CFileSystemPath_t
	{
	}; // CLoadFromJSONFile_t<T>

	struct LoadFromJSONFile_t : public CLoadFromJSONFile_t<KeyValues3 *>
	{
	}; // LoadFromJSONFile_t

	class LoadFromJSONFile_NoContext_t : public CNoContextBase<CLoadFromJSONFile_t<CEmpty_t>>
	{
	}; // LoadFromJSONFile_NoContext_t

	class CJSONReader : public CBaseReader
	{
	public:
		//
		// Load ones (globals).
		//
		static bool _LoadFromJSON(const LoadFromJSON_t &aParams);
		static bool _LoadFromJSONFile(const LoadFromJSONFile_t &aParams);

	public: // IBaseReader<Load_Generic_t>
		bool Load(const Load_Generic_t &aParams);

	public: // IBaseReader<LoadFromFile_Generic_t>
		bool Load(const LoadFromFile_Generic_t &aParams);

	public:
		//
		// Load ones (members).
		//
		bool LoadFromJSON(const LoadFromJSON_NoContext_t &aParams);
		bool LoadFromJSONFile(const LoadFromJSONFile_NoContext_t &aParams);
	}; // CJSONReader
}; // AnyConfig

#endif //_INCLUDE_ANY_CONFIG_JSON_READER_HPP_
