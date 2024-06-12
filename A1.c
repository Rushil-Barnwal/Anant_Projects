#include<stdio.h>
#include<fcntl.h> 
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
	int fd;
	FILE *fp;
	char filename[]="filename.txt";
	//forking the process
	pid_t pid = fork();
	if(pid<0)
	{
		perror("fork failed");
		exit(1);
	}
	else if(pid==0) //child process
	{
		 fp = fopen(filename, "r"); //opening the file in read mode
        	if (fp == NULL)
		{
            		perror("fopen failed");
            		exit(1);
        	}
		char line[100];
		while(fgets(line, sizeof(line), fp)!=NULL)
		{
			if(strlen(line)>1) //checking whether the line is empty or not
			{
				printf("%s\n", line);
			}
		}
	fclose(fp);
	}
	else //parent process
	{
		if((fd = open(filename, O_RDWR))<0) //opening the file
		{
			perror("file open error\n");
			close(fd);
			exit(1);
		}
		char line[1000];
		int end = lseek(fd,0,SEEK_END); //setting the offset at the end of the file
		fgets(line,1000,stdin);
		if(write(fd,line,strlen(line))!=strlen(line))
		{
			perror("write error\n");
			close(fd);
			exit(1);
		}
	close(fd);
	}
}