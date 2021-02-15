std::string ReplaceString(const std::string& line, const std::string& searchString, const std::string& replacementString);
void CopyFileWithReplacedStrings(std::ifstream& input, std::ofstream& output, const std::string& searchString, const std::string& replacementString);
