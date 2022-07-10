#include <iostream>
#include <math.h>
#include <string.h>
using namespace std;

typedef unsigned char(frame_mem)[8][128];
typedef uint8_t (frame_shd)[64][128];
typedef float (vertex_init_t) [10][3];
typedef float (vertex_t) [10][3];
typedef int (vertex_proj_t) [10][2];
typedef int (link_t) [100][2];
typedef float (motion_t)[3];



void divider(frame_shd *input, frame_mem *output)
{
    static frame_mem frm;
   for (int i = 0; i < 8 ;i++)
   {
        for (int x=0;x<128;x++)
        {
            for (int j=0;j<8;j++)
                {
                    int y=i+j;
                    (*output)[i][x]+=(char)(*input)[y][x]<<j;
                }
        }
   } 
}


void line(int p[2],int q[2], frame_shd * frame)
    {   
        int yi = p[1];
        int yt = q[1];
        int xi = p[0];
        int xt = q[0];

        
        if(abs(yi-yt) >= abs(xi-xt))
        {
            if (yi>yt)
            {
                for (int m = yi; m >= yt; m--)
                {
                    int n = round((m-yi)*(xi-xt)/(yi-yt)+xi);
                    (*frame)[m][n] = 1;
                }
            }
            else if (yi<yt)
            {
                for (int m = yi; m <= yt; m++)
                {
                    int n = round((m-yi)*(xi-xt)/(yi-yt)+xi);
                    (*frame)[m][n]=1;
                }
            }
            else
            {
                (*frame)[yi][xi]=1;
            }
        }

        else
        {
           if (xi>xt)
            {
                for (int m = xi; m >= xt; m--)
                {
                    int n = round((m-xi)*(yi-yt)/(xi-xt)+yi);
                    (*frame)[n][m]=1;
                }
            }
            else if (xi<xt)
            {
                 for (int m = xi; m <= xt; m++)
                {
                    int n = round((m-xi)*(yi-yt)/(xi-xt)+yi);
                    (*frame)[n][m]=1;
                }
            }
            else
            {
                (*frame)[yi][xi]=1;
            } 
        }
        
    }

void linker(vertex_proj_t *vertex, link_t *link,int num_line, frame_shd *output)
{   
    frame_shd frm={0};
    int pa, qa;
    int yi,yt,xi,xt;
    int p[2],q[2];
        
    for (int i = 0; i < num_line; i++)
    { 
        
        pa = (*link)[i][0];
        qa = (*link)[i][1];

        memcpy(p,(*vertex)[pa],sizeof((*vertex)[0]));
        memcpy(q,(*vertex)[qa],sizeof((*vertex)[0]));
        
        line(p,q,&frm);
    }   

    memcpy(output,&frm,sizeof(frm)); 

}



void projecter(vertex_t * input, int num_ver, int cam_pos,float view, vertex_proj_t * output)
{
    static float x,y,z;
    static int m,n;
    for (int i = 0; i < num_ver; i++)
    {
        x = (*input)[i][0];
        y = (*input)[i][1];
        z = (*input)[i][2];
        m = round((x*cam_pos/(cam_pos-z+127))*view/4)+63;
        n = -round((y*cam_pos/(cam_pos-z+127)*view)/4)+31;
        if (m>127 or m<0) continue;
        if (n>63 or n<0) continue;
        
        (*output)[i][0] = n;
        (*output)[i][1] = m;
    }
}


void transleter(vertex_t * input, int num_ver, motion_t * tra_par, vertex_t * output)
{
    for(int i = 0; i < num_ver; i++ )
    {
        for(int j = 0; j < 3; j++)
        {
            (* output)[i][j] = (* input)[i][j] + (* tra_par)[j];
        }
    } 
}

void rotater(vertex_t * input, int num_ver, motion_t * rot_par, vertex_t * output)
{
    static float yaw, pitch, roll;
    yaw = (* rot_par)[0];
    pitch = (* rot_par)[1];
    roll = (* rot_par)[2];
    
    static float vertex0[3], vertex1[3];

    for(int i = 0; i < num_ver; i++ )
    {
    memcpy(vertex0,(*input)[i],sizeof(vertex0));
    
    vertex1[0] = vertex0[0] * cos(yaw) - vertex0[2] * sin(yaw);
    vertex1[2] = vertex0[2] * cos(yaw) + vertex0[0] * sin(yaw);
    vertex1[1] = vertex0[1];

    vertex0[1] = vertex1[1] * cos(pitch) + vertex1[2] * sin(pitch);
    vertex0[2] = vertex1[2] * cos(pitch) - vertex1[1] * sin(pitch);
    vertex0[0] = vertex1[0];

    vertex1[0] = vertex0[0] * cos(roll) + vertex0[1] * sin(roll);
    vertex1[1] = vertex0[1] * cos(roll) - vertex0[0] * sin(roll); 
    vertex1[2] = vertex0[2];
    
    memcpy ((*output)[i],vertex1,sizeof(vertex1));      
    }
    
}


void cube(frame_shd * op, motion_t *rot_para)
{

    static vertex_t vertex_init = {{64,64,64},{-64,64,64},{-64,-64,64},{64,-64,64},{64,64,-64},{-64,64,-64},{-64,-64,-64},{64,-64,-64}};
    static vertex_t vertex_0, vertex_1;
    static link_t link = {{0,1},{1,2},{2,3},{3,0},{4,5},{5,6},{6,7},{7,4},{0,4},{1,5},{2,6},{3,7}};
    static vertex_proj_t vertex_proj;
    static frame_shd frame;
    static frame_mem pack;
    
    rotater(&vertex_init,8,rot_para,&vertex_0);
    projecter(&vertex_0, 8, 80,1.5 ,&vertex_proj);
    linker(&vertex_proj, &link, 12,&frame);
    divider(&frame,&pack);
    
    memcpy(op,&frame,sizeof(frame));

}