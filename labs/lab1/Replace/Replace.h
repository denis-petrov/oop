std::string ReplaceString(std::string& line, std::string& searchString, std::string& replacementString);
void CopyFileWithReplacedStrings(std::ifstream& input, std::ofstream& output, std::string& searchString, std::string& replacementString);
