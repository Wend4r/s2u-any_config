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

#ifndef _INCLUDE_ANY_CONFIG_BASE_READER_HPP_
#define _INCLUDE_ANY_CONFIG_BASE_READER_HPP_

#pragma once

#include "config.hpp"
#include "ireader.hpp"
#include "types.hpp"

namespace AnyConfig
{
	template<class T, typename I>
	struct LoadBase_t : public LoadTo_t<T>, 
	                    public Error_t, 
	                    public Input_t<I>
	{
	public:
		LoadBase_t(const T &aInitContext, CUtlString *psInitMessage, const I &aInitInput)
		 :  LoadTo_t<T>{aInitContext}, 
		    Error_t{psInitMessage}, 
		    Input_t<I>{aInitInput}
		{
		}

		LoadBase_t(CUtlString *psInitMessage, const I &aInitInput)
		 :  LoadBase_t({}, psInitMessage, aInitInput)
		{
		}
	}; // LoadBase_t<T, I>

	template<class T, typename I>
	struct Load_t : public LoadBase_t<T, I>, 
	                public Format_t, 
	                public LoadRoot_t
	{
	public:
		using Base_t = LoadBase_t<T, I>;

		Load_t(const Base_t &aInitBase, const KV3ID_t &aInitFormat, const char *pszInitRoot)
		 :  LoadBase_t<T, I>{aInitBase}, 
		    Format_t{aInitFormat}, 
		    LoadRoot_t{pszInitRoot}
		{
		}

		Load_t(const Load_t &aInit)
		 :  Load_t({aInit.m_aContext, aInit.m_psMessage, aInit.m_aData}, aInit.m_aFormat, aInit.m_pszName)
		{
		}
	}; // Load_t<T, I>

	class ILoad
	{
	public:
		virtual bool Load() = 0;
	}; // ILoad

	template<class T>
	class CLoadBase : public ILoad, 
	                  public T
	{
	public:
		using Base_t = T;

		CLoadBase(const Base_t &aInit)
		 :  Base_t(aInit)
		{
		}
	}; // CLoadBase<T>

	using CLoadBase_t = CLoadBase<Load_t<CKeyValues3Context *, CUtlBuffer *>>;

	class CLoad : public CLoadBase_t
	{
	public:
		using Base_t = CLoadBase_t;

		CLoad(const Base_t::Base_t &aInit)
		 :  Base_t(aInit)
		{
		}

	public: // ILoad
		bool Load();
	}; // CLoad

	class Load final : public CLoad
	{
	public:
		using CBase = CLoad;
		using CBase::CBase;
	}; // Load

	using Load2_t = CLoadBase<Load_t<KeyValues3 *, CUtlBuffer *>>;

	class CLoad2 : public Load2_t
	{
	public:
		using Base_t = Load2_t;

		CLoad2(const Base_t::Base_t &aInit)
		 :  Base_t(aInit)
		{
		}

	public: // ILoad
		bool Load();
	}; // CLoad2

	class Load2 final : public CLoad2
	{
	public:
		using CBase = CLoad2;
		using CBase::CBase;
	}; // Load2

	using Load3_t = CLoadBase<Load_t<KeyValues3 *, const char *>>;

	class CLoad3 : public Load3_t
	{
	public:
		using Base_t = Load3_t;

		CLoad3(const Base_t::Base_t &aInit)
		 :  Base_t(aInit)
		{
		}

	public: // ILoad
		bool Load();
	}; // CLoad3

	class Load3 final : public CLoad3
	{
	public:
		using CBase = CLoad3;
		using CBase::CBase;
	}; // Load3

	using Load_NoContext_t = CNoContextBase<Load_t<Empty_t, CUtlBuffer *>>;

	class CLoad_NoContext : public Load_NoContext_t
	{
	public:
		using Base_t = Load_NoContext_t;

		CLoad_NoContext(const Base_t::Base_t &aInit)
		 :  Base_t(aInit)
		{
		}
	}; // CLoad_NoContext

	class Load_NoContext final : public CLoad_NoContext
	{
	public:
		using CBase = CLoad_NoContext;
		using CBase::CBase;
	}; // Load_NoContext

	using Load2_NoContext_t = CNoContextBase<Load_t<Empty_t, CUtlBuffer *>>;

	class CLoad2_NoContext : public Load2_NoContext_t
	{
	public:
		using Base_t = Load2_NoContext_t;

		CLoad2_NoContext(const Base_t::Base_t &aInit)
		 :  Base_t(aInit)
		{
		}
	}; // CLoad2_NoContext

	class Load2_NoContext : public CLoad2_NoContext
	{
	public:
		using CBase = CLoad2_NoContext;
		using CBase::CBase;
	}; // Load2_NoContext

	using Load3_NoContext_t = CNoContextBase<Load_t<Empty_t, const char *>>;

	class CLoad3_NoContext : public Load3_NoContext_t
	{
	public:
		using Base_t = Load3_NoContext_t;

