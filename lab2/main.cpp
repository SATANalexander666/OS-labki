#include<string>
#include<iostream>

#include<child.hpp>
#include<parent.hpp>

#include<unistd.h>
#include<stdlib.h>
#include<cstring>
#include<sys/wait.h>

int main()
{
    int fd[2], fd1[2];

	if (pipe(fd) == -1 || pipe(fd1) == -1)
	{
		perror("pipe error )");
		exit(EXIT_FAILURE);
	}

	int pid = fork();
	int pid1 = 1;

	if (pid > 0){
		pid1 = fork();
	}

	if (pid < 0 || pid1 < 0)
	{
		perror("process error )");
		exit(EXIT_FAILURE);
	}

	if(pid == 0){
		ChildMain(fd);
	}
	else if (pid1 == 0){
		ChildMain(fd1);
	}
	else{
		ParentMain(fd, fd1);
	}

	/*
	if(pid == 0)
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
	else if (pid1 == 0)
	{
		std::string file = ReadFromPipe(fd1);
		std::cout << "[" << getpid() << "] " << file << std::endl;

		while (true)
		{
			std::string strRes = ReadFromPipe(fd1);
			RemoveVowels(strRes);
			WriteToFile(file, strRes);

			std::cout << "[" << getpid() << "] " << strRes << std::endl;
		}
	}
	else
	{
		std::string file, file1;
		std::cin >> file >> file1;

		WriteToPipe(fd, file);
		WriteToPipe(fd1, file1);

		std::string strInput;

		while (std::cin >> strInput)
		{
			if (ChosePipe() == 0){
				WriteToPipe(fd, strInput);
			}
			else{
				WriteToPipe(fd1, strInput);
			}
		}
	}
	*/

    return 0;
}