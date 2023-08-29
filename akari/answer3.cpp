//
// Created by cxy on 19-7-22.
//
# include <bits/stdc++.h>
using namespace std;
 
/**
???????????,????????Akari???????,?????????,
???????????????,??????,???????????????,
???????? n,m,???????????
??? n ???? m ???????????????,
??? -2,???????,
??? -1,????????????,
??? 0-4,?????? 0-4 ?????
??????????????,???? -2 ?? 5,?? 5 ?????????
???????????????????????,???????????light up??,
???????????????????????????light up,????????
?????,??????????????,?????,??The answer is right!,
???????
*/
 
namespace aka{
//???????????,??????
 
    //????????
    typedef struct{
        int x = 0;
        int y = 0;
        int val = -2;
    }POINT;
 
    //???????????????
    typedef struct{
        int value = 0;
        bool valid = true;
    }grid;
 
    //???????
    bool findRes = false;
 
    //????????
    int darkSum = 0;
 
    //???????
    vector<POINT> bs;
 
    //n?m?
    int n = 0, m = 0;
 
    //????: ???????????,????????????,??true,???false
    vector<vector<bool> >aroundBlack;
    //??: ????????????????;
    vector<vector<int> >aroundBlackValue;
    //??????????????????????????;
    bool cmp(POINT a, POINT b){
        return a.val > b.val;
    }
//    struct {
//        bool operator()(int a, int b) const
//        {
//            return a < b;
//        }
//    } customLess;
    //???????
    vector<vector<bool> >lightedUp;
 
    void display(vector<vector<grid> > & ans)
    {
        printf("your magic matrix--------------------------------> \n");
        int n = ans.size(), m = ans[0].size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                printf("%4d", ans[i][j].value);
            }
            printf("\n");
        }
        printf("your valid matrix \n");
 
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                printf("%4d", ans[i][j].valid);
            }
            printf("\n");
        }
 
