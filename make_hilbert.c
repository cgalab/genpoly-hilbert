/*****************************************************************************/
/*                                                                           */
/*                       2015-2020      Martin Held                          */
/*                                                                           */
/*                                                                           */
/* E-Mail:      held@cs.sbg.ac.at                                            */
/* Snail Mail:  Universitaet Salzburg, FB Computerwissenschaften,            */
/*              Jakob-Haringer Str. 2, A-5020 Salzburg, Austria (Europe).    */
/*                                                                           */
/*****************************************************************************/

/* get standard i/o library */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


#ifdef BOOL_DEFINED
typedef bool boolean;
#else
#define false 0
#define true  (!false)
typedef unsigned char  boolean;
#endif

void Hilbert(FILE *output, int x0, int y0, int xis, int xjs, int yis, int yjs,
             int n)
/* x0 and y0 are the coordinates of the bottom left corner */
/* xis & xjs are the i and j components of the unit x vector for this frame */
/* similarly yis and yjs */
{
   if (n<= 0) {
      fprintf (output, "%d %d\n", x0+(xis+yis)/2, y0+(xjs+yjs)/2);
   }
   else {
      Hilbert(output, x0, y0, yis/2, yjs/2, xis/2, xjs/2, n-1);
      Hilbert(output, x0+xis/2, y0+xjs/2 ,xis/2, xjs/2, yis/2, yjs/2, n-1);
      Hilbert(output, x0+xis/2+yis/2, y0+xjs/2+yjs/2, xis/2, xjs/2, 
              yis/2, yjs/2, n-1);
      Hilbert(output, x0+xis/2+yis, y0+xjs/2+yjs, -yis/2,-yjs/2, 
              -xis/2, -xjs/2, n-1);
   }

   return;
}

void PrintHeader(void)
{
   printf("\n");
   printf("***********************************************************\n");
   printf("*                                                         *\n");
   printf("*                      make_hilbert                       *\n");
   printf("*                                                         *\n");
   printf("* Generation of a (closed) Hilbert curve.                 *\n");
   printf("*                                                         *\n");
   printf("*      Martin Held 2015-2020        held@cs.sbg.ac.at     *\n");
   printf("*                                                         *\n");
   printf("***********************************************************\n");

   return;
}


void OpenFile(FILE  **output, const char *file_name)
{
   /* open file */
   if((*output = fopen(file_name, "w")) == NULL) {
      fprintf(stderr,"*** Output file not created! ***\n");
      exit(1);
   }
   
   return;
}   


int main(int argc, char **argv)
{
   int count = 1;
   boolean name_read = false, success = true;
   int     Depth = -1, i, j, x_start, y_start, k, m;
   FILE    *output;
   char    *file_name = "hilbert.line";

   PrintHeader();

   /*                                                                        */
   /* parse command-line arguments                                           */
   /*                                                                        */
   while ((count < argc)  &&  success)    {

      if (strcmp(argv[count],"--number") == 0) {
         ++count;
         if ((success = (count < argc)))  Depth = atoi(argv[count]);
      }
      else if (strcmp(argv[count],"--output") == 0) {
         ++count;
         if ((success = (count < argc))) {
            file_name = argv[count];
            name_read = true;
         }
      }
      else {
         success = false;
      }
      ++count;
   }

   if (!success  ||  !name_read  ||  (Depth <= 0)) {
      if (!success) 
         printf("\nUnrecognized command-line option: %s\n", argv[count-1]); 
      printf("\nUsage: make_hilbert --number N --output XYZ\n       where N is a positive integer.\n"); 
      exit(2);
   }

   /*                                                                        */
   /* initialization                                                         */
   /*                                                                        */
   OpenFile(&output, file_name);
   
   i = 1;
   for (j = 0; j < Depth;  ++j)  i *= 4;
   k = 1;
   for (j = Depth; j >= 2; --j)  k *= 2;

   fprintf(output,"%d\n", i + k * 2 + 1);

   /* write point to the left of start point */
   x_start = 0;
   y_start = 0;

   fprintf(output,"%d %d\n", x_start, y_start + k);
   
   /* recursive generation of the Hilbert curve: */
   Hilbert(output, x_start + k, y_start, i, 0, 0, i, Depth);

   /* write point to the left of end point */ 
   fprintf(output,"%d %d\n", x_start, y_start + i - k);

   /* close polygon */ 
   m = k * 2;
   for (j = y_start + i - k - m; j >= y_start + k; j -= m) {
      fprintf(output,"%d %d\n", x_start, j);
   }

   fclose(output);

   exit(0);
}
