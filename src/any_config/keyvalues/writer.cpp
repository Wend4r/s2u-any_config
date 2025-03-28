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

#include <any_config/keyvalues/writer.hpp>

#include <tier0/bufferstring.h>
#include <tier0/keyvalues3.h>
#include <tier0/utlstring.h>

bool AnyConfig::SaveAsKV1Text_t::SaveAsKV1Text()
{
	return SaveKV3AsKV1Text(m_aContext, 
	                        m_psMessage, 
	                        m_aData, 
	                        m_eBehavior);
}

AnyConfig::CSaveAsKV1Text_NoContext::CSaveAsKV1Text_NoContext(const CSave_General::Base_t &aInit)
 :  Base_t({aInit.m_psMessage, aInit.Output_t<CUtlBuffer *>::m_aData, KV1TEXT_ESC_BEHAVIOR_UNK1})
{
}

bool AnyConfig::CSaveAsKV1Text_Translated::SaveAsKV1Text_Translated()
{
	return SaveKV3AsKV1Text_Translated(m_aContext, 
	                                   m_psMessage, 
	                                   Output_t<CUtlBuffer *>::m_aData, 
	                                   m_eBehavior,
	                                   KV1Proccessor_t<KV3ToKV1Translation_t *>::m_aData, 
	                                   KV1Unk_t<int>::m_aValue);
}

bool AnyConfig::CKeyValuesWriter::Save(const CSave_General &aParams)
{
	return SaveAsKV1Text(aParams.To<CSaveAsKV1Text_NoContext>());
}

bool AnyConfig::CKeyValuesWriter::Save(const CSaveToFile_General &aParams)
{
	static const char *s_pszMessageConcat[] = {"<", "Save", " KeyValues", " to file", ": ", "Not supported now", ">"};

	*aParams.m_psMessage = CBufferStringN<256>(s_pszMessageConcat);

	return false;
}

bool AnyConfig::CKeyValuesWriter::SaveAsKV1Text(const CSaveAsKV1Text_NoContext &aParams) const
{
	return SaveKV3AsKV1Text(Get(), 
	                        aParams.m_psMessage, 
	                        aParams.m_aData, 
	                        aParams.m_eBehavior);
}

bool AnyConfig::CKeyValuesWriter::SaveAsKV1Text_Translated(const CSaveAsKV1Text_Translated_NoContext &aParams) const
{
	return SaveKV3AsKV1Text_Translated(Get(), 
	                                   aParams.m_psMessage, 
	                                   aParams.Output_t<CUtlBuffer *>::m_aData, 
	                                   aParams.m_eBehavior, 
	                                   aParams.KV1Proccessor_t<KV3ToKV1Translation_t *>::m_aData, 
	                                   aParams.m_aValue);
}