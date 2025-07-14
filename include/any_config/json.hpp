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

#ifndef _INCLUDE_ANY_CONFIG_JSON_HPP_
#define _INCLUDE_ANY_CONFIG_JSON_HPP_

#pragma once

#include "json/reader.hpp"
#include "json/writer.hpp"

#include "file_extension/check.hpp"

namespace AnyConfig
{
	class CJSON : virtual public CJSONReader, virtual public CJSONWriter
	{
	public:
		static constexpr const char sm_szFileExtensionJSON[] = ".json";

		FileExtension::CCheck<sm_szFileExtensionJSON> m_aCheckFileExtension;
	}; // CJSON

	class JSON final : public CJSON
	{
	public:
		using CJSON::CJSON;
	}; // JSON
}; // AnyConfig

#endif // _INCLUDE_ANY_CONFIG_JSON_HPP_
