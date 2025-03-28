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

#ifndef _INCLUDE_ANY_CONFIG_JSON_WRITER_HPP_
#define _INCLUDE_ANY_CONFIG_JSON_WRITER_HPP_

#pragma once

#include "types.hpp"

#include <any_config/base/writer.hpp>

namespace AnyConfig
{
	template<class T, class O>
	struct CSaveJSON_t : public SaveFrom_t<T>, 
	                     public Error_t, 
	                     public Output_t<O>
	{
		CSaveJSON_t(const T &aInitInput, CUtlString *psInitMessage, const O &aInitOutput)
		 :  SaveFrom_t<T>{aInitInput}, 
		    Error_t{psInitMessage}, 
		    Output_t<O>{aInitOutput}
		{
		}

		CSaveJSON_t(CUtlString *psInitMessage, const O &aInitOutput)
		 :  CSaveJSON_t({}, psInitMessage, aInitOutput)
		{
		}
	}; // CSaveJSON_t<T, O>

	class ISaveJSON
	{
	public:
		virtual bool SaveJSON() = 0;
	}; // ISaveJSON

	template<class T>
	class CSaveJSONBase : public ISaveJSON, 
	                      public T
	{
	public:
		using Base_t = T;

		CSaveJSONBase(const Base_t &aInit)
		 :  Base_t(aInit)
		{
		}
	}; // CSaveJSONBase<T>

	using SaveJSON_t = CSaveJSONBase<CSaveJSON_t<KeyValues3 *, CUtlBuffer *>>;

	class CSaveJSON : public SaveJSON_t
	{
	public:
		using Base_t = SaveJSON_t;

		CSaveJSON(const Base_t::Base_t &aInit)
		 :  Base_t(aInit)
		{
		}

	public: // ISaveJSON
		bool SaveJSON();
	}; // CSaveJSON

	class SaveJSON final : public CSaveJSON
	{
	public:
		using CBase = CSaveJSON;
		using CBase::CBase;
	}; // SaveJSON

	using SaveJSON2_t = CSaveJSONBase<CSaveJSON_t<KeyValues3 *, CUtlString *>>;

	class CSaveJSON2 : public SaveJSON2_t
	{
	public:
		using Base_t = SaveJSON2_t;

		CSaveJSON2(const Base_t::Base_t &aInit)
		 :  Base_t(aInit)
		{
		}

	public: // ISaveJSON
		bool SaveJSON() override;
	}; // CSaveJSON2

	class SaveJSON2 final : public CSaveJSON2
	{
	public:
		using CBase = CSaveJSON2;
		using CBase::CBase;
	}; // SaveJSON

	using SaveJSON_NoContext_t = CNoContextBase<CSaveJSON_t<Empty_t, CUtlBuffer *>>;

	class CSaveJSON_NoContext : public SaveJSON_NoContext_t
	{
	public:
		using Base_t = SaveJSON_NoContext_t;

		CSaveJSON_NoContext(const Base_t::Base_t &aInit)
		 :  Base_t(aInit)
		{
		}

		CSaveJSON_NoContext(const CSave_General::Base_t &aInit);
	}; // CSaveJSON_NoContext

	class SaveJSON_NoContext final : public CSaveJSON_NoContext
	{
	public:
		using CBase = CSaveJSON_NoContext;
		using CBase::CBase;
	}; // SaveJSON_NoContext

	using SaveJSON2_NoContext_t = CNoContextBase<CSaveJSON_t<Empty_t, CUtlString *>>;

	class CSaveJSON2_NoContext : public SaveJSON2_NoContext_t
	{
	public:
		using Base_t = SaveJSON2_NoContext_t;

		CSaveJSON2_NoContext(const Base_t::Base_t &aInit)
		 :  Base_t(aInit)
		{
		}
	}; // CSaveJSON2_NoContext

	class SaveJSON2_NoContext final : public CSaveJSON2_NoContext
	{
	public:
		using CBase = CSaveJSON2_NoContext;
		using CBase::CBase;
	}; // SaveJSON2_NoContext

	class CJSONWriter : public CWriterBase<CConfig>
	{
	public: // IBaseWriter<CSave_General>
		bool Save(const CSave_General &aParams);

	public: // IBaseWriter<CSaveToFile_General>
		bool Save(const CSaveToFile_General &aParams);

	public:
		//
		// Save ones (members).
		//
		bool SaveJSON(const CSaveJSON_NoContext &aParams) const;
		bool SaveJSON(const CSaveJSON2_NoContext &aParams) const;
	}; // CJSONWriter
}; // AnyConfig

#endif // _INCLUDE_ANY_CONFIG_JSON_WRITER_HPP_
