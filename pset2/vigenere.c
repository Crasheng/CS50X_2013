/***********************************************************************
* this is a programming method to describe how implement code          * 
* which work as ciphering and this technique called (vigenere caesar)  * 
*                      Eng : Ahmed Adel                                *
************************************************************************/


#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //Check about user key
    if (argc != 2 )
    {
        printf("usage : ./vigenere <keyword>\n") ;
        return 1 ;
    }
    
    //Assign the key & its length.
    string k= argv[1] ;
    int klen= strlen(k) ;
    for(int i=klen ; i >0 ; i--)
    if (isdigit(k[i]))
    {
        printf("rejected\n");    
        return 1 ;
    }
    for(int i=0 ; i<klen ; i++)
    {
        if(isupper(k[i]))
        k[i] = k[i] + 32 ;
    }
    
    //Get User I/p .
    printf("Enter Your plain text : ");
    string u= GetString() ;
    
    //Start ciphering .
    for (int i=0, j=0, l=strlen(u) ; i<l ; i++)    
    {
        if (isupper(u[i]))
        {
            k[j] = k[j % klen] ;
            int indk = k[j] % 97 ;
            int indu = u[i] + indk ;
            u[i] += indk ;
            if(indu > 90 )
            {
                indu = indu % 90 ;
                u[i] = '@' ;
                u[i] += indu ;
            } 
            j++ ;     
        }
        else if (islower(u[i]))
        {
            k[j] = k[j % klen] ;  
            int indk = k[j] % 97 ;
            int indu = u[i] + indk ;
            u[i] += indk ;
            if(indu > 122 )
            {
                indu = indu % 122 ;
                u[i] = 96 ;
                u[i] += indu ;
            }
            j++ ;
        }
    }
    printf("The Cryptic text is : ");
    printf("%s\n",u) ;   
    return 0 ;
}
