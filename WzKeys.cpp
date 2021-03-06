//////////////////////////////////////////////////////////////////////////////////
//	This file is part of the WzKeys project										//
//	Copyright (C) 2020 Ryan Payton												//
//																				//
//	This program is free software: you can redistribute it and/or modify		//
//	it under the terms of the GNU Affero General Public License as published by	//
//	the Free Software Foundation, either version 3 of the License, or			//
//	(at your option) any later version.											//
//																				//
//	This program is distributed in the hope that it will be useful,				//
//	but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the				//
//	GNU Affero General Public License for more details.							//
//																				//
//	You should have received a copy of the GNU Affero General Public License	//
//	along with this program.  If not, see <https://www.gnu.org/licenses/>.		//
//////////////////////////////////////////////////////////////////////////////////
#include "WzKeysTrimmed.h"

#include <iomanip>
#include <iostream>
#include <sstream>

static constexpr bool SHOW_SIZES = false;

std::string int_to_hex(unsigned int i)
{
	std::stringstream stream;
	stream << "0x" << std::setfill('0') << std::setw(sizeof(unsigned int) / 2) << std::hex << std::uppercase << i;

	return stream.str();
}

void show_sizes(const unsigned int oSize, const unsigned int cSize)
{
	std::cout
		<< "Key size: " << oSize << std::endl
		<< "Comparison key size: " << cSize << std::endl;
}

namespace WzKeysTest
{
	unsigned int TestKey[4 * 8] =
	{
		0x13, 0x00, 0x00, 0x00,
		0x08, 0x00, 0x00, 0x00,
		0x06, 0x00, 0x00, 0x00,
		0xB4, 0x00, 0x00, 0x00,
		0x1B, 0x00, 0x00, 0x00,
		0x0F, 0x00, 0x00, 0x00,
		0x33, 0x00, 0x00, 0x00,
		0x52, 0x00, 0x00, 0x00
	};

	unsigned int sizeOfTestKey()
	{
		return sizeof(TestKey) / sizeof(unsigned int);
	}
}

int main()
{
	unsigned int* oKey = WzKeysTrimmed::getTrimmedUserKey();
	unsigned int* cKey = WzKeysTest::TestKey;

	unsigned int oSize = WzKeysTrimmed::sizeOfTrimmedUserKey();
	unsigned int cSize = WzKeysTest::sizeOfTestKey();

	if (SHOW_SIZES)
	{
		show_sizes(oSize, cSize);

		std::cout << std::endl;
	}

	if (oSize != cSize)
	{
		std::cout << "Size mismatch" << std::endl;

		if (!SHOW_SIZES)
			show_sizes(oSize, cSize);

		return 0;
	}

	for (unsigned int i = 0; i < oSize; i++)
	{
		if (oKey[i] != cKey[i])
		{
			std::cout
				<< "Keys don't match at index [" << i << "]" << std::endl
				<< "Key: '" << int_to_hex(oKey[i]) << "'" << std::endl
				<< "Comparison key: '" << int_to_hex(cKey[i]) << "'" << std::endl;

			return 0;
		}
	}

	std::cout << "Keys match!" << std::endl;
}