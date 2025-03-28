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

#ifndef _INCLUDE_ANY_CONFIG_BASE_WRITER_HPP_
#define _INCLUDE_ANY_CONFIG_BASE_WRITER_HPP_

#pragma once

#include "config.hpp"
#include "iwriter.hpp"
#include "types.hpp"

namespace AnyConfig
{
	template<class T, class O>
	struct SaveBase_t : public SaveFrom_t<T>, 
	                    public Error_t, 
	                    public Output_t<O>
	{
	public:
		SaveBase_t(const T &aInitInput, CUtlString *psInitMessage, const O &aInitOutput)
		 :  SaveFrom_t<T>{aInitInput}, 
		    Error_t{psInitMessage}, 
		    Output_t<O>{aInitOutput}
		{
		}

		SaveBase_t(CUtlString *psInitMessage, const O &aInitOutput)
		 :  SaveBase_t({}, psInitMessage, aInitOutput)
		{
		}
	}; // SaveBase_t<T, O>

	template<class T, class O>
	struct CSave_t : public Encode_t, 
	                 public Format_t, 
	                 public SaveBase_t<T, O>, 
	                 public SaveText_t
	{
	public:
		using Base_t = SaveBase_t<T, O>;

		CSave_t(const KV3ID_t &aInitEncode, const KV3ID_t &aInitFormat, const Base_t &aInitBase, unsigned int uFlags)
		 :  Encode_t{aInitEncode}, 
		    Format_t{aInitFormat}, 
		    Base_t{aInitBase}, 
		    SaveText_t{uFlags}
		{
		}
	}; // CSave_t<T, O>

	class ISave
	{
	public:
		virtual bool Save() = 0;
	}; // ISave

	template<class T>
	class CSaveBase : public ISave, 
	                  public T
	{
	public:
		using Base_t = T;

		CSaveBase(const Base_t &aInit)
		 :  Base_t(aInit)
		{
		}
	}; // CSaveBase<T>

	using CSaveBase_t = CSaveBase<CSave_t<KeyValues3 *, CUtlBuffer *>>;

	class CSave : public CSaveBase_t
	{
	public:
		using Base_t = CSaveBase_t;

		CSave(const Base_t::Base_t &aInit)
		 :  Base_t(aInit)
		{
		}

	public: // ISave
		bool Save();
	}; // CSave

	class Save final : public CSave
	{
	public:
		using CBase = CSave;
		using CBase::CBase;
	};

	using SaveNoContext_t = CNoContextBase<CSave_t<Empty_t, CUtlBuffer *>>;

	class CSave_NoContext : public SaveNoContext_t
	{
	public:
		using Base_t = SaveNoContext_t;

		CSave_NoContext(const Base_t::Base_t &aInit)
		 :  Base_t(aInit)
		{
		}
	}; // CSave_NoContext

	class Save_NoContext final : public CSave_NoContext
	{
	public:
		using CBase = CSave_NoContext;
		using CBase::CBase;
	}; // Save_NoContext

	using Save_General_t = CGeneralBase<CSave_NoContext>;

	class CSave_General : public Save_General_t
	{
	public:
		using Base_t = Save_General_t;
		using GeneralBase_t = Base_t::Base_t;
		using NoContextBase_t = GeneralBase_t::Base_t::Base_t;

		CSave_General(const GeneralBase_t &aInit)
		 :  Base_t(aInit)
		{
		}

		CSave_General(const NoContextBase_t &aInit)
		 :  Base_t(aInit)
		{
		}
	}; // CSave_General

	class Save_General final : public CSave_General
	{
	public:
		using CBase = CSave_General;
		using CBase::CBase;
	}; // Save_General

