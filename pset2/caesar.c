/*************************************************************
* this is a programming method to describe how implement code * 
* which work as ciphering and this technique called (caesar)  * 
*                      Eng : Ahmed Adel                       *
***************************************************************/

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc , string argv[])
{
    //Check the kweyword 
    if (argc != 2) 
    {
        printf("usage : ./caesar <Number>\n") ;
        return 1 ;
    }
    
    //Convert from string to number 
    int key = atoi(argv[1]) ; 
    
    //Get the plaintext .
    printf("Enter Your plain text to cipher it!\n");
    string plain =  GetString() ;
    
    //Sart Ecryption for each letter
    for (int i =0 , n= strlen(plain); i < n ; i++ )
    {
        if (islower(plain[i]))
        {   
            
            //Assign to ciphertext letter (indp).     
            int indp = plain[i] + (key % 26)  ;     
            
            //Start Encryption .
            plain[i] = plain[i] + (key % 26) ;
            
            //Loop for wrapping up .
            if (  indp >=122 )
            {
                indp -= 123  ;
                plain[i] ='a' ;
                plain[i] += indp ;
            }                
        }
        else if (isupper(plain[i]))             // Encrypting uppercase cipherletter .
        {
            //Assign to ciphertext letter index (indp)
            int indp = plain[i] + (key % 26) ;
                
            //Start Encryption 
            plain[i] = plain[i] + (key % 26) ;
                
           //Loop fo wrappin up for uppercase cipherletter.
           if( indp >= 90)
           {
               indp -= 91 ;
               plain[i] ='A' ;
               plain[i] += indp ;
           }
       }  
    }  
    printf("Cipher Text is : ");
    printf("%s\n",plain) ;             
    return 0 ;
}
