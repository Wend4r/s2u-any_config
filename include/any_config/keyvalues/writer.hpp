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

#ifndef _INCLUDE_ANY_CONFIG_KEYVALUES_WRITER_HPP_
#define _INCLUDE_ANY_CONFIG_KEYVALUES_WRITER_HPP_

#pragma once

#include "types.hpp"

#include <any_config/base/writer.hpp>

namespace AnyConfig
{
	template<class T, class O>
	struct CSaveAsKV1Text_t : public LoadTo_t<T>, 
	                          public Error_t, 
	                          public Output_t<O>, 
	                          public KV1TextEscape_t
	{
		CSaveAsKV1Text_t(const T &aInitContext, CUtlString *psInitMessage, const O &aInitOutput, KV1TextEscapeBehavior_t eInitBehavior)
		 :  LoadTo_t<T>{aInitContext}, 
		    Error_t{psInitMessage}, 
		    Output_t<O>{aInitOutput}, 
		    KV1TextEscape_t{eInitBehavior}
		{
		}

		CSaveAsKV1Text_t(CUtlString *psInitMessage, const O &aInitOutput, KV1TextEscapeBehavior_t eInitBehavior)
		 :  CSaveAsKV1Text_t({}, psInitMessage, aInitOutput, eInitBehavior)
		{
		}
	}; // CSaveAsKV1Text_t<T, O>

	class ISaveAsKV1Text
	{
	public:
		virtual bool SaveAsKV1Text() = 0;
	}; // ISaveAsKV1Text

	template<class T>
	class CSaveAsKV1TextBase : public ISaveAsKV1Text, 
	                           public T
	{
	public:
		using Base_t = T;

		CSaveAsKV1TextBase(const Base_t &aInit)
		 :  Base_t(aInit)
		{
		}
	}; // CSaveAsKV1TextBase<T>

	using SaveAsKV1TextBase_t = CSaveAsKV1TextBase<CSaveAsKV1Text_t<KeyValues3 *, CUtlBuffer *>>;

	class SaveAsKV1Text_t : public SaveAsKV1TextBase_t
	{
	public:
		using Base_t = SaveAsKV1TextBase_t;

		SaveAsKV1Text_t(const Base_t::Base_t &aInit)
		 :  Base_t(aInit)
		{
		}

	public: // ISaveAsKV1Text
		bool SaveAsKV1Text() override;
	}; // SaveAsKV1Text_t

	using SaveAsKV1TextNoContext_t = CNoContextBase<CSaveAsKV1Text_t<Empty_t, CUtlBuffer *>>;

	class CSaveAsKV1Text_NoContext : public SaveAsKV1TextNoContext_t
	{
	public:
		using Base_t = SaveAsKV1TextNoContext_t;

		CSaveAsKV1Text_NoContext(const Base_t::Base_t &aInit)
		 :  Base_t(aInit)
		{
		}

		CSaveAsKV1Text_NoContext(const CSave_General::Base_t &aInit);
	}; // CSaveAsKV1Text_NoContext

	class SaveAsKV1Text_NoContext final : public CSaveAsKV1Text_NoContext
	{
	public:
		using CBase = CSaveAsKV1Text_NoContext;
		using CBase::CBase;
	}; // SaveAsKV1Text_NoContext

	template<class T, class O, class P>
	struct CSaveAsKV1Text_Translated_t : public CSaveAsKV1Text_t<T, O>, 
	                                     public KV1Unk_t<int>, 
	                                     public KV1Proccessor_t<P>
	{
	public:
		using Base_t = CSaveAsKV1Text_t<T, O>;

		CSaveAsKV1Text_Translated_t(const Base_t &aInit, int nInitUnk, const P &aInitProcessor)
		 :  Base_t{aInit}, 
		    KV1Unk_t<int>{nInitUnk}, 
		    KV1Proccessor_t<P>{aInitProcessor}
		{
		}

	}; // CSaveAsKV1Text_Translated_t<T, O, P>

	class ISaveAsKV1Text_Translated
	{
	public:
		virtual bool SaveAsKV1Text_Translated() = 0;
	}; // ISaveAsKV1Text_Translated

	template<class T>
	class CSaveAsKV1TextBase_Translated : public ISaveAsKV1Text_Translated, 
	                                      public T
	{
	public:
		using Base_t = T;

		CSaveAsKV1TextBase_Translated(const Base_t &aInit)
		 :  Base_t(aInit)
		{
		}
	}; // CSaveAsKV1TextBase_Translated<T>

	using SaveAsKV1TextTranslated_t = CSaveAsKV1TextBase_Translated<CSaveAsKV1Text_Translated_t<KeyValues3 *, CUtlBuffer *, KV3ToKV1Translation_t *>>;

	class CSaveAsKV1Text_Translated : public SaveAsKV1TextTranslated_t
	{
	public:
		using Base_t = SaveAsKV1TextTranslated_t;

		CSaveAsKV1Text_Translated(const Base_t::Base_t &aInit)
		 :  Base_t(aInit)
		{
		}

	public:
		bool SaveAsKV1Text_Translated() override;
	}; // CSaveAsKV1Text_Translated

	class SaveAsKV1Text_Translated final : public CSaveAsKV1Text_Translated
	{
	public:
		using CBase = CSaveAsKV1Text_Translated;
		using CBase::CBase;
	};

	using SaveAsKV1TextTranslated_NoContext_t = CNoContextBase<CSaveAsKV1Text_Translated_t<Empty_t, CUtlBuffer *, KV3ToKV1Translation_t *>>;

	class CSaveAsKV1Text_Translated_NoContext : public SaveAsKV1TextTranslated_NoContext_t
	{
	public:
		using Base_t = SaveAsKV1TextTranslated_NoContext_t;

		CSaveAsKV1Text_Translated_NoContext(const Base_t::Base_t &aInit)
		 :  Base_t(aInit)
		{
		}
	}; // CSaveAsKV1Text_Translated_NoContext

	class SaveAsKV1Text_Translated_NoContext final : public CSaveAsKV1Text_Translated_NoContext
	{
	public:
		using CBase = CSaveAsKV1Text_Translated_NoContext;
		using CBase::CBase;
	};

	class CKeyValuesWriter : public CWriterBase<CConfig>
	{
	public:
		CKeyValuesWriter() = default;
		CKeyValuesWriter(KeyValues3 *pRoot) : CConfig(pRoot) {}

	public: // IBaseWriter<CSave_General>
		bool Save(const CSave_General &aParams);

	public: // IBaseWriter<CSaveToFile_General>
		bool Save(const CSaveToFile_General &aParams);

	public:
		//
		// Save ones (members).
		//
		bool SaveAsKV1Text(const CSaveAsKV1Text_NoContext &aParams) const;
		bool SaveAsKV1Text_Translated(const CSaveAsKV1Text_Translated_NoContext &aParams) const;
	}; // CKeyValuesWriter
}; // AnyConfig

#endif // _INCLUDE_ANY_CONFIG_KEYVALUES_WRITER_HPP_
