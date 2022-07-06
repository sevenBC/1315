#include <iostream>
#include <math.h>
#include <string.h>
using namespace std;

typedef unsigned char(frame_mem)[8][64];
typedef int (frame_shd)[64][64];
typedef float (vertex_init_t) [10][3];
typedef float (vertex_t) [10][3];
typedef int (vertex_proj_t) [10][2];
typedef int (link_t) [100][2];

void shdtomem(frame_shd *input, frame_mem *output)
{
    static frame_mem frm;
   for (int i = 0; i < 8 ;i++)
   {
        for (int x=0;x<64;x++)
        {
            for (int j=0;j<8;j++)
                {
                    int y=i+j;
                    (*output)[i][x]+=(char)(*input)[y][x]<<j;
                }
        }
   } 
}

void linker(vertex_proj_t *vertex, link_t *link, frame_shd *output)
{   
    vertex_proj_t frm={0};
    int nums = sizeof (*link);
    for (int i = 0; i < nums; i++)
    { 
        int pa, qa;
        int yi,yt,xi,xt;
        int p[2],q[2];
        
        pa = (*link)[i][0];
        qa = (*link)[i][1];

        memcpy(p,(*vertex)[pa],sizeof((*vertex)[0]));
        memcpy(q,(*vertex)[qa],sizeof((*vertex)[0]));
        
        line(p,q,&frm);
    }   

    memcpy(output,&frm,sizeof(frm)); 

}

void line(int p[2],int q[2], vertex_proj_t * frame)
    {   
        int yi = p[1];
        int yt = q[1];
        int xi = p[0];
        int xt = q[0];

        
        if(abs(yi-yt) >= abs(xi-xt))
        {
            if (yi>=yt)
            {
                for (int m = yi; m >= yt; m--)
                {
                    int n = round((m-yi)*(xi-xt)/(yi-yt)+xi);
                    (*frame)[m][n]=1;
                }
            }
            else if (yt<yi)
            {
                for (int m = yi; m <= yt; m++)
                {
                    int n = round((m-yi)*(xi-xt)/(yi-yt)+xi);
                    (*frame)[m][n]=1;
                }
            }
        }

        else
        {
           if (xi>=xt)
            {
                for (int m = xi; m >= xt; m--)
                {
                    int n = round((m-xi)*(yi-yt)/(xi-xt)+yi);
                    (*frame)[n][m]=1;
                }
            }
            else if (xt<xi)
            {
                 for (int m = xi; m <= xt; m++)
                {
                    int n = round((m-xi)*(yi-yt)/(xi-xt)+yi);
                    (*frame)[n][m]=1;
                }
            } 
        }
        
    }



void projecter()
{

}
