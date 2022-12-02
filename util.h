#pragma once

#include <vector>
#include <string>
#include <regex>
#include <filesystem>

inline std::vector<std::string> split(const std::string str, const std::string regex_str)
{
    std::regex regexz(regex_str);
    std::vector<std::string> list(std::sregex_token_iterator(str.begin(), str.end(), regexz, -1),
                                  std::sregex_token_iterator());
    return list;
}

inline std::filesystem::path getCurrentPath()
{
	if (std::filesystem::exists(std::filesystem::current_path() / "dbc"))
		return std::filesystem::current_path();
	else if (std::filesystem::exists(std::filesystem::current_path() / ".." / "dbc"))
		return std::filesystem::current_path() / "..";
	else {
		cout << "please place binary besides dbc directories" << endl;
		return {};
	}
}