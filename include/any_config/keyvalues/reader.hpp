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

#ifndef _INCLUDE_ANY_CONFIG_KEYVALUES_READER_HPP_
#define _INCLUDE_ANY_CONFIG_KEYVALUES_READER_HPP_

#pragma once

#include "types.hpp"

#include <any_config/base/reader.hpp>

namespace AnyConfig
{
	template<class T>
	struct CLoadFromKV1File_t : public LoadTo_t<T>, 
	                            public Error_t, 
	                            public FileSystemPath_t, 
	                            public KV1TextEscape_t
	{
		CLoadFromKV1File_t(const T &aInitContext, CUtlString *psInitMessage, const char *pszInitFilename, const char *pszInitPathID, KV1TextEscapeBehavior_t eInitBehavior)
		 :  LoadTo_t<T>{aInitContext}, 
		    Error_t{psInitMessage}, 
		    FileSystemPath_t{pszInitFilename, pszInitPathID}, 
		    KV1TextEscape_t{eInitBehavior}
		{
		}

		CLoadFromKV1File_t(CUtlString *psInitMessage, const char *pszInitFilename, const char *pszInitPathID, KV1TextEscapeBehavior_t eInitBehavior)
		 :  CLoadFromKV1File_t({}, psInitMessage, pszInitFilename, pszInitPathID, eInitBehavior)
		{
		}
	}; // CLoadFromKV1File_t<T>

	class ILoadFromKV1File
	{
	public:
		virtual bool LoadFromKV1File() = 0;
	}; // ILoadFromKV1File

	template<class T>
	class CLoadFromKV1FileBase : public ILoadFromKV1File, 
	                             public T
	{
	public:
		using Base_t = T;

		CLoadFromKV1FileBase(const Base_t &aInit)
		 :  Base_t(aInit)
		{
		}
	}; // CLoadFromKV1FileBase<T>

	using LoadFromKV1FileBase_t = CLoadFromKV1FileBase<CLoadFromKV1File_t<KeyValues3 *>>;

	class CLoadFromKV1File : public LoadFromKV1FileBase_t
	{
	public:
		using Base_t = LoadFromKV1FileBase_t;

		CLoadFromKV1File(const Base_t &aInit)
		 :  Base_t(aInit)
		{
		}

	public: // ILoadFromKV1File
		bool LoadFromKV1File();
	}; // CLoadFromKV1File

	class LoadFromKV1File final : public CLoadFromKV1File
	{
	public:
		using CBase = CLoadFromKV1File;
		using CBase::CBase;
	};

	using LoadFromKV1FileBase_NoContext_t = CNoContextBase<CLoadFromKV1File_t<Empty_t>>;

	class CLoadFromKV1File_NoContext : public LoadFromKV1FileBase_NoContext_t
	{
	public:
		using Base_t = LoadFromKV1FileBase_NoContext_t;

		CLoadFromKV1File_NoContext(const Base_t &aInit)
		 :  Base_t(aInit)
		{
		}

	public:
		CLoadFromKV1File_NoContext(const CLoadFromFile_General::Base_t &aInit);
	}; // CLoadFromKV1File_NoContext

	class LoadFromKV1File_NoContext : public CLoadFromKV1File_NoContext
	{
	public:
		using CBase = CLoadFromKV1File_NoContext;
		using CBase::CBase;
	};

	template<class T, class I>
	struct CLoadFromKV1Text_t : public LoadTo_t<T>, 
	                            public Error_t, 
	                            public Input_t<I>, 
	                            public KV1TextEscape_t, 
	                            public LoadRoot_t, 
	                            public KV1Unk_t<bool>
	{
	public:
		CLoadFromKV1Text_t(const T &aInitContext, CUtlString *psInitMessage, const I &aInitInput, KV1TextEscapeBehavior_t eInitBehavior, const char *pszInitRoot, bool bInitUnk)
		 :  LoadTo_t<T>{aInitContext}, 
		    Error_t{psInitMessage}, 
		    Input_t<I>{aInitInput}, 
		    KV1TextEscape_t{eInitBehavior}, 
		    LoadRoot_t{pszInitRoot}, 
		    KV1Unk_t<bool>{bInitUnk}
		{
		}

		CLoadFromKV1Text_t(CUtlString *psInitMessage, const I &aInitInput, KV1TextEscapeBehavior_t eInitBehavior, const char *pszInitRoot, bool bInitUnk)
		 :  CLoadFromKV1Text_t({}, psInitMessage, aInitInput, eInitBehavior, pszInitRoot, bInitUnk)
		{
		}
	}; // CLoadFromKV1Text_t<T, I>

	class ILoadFromKV1Text
	{
	public:
		virtual bool LoadFromKV1Text() = 0;
	}; // ILoadFromKV1Text

	template<class T>
	class CLoadFromKV1TextBase : public ILoadFromKV1Text, 
	                             public T
	{
	public:
		using Base_t = T;

	public:
		CLoadFromKV1TextBase(const Base_t &aInit)
		 :  Base_t(aInit)
		{
		}
	}; // CLoadFromKV1TextBase<T>

	using LoadFromKV1TextBase_t = CLoadFromKV1TextBase<CLoadFromKV1Text_t<KeyValues3 *, const char *>>;

	class CLoadFromKV1Text : public LoadFromKV1TextBase_t
	{
	public:
		using Base_t = LoadFromKV1TextBase_t;

		CLoadFromKV1Text(const Base_t &aInit)
		 :  Base_t(aInit)
		{
		}

	public: // ILoadFromKV1Text
		bool LoadFromKV1Text();
	}; // CLoadFromKV1Text

	class LoadFromKV1Text final : public CLoadFromKV1Text
	{
	public:
		using CBase = CLoadFromKV1Text;
		using CBase::CBase;
	};

