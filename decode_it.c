 # include <stdio.h>
 # include <unistd.h>
 # include <sys/stat.h>
 # include <sys/types.h>
 # include <sys/mman.h>
 # include <stdlib.h>

 # include "mad_decode.h"


int main(int argc, char **argv) {

  if(argc < 2 || argc > 2){
    printf("\nUSAGE:\t\nPass an audiofile to play stuff\n");
    exit(1);
  }



/*
if ((fp = fopen(argv[1],"r"))){

  printf("File is open\n");

    struct stat stat;
    int filename = fileno(fp);
    char result = fstat(filename, &stat);

    printf("Size of file is: %lld\n",stat.st_size);
    fclose(fp);
}
*/

//file pointer
FILE *fp;
//stat struct
struct stat stat;

//open file in argument
fp = fopen(argv[1],"r");

//get descriptor
int fd = fileno(fp);

/*
 if (fstat(fd, &stat) == 0){
   printf("st_size: %lld\n",stat.st_size);
 } else printf("an error acquired\n");
*/

void *fdm;

fdm = mmap(0,stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
/*
if (fdm == MAP_FAILED){
  printf("map is failed\n");
} else printf("mapped at %d\n",&fdm);
*/

//release file
fclose(fp);

decode(fdm, stat.st_size);

//unmap thing
munmap(fdm, stat.st_size);

  return 0;
}
