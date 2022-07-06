#include <string.h>
#include <iostream>
#include <typeinfo>

using namespace std;
typedef int (es)[2][3];
typedef int (se)[3][2];
void tran(se * ip,se * op){
    cout<< ip<<endl;
  
    for (int i = 0; i<3; i++)
    {
       
        memcpy((*op)[i],(*ip)[2-i],sizeof((*ip)[0]));
    }
}

int main()
{
    static se b={{11,12},{21,22},{31,32}};
    static se c={};

    tran(&b,&c);

    for (int i = 0; i<3; i++)
    {
        for (int j = 0;j<2;j++){
            cout<<c[i][j]<<endl;
        }
    }
  
    return 0;
}