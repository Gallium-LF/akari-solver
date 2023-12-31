#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define maxn 10
using namespace std;
 
int n,m,b,ans;
int mp[maxn][maxn];
int vis[maxn][maxn];
int jmp[maxn][maxn];
int light[maxn][maxn];
int dx[]= {-1,1,0,0};
int dy[]= {0,0,-1,1};
bool getanswer = false;
 
void showvis()             // 中间输出  方便debug
{
    int i,j;
    printf("\n");
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=m; j++)
        {
            printf("%d",vis[i][j]);
        }
        printf("\n");
    }
}
bool isok(int tx,int ty)  // 判断能否放灯
{
    int i,j;
    for(i=tx-1; i>=1; i--)
    {
        if(vis[i][ty]) return false;
        else if(mp[i][ty]) break ;
    }
    for(i=tx+1; i<=n; i++)
    {
        if(vis[i][ty]) return false;
        else if(mp[i][ty]) break ;
    }
    for(j=ty-1; j>=1; j--)
    {
        if(vis[tx][j]) return false;
        else if(mp[tx][j]) break ;
    }
    for(j=ty+1; j<=m; j++)
    {
        if(vis[tx][j]) return false;
        else if(mp[tx][j]) break ;
    }
    return true ;
}
void expand(int tx,int ty)     // 扩展  将灯能照亮的地方都点亮
{
    int i,j;
    for(i=tx; i>=1; i--)
    {
        if(mp[i][ty]) break ;
        else jmp[i][ty]=1;
    }
    for(i=tx; i<=n; i++)
    {
        if(mp[i][ty]) break ;
        else jmp[i][ty]=1;
    }
    for(j=ty-1; j>=1; j--)
    {
        if(mp[tx][j]) break ;
        else jmp[tx][j]=1;
    }
    for(j=ty+1; j<=m; j++)
    {
        if(mp[tx][j]) break ;
        else jmp[tx][j]=1;
    }
}
bool judge()                 // 判断搜出来的情况是否合理
{
    int i,j,k,cnt;
    memset(jmp,0,sizeof(jmp));
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=m; j++)
        {
            if(vis[i][j]) expand(i,j);        // 将标记了的都扩展
        }
    }
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=m; j++)
        {
            if(!mp[i][j]&&!jmp[i][j]) return false ;      // 如果还有一个位置没亮的话就不行
        }
    }
//    showvis();
    for(i=1; i<=n; i++)              // 检测墙的周围灯的个数是否满足条件
    {
        for(j=1; j<=m; j++)
        {
            if(light[i][j]==-1) continue ;
            cnt=0;
            for(k=0; k<4; k++)
            {
                if(vis[i+dx[k]][j+dy[k]]) cnt++;
            }
            if(cnt!=light[i][j]) return false ;
        }
    }
    return true ;
}
bool midcut(int tx,int ty)        // 中间剪枝  如果有墙的周围不满足条件了 就 return false
{
    int i,j,k,cnt;
    for(i=1; i<=tx-2; i++)
    {
        for(j=1; j<=m; j++)
        {
            if(light[i][j]==-1) continue ;
            cnt=0;
            for(k=0; k<4; k++)
            {
                if(vis[i+dx[k]][j+dy[k]]) cnt++;
            }
            if(cnt!=light[i][j]) return false ;
        }
    }
    i=tx-1;
    for(j=1; j<=ty-1; j++)
    {
        if(light[i][j]==-1) continue ;
        cnt=0;
        for(k=0; k<4; k++)
        {
            if(vis[i+dx[k]][j+dy[k]]) cnt++;
        }
        if(cnt!=light[i][j]) return false ;
    }
    return true ;
}
bool goodcut(int tx,int ty)     // 强剪枝   如果所搜点为墙 且其上方为黑暗的，则剪枝！
{
    int i,j,k,cnt;
    memset(jmp,0,sizeof(jmp));
    for(i=1; i<=tx-1; i++)
    {
        for(j=1; j<=m; j++)
        {
            if(vis[i][j]) expand(i,j);
        }
    }
    if(!jmp[tx-1][ty]) return false;
    return true ;
}
void dfs(int nx,int ny,int cxx)
{
    if(getanswer) return ;
    if(!midcut(nx,ny)) return ;  
    if(nx>=n&&ny>m||nx>n)
    {
        if(judge())               // 全部搜完后判断情况是否合理
        {
           getanswer=true;
        }
        return ;
    }
    if(ny>m) dfs(nx+1,1,cxx);
    else if(mp[nx][ny])
    {
        if(nx>=2&&!mp[nx-1][ny]&&!goodcut(nx,ny)) return ;   // 注意前面的条件
        dfs(nx,ny+1,cxx);
    }
    else
    {
        dfs(nx,ny+1,cxx);
        if(!vis[nx][ny]&&isok(nx,ny))
        {
            vis[nx][ny]=1;
            dfs(nx,ny+1,cxx+1);
            vis[nx][ny]=0;
        }
    }
}
int main()
{
    int i,j,r,c,k;
    while(scanf("%d%d",&n,&m),n||m)
    {
        scanf("%d",&b);
        memset(mp,0,sizeof(mp));
        memset(light,-1,sizeof(light));
        for(i=1; i<=b; i++)
        {
            scanf("%d%d%d",&r,&c,&k);
            mp[r][c]=1;
            light[r][c]=k;
        }
        memset(vis,0,sizeof(vis));
        ans=1000000;
        dfs(1,1,0);
        if(ans<1000000) printf("%d\n",ans);
        else printf("No solution\n");
    }
    return 0;
}
