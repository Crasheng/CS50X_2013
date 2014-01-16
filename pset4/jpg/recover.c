#include<cs50.h>
#include<stdio.h>
#include<stdint.h>

// Define BYTE
typedef uint8_t BYTE ;


int main(void)
{

    char card[10] = "card.raw"  ;
    FILE* raw = fopen(card, "r") ;
    if (raw == NULL)
    {
        printf("can't open file :(") ;
        return -1 ;
    }
    FILE* jpgs ;
    //declarecalre buffer and intialize
    // declare tittle
    BYTE buffer[512] ;
    char title[8] ;

    //indicate the beginning of catching
    int var = 0 ;

    while (! feof(raw))
    {
        //start reading the file
        fread(buffer, 512, 1, raw);

        //check beginning of jpg files ..
        if (buffer[0] == 0xff && buffer[1] == 0xd8\
            && buffer[2] == 0xff && (buffer[3] == 0xe1 || buffer[3] == 0xe0))
        {
            if (var > 0)
            {
                fclose(jpgs);
            }
            var++ ;
	    sprintf(title,"%.3d.jpg",var);
	    jpgs = fopen(title, "w") ;
	    if(jpgs == NULL)
	    {
	      printf("can't open") ;
	      return 1 ;
	    }
            
        }
        //start writing file :)
        if (var > 0)
        {
            fwrite(buffer, 512 , 1 , jpgs) ;
        }
    }
    fclose(raw) ;
    fclose(jpgs);
    return 0 ;
}