	using LoadFromKV1TextBase_NoContext_t = CNoContextBase<CLoadFromKV1Text_t<Empty_t, const char *>>;

	class CLoadFromKV1Text_NoContext : public LoadFromKV1TextBase_NoContext_t
	{
	public:
		using Base_t = LoadFromKV1TextBase_NoContext_t;

		CLoadFromKV1Text_NoContext(const Base_t::Base_t &aInit)
		 :  Base_t(aInit)
		{
		}

		CLoadFromKV1Text_NoContext(const CLoad_General::Base_t &aInit);
	}; // CLoadFromKV1Text_NoContext

	class LoadFromKV1Text_NoContext : public CLoadFromKV1Text_NoContext
	{
	public:
		using CBase = CLoadFromKV1Text_NoContext;
		using CBase::CBase;
	}; // LoadFromKV1Text_NoContext

	template<class T, class I, class P>
	struct CLoadFromKV1Text_Translated_t : public LoadTo_t<T>, 
	                                       public Error_t, 
	                                       public Input_t<I>, 
	                                       public KV1TextEscape_t, 
	                                       public KV1Proccessor_t<P>, 
	                                       public KV1Unk_t<int>, 
	                                       public LoadRoot_t, 
	                                       public KV1Unk_t<bool>
	{
		CLoadFromKV1Text_Translated_t(const T &aInitContext, CUtlString *psInitMessage, const I &aInitInput, const P &aInitProcessor, KV1Unk_t<int> nInitUnk, const char *pszInitRoot, bool bInitUnk)
		 :  LoadTo_t<T>{aInitContext}, 
		    Error_t{psInitMessage}, 
		    Input_t<I>{aInitInput}, 
		    KV1Proccessor_t<P>{aInitProcessor}, 
		    KV1Unk_t<int>{nInitUnk}, 
		    LoadRoot_t{pszInitRoot}, 
		    KV1Unk_t<bool>{bInitUnk}
		{
		}

		CLoadFromKV1Text_Translated_t(CUtlString *psInitMessage, const I &aInitInput, const P &aInitProcessor, KV1Unk_t<int> nInitUnk, const char *pszInitRoot, bool bInitUnk)
		 :  CLoadFromKV1Text_Translated_t({}, psInitMessage, aInitInput, aInitProcessor, nInitUnk, pszInitRoot, bInitUnk)
		{
		}
	}; // CLoadFromKV1Text_Translated_t<T, I, P>

	class ILoadFromKV1Text_Translated
	{
	public:
		virtual bool LoadFromKV1Text_Translated() = 0;
	}; // ILoadFromKV1Text_Translated

	template<class T>
	class CLoadFromKV1TextBase_Translated : public ILoadFromKV1Text_Translated, 
	                                        public T
	{
	public:
		using Base_t = T;

		CLoadFromKV1TextBase_Translated(const Base_t &aInit)
		 :  Base_t(aInit)
		{
		}
	}; // CLoadFromKV1TextBase_Translated<T>

	using LoadFromKV1TextBase_Translated_t = CLoadFromKV1TextBase_Translated<CLoadFromKV1Text_Translated_t<KeyValues3 *, const char *, KV1ToKV3Translation_t *>>;

	class CLoadFromKV1Text_Translated : public LoadFromKV1TextBase_Translated_t
	{
	public:
		using Base_t = LoadFromKV1TextBase_Translated_t;

		CLoadFromKV1Text_Translated(const Base_t::Base_t &aInit)
		 :  Base_t(aInit)
		{
		}

	public: // ILoadFromKV1Text_Translated
		bool LoadFromKV1Text_Translated();
	}; // CLoadFromKV1Text_Translated

	class LoadFromKV1Text_Translated final : public CLoadFromKV1Text_Translated
	{
	public:
		using CBase = CLoadFromKV1Text_Translated;
		using CBase::CBase;
	}; // LoadFromKV1Text_Translated

	using LoadFromKV1TextTranslated_NoContext_t = CNoContextBase<CLoadFromKV1Text_Translated_t<Empty_t, const char *, KV1ToKV3Translation_t *>>;

	class CLoadFromKV1Text_Translated_NoContext : public LoadFromKV1TextTranslated_NoContext_t
	{
	public:
		using Base_t = LoadFromKV1TextTranslated_NoContext_t;

		CLoadFromKV1Text_Translated_NoContext(const Base_t::Base_t &aInit)
		 :  Base_t(aInit)
		{
		}
	}; // CLoadFromKV1Text_Translated_NoContext

	class LoadFromKV1Text_Translated_NoContext final : public CLoadFromKV1Text_Translated_NoContext
	{
	public:
		using CBase = CLoadFromKV1Text_Translated_NoContext;
		using CBase::CBase;
	}; // LoadFromKV1Text_Translated_NoContext

	class CKeyValuesReader : public CReaderBase<CConfig>
	{
	public:
		CKeyValuesReader() = default;
		CKeyValuesReader(KeyValues3 *pRoot) : CConfig(pRoot) {}

	public: // IBaseReader<CLoad_General>
		bool Load(const CLoad_General &aParams);

	public: // IBaseReader<CLoadFromFile_General>
		bool Load(const CLoadFromFile_General &aParams);

	public:
		//
		// Load ones (members).
		//
		bool LoadFromKV1File(const CLoadFromKV1File_NoContext &aParams);
		bool LoadFromKV1Text(const CLoadFromKV1Text_NoContext &aParams);
		bool LoadFromKV1Text_Translated(const CLoadFromKV1Text_Translated_NoContext &aParams);
	}; // CKeyValuesReader
}; // AnyConfig

#endif //_INCLUDE_ANY_CONFIG_KEYVALUES_READER_HPP_