	template<class T>
	struct CSaveToFile_t : public Encode_t, 
	                       public Format_t, 
	                       public SaveFrom_t<T>, 
	                       public Error_t, 
	                       public FileSystemPath_t, 
	                       public SaveText_t
	{
	public:
		CSaveToFile_t(const KV3ID_t &aInitEncode, const KV3ID_t &aInitFormat, const T &aInitInput, CUtlString *psInitMessage, const char *pszInitFilename, const char *pszInitPathID, unsigned int uFlags)
		 :  Encode_t{aInitEncode}, 
		    Format_t{aInitFormat}, 
		    SaveFrom_t<T>{aInitInput}, 
		    Error_t{psInitMessage}, 
		    FileSystemPath_t{pszInitFilename, pszInitPathID}, 
		    SaveText_t{uFlags}
		{
		}

		CSaveToFile_t(const KV3ID_t &aInitEncode, const KV3ID_t &aInitFormat, CUtlString *psInitMessage, const char *pszInitFilename, const char *pszInitPathID, unsigned int uFlags)
		 :  CSaveToFile_t(aInitEncode, aInitFormat, {}, psInitMessage, pszInitFilename, pszInitPathID, uFlags)
		{
		}
	}; // CSaveToFile_t<T>

	class ISaveToFile
	{
	public:
		virtual bool SaveToFile() = 0;
	}; // ISaveToFile

	template<class T>
	class CSaveToFileBase : public ISaveToFile, 
	                        public T
	{
	public:
		using Base_t = T;

		CSaveToFileBase(const Base_t &aInit)
		 :  Base_t(aInit)
		{
		}
	}; // CSaveToFileBase<T>

	using SaveToFile_t = CSaveToFileBase<CSaveToFile_t<KeyValues3 *>>;

	class CSaveToFile : public SaveToFile_t
	{
	public:
		using Base_t = SaveToFile_t;

		CSaveToFile(const Base_t::Base_t &aInit)
		 :  Base_t(aInit)
		{
		}

	public: // ISaveToFile
		bool SaveToFile() override;
	}; // CSaveToFile

	class SaveToFile final : public CSaveToFile
	{
	public:
		using CBase = CSaveToFile;
		using CBase::CBase;
	}; // SaveToFile

	using SaveToFile_NoContext_t = CNoContextBase<CSaveToFile_t<Empty_t>>;

	class CSaveToFile_NoContext : public SaveToFile_NoContext_t
	{
	public:
		using Base_t = SaveToFile_NoContext_t;

		CSaveToFile_NoContext(const Base_t::Base_t &aInit)
		 :  Base_t(aInit)
		{
		}
	}; // CSaveToFile_NoContext

	class SaveToFile_NoContext final : public CSaveToFile_NoContext
	{
	public:
		using CBase = CSaveToFile_NoContext;
		using CBase::CBase;
	}; // SaveToFile_NoContext

	using SaveToFile_General_t = CGeneralBase<CSaveToFile_NoContext>;

	class CSaveToFile_General : public SaveToFile_General_t
	{
	public:
		using Base_t = SaveToFile_General_t;
		using GeneralBase_t = Base_t::Base_t;
		using NoContextBase_t = GeneralBase_t::Base_t::Base_t;

		CSaveToFile_General(const GeneralBase_t &aInit)
		 :  Base_t(aInit)
		{
		}

		CSaveToFile_General(const NoContextBase_t &aInit)
		 :  Base_t(aInit)
		{
		}
	}; // CSaveToFile_General

	class SaveToFile_General final : public CSaveToFile_General
	{
	public:
		using CBase = CSaveToFile_General;
		using CBase::CBase;
	}; // SaveToFile_General

	template<class T>
	class CWriterBase : virtual public T, 
	                    public IBaseWriter<CSave_General>, 
	                    public IBaseWriter<CSaveToFile_General>
	{
	public:
		virtual ~CWriterBase() = default;
	}; // CWriterBase<T>

	class CBaseWriter : public CWriterBase<CConfig>
	{
	public:
		CBaseWriter();
		CBaseWriter(KeyValues3 *pRoot);

	public: // IBaseWriter<CSave_General>
		bool Save(const CSave_General &aParams) override;

	public: // IBaseWriter<CSaveToFile_General>
		bool Save(const CSaveToFile_General &aParams) override;

	public:
		//
		// Save ones (members).
		//
		bool Save(const CSave_NoContext &aParams) const;
		bool SaveToFile(const CSaveToFile_NoContext &aParams) const;
	}; // CBaseWriter
}; // AnyConfig

#endif // _INCLUDE_ANY_CONFIG_BASE_WRITER_HPP_
