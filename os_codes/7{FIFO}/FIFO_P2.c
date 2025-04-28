#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
    int fd1, fd2;
    char myfifo1[] = "file1";
    char myfifo2[] = "file2";
    char str1[100] , str2[100] ;
    int l = 0, w = 1, c = 0;
    int i=0;
    char ch;
    // Read from myfifo1
    fd1 = open(myfifo1, O_RDONLY);
    

    read(fd1, str1, sizeof(str1));
    printf("\n pipe1: %s", str1);
    close(fd1); // Close after reading

    while(str1[i]!='\0')
    {
        if(str1[i]=='.'|| str1[i]=='\n')
        {
            l++;
        }
        else if(str1[i]==' ')
        {
            w++;
        }
        else
        {
            c++;
        }
        i++;
    }


    printf("\nno of lines = %d", l);
    printf("\nno of words = %d", w);
    printf("\nno of characters = %d", c);

    FILE *fp = fopen("kp.txt", "w");
    
    fprintf(fp, "\nno of lines = %d", l);
    fprintf(fp, "\nno of words = %d", w);
    fprintf(fp, "\nno of characters = %d", c);
    fclose(fp);

    // Read from the file
    fp=fopen("kp.txt","r");
    ch=fgetc(fp);
    i=0;
    while(ch!=EOF)
    {
        str2[i]=ch;
        i++;
        ch=fgetc(fp);
    }
    str2[i]='\0';

    fclose(fp);

    // Write to second fifo pipe
    fd2 = open(myfifo2, O_WRONLY);
   
    write(fd2, str2, strlen(str2) + 1);
    close(fd2);
    
    return 0;
}
