/*************	Largest File in the directory in the path given **************************************
Name : Saurabh Pandurang Bhosale
MIS no: 121935007
********************************************************************************************************/

#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>

void subDirectoryVisit(char *path);
void fileRead(char *path);
long int fileSize(const char *path);
long int ar_file[100] = {0};
int ar_idx=0;
long int large = 0;


int main()
{
	char path[100];
	printf("\Enter the directory path :");
	scanf("%s",path);
	
	subDirectoryVisit(path);
	printf("\nLargest file size : %ld",large);
	return 0;
}

void subDirectoryVisit(char *basePath)
{
	char path[100];
	struct dirent *dp;
	DIR *dir = opendir(basePath);
	struct stat filestat;
	int idx=0;
	
	if(!dir)
	{
		return ;
	}
	else
	{
		while((dp = readdir(dir)) != NULL)
		{
			if(strcmp(dp->d_name,".") != 0 && strcmp(dp->d_name,"..") !=0)
			{
				
				//construct name path from our basePath:
				strcpy(path,basePath);
				strcat(path,"/");
				strcat(path,dp->d_name);
			
				subDirectoryVisit(path);	
			}
			
			stat(dp->d_name,&filestat);
			if(	!(S_ISDIR(filestat.st_mode)))
			{
				//printf("%s\n",dp->d_name);
				fileRead(dp->d_name);	
			}
		}
		
		for(idx = 0;idx<ar_idx;idx++)
		{
			if(ar_file[idx]>large)
			{
				large = ar_file[idx];
			}
		}
		


		closedir(dir);
	}
}

void fileRead(char *filePath)
{

	FILE *fp;
	long int size =0;
	fp = fopen(filePath,"r");
	if(!(fp == NULL))
	{
		size = fileSize(filePath);
		printf("%s\t: %ld\n",filePath,size);
		ar_file[ar_idx] = size;
		ar_idx ++;
		
	}
	fclose(fp);
	

}

long int fileSize(const char *fileName)
{
	struct stat stSize;
	
	if(stat(fileName,&stSize) == 0)
		return (stSize.st_size);
	else 
		return -1;
}


