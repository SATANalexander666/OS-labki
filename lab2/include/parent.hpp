void WriteToPipe(int fd[2], std::string strSrc);
int ChosePipe();
void ParentMain(int fd[2], int fd1[2]);