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

#include <any_config/base/config.hpp>

#include <tier1/keyvalues3.h>

KeyValues3 *AnyConfig::CConfig::Get()
{
	return m_pRoot;
}

const KeyValues3 *AnyConfig::CConfig::Get() const
{
	return m_pRoot;
}

AnyConfig::CConfig::CConfig()
 :  m_bExternalAllocated(false), 
    m_pRoot(new KeyValues3(KV3_TYPEEX_INVALID, KV3_SUBTYPE_INVALID))
{
}

AnyConfig::CConfig::CConfig(KeyValues3 *pRoot)
 :  m_bExternalAllocated(true), 
    m_pRoot(pRoot)
{
}

AnyConfig::CConfig::~CConfig()
{
	if(!m_bExternalAllocated)
	{
		delete m_pRoot;
	}
}

void AnyConfig::CConfig::DebugPrint()
{
	DebugPrintKV3(m_pRoot);
}
