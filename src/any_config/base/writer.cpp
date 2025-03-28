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

#include <any_config/base/writer.hpp>

#include <tier0/keyvalues3.h>

bool AnyConfig::CSave::Save()
{
	return SaveKV3(m_aEncoding, 
	               m_aFormat, 
	               SaveFrom_t<KeyValues3 *>::m_aData, 
	               m_psMessage, 
	               Output_t<CUtlBuffer *>::m_aData, 
	               m_uFlags);
}

bool AnyConfig::CSaveToFile::SaveToFile()
{
	return SaveKV3ToFile(m_aEncoding, 
	                     m_aFormat, 
	                     m_aData, 
	                     m_psMessage, 
	                     m_pszFilename,
	                     m_pszPathID, 
	                     m_uFlags);
}

AnyConfig::CBaseWriter::CBaseWriter()
 :  CConfig()
{
}


AnyConfig::CBaseWriter::CBaseWriter(KeyValues3 *pRoot)
 :  CConfig(pRoot)
{
}

bool AnyConfig::CBaseWriter::Save(const CSave_General &aParams)
{
	return const_cast<const CBaseWriter *>(this)->Save(aParams.ToBase());
}

bool AnyConfig::CBaseWriter::Save(const CSaveToFile_General &aParams)
{
	return SaveToFile(aParams.ToBase());
}

bool AnyConfig::CBaseWriter::Save(const CSave_NoContext &aParams) const
{
	return SaveKV3(aParams.m_aEncoding, 
	               aParams.m_aFormat, 
	               Get(), 
	               aParams.m_psMessage, 
	               aParams.Output_t<CUtlBuffer *>::m_aData, 
	               aParams.m_uFlags);
}

bool AnyConfig::CBaseWriter::SaveToFile(const CSaveToFile_NoContext &aParams) const
{
	return SaveKV3ToFile(aParams.m_aEncoding, 
	                     aParams.m_aFormat, 
	                     Get(), 
	                     aParams.m_psMessage, 
	                     aParams.m_pszFilename, 
	                     aParams.m_pszPathID, 
	                     aParams.m_uFlags);
}