		CLoad3_NoContext(const Base_t::Base_t &aInit)
		 :  Base_t(aInit)
		{
		}
	}; // CLoad3_NoContext

	class Load3_NoContext : public CLoad3_NoContext
	{
	public:
		using CBase = CLoad3_NoContext;
		using CBase::CBase;
	}; // Load3_NoContext

	using Load_General_t = CGeneralBase<CLoad2_NoContext>;

	class CLoad_General : public Load_General_t
	{
	public:
		using Base_t = Load_General_t;
		using GeneralBase_t = Base_t::Base_t;
		using NoContextBase_t = GeneralBase_t::Base_t::Base_t;

		CLoad_General(const GeneralBase_t &aInit)
		 :  Base_t(aInit)
		{
		}

		CLoad_General(const NoContextBase_t &aInit)
		 :  Base_t(aInit)
		{
		}
	}; // CLoad_General

	class Load_General final : public CLoad_General
	{
	public:
		using CBase = CLoad_General;
		using CBase::CBase;
	}; // Load_General

	template<class T>
	struct LoadFromFileBase_t : public LoadTo_t<T>, 
	                            public Error_t, 
	                            public FileSystemPath_t
	{
		using Base_t = Load_General_t;

		LoadFromFileBase_t(const T &aInitContext, CUtlString *psInitMessage, const char *pszFilename, const char *pszPathID)
		 :  LoadTo_t<T>{aInitContext}, 
		    Error_t{psInitMessage}, 
		    FileSystemPath_t{pszFilename, pszPathID}
		{
		}

		LoadFromFileBase_t(CUtlString *psInitMessage, const char *pszFilename, const char *pszPathID)
		 :  LoadFromFileBase_t({}, psInitMessage, pszFilename, pszPathID)
		{
		}

		LoadFromFileBase_t(const LoadFromFileBase_t &aInit)
		 :  LoadFromFileBase_t{aInit.m_aContext, aInit.m_psMessage, aInit.m_pszFilename, aInit.m_pszPathID}
		{
		}
	}; // LoadFromFileBase_t<T>

	template<class T>
	struct CLoadFromFile_t : public LoadFromFileBase_t<T>, 
	                         public Format_t
	{
	public:
		using Base_t = LoadFromFileBase_t<T>;

		CLoadFromFile_t(const Base_t &aInitBase, const KV3ID_t &aFormat)
		 :  Base_t{aInitBase}, 
		    Format_t{aFormat}
		{
		}

		CLoadFromFile_t(const CLoadFromFile_t &aInit)
		 :  CLoadFromFile_t({aInit.m_aContext, aInit.m_psMessage, aInit.m_pszFilename, aInit.m_pszPathID}, aInit.m_aFormat)
		{
		}
	}; // CLoadFromFile_t<T>

	class ILoadFromFile
	{
	public:
		virtual bool LoadFromFile() = 0;
	}; // ILoadFromFile

	template<class T>
	class CLoadFromFileBase : public ILoadFromFile, 
	                          public T
	{
	public:
		using Base_t = T;

		CLoadFromFileBase(const Base_t &aInit)
		 :  Base_t(aInit)
		{
		}
	}; // CLoadFromFileBase<T>

	class CLoadFromFile : public CLoadFromFileBase<CLoadFromFile_t<CKeyValues3Context *>>
	{
	public:
		using Base_t = CLoadFromFileBase<CLoadFromFile_t<CKeyValues3Context *>>;

		CLoadFromFile(const Base_t::Base_t &aInit)
		 :  Base_t(aInit)
		{
		}

	public: // ILoadFromFile
		bool LoadFromFile() override;
	}; // CLoadFromFile

	class LoadFromFile final : public CLoadFromFile
	{
	public:
		using CBase = CLoadFromFile;
		using CBase::CBase;
	}; // LoadFromFile

	using LoadFromFile2_t = CLoadFromFileBase<CLoadFromFile_t<KeyValues3 *>>;

	class CLoadFromFile2 : public LoadFromFile2_t
	{
	public:
		using Base_t = LoadFromFile2_t;

		CLoadFromFile2(const Base_t::Base_t &aInit)
		 :  Base_t(aInit)
		{
		}

	public: // ILoadFromFile
		bool LoadFromFile() override;
	}; // CLoadFromFile2

	class LoadFromFile2 final : public CLoadFromFile2
	{
	public:
		using CBase = CLoadFromFile2;
		using CBase::CBase;
	}; // LoadFromFile2

	using LoadFromFile_NoContext_t = CLoadFromFileBase<CLoadFromFile_t<KeyValues3 *>>;

	class CLoadFromFile_NoContext : public LoadFromFile_NoContext_t
	{
	public:
		using Base_t = LoadFromFile_NoContext_t;

		CLoadFromFile_NoContext(const Base_t::Base_t &aInit)
		 :  Base_t(aInit)
		{
		}
	}; // CLoadFromFile_NoContext

	using LoadFromFile2_NoContext_t = CNoContextBase<CLoadFromFile_t<Empty_t>>;

