#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<cctype>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;
const char goal[5][5]={{'1','1','1','1','1'},
                     {'0','1','1','1','1'}, 
                     {'0','0','*','1','1'}, 
                     {'0','0','0','0','1'},
                     {'0','0','0','0','0'}};
int sx,sy,T,step;
char map[5][5];
struct node
{
  int gox;
  int goy;
}go[8];
inline void pre()
{
  go[0].gox=1,go[0].goy=2;
  go[1].gox=1,go[1].goy=-2;
  go[2].gox=2,go[2].goy=1;
  go[3].gox=2,go[3].goy=-1;
  go[4].gox=-1,go[4].goy=2;
  go[5].gox=-1,go[5].goy=-2;
  go[6].gox=-2,go[6].goy=1;
  go[7].gox=-2,go[7].goy=-1;
}
inline bool jud(int x,int y)
{
  return x>=0&&x<=4&&y>=0&&y<=4;
}
inline int check()
{
  int dif=0;
  for(int i=0;i<=4;i++)
    for(int j=0;j<=4;j++)
      if(map[i][j]!=goal[i][j])  dif++;
  return dif;
}
inline bool dfs(int x,int y,int now)
{
  if(now==step+1)
  {
	      if(check()==0)  return true;
    else 
	{return false;}
  }
  if(now+check()-3>step)  {return false;}
  for(int i=0;i<=7;i++)  
  {
    int tx=x+go[i].gox;
    int ty=y+go[i].goy;
    if(jud(tx,ty))
    {
      swap(map[x][y],map[tx][ty]);
      if(dfs(tx,ty,now+1))  return true;
      swap(map[x][y],map[tx][ty]);
    }
  }
  return false;
}
int main()
{
  //freopen("a.in","r",stdin);
	printf("输入将要进行的组数：");
  scanf("%d",&T);
  pre();
  while(T--)
  {
    sx=sy=0;
    for(int i=0;i<=4;i++)
      scanf("%s",map[i]);
    bool flag=false;
    for(i=0;i<=4;i++)
    {  
      if(flag==true)  break; 
      for(int j=0;j<=4;j++)
        if(map[i][j]=='*')
        {
          sx=i,sy=j;
          flag=true;
          break;
        }
    }
    step=1;
    for(i=1;i<=15;i++)
    {  
      if(dfs(sx,sy,1))  break;
      step++;
    }
    if(step==16)  cout<<"-1"<<endl;
    else  cout<<step<<endl;
  }
  return 0;
}