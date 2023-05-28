#pragma once
#include <windows.h>
#include <string>
#include <sstream>
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

LPCWSTR ConvertToLPCWSTR(const std::string& str) {
	// Konversi string menjadi wide string UTF-16
	int wideStrLength = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
	std::vector<wchar_t> wideStr(wideStrLength);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wideStr.data(), wideStrLength);

	// Mengalokasikan buffer dan menyalin wide string ke dalamnya
	size_t bufferSize = (wideStrLength + 1) * sizeof(wchar_t);  // Ukuran buffer dalam byte
	LPWSTR buffer = static_cast<LPWSTR>(CoTaskMemAlloc(bufferSize));
	if (buffer != nullptr) {
		memcpy(buffer, wideStr.data(), bufferSize);
		buffer[wideStrLength] = L'\0';  // Menambahkan karakter null di akhir wide string
	}

	return buffer;
}

std::vector<std::string> SplitString(const std::string& str, char delimiter) {
	std::vector<std::string> tokens;
	size_t start = 0;
	size_t end = str.find(delimiter);

	while (end != std::string::npos) {
		tokens.push_back(str.substr(start, end - start));
		start = end + 1;
		end = str.find(delimiter, start);
	}

	tokens.push_back(str.substr(start));

	return tokens;
}
std::vector<std::wstring> SplitStringW(const std::wstring& str, char delimiter) {
	std::vector<std::wstring> tokens;
	size_t start = 0;
	size_t end = str.find(delimiter);

	while (end != std::string::npos) {
		tokens.push_back(str.substr(start, end - start));
		start = end + 1;
		end = str.find(delimiter, start);
	}

	tokens.push_back(str.substr(start));

	return tokens;
}

std::vector<std::string> ParseArguments(LPSTR lpCmdLine)
{
	std::vector<std::string> arguments;

	std::string cmdLine(lpCmdLine);
	std::string argument;

	bool insideQuotes = false;

	for (char c : cmdLine)
	{
		if (c == '\"')
		{
			insideQuotes = !insideQuotes;
		}
		else if (c == ' ' && !insideQuotes)
		{
			if (!argument.empty())
			{
				arguments.push_back(argument);
				argument.clear();
			}
		}
		else
		{
			argument += c;
		}
	}

	if (!argument.empty())
	{
		arguments.push_back(argument);
	}

	return arguments;
}
