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
	struct CLoadFromJSON_t : public LoadTo_t<T>, 
	                         public Error_t, 
	                         public Input_t<I>, 
	                         public LoadRoot_t
	{
	public:
		CLoadFromJSON_t(const T &aInitContext, CUtlString *psInitMessage, I aInitInput, const char *pszInitRoot)
		 :  LoadTo_t<T>{aInitContext}, 
		    Error_t{psInitMessage}, 
		    Input_t<I>{aInitInput}, 
		    LoadRoot_t{pszInitRoot}
		{
		}

		CLoadFromJSON_t(CUtlString *psInitMessage, I aInitInput, const char *pszInitRoot)
		 :  CLoadFromJSON_t({}, psInitMessage, aInitInput, pszInitRoot)
		{
		}

		CLoadFromJSON_t(const CLoadFromJSON_t &aInit)
		 :  CLoadFromJSON_t(aInit.m_aContext, aInit.m_psMessage, aInit.m_aData, aInit.m_pszName)
		{
		}
	}; // CLoadFromJSON_t<T, I>

	class ILoadFromJSON
	{
	public:
		virtual bool LoadFromJSON() = 0;
	}; // ILoadFromJSON

	template<class T>
	class CLoadFromJSONBase : public ILoadFromJSON,  
	                          public T
	{
	public:
		using Base_t = T;

		CLoadFromJSONBase(const Base_t &aInit)
		 :  Base_t(aInit)
		{
		}
	}; // CLoadFromJSONBase<T>

	using LoadFromJSONBase_t = CLoadFromJSONBase<CLoadFromJSON_t<KeyValues3 *, const char *>>;

	class CLoadFromJSON : public LoadFromJSONBase_t
	{
	public:
		using Base_t = LoadFromJSONBase_t;

		CLoadFromJSON(const Base_t &aInit)
		 :  Base_t(aInit)
		{
		}

	public: // ILoadFromJSON
		bool LoadFromJSON() override;
	}; // CLoadFromJSON

	class LoadFromJSON : public CLoadFromJSON
	{
	public:
		using CBase = CLoadFromJSON;
		using CBase::CBase;
	}; // LoadFromJSON

	using LoadFromJSON_NoContext_t = CNoContextBase<CLoadFromJSON_t<KeyValues3 *, const char *>>;

	class CLoadFromJSON_NoContext : public LoadFromJSON_NoContext_t
	{
	public:
		using Base_t = LoadFromJSON_NoContext_t;

		CLoadFromJSON_NoContext(const Base_t::Base_t &aInit)
		 :  Base_t(aInit)
		{
		}

		CLoadFromJSON_NoContext(const CLoad_General &aInit);
	}; // CLoadFromJSON_NoContext

	class LoadFromJSON_NoContext final : public CLoadFromJSON_NoContext
	{
	public:
		using CBase = CLoadFromJSON_NoContext;
		using CBase::CBase;
	}; // LoadFromJSON_NoContext

	template<class T>
	struct CLoadFromJSONFile_t : public LoadTo_t<T>, 
	                             public Error_t, 
	                             public FileSystemPath_t
	{
	public:
		CLoadFromJSONFile_t(const T &aInitContext, CUtlString *psInitMessage, const char *pszInitFilename, const char *pszInitPathID)
		 :  LoadTo_t<T>{aInitContext}, 
		    Error_t{psInitMessage}, 
		    FileSystemPath_t{pszInitFilename, pszInitPathID}
		{
		}

		CLoadFromJSONFile_t(CUtlString *psInitMessage, const char *pszInitFilename, const char *pszInitPathID)
		 :  CLoadFromJSONFile_t({}, psInitMessage, pszInitFilename, pszInitPathID)
		{
		}
	}; // CLoadFromJSONFile_t<T>

	class ILoadFromJSONFile
	{
	public:
		virtual bool LoadFromJSONFile() = 0;
	}; // ILoadFromJSONFile

	template<class T>
	class CLoadFromJSONFileBase : public ILoadFromJSONFile, 
	                              public T
	{
	public:
		using Base_t = T;

		CLoadFromJSONFileBase(const Base_t &aInit)
		 :  Base_t(aInit)
		{
		}
	}; // CLoadFromJSONFileBase<T>

	using LoadFromJSONFileBase_t = CLoadFromJSONFileBase<CLoadFromJSONFile_t<KeyValues3 *>>;

	class CLoadFromJSONFile : public LoadFromJSONFileBase_t
	{
	public:
		using Base_t = LoadFromJSONFileBase_t;

		CLoadFromJSONFile(const Base_t::Base_t &aInit)
		 :  Base_t(aInit)
		{
		}

	public: // ILoadFromJSONFile
		bool LoadFromJSONFile();
	}; // CLoadFromJSONFile

	class LoadFromJSONFile final : public CLoadFromJSONFile
	{
	public:
		using CBase = CLoadFromJSONFile;
		using CBase::CBase;
	}; // LoadFromJSONFile

	using LoadFromJSONFile_NoContext_t = CNoContextBase<CLoadFromJSONFile_t<Empty_t>>;

	class CLoadFromJSONFile_NoContext : public LoadFromJSONFile_NoContext_t
	{
	public:
		using Base_t = LoadFromJSONFile_NoContext_t;

		CLoadFromJSONFile_NoContext(const Base_t::Base_t &aInit)
		 :  Base_t(aInit)
		{
		}

		CLoadFromJSONFile_NoContext(const CLoadFromFile_General::Base_t &aInit);
	}; // CLoadFromJSONFile_NoContext

	class LoadFromJSONFile_NoContext final : public CLoadFromJSONFile_NoContext
	{
	public:
		using CBase = CLoadFromJSONFile_NoContext;
		using CBase::CBase;
	}; // LoadFromJSONFile_NoContext

	class CJSONReader : public CReaderBase<CConfig>
	{
	public:
		CJSONReader() = default;
		CJSONReader(KeyValues3 *pRoot) : CConfig(pRoot) {}

	public: // IBaseReader<CLoad_General>
		bool Load(const CLoad_General &aParams);

	public: // IBaseReader<CLoadFromFile_General>
		bool Load(const CLoadFromFile_General &aParams);

	public:
		//
		// Load ones (members).
		//
		bool LoadFromJSON(const CLoadFromJSON_NoContext &aParams);
		bool LoadFromJSONFile(const CLoadFromJSONFile_NoContext &aParams);
	}; // CJSONReader
}; // AnyConfig

#endif //_INCLUDE_ANY_CONFIG_JSON_READER_HPP_