	class CLoadFromFile2_NoContext : public LoadFromFile2_NoContext_t
	{
	public:
		using Base_t = LoadFromFile2_NoContext_t;

		CLoadFromFile2_NoContext(const Base_t::Base_t &aInit)
		 :  Base_t(aInit)
		{
		}
	}; // CLoadFromFile2_NoContext

	using LoadFromFile_General_t = CGeneralBase<CLoadFromFile2_NoContext>;

	class CLoadFromFile_General : public LoadFromFile_General_t
	{
	public:
		using Base_t = LoadFromFile_General_t;
		using GeneralBase_t = Base_t::Base_t;
		using NoContextBase_t = GeneralBase_t::Base_t::Base_t;

		CLoadFromFile_General(const GeneralBase_t &aInit)
		 :  Base_t(aInit)
		{
		}

		CLoadFromFile_General(const NoContextBase_t &aInit)
		 :  Base_t(aInit)
		{
		}
	}; // CLoadFromFile_General

	class LoadFromFile_General final : CLoadFromFile_General
	{
	public:
		using CBase = CLoadFromFile_General;
		using CBase::CBase;
	}; // LoadFromFile_General

	template<class T, class I>
	struct LoadNoHeader_t : public LoadTo_t<T>, 
	                        public Error_t, 
	                        public Input_t<I>, 
	                        public Format_t, 
	                        public LoadRoot_t
	{
		LoadNoHeader_t(const T &aInitContext, CUtlString *psInitMessage, I aInitData, const KV3ID_t &aInitFormat, const char *pszInitRoot)
		 :  LoadTo_t<T>{aInitContext}, 
		    Error_t{psInitMessage}, 
		    Input_t<I>{aInitData}, 
		    Format_t{aInitFormat}, 
		    LoadRoot_t{pszInitRoot}
		{
		}

		LoadNoHeader_t(CUtlString *psInitMessage, I aInitData, const KV3ID_t &aInitFormat, const char *pszInitRoot)
		 :  LoadNoHeader_t({}, psInitMessage, aInitData, aInitFormat, pszInitRoot)
		{
		}
	}; // LoadNoHeader_t<T, I>

	class ILoadNoHeader
	{
	public:
		virtual bool LoadNoHeader() = 0;
	}; // ILoadNoHeader

	template<class T>
	class CLoadNoHeaderBase : public ILoadNoHeader, 
	                          public T
	{
	public:
		using Base_t = T;
	
		CLoadNoHeaderBase(const Base_t &aInit)
		 :  Base_t(aInit)
		{
		}
	}; // CLoadNoHeaderBase<T>

	using LoadNoHeaderBase_t = CLoadNoHeaderBase<LoadNoHeader_t<KeyValues3 *, const char *>>;

	class CLoadNoHeader : public LoadNoHeaderBase_t
	{
	public:
		using Base_t = LoadNoHeaderBase_t;

		CLoadNoHeader(const Base_t::Base_t &aInit)
		 :  Base_t(aInit)
		{
		}

	public: // ILoadNoHeader
		bool LoadNoHeader() override;
	}; // CLoadNoHeader

	using LoadNoHeader_NoContext_t = CNoContextBase<CLoadNoHeader>;

	class CLoadNoHeader_NoContext : public LoadNoHeader_NoContext_t
	{
	public:
		using Base_t = LoadNoHeader_NoContext_t;

		CLoadNoHeader_NoContext(const Base_t::Base_t &aInit)
		 :  Base_t(aInit)
		{
		}
	}; // CLoadNoHeader_NoContext

	class LoadNoHeader_NoContext final : public CLoadNoHeader_NoContext
	{
	public:
		using CBase = CLoadNoHeader_NoContext;
		using CBase::CBase;
	}; // LoadNoHeader_NoContext

	template<class T>
	class CReaderBase : virtual public T, 
	                    public IBaseReader<CLoad_General>, 
	                    public IBaseReader<CLoadFromFile_General>
	{
	public:
		virtual ~CReaderBase() = default;
	}; // CReaderBase<T>

	class CBaseReader : public CReaderBase<CConfig>
	{
	public:
		CBaseReader();
		CBaseReader(KeyValues3 *pRoot);

	public: // IBaseReader<CLoad_General>
		bool Load(const CLoad_General &aParams);

	public: // IBaseReader<CLoadFromFile_General>
		bool Load(const CLoadFromFile_General &aParams);

	public:
		//
		// Load ones (members).
		//
		bool Load(const CLoad_NoContext &aParams);
		bool Load(const CLoad2_NoContext &aParams);
		bool Load(const CLoad3_NoContext &aParams);

		bool LoadFromFile(const CLoadFromFile_NoContext &aParams);
		bool LoadFromFile(const CLoadFromFile2_NoContext &aParams);

		bool LoadNoHeader(const CLoadNoHeader_NoContext &aParams);
	}; // CBaseReader
}; // AnyConfig

#endif //_INCLUDE_ANY_CONFIG_BASE_READER_HPP_
