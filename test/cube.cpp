#include "render.h"
#include <iostream>

using namespace std;

int main()
{   
    static frame_shd printed;
   
    motion_t rotation={0};

    for (int s = 0; s <180 ;s+=10)
    {
        rotation[2]= s*3.14/180;
        cube(& printed,&rotation);
        for (int i = 0; i < 64; i++)
        {
            for (int j = 0; j < 64; j++)
            {   
                if(printed[i][j]==0)cout<<".";
                else cout<<"X";
            }
            cout<<endl;
        }
    }

    
    return 0;
    
}