//        printf("your aroundBlack \n");
//
//        for (int i = 0; i < n; ++i) {
//            for (int j = 0; j < m; ++j) {
//                printf("%4d", aroundBlack[i][j]?1:0);
//            }
//            printf("\n");
//        }
 
    }
 
    void pv(vector<POINT> a){
        printf("left is \n");
 
        for (int j = 0; j < a.size(); ++j) {
            printf("%4d", a[j].x);
        }printf("\n");
 
        for (int j = 0; j < a.size(); ++j) {
            printf("%4d", a[j].y);
        }printf("\n");
 
        for (int j = 0; j < a.size(); ++j) {
            printf("%4d", a[j].val);
        }printf("\n");
    }
 
    void pv1(vector<vector<int> > a){
        printf("around black 's value is \n");
 
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                printf("%4d", a[i][j]);
            }
            printf("\n");
        }
    }
 
    void pv2(vector<vector<bool> > a){
        printf("lightedUp is \n");
 
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                printf("%4d", a[i][j]?1:0);
            }
            printf("\n");
        }
    }
 
    // ??curm????????????????
    // arg1: ???????????
    // arg2: ????
    void getLeft(vector<POINT>& left, vector<vector<grid> > & curm){
        //????, ,????????????left???,
        // ????????????,?????????????????;
        left.clear();
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                POINT tmp;
                if(curm[i][j].valid){ //????????
                    tmp.x = i;
                    tmp.y = j;
                    //????????????????
                    if(aroundBlack[i][j]){ //????
                        //?????????????
                        tmp.val = aroundBlackValue[i][j];
                        left.emplace(left.begin(), tmp);
                    }else{ //?????
                        left.push_back(tmp);
                    }
                }
            }
        }
        sort(left.begin(), left.end(), cmp);
    }
 
    //??i,j???,???0,??i????false
    void setAround0(int i,  int j, vector<vector<grid> > & curm){
        if(curm[i][j].value == 0){
            if(i==0){
                if(j==0){
                    curm[i+1][j].valid = false;curm[i][j+1].valid = false;
                }else if(j==m-1){
                    curm[i][j-1].valid = false;curm[i+1][j].valid = false;
                }else{
                    curm[i][j+1].valid = false;
                    curm[i][j-1].valid = false;
                    curm[i+1][j].valid = false;
                }
            }else if(i==n-1){
                if(j==0){
                    curm[i-1][j].valid = false;curm[i][j+1].valid = false;
                }else if(j==m-1){
                    curm[i-1][j].valid = false;curm[i][j-1].valid = false;
                }else{
                    curm[i-1][j].valid = false;
                    curm[i][j+1].valid = false;
                    curm[i][j-1].valid = false;
                }
            }else{
                if(j==0){
                    curm[i][j+1].valid = false;
                    curm[i-1][j].valid = false;
                    curm[i+1][j].valid = false;
                }else if(j==m-1){
                    curm[i][j-1].valid = false;
                    curm[i-1][j].valid = false;
                    curm[i+1][j].valid = false;
                }else{
                    curm[i+1][j].valid = false;curm[i][j+1].valid = false;
                    curm[i-1][j].valid = false;curm[i][j-1].valid = false;
                }
            }
        }
    }
 
 
    // ???????????????,????????????
    // ???????????????,curm?????????,???false??????????
    bool updateCurmByLight(POINT light, vector<vector<grid> > & curm) {
        int x0 = light.x, y0= light.y;
        //?????????
        if(!curm[x0][y0].valid){
            return false;
        }
        //????,???????????,???darkSum-1:
        curm[x0][y0].value = 5;
        curm[x0][y0].valid = false;
        darkSum--;
 
        //?????,???????????????,????????????,?0?????????????
        vector<POINT> blacks;
        if(y0 >= 1 && (1<=curm[x0][y0-1].value && 4>=curm[x0][y0-1].value)){
            curm[x0][y0-1].value --;
 
            setAround0(x0, y0-1, curm);
        }
        if(x0 >= 1 && (1<=curm[x0-1][y0].value && 4>=curm[x0-1][y0].value)){
            curm[x0-1][y0].value --;
 
            setAround0(x0-1, y0, curm);
        }
        if(y0 <= n-2 && (1<=curm[x0][y0+1].value && 4>=curm[x0][y0+1].value)){
            curm[x0][y0+1].value --;
 
            setAround0(x0, y0+1, curm);
        }
        if(x0 <= m-2 && (1<=curm[x0+1][y0].value && 4>=curm[x0+1][y0].value)){
            curm[x0+1][y0].value --;
 
            setAround0(x0+1, y0, curm);
        }
 
 
        //??????+x,-x,+y,-y??????????,???????fasle
        int xp=light.x, xn=xp;
        int yp=light.y, yn=yp;
        //curm ?????????-1?4,5??,???????????-2,?????
        //????5???????false,???[-1, 4]??????????;
        //x???
        for(int i=xp+1; i<m ;i++){
            if(-1<=curm[i][y0].value && 4>=curm[i][y0].value){
                break;
            }else if(curm[i][y0].value == 5){
                return false;
            }else{
                //??? ??i?????,????darkSum?1
                if(!lightedUp[i][y0]){
                    curm[i][y0].valid = false;
                    darkSum--;
                    lightedUp[i][y0] = true;
                }
            }
        }
        //x???
        for(int i=xp-1; i>=0 ;i--){
            if(-1<=curm[i][y0].value && 4>=curm[i][y0].value){
                break;
            }else if(curm[i][y0].value == 5){
                return false;
            }else{
                //??? ??i?????,????darkSum?1
                if(!lightedUp[i][y0]){
                    curm[i][y0].valid = false;
                    darkSum--;
                    lightedUp[i][y0] = true;
                }
            }
        }
        //y???
        for(int i=yp+1; i<n ;i++){
            if(-1<=curm[x0][i].value && 4>=curm[x0][i].value){
                break;
            }else if(curm[x0][i].value == 5){
                return false;
            }else{
                //??i?????,????darkSum?1, ???valid?????
                if(!lightedUp[x0][i]){
                    curm[x0][i].valid = false;
                    darkSum--;
                    lightedUp[x0][i] = true;
                }
            }
        }
        //y???
        for(int i=yn-1; i>=0 ;i--){
            if(-1<=curm[x0][i].value && 4>=curm[x0][i].value){
                break;
            }else if(curm[x0][i].value == 5){
                return false;
            }else{
                //??i?????,????darkSum?1, ???valid?????
                if(!lightedUp[x0][i]){
                    curm[x0][i].valid = false;
                    darkSum--;
                    lightedUp[x0][i] = true;
                }
            }
        }
        return true;
    }
 
 
    //????
    void backT(vector<POINT>& left, vector<vector<grid> > & curm,\
                                                          vector<vector<int> > & res){
        //??????:
        //1,????,?update???????
        // ????,update???,??????????????,??????
        //2,?????
        //????????????(???????????)????,?????
 
        //???cover??????,??res??,????findRes
        if(darkSum == 0){
            bool satisfy = true;
            //???????????????????0
            for(int i=0; i<bs.size(); i++){
                satisfy = satisfy && (curm[bs[i].x][bs[i].y].value == 0);
            }
            //????
            if(!satisfy){
                return ;
            }
            for(int i=0; i<n; i++){
                for(int j=0; j<m; j++){
                    res[i][j] = curm[i][j].value;
                }
            }
            findRes = true;
            exit(0);
            return ;
        }
 
        //?????????,???????,????
        if(left.empty()){
//            cout <<endl<<endl<< "backTrack to last backT's next loop"<<endl<<endl;
            return ;
        }
        //???backT?,???left,lights?curm??????????
        //??left???????????????,????????left????,
        // ??????for???????l?????????????,?????????
        // ?????left???,?????????????left???,????????????,??????????????;
#pragma omp parallel for
        for(int i=0; i<left.size() &&(!findRes); i++){
            auto tmpCurm= curm;
            auto tmpLightedUp = lightedUp;
            int tmpDarkSum=darkSum;
            auto tmpleft = left;
            //>>>>>>>>>>>>>??????>>>>>>>>>>>>>>>>
//            display(curm);
//            pv(left);
//            pv2(lightedUp);
//            cout<<"--------dark: "<<darkSum<<" | ready to using x:"<<left[i].x<<", y: "<<left[i].y<<"  left len: "<<left.size()<<endl;
            if(left.size() >= 15){
                cout<<"  left len: "<<left.size()<<endl;
            }
 
            if(updateCurmByLight(left[i], curm)){ //??????,?????????
                //????,????,????
                getLeft(left, curm);
                backT(left, curm, res);
            }
 
            //??????????,???????????,??????????;
            curm = tmpCurm;
            darkSum = tmpDarkSum;
            lightedUp = tmpLightedUp;
            left = tmpleft;
        }
    }
 
    vector<vector<int> > solveAkari(vector<vector<int> > & g){
        // ???????????????
 
        //??n?m?
        n = g.size();
        m = g[0].size();
 
 
        //?????????????????
        vector<POINT> left(0);
 
        //???????????????
        vector<vector<grid> > curm(0);
 
        //???,?????ABlack,???????aroundBlack??
        //????: ???????????,????????????,??true,???false
        //????: lightUp??????????
        vector<vector<bool> > ABlack(n, vector<bool>(m, false));
        vector<vector<int> > ABlackValue(n, vector<int>(m, false));
        vector<vector<bool> > LUp(n, vector<bool>(m, false));
 
        //???????????????????,?????darkSum,????aroundBlack??
        for(int i=0; i<n; i++) {
            curm.emplace_back(vector<grid>(m));
        }
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                curm[i][j].value = g[i][j];
                if(g[i][j] != -2){  //???????,????????,????????,?????0?????????
                    //?????fasle
                    curm[i][j].valid = false;
                    //??????0??????????false
                    setAround0(i, j, curm);
                    //??????????aroundBlack
                    if(i==0){
                        if(j==0){
                            ABlack[i+1][j] = true;ABlack[i][j+1] = true;
                            ABlackValue[i+1][j] = curm[i][j].value;
                            ABlackValue[i][j+1] = curm[i][j].value;
                        }else if(j==m-1){
                            ABlack[i][j-1] = true;ABlack[i+1][j] = true;
                            ABlackValue[i][j-1] = curm[i][j].value;
                            ABlackValue[i+1][j] = curm[i][j].value;
                        }else{
                            ABlack[i][j+1] = true;
                            ABlack[i][j-1] = true;
                            ABlack[i+1][j] = true;
                            ABlackValue[i][j+1] = curm[i][j].value;
                            ABlackValue[i][j-1] = curm[i][j].value;
                            ABlackValue[i+1][j] = curm[i][j].value;
                        }
                    }else if(i==n-1){
                        if(j==0){
                            ABlack[i-1][j] = true;ABlack[i][j+1] = true;
                            ABlackValue[i][j+1] = curm[i][j].value;
                            ABlackValue[i-1][j] = curm[i][j].value;
                        }else if(j==m-1){
                            ABlack[i-1][j] = true;ABlack[i][j-1] = true;
                            ABlackValue[i-1][j] = curm[i][j].value;
                            ABlackValue[i][j-1] = curm[i][j].value;
                        }else{
                            ABlack[i-1][j] = true;
                            ABlack[i][j+1] = true;
                            ABlack[i][j-1] = true;
                            ABlackValue[i-1][j] = curm[i][j].value;
                            ABlackValue[i][j+1] = curm[i][j].value;
                            ABlackValue[i][j-1] = curm[i][j].value;
                        }
                    }else{
                        if(j==0){
                            ABlack[i][j+1] = true;
                            ABlack[i-1][j] = true;
                            ABlack[i+1][j] = true;
                            ABlackValue[i][j+1] = curm[i][j].value;
                            ABlackValue[i-1][j] = curm[i][j].value;
                            ABlackValue[i+1][j] = curm[i][j].value;
                        }else if(j==m-1){
                            ABlack[i][j-1] = true;
                            ABlack[i-1][j] = true;
                            ABlack[i+1][j] = true;
                            ABlackValue[i][j-1] = curm[i][j].value;
                            ABlackValue[i-1][j] = curm[i][j].value;
                            ABlackValue[i+1][j] = curm[i][j].value;
                        }else{
                            ABlack[i+1][j] = true;ABlack[i][j+1] = true;
                            ABlack[i-1][j] = true;ABlack[i][j-1] = true;
                            ABlackValue[i][j-1] = curm[i][j].value;
                            ABlackValue[i][j+1] = curm[i][j].value;
                            ABlackValue[i+1][j] = curm[i][j].value;
                            ABlackValue[i-1][j] = curm[i][j].value;
                        }
                    }
                }else{ //??????,??????????
                    darkSum ++;
                    LUp[i][j] = false;
                }
            }
        }
        aroundBlack = ABlack;
        aroundBlackValue = ABlackValue;
        lightedUp = LUp;
 
        //?????bs
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(1<=curm[i][j].value && 4>=curm[i][j].value){
                    POINT tmp;
                    tmp.x = i; tmp.y = j;
                    bs.emplace_back(tmp);
                }
            }
        }
 
        //>>>>>>>>>>>>>??????>>>>>>>>>>>>>>>>
//            display(curm);
//            pv(left);
            pv2(aroundBlack);
        pv1(aroundBlackValue);
        cout<<"-----------------------------";
 
        //???????????? ????: getLeft
 
        //????
        vector<vector<int> > res(n, vector<int>(m, 0));
 
        //??backT??????
        getLeft(left, curm);
 
        //???????,?????,?????????????????????,???????????;
        backT(left, curm, res);
 
        //???res??????1,?4???????????????,?????????:
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(1<=g[i][j] && 4>=g[i][j]){
                    res[i][j] = g[i][j];
                }
            }
        }
        return res;
    }
}
