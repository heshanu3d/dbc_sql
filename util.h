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

inline std::filesystem::path currentPath(int32_t max_depth = 10)
{
    std::filesystem::path cur = std::filesystem::current_path();
    while (!std::filesystem::exists(cur / "dbc") && (--max_depth > 0) ) {
        cur = cur / "..";
    }
    if (max_depth > 0)
        return cur;
    return {};
}

inline std::filesystem::path getCurrentPath()
{
    static std::filesystem::path cur = currentPath();
    return cur;
//	if (std::filesystem::exists(std::filesystem::current_path() / "dbc"))
//		return std::filesystem::current_path();
//	else if (std::filesystem::exists(std::filesystem::current_path() / ".." / "dbc"))
//		return std::filesystem::current_path() / "..";
//	else {
//		cout << "please place binary besides dbc directories" << endl;
//		return {};
//	}
}