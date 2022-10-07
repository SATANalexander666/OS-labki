void RemoveVowels(std::string &str);
std::string ReadFromPipe(int fd[2]);
void WriteToFile(std::string path, std::string data);
void ChildMain(int fd[2]);