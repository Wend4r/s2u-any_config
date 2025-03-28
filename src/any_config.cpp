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

#include <any_config.hpp>

#include <tier0/bufferstring.h>
#include <tier0/commonmacros.h>
#include <tier0/utlstring.h>

AnyConfig::CAnyone::CAnyone()
 :  CConfig()
{
}

AnyConfig::CAnyone::CAnyone(KeyValues3 *pRoot)
 :  CConfig(pRoot)
{
}

bool AnyConfig::CAnyone::Load(const CLoad_General &aParams)
{
	AssertMsg(false, "Use an explicit conversion");

	static const char *s_pszMessageConcat[] = {"<", "Load", " Anyone", ": ", "Use an explicit conversion", ">"};

	*aParams.m_psMessage = CBufferStringN<256>(s_pszMessageConcat);

	return false;
}

bool AnyConfig::CAnyone::Load(const CLoadFromFile_General &aParams)
{
	const char *pszFilename = aParams.m_pszFilename;

	if(CBase::m_aCheckFileExtension.Check(pszFilename))
	{
		return CBase::Load(aParams);
	}
	else if(CJSON::m_aCheckFileExtension.Check(pszFilename))
	{
		return CJSON::Load(aParams);
	}
	else if(CKeyValues::m_aCheckFileExtension.Check(pszFilename))
	{
		return CKeyValues::Load(aParams);
	}

	const char *pszMessageConcat[] = {"<", "Load", " Anyone", " from file", ": ", "Unknown file extension", " of ", "\"", pszFilename, "\"", ">"};

	*aParams.m_psMessage = CBufferStringN<256 + MAX_PATH>(pszMessageConcat);

	return false;
}

bool AnyConfig::CAnyone::Save(const CSave_General &aParams)
{
	AssertMsg(false, "Use an explicit conversion");

	static const char *s_pszMessageConcat[] = {"<", "Save", " Anyone", ": ", "Use an explicit conversion", ">"};

	*aParams.m_psMessage = CBufferStringN<256>(s_pszMessageConcat);

	return false;
}

bool AnyConfig::CAnyone::Save(const CSaveToFile_General &aParams)
{
	const char *pszFilename = aParams.m_pszFilename;

	if(CBase::m_aCheckFileExtension.Check(pszFilename))
	{
		return CBase::Save(aParams);
	}
	else if(CJSON::m_aCheckFileExtension.Check(pszFilename))
	{
		return CJSON::Save(aParams);
	}
	else if(CKeyValues::m_aCheckFileExtension.Check(pszFilename))
	{
		return CKeyValues::Save(aParams);
	}

	const char *pszMessageConcat[] = {"<", "Save", "  Anyone", " to file", ": ", "Unknown file extension", " of ", "\"", pszFilename, "\"", ">"};

	CBufferStringN<256 + MAX_PATH> sMessage;

	sMessage.AppendConcatN(pszMessageConcat);
	*aParams.m_psMessage = sMessage;

	return false;
}
