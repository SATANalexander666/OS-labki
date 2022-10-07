#include<string>
#include<set>
#include<algorithm>
#include<iostream>
#include<fstream>

#include<unistd.h>

void RemoveVowels(std::string &str)
{
    std::set<char> setVowels;
    std::string strVowels = "aeiouyAEIOUY";

    for (char elem : strVowels){
        setVowels.insert(elem);
    }

    for (char letter : setVowels){
        str.erase(remove(str.begin(), str.end(), letter), str.end());
    }
}

void WriteToFile(std::string path, std::string data)
{
    std::fstream file;
    file.open(path, std::ios::app);

    if (!file.is_open())
    {
        perror("opening file error )");
        exit(EXIT_FAILURE);
    }
    else
    {
        file << data << std::endl;
    }

    file.close();
}

std::string ReadFromPipe(int fd[2])
{
    close(fd[1]);

	int strSize;
	if (read(fd[0], &strSize, sizeof(int)) == -1)
    {
		perror("reading from pipe error )");
        exit(EXIT_FAILURE);
	}

	char str[strSize];
	if (read(fd[0], &str, strSize) == -1)
    {
		perror("reading from pipe error )");
        exit(EXIT_FAILURE);
    }

    std::string strOutput(str);

    return strOutput;
}

void ChildMain(int fd[2])
{
    std::string file = ReadFromPipe(fd);
	std::cout << "[" << getpid() << "] " << file << std::endl;

	while (true)
	{
		std::string strRes = ReadFromPipe(fd);
		RemoveVowels(strRes);
		WriteToFile(file, strRes);

		std::cout << "[" << getpid() << "] " << strRes << std::endl;
	}
}
