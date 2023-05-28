#pragma once
#include <string>
#include <vector>
#include <windows.h> 
#include <sstream> 
#include "tools.h"
#include <map>
 
 
bool startsWith(const std::string& str, const std::string& prefix) {
	if (str.length() < prefix.length()) {
		return false;
	}
	return str.substr(0, prefix.length()).compare(prefix) == 0;
}
class ArgMap
{
	std::map<std::wstring, std::wstring> mapArg;

	
	public :
		std::wstring getVal(std::wstring name) {
			std::wstring val = mapArg[name];
			return val;
		}

		static ArgMap parse(LPSTR commandLine) {
			int argc; 
			
			LPWSTR cmdLine = GetCommandLine();


			ArgMap result;
			LPWSTR* wideArgv = CommandLineToArgvW(cmdLine, &argc); 
			// Mengisi array argv dengan argumen dari wideArgv
			for (int i = 1; i < argc; i++)
			{
				std::wstring argument = wideArgv[i];
				size_t pos = argument.find(L"=");
				 
				if (pos != -1) {
					std::wstring  name = argument.substr(0, pos);
					std::wstring val = argument.substr(pos + 1, argument.size());

					//val = DecodeURIComponent(val);

					result.mapArg[name] = val;
				}
			} 
			return result;
	
		}
};