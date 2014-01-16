#include<stdio.h>
#include<cs50.h>

int main(void)
{
    printf("Entrer ur height plz..") ;
    int height= GetInt() ;
    if(height < 0 || height> 24)
    {    
        printf("rejects This") ;
        return 1 ;
    }   
    int iter= 1 ;
    int iter1= 1 ;
    int k= 1 ;
    for(int i= 0; i< height; i++, k++ )
    {   
        for(int j= height-k; j> 0;j--)
            printf(" ") ;
        for(int o= iter; o> 0; o--)
            printf("#") ;
        printf("  ") ;
        for(int o=iter1; o> 0; o--)
            printf("#") ;
        printf("\n") ;
        iter++ ;
        iter1++ ;                   
    }
}

