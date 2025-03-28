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

#ifndef _INCLUDE_ANY_CONFIG_FILE_EXTENSION_CHECK_HPP_
#define _INCLUDE_ANY_CONFIG_FILE_EXTENSION_CHECK_HPP_

#pragma once

#include <array>
#include <cassert>
#include <string_view>

namespace AnyConfig
{
	namespace FileExtension
	{
		class ICheck
		{
		public:
			virtual bool Check(std::string_view svFilename) = 0;
		}; // ICheck

		template<const char *...t_pszExtensions>
		class CCheck : public ICheck
		{
			static constexpr std::array<std::string_view, sizeof...(t_pszExtensions)> sm_aExtensions = {t_pszExtensions...};

		public: // ICheck
			bool Check(std::string_view svFilename) override
			{
				assert(!svFilename.empty());

				for(std::string_view svExtension : sm_aExtensions)
				{
					if(svFilename.length() < svExtension.length())
					{
						continue;
					}

					if(svFilename.substr(svFilename.length() - svExtension.length()) == svExtension)
					{
						return true;
					}
				}

				return false;
			}
		}; // CCheck<t_pszExtensions>
	}; // FileExtension
}; // AnyConfig

#endif // _INCLUDE_ANY_CONFIG_FILE_EXTENSION_CHECK_HPP_
