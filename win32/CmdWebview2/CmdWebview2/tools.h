#pragma once
#include <windows.h>
#include <string>
std::string DecodeURIComponent(const std::string& encodedStr) {
	std::string decodedStr;

	size_t length = encodedStr.length();
	size_t index = 0;

	while (index < length)
	{
		if (encodedStr[index] == '%')
		{
			if (index + 2 < length)
			{
				// Decode hexadecimal representation
				std::string hexStr = encodedStr.substr(index + 1, 2);
				int hexValue = std::stoi(hexStr, nullptr, 16);
				decodedStr.push_back(static_cast<char>(hexValue));
				index += 3;
			}
			else
			{
				// Invalid format, append '%' as is
				decodedStr.push_back(encodedStr[index]);
				index++;
			}
		}
		else
		{
			// Append character as is
			decodedStr.push_back(encodedStr[index]);
			index++;
		}
	}

	return decodedStr;
}

std::wstring ConvertToWideString(const std::string& str)
{
	int length = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
	std::wstring wideStr(length, L'\0');
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wideStr[0], length);
	return wideStr;
}