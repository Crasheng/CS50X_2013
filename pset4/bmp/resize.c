/**************************************************************************
 * myself
 * 14/2/2013
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 ***************************************************************************/
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int count =0 ;

void fwrrite(FILE* optr, RGBTRIPLE pixel, int amount, int npadding, int Width)
{
  count++ ;
  for (int i=0 ; i<amount ; i++)
  fwrite(&pixel, sizeof(RGBTRIPLE), 1,optr) ;
  if (count == Width && npadding != 0)
    //asign to new padding
    while(npadding >0)
      {
	fputc(0x00 , optr) ;
	npadding--;
      }     
      
}

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize  infile outfile\n");
        return 1;
    }
    
    //take ratio
    int n = atoi(argv[1]) ;
    if(n < 1 )
      {
	printf("usage: ./resize n infile outfile   \n") ;
	return 4 ;
      }
    if(!((0 < n) && (n <= 100)))
      {
	printf("usage :   0 < n <=100 \n") ;
	return 4 ;
      }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
   
    //Take image before change it .. 
    int oldbiHeight = abs(bi.biHeight) ;
    int oldbiWidth = bi.biWidth  ;
    // int oldbiSizeImage = bi.biSizeImage ;
  
    //new Changes...
    bi.biWidth *= n ;
    bi.biHeight *= n ;
        
    //padding of inptr...
    int padding = (4- (oldbiWidth * sizeof(RGBTRIPLE)) %4 ) % 4 ;

    //neww padding of outptre..
    int npadding = (4- (bi.biWidth * sizeof(RGBTRIPLE)) %4) %4 ;

    //Bi.Image Size ...
    bi.biSizeImage = (bi.biWidth + npadding) * sizeof(RGBTRIPLE) * abs(bi.biHeight) ;
    
    //Size ..
    bf.bfSize = (bi.biSizeImage) + 54  ;
    
    //renew bi.biWidth with npadding...
    // bi.biWidth = bi.biWidth + npadding ;    
    
    //Bitmap file header writing..
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr) ;
    
    //bitmap info header writing..
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr) ;

    RGBTRIPLE triple;

    for (int i=0 ; i < oldbiHeight; i++)
    {
      int mew = n ;
      while(mew >0 )
      {
	  for(int j=0; j< oldbiWidth; j++)
	  {
	      //read pixel color.....
	      fread(&triple, sizeof(RGBTRIPLE), 1, inptr) ;
	      
	      //write...
	      fwrrite(outptr,triple, n, npadding,oldbiWidth) ;
	  }
	  
	  fseek(inptr, -(oldbiWidth * sizeof(RGBTRIPLE) ), SEEK_CUR) ;
	  
	  mew-- ;
	  count =0 ;
      } 
	 fseek(inptr, (sizeof(RGBTRIPLE) * oldbiWidth ), SEEK_CUR) ;
	 fseek(inptr,padding,SEEK_CUR) ;
    }
    // close infile
    fclose(inptr);
    
    // close outfile
    fclose(outptr);
    
    // that's all folks
    return 0;
}
