#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

char timbuf[80];

char* convert_time(time_t time){
  struct tm lt;
  localtime_r(&time, &lt);
  strftime(timbuf, sizeof(timbuf), "%c", &lt);
  return timbuf;
}

int main(int argc, char* argv[]){

  if(argc == 1){
    printf("usage: ./stat path_to_file\n");
    return 1;
  }

  struct stat file_status;

  if(stat(argv[1], &file_status) < 0){
    printf("error reading file\n");
    return 1;
  }
  printf("\nSTAT UTILITY\n");
  printf("information for (%s)\n", argv[1]);
  printf("-------------------------\n");
  printf("File Size: \t\t%lld bytes\n",file_status.st_size);
  printf("Number of Links: \t%d\n",file_status.st_nlink);
  printf("File inode: \t\t%llu\n",file_status.st_ino);
  char* access_time = convert_time(file_status.st_atime);
  printf("Most recent accessed time: %s\n", access_time);
  char* perm_time = convert_time(file_status.st_mtime);
  printf("Most recent changed permission time: %s\n", perm_time);

  printf("File Permissions: \t");
  printf( (S_ISDIR(file_status.st_mode)) ? "d" : "-");
  printf( (file_status.st_mode & S_IRUSR) ? "r" : "-");
  printf( (file_status.st_mode & S_IWUSR) ? "w" : "-");
  printf( (file_status.st_mode & S_IXUSR) ? "x" : "-");
  printf( (file_status.st_mode & S_IRGRP) ? "r" : "-");
  printf( (file_status.st_mode & S_IWGRP) ? "w" : "-");
  printf( (file_status.st_mode & S_IXGRP) ? "x" : "-");
  printf( (file_status.st_mode & S_IROTH) ? "r" : "-");
  printf( (file_status.st_mode & S_IWOTH) ? "w" : "-");
  printf( (file_status.st_mode & S_IXOTH) ? "x" : "-");
  printf("\n\n");

  printf("The file %s a symbolic link\n", (S_ISLNK(file_status.st_mode)) ? "is" : "is not");

  return 0;
}
