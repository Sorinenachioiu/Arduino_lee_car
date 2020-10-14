#include <fstream>

using namespace std;
ifstream in ("ard.in");
ofstream out ("ard.out");

//global variables

#define LUNGIME 30
#define LATIME 30

bool not_finish=1;
int room[30][30];
bool obs[LUNGIME][LATIME];
int dlin[4]={-1,0,1,0},
    dcol[4]={0,1,0,-1};

int current_direction=1;//directia de mers curenta

struct queue
{
    int row,col;
}q[10000],temp,current,s_point,f_point;

struct r
{
    int row,col;
}stiva[10000];


void citire()
{
    int i,j;
    in>>s_point.row>>s_point.col>>f_point.row>>f_point.col;
    for(i=0;i<LUNGIME;i++)
        for(j=0;j<LATIME;j++)
            in>>obs[i][j];
}

void afisare()
{
    int i,j;
    out<<"bool obs["<<LUNGIME<<"]["<<LATIME<<"]={";
    for(i=0;i<LUNGIME;i++)
    {
        out<<"{";
        for(j=0;j<LATIME-1;j++)
            out<<obs[i][j]<<" , ";
        out<<obs[i][j]<<" ";
        out<<"},"<<'\n';
    }
    out<<"};";
}

bool capat(int i,int j,int n,int m)
{
    return i>=0&&j>=0&&i<n&&j<m&&obs[i][j]==0&&room[i][j]==0;
}

bool capatnr(int i,int j,int n,int m,int z)
{
    return i>=0&&j>=0&&i<n&&j<m&&room[i][j]==z-1;
}

void obs_to_zero(int n,int m)
{
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            obs[i][j]=0;
}

void go_back(int n, int m)
{
    int j=1,i,z;
    stiva[0].row=f_point.row;
    stiva[0].col=f_point.col;
    obs[f_point.row][f_point.col]=1;
    while(stiva[j-1].row!=s_point.row||stiva[j-1].col!=s_point.col)
    {
        z=room[stiva[j-1].row][stiva[j-1].col];
        for(i=0;i<4;i++)
        {
            if(capatnr(stiva[j-1].row+dlin[i],stiva[j-1].col+dcol[i],n,m,z))
            {
                obs[stiva[j-1].row+dlin[i]][stiva[j-1].col+dcol[i]]=1;
                stiva[j].row=stiva[j-1].row+dlin[i];
                stiva[j].col=stiva[j-1].col+dcol[i];
                i=5;
            }
        }
        j++;
    }
    obs[s_point.row][s_point.col]=1;
}

void lee()
{

  int pr=0,ul=0;
  int k;
  bool found=0;



  room[s_point.row][s_point.col]=1;
  q[0].row=s_point.row;
  q[0].col=s_point.col;

  while(pr<=ul&&!found)
  {
      temp=q[pr++];
      for(k=0;k<4&&!found;k++)
      {
        current.row=temp.row+dlin[k];
        current.col=temp.col+dcol[k];

        if(capat(current.row,current.col,LUNGIME,LATIME))
        {
            obs[current.row][current.col]=1;
            room[current.row][current.col]=room[temp.row][temp.col]+1;
            if(current.row==f_point.row&&current.col==f_point.col)
                found=1;
            q[++ul]=current;
        }
      }
  }
/*
    for(int i=0;i<LUNGIME;i++)
    {
        for(k=0;k<LATIME;k++)
            out<<room[i][k]<<" ";
        out<<'\n';
    }
*/
    obs_to_zero(LUNGIME,LATIME);
    go_back(LUNGIME,LATIME);

}

int main()
{
    citire();
    lee();
    afisare();
    return 0;
}
