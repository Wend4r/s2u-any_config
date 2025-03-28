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

#ifndef _INCLUDE_ANY_CONFIG_HPP_
#define _INCLUDE_ANY_CONFIG_HPP_

#pragma once

#include "any_config/base.hpp"
#include "any_config/json.hpp"
#include "any_config/keyvalues.hpp"

class KeyValues3;

namespace AnyConfig
{
	class CAnyone : virtual public CBase, 
	                virtual public CJSON, 
	                virtual public CKeyValues
	{
	public:
		CAnyone();
		CAnyone(KeyValues3 *pRoot);

	public: // IBaseReader<CLoad_General>
		bool Load(const CLoad_General &aParams);

	public: // IBaseReader<CLoadFromFile_General>
		bool Load(const CLoadFromFile_General &aParams);

	public: // IBaseWriter<CSave_General>
		bool Save(const CSave_General &aParams);

	public: // IBaseWriter<CSaveToFile_General>
		bool Save(const CSaveToFile_General &aParams);
	}; // CAnyone

	class Anyone final : public CAnyone
	{
	public:
		using CAnyone::CAnyone;
	};
}; // AnyConfig

#endif // _INCLUDE_ANY_CONFIG_HPP_
