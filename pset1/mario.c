#include<cs50.h>
#include<stdio.h>

int main(void)
{   
    int h; 
   while (true)
      {
         printf("Enter your required hight : ") ;
         h=GetInt() ;
         if(h>=0&&h<=23)
         break ;
          
       }
              
    int y = h ;
    // Start Drawing :) .
    
    while( y>0 )
    {  
        for(int i=y-1 ; i>0 ; i--)
           printf(" ") ;
        
        for( int m = h-y+1 ; m>=0 ; m--)
           printf("#") ;
        printf("\n") ;
        y-- ;
        
    }
 return 0;
 
}    
