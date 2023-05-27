#pragma once
#include <string>
#include <vector>
#include <windows.h> 
#include <sstream> 
#include "tools.h"
#include <map>
 
 

class ArgMap
{
	std::map<std::string, std::string> mapArg;

	
	public :
		std::string getVal(std::string name) {
			std::string val = mapArg[name];
			return val;
		}

		static ArgMap parse(LPSTR commandLine) {
			 
			ArgMap result;
			std::istringstream iss(commandLine);
			std::string argument;
			while (std::getline(iss, argument, ' '))
			{  
				size_t pos = argument.find("=");

				if (pos != -1) { 
					std::string  name = argument.substr(0, pos);
					std::string val = argument.substr(pos + 1, argument.size());
					val = DecodeURIComponent(val); 
					
					result.mapArg[name] = val;
				}
			}

			return result;
	
		}
};