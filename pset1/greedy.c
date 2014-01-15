#include<math.h>
#include<cs50.h>
#include<stdio.h>

int main(void)
{

    // Get User I/P .   
    float cash ;
    do 
    {
        printf("O hai!  How much change is owed?\n") ;
        cash=GetFloat() ;
    }
    while(cash < 0) ;
    
    // decleare cents
    int d =round ((float) (cash * 100)) ; 
       
    
    // start pay with different coins.
    int y=0; 
    
    // start iterationes
    while (d > 0) 
    {
        if (d >= 25)
        {
            d = d - 25 ;
            y++ ;
        }
        else if (d >= 10)
             {
                 d = d - 10 ;
                 y++ ;
             }
        else if (d >= 5)
             {
                 d = d - 5 ;
                 y++ ; 
             }
        else if (d >= 1)
             {
                 d = d - 1 ;
                 y++ ;
             }
    }
    
    // print the final result.
    printf("%i\n" , y ) ;
     
    return 0 ;     
}
