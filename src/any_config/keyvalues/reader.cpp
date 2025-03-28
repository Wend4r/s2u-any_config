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

#include <any_config/keyvalues/reader.hpp>

#include <tier0/keyvalues3.h>
#include <tier0/utlbuffer.h>
#include <tier0/strtools.h>

bool AnyConfig::CLoadFromKV1File::LoadFromKV1File()
{
	return LoadKV3FromKV1File(m_aContext, 
	                          m_psMessage, 
	                          m_pszFilename, 
	                          m_pszPathID, 
	                          m_eBehavior);
}

AnyConfig::CLoadFromKV1File_NoContext::CLoadFromKV1File_NoContext(const CLoadFromFile_General::Base_t &aInit)
 :  Base_t({aInit.m_psMessage, aInit.m_pszFilename, aInit.m_pszPathID, KV1TEXT_ESC_BEHAVIOR_UNK1})
{
}

bool AnyConfig::CLoadFromKV1Text::LoadFromKV1Text()
{
	return LoadKV3FromKV1Text(m_aContext, 
	                          m_psMessage, 
	                          m_aData, 
	                          m_eBehavior, 
	                          m_pszName, 
	                          m_aValue);
}

bool AnyConfig::CLoadFromKV1Text_Translated::LoadFromKV1Text_Translated()
{
	return LoadKV3FromKV1Text_Translated(m_aContext, 
	                                     m_psMessage, 
	                                     Input_t<const char *>::m_aData, 
	                                     m_eBehavior,
	                                     KV1Proccessor_t<KV1ToKV3Translation_t *>::m_aData, 
	                                     KV1Unk_t<int>::m_aValue, 
	                                     m_pszName, 
	                                     KV1Unk_t<bool>::m_aValue);
}

AnyConfig::CLoadFromKV1Text_NoContext::CLoadFromKV1Text_NoContext(const CLoad_General::Base_t &aInit)
 :  CLoadFromKV1Text_NoContext({aInit.m_psMessage, (const char *)aInit.m_aData->Base(), KV1TEXT_ESC_BEHAVIOR_UNK1, aInit.m_pszName, false})
{
}

bool AnyConfig::CKeyValuesReader::Load(const CLoad_General &aParams)
{
	return LoadFromKV1Text(aParams.To<CLoadFromKV1Text_NoContext>());
}

bool AnyConfig::CKeyValuesReader::Load(const CLoadFromFile_General &aParams)
{
	return LoadFromKV1File(aParams.To<CLoadFromKV1File_NoContext>());
}

bool AnyConfig::CKeyValuesReader::LoadFromKV1File(const CLoadFromKV1File_NoContext &aParams)
{
	return LoadKV3FromKV1File(Get(), 
	                          aParams.m_psMessage, 
	                          aParams.m_pszPathID, 
	                          aParams.m_pszFilename, 
	                          aParams.m_eBehavior);
}

bool AnyConfig::CKeyValuesReader::LoadFromKV1Text(const CLoadFromKV1Text_NoContext &aParams)
{
	return LoadKV3FromKV1Text(Get(), 
	                          aParams.m_psMessage, 
	                          aParams.m_aData, 
	                          aParams.m_eBehavior, 
	                          aParams.m_pszName, 
	                          aParams.m_aValue);
}

bool AnyConfig::CKeyValuesReader::LoadFromKV1Text_Translated(const CLoadFromKV1Text_Translated_NoContext &aParams)
{
	return LoadKV3FromKV1Text_Translated(Get(), 
	                                     aParams.m_psMessage, 
	                                     aParams.Input_t<const char *>::m_aData, 
	                                     aParams.m_eBehavior, 
	                                     aParams.KV1Proccessor_t<KV1ToKV3Translation_t *>::m_aData, 
	                                     aParams.KV1Unk_t<int>::m_aValue, 
	                                     aParams.m_pszName, 
	                                     aParams.KV1Unk_t<bool>::m_aValue);
}
