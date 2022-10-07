#include<iostream>
#include<string>
#include<random>

#include<unistd.h>
#include<cstring>

int ChosePipe()
{
	std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

	double epsilon = 1.0;
	while (epsilon > 0){
		epsilon /= 2;
	}

	if (dist(mt) - 0.8 > epsilon){
		return 1;
	}
	else{
		return 0;
	}
}

void WriteToPipe(int fd[2], std::string strSrc)
{
	close(fd[0]);

	int strSize = strSrc.length() * sizeof(char) + 1;
	if (write(fd[1], &strSize, sizeof(int)) == -1)
	{
		perror("writing to pipe error )");
		exit(EXIT_FAILURE);
	}

	char strContainer[strSize];
	strcpy(strContainer, strSrc.c_str());
	if (write(fd[1], &strContainer, sizeof(strContainer)) == -1)
	{
		perror("writing to pipe error )");
		exit(EXIT_FAILURE);
	}
}

void ParentMain(int fd[2], int fd1[2])
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