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

#include <any_config/json/writer.hpp>

#include <tier0/bufferstring.h>
#include <tier0/keyvalues3.h>
#include <tier0/utlstring.h>

AnyConfig::CSaveJSON_NoContext::CSaveJSON_NoContext(const CSave_General::Base_t &aInit)
 :  CSaveJSON_NoContext({aInit.m_psMessage, aInit.Output_t<CUtlBuffer *>::m_aData})
{
}

bool AnyConfig::CSaveJSON::SaveJSON()
{
	return SaveKV3AsJSON(SaveFrom_t<KeyValues3 *>::m_aData, 
	                     m_psMessage, 
	                     Output_t<CUtlBuffer *>::m_aData);
}

bool AnyConfig::CSaveJSON2::SaveJSON()
{
	return SaveKV3AsJSON(SaveFrom_t<KeyValues3 *>::m_aData, 
	                     m_psMessage, 
	                     Output_t<CUtlString *>::m_aData);
}

bool AnyConfig::CJSONWriter::Save(const CSave_General &aParams)
{
	return SaveJSON(aParams.To<CSaveJSON_NoContext>());
}

bool AnyConfig::CJSONWriter::Save(const CSaveToFile_General &aParams)
{
	static const char *s_pszMessageConcat[] = {"<", "Save", "  JSON", " to file", ": ", "Not supported now", ">"};

	*aParams.m_psMessage = CBufferStringN<256>(s_pszMessageConcat);

	return false;
}

bool AnyConfig::CJSONWriter::SaveJSON(const CSaveJSON_NoContext &aParams) const
{
	return SaveKV3AsJSON(Get(), 
	                     aParams.m_psMessage, 
	                     aParams.Output_t<CUtlBuffer *>::m_aData);
}

bool AnyConfig::CJSONWriter::SaveJSON(const CSaveJSON2_NoContext &aParams) const
{
	return SaveKV3AsJSON(Get(), 
	                     aParams.m_psMessage, 
	                     aParams.Output_t<CUtlString *>::m_aData);
}
