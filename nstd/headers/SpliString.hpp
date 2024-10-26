#ifndef SPLITSTRING_HED
#define SPLITSTRING_HED

#include <vector>
#include <sstream>

namespace nihil {
	namespace nstd {
		static std::vector<std::string> splitString(const std::string& input, char delimiter)
		{
			std::vector<std::string> tokens;
			std::istringstream tokenStream(input);
			std::string token;

			while (std::getline(tokenStream, token, delimiter)) {
				tokens.push_back(token);
			}

			return tokens;
		}
	}
}
#endif
