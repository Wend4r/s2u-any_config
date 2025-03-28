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

#include <any_config/json/reader.hpp>

#include <tier0/bufferstring.h>
#include <tier0/keyvalues3.h>
#include <tier0/utlbuffer.h>
#include <tier0/utlstring.h>

bool AnyConfig::CLoadFromJSON::LoadFromJSON()
{
	return LoadKV3FromJSON(m_aContext, 
	                       m_psMessage, 
	                       m_aData, 
	                       m_pszName);
}

AnyConfig::CLoadFromJSON_NoContext::CLoadFromJSON_NoContext(const CLoad_General &aInit)
 :  LoadFromJSON_NoContext_t({aInit.m_psMessage, (const char *)aInit.m_aData->Base(), aInit.m_pszName})
{
}

AnyConfig::CLoadFromJSONFile_NoContext::CLoadFromJSONFile_NoContext(const CLoadFromFile_General::Base_t &aInit)
 :  Base_t({aInit.m_psMessage, aInit.m_pszFilename, aInit.m_pszPathID})
{
}

bool AnyConfig::CJSONReader::Load(const CLoad_General &aParams)
{
	return LoadFromJSON(aParams.To<CLoadFromJSON_NoContext>());
}

bool AnyConfig::CJSONReader::Load(const CLoadFromFile_General &aParams)
{
	return LoadFromJSONFile(aParams.To<CLoadFromJSONFile_NoContext>());
}

bool AnyConfig::CJSONReader::LoadFromJSON(const CLoadFromJSON_NoContext &aParams)
{
	return LoadKV3FromJSON(Get(), 
	                       aParams.m_psMessage, 
	                       aParams.m_aData, 
	                       aParams.m_pszName);
}

bool AnyConfig::CJSONReader::LoadFromJSONFile(const CLoadFromJSONFile_NoContext &aParams)
{
	return LoadKV3FromJSONFile(Get(), 
	                           aParams.m_psMessage, 
	                           aParams.m_pszPathID, 
	                           aParams.m_pszFilename);
}
