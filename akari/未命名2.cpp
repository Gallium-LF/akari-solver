#include<iostream>
using namespace std;
/*******************************/
template <class T>
class VecList{
    private:
        int capacity;
        int length;
        T* arr;
        void doubleListSize(){
            T * oldArr = arr;
            arr = new T[2*capacity];
            capacity = 2 * capacity;
            for(int i=0;i<length;i++){
                arr[i] = oldArr[i];
            }
            delete [] oldArr;
        }
    public:
        VecList(){
            length = 0;
            capacity = 100;
            arr = new T[capacity];
        }
        VecList(T* a, int n){
            length = n;
            capacity = 100 + 2*n;
            arr = new T[capacity];
            for(int i=0;i<n;i++){
                arr[i] = a[i];
            }
        }
        ~VecList(){
            delete [] arr;
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0;
        }
        void insertEleAtPos(int i, T x){
            if(length==capacity)
                doubleListSize();
            if(i > length || i < 0)
                throw "Illegal position";
            for(int j=length;j>i;j--)
                arr[j] = arr[j-1];
            arr[i] = x;
            length++;
        }
        T deleteEleAtPos(int i){
            if(i >= length || i < 0)
                throw "Illegal position";
            T tmp = arr[i];
            for(int j=i;j<length-1;j++)
                arr[j] = arr[j+1];
            length--;
            return tmp;
        }
        void setEleAtPos(int i, T x){
            if(i >= length || i < 0)
                throw "Illegal position";
            arr[i] = x;
        }
        T getEleAtPos(int i){
            if(i >= length || i < 0)
                throw "Illegal position";
            return arr[i];
        }
        int locateEle(T x){
            for(int i=0;i<length;i++){
                if(arr[i]==x)
                    return i;
            }
            return -1;
        }
        void insertLast(T x){
            insertEleAtPos(length,x);
        }
        void printList(){
            for(int i=0;i<length;i++)
                cout << arr[i] << " ";
        }
};

/************************************/
struct nodes{
	int type;
	bool light;
	bool canput;
	void operator=(const nodes &D){ 
		type=D.type;light=D.light;
    }
};
/*******************************/
struct stack{
	int x,y;
};
/*******************************/
nodes **result;
int m,n;
bool finish;
int a[4] = {-1, 1, 0, 1};
int b[4] = {0, 0, -1, 0};
/*******************************/
void buildR(char *t,nodes **r){
	int i,j;
	int blacktimes=0;
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			switch(t[i*n+j]){
				case '.':{
					r[i][j].type=-2;//white
					r[i][j].light=false;
					break;
				}
				case 'X':{
					r[i][j].type=-1;//black
					r[i][j].light=false;
					break;
				}
				case '0':{
					r[i][j].type=0;//0 black
					r[i][j].light=false;
					break;
				}
				case '1':{
					r[i][j].type=1;//1 black
					r[i][j].light=false;
					break;
				}
				case '2':{
					r[i][j].type=2;//2 black
					r[i][j].light=false;
					break;
				}
				case '3':{
					r[i][j].type=3;//3 black
					r[i][j].light=false;
					break;
				}
				case '4':{
					r[i][j].type=4;//4 black
					r[i][j].light=false;
					break;
				}
			}
		}
	}
}
/*******************************/
void printR(nodes **a){
	int i,j;
	for(int i=0;i<n+1;i++)
		cout<<"__";
	cout<<endl;
	for(i=0;i<m;i++){
		cout<<"|";
		for(j=0;j<n;j++){
			switch(a[i][j].type){
				case -3:{
					cout<<"  ";
					break;
				}
				case -2:{
					cout<<"  ";
					break;
				}
				case -1:{
					cout<<"X ";
					break;
				}
				case 0:{
					cout<<"0 ";
					break;
				}
				case 1:{
					cout<<"1 ";
					break;
				}
				case 2:{
					cout<<"2 ";
					break;
				}
				case 3:{
					cout<<"3 ";
					break;
				}
				case 4:{
					cout<<"4 ";
					break;
				}
				case 5:{
					cout<<"+ ";
					break;
				}
				case 6:{
					cout<<"  ";
					break;
				}
			}
		}
		cout<<"|"<<endl;
	}
	for(int i=0;i<n+1;i++)
		cout<<"__";
	cout<<endl;
}
/*******************************/
void findway(nodes **g,int row,int col,nodes **islight);

bool  issame(nodes** s1,nodes** s2){
    for (int i = 0; i < m;i++){
        for (int j = 0; j < n;j++){
            if(s1[i][j].type!=s2[i][j].type)
                return false;
        }
    }
    return true;
}
/*******************************/
void copy(nodes **a,nodes **b){
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++)
			b[i][j]=a[i][j];
	}	
}
/*******************************/
void putlight(nodes **g,nodes **islight,VecList<stack> &save,int x,int y){cout<<"!";
    for (int i = x; i >= 0;i--){ //?
        if(g[i][y].type>=-1 && g[i][y].type<=4)
            break;
        else if(g[i][y].type==-2){
            g[i][y].type = -3;//??????
            islight[i][y].type = 6;
            stack aa;aa.x=i;aa.y=y;
            save.insertLast(aa); 
        }
    }

    for (int i = x;i<m;i++){ //?
        if(g[i][y].type>=-1 && g[i][y].type<=4)
            break;
        else if(g[i][y].type==-2){
            g[i][y].type = -3;//??????
            islight[i][y].type = 6;//????
            stack aa;aa.x=i;aa.y=y;
            save.insertLast(aa); 
        }
    }
    for (int j = y; j >= 0;j--){//?
        if(g[x][j].type>=-1 && g[x][j].type<=4)
            break;
        else if(g[x][j].type==-2){
            g[x][j].type=-3;
            islight[x][j].type = 6;
            stack aa;aa.x=x;aa.y=j;
            save.insertLast(aa); 
        }
    }
    for (int j = y; j <n ;j++){//?
        if(g[x][j].type>=-1 && g[x][j].type<=4)
            break;
        else if(g[x][j].type==-2){
            g[x][j].type=-3;
            islight[x][j].type = 6;
            stack aa;aa.x=x;aa.y=j;
            save.insertLast(aa); 
        }
    }
    return;
}
/*******************************/
void DFS1(int x,int y,nodes **g,nodes **islight){
    for (int k = 0; k < 4;k++){
        if(g[x+a[k]][y+b[k]].type==-2){
        	VecList<stack> save;
            g[x + a[k]][y + b[k]].type = 5;
            islight[x + a[k]][y + b[k]].type=5;
            putlight(g, islight, save, x + a[k], y + b[k]);
            for(int i = 0; i < 4; i++){
                if(g[x+a[i]][y+b[i]].type==-2){
                    g[x + a[i]][y + b[i]].type = -3;
                    islight[x + a[i]][y + b[i]].type = -2;
                } 
            }
            findway(g, x,y + 1, islight);
            
            for(int i=0;i<4;i++){
                if((g[x+a[i]][y+b[i]].type==5 && islight[x+a[i]][y+b[i]].type==5) || ( g[x+a[i]][y+b[i]].type==-3 && islight[x+a[i]][y+b[i]].type==-2 )){
                    g[x + a[i]][y + b[i]].type = -2;
                    islight[x + a[i]][y + b[i]].type = -2;
                }
             }
			 for(int i=0;i<save.getLength();i++){
			 	g[save.getEleAtPos(i).x][save.getEleAtPos(i).y].type=-2;
			 	islight[save.getEleAtPos(i).x][save.getEleAtPos(i).y].type=-2;
			 }       
        }
           
    }
}

void DFS2(int x,int y,nodes **g,nodes **islight){

    for (int k = 0;k<4;k++){
    	VecList<stack> save0;
        if (g[x + a[k]][y + b[k]].type == -2 && islight[x + a[k]][y + b[k]].type != -2){
            g[x + a[k]][y + b[k]].type = 5;
            islight[x + a[k]][y + b[k]].type = 5;
            putlight(g, islight, save0, x + a[k], y + b[k]);
            for (int t = k + 1; t < 4; t++){
            	VecList<stack> save1;
                if (g[x + a[t]][y + b[t]].type == -2 && islight[x + a[t]][y + b[t]].type != -2){
                    g[x + a[t]][y + b[t]].type = 5;
                    islight[x + a[t]][y + b[t]].type = 5;//?????????????????
                    putlight(g, islight,save1, x + a[t], y + b[t]);
                    for (int i = 0; i < 4; i++)
                    {
                        if(g[x+a[i]][y+b[i]].type==-2){
                            g[x + a[i]][y + b[i]].type = -3;
                            islight[x + a[i]][y + b[i]].type = -2;
                        }   
                    }
                    findway(g, x, y + 1, islight);
                    for(int i=0;i<4;i++){
                         if((g[x+a[i]][y+b[i]].type==5 && islight[x+a[i]][y+b[i]].type==5) || ( g[x+a[i]][y+b[i]].type==-3 && islight[x+a[i]][y+b[i]].type==-2 )){
                            g[x + a[i]][y + b[i]].type = -2;
                            islight[x + a[i]][y + b[i]].type = -2;
                     }
                    }
                    for(int i=0;i<save1.getLength();i++){
			 			g[save1.getEleAtPos(i).x][save1.getEleAtPos(i).y].type=-2;
			 			islight[save1.getEleAtPos(i).x][save1.getEleAtPos(i).y].type=-2;
				 	}
                }
            }
            for(int i=0;i<save0.getLength();i++){
			 	g[save0.getEleAtPos(i).x][save0.getEleAtPos(i).y].type=-2;
			 	islight[save0.getEleAtPos(i).x][save0.getEleAtPos(i).y].type=-2;
			 }
        }
    }
}
       

void DFS3(int x,int y,nodes **g,nodes **islight){
    for (int k = 0;k<4;k++){
    	VecList<stack> save0;
         if(g[x+a[k]][y+b[k]].type==-2 && islight[x+a[k]][y+b[k]].type!=-2){
            g[x + a[k]][y + b[k]].type = 5;
            islight[x + a[k]][y + b[k]].type = 5;
            putlight(g, islight, save0,x+a[k],y+b[k]);
            for (int t = k + 1;t<4;t++){
            	VecList<stack> save1;
                if(g[x+a[t]][y+b[t]].type==-2 && islight[x+a[t]][y+b[t]].type!=-2){
                     g[x + a[t]][y + b[t]].type = 5;
                    islight[x + a[t]][y + b[t]].type = 5;
                    putlight(g, islight, save1,x+a[t],y+b[t]);
                    for (int p = k + 1; p < 4;p++){
                    	VecList<stack> save2;
                        if(g[x+a[p]][y+b[p]].type==-2 && islight[x+a[p]][y+b[p]].type!=-2){
                            g[x + a[p]][y + b[p]].type = 5;
                            islight[x + a[p]][y + b[p]].type = 5;
                            putlight(g, islight, save2,x+a[p],y+b[p]);
                            for (int i = 0; i < 4; i++)
                            {
                                if(g[x+a[i]][y+b[i]].type==-2){
                                    g[x + a[i]][y + b[i]].type = -3;
                                    islight[x + a[i]][y + b[i]].type = -2;
                                }
                                    
                            }
                            findway(g, x, y + 1, islight);
                             for(int i=0;i<4;i++){
                                if((g[x+a[i]][y+b[i]].type==5 && islight[x+a[i]][y+b[i]].type==5) || ( g[x+a[i]][y+b[i]].type==-3 && islight[x+a[i]][y+b[i]].type==-2 )){
                                    g[x + a[i]][y + b[i]].type = -2;
                                    islight[x + a[i]][y + b[i]].type = -2;
                                }
                            }
                            for(int i=0;i<save2.getLength();i++){
			 					g[save2.getEleAtPos(i).x][save2.getEleAtPos(i).y].type=-2;
			 					islight[save2.getEleAtPos(i).x][save2.getEleAtPos(i).y].type=-2;
			 				}
                        }
                    }
                    for(int i=0;i<save1.getLength();i++){
			 			g[save1.getEleAtPos(i).x][save1.getEleAtPos(i).y].type=-2;
			 			islight[save1.getEleAtPos(i).x][save1.getEleAtPos(i).y].type=-2;
					 }
                }
            }
            for(int i=0;i<save0.getLength();i++){
			 	g[save0.getEleAtPos(i).x][save0.getEleAtPos(i).y].type=-2;
			 	islight[save0.getEleAtPos(i).x][save0.getEleAtPos(i).y].type=-2;
			 }
         }   
    }
}
/*********************************************************/
void DFSwhite(nodes **g,nodes **islight,VecList<stack> white,int i){
	cout<<white.getLength()<<"!";
    if(i==white.getLength()){
        for (int i = 0; i < m;i++){
            for(int j=0;j<n;j++){
                if(islight[i][j].type==-2){
                    return;
                }
             }
        }

        for (int i = 0; i < m;i++){
            for(int j=0;j<n;j++){
            if(islight[i][j].type==6){
                islight[i][j].type = -2;
            }
         }
        }
        copy(islight,result);
        return;
    }
	cout<<"!";
    for(int x=i;x<white.getLength();x++){
    	
    	cout<<white.getEleAtPos(x).x<<","<<white.getEleAtPos(x).y<<endl;
        if(g[white.getEleAtPos(x).x][white.getEleAtPos(x).y].type==-2 && islight[white.getEleAtPos(x).x][white.getEleAtPos(x).y].type==-2){
            VecList<stack> save;
            cout<<save.getLength()<<"!!!!!";
            g[white.getEleAtPos(x).x][white.getEleAtPos(x).y].type=5;
            islight[white.getEleAtPos(x).x][white.getEleAtPos(x).y].type = 5;
            putlight(g, islight, save, white.getEleAtPos(x).x,white.getEleAtPos(x).y );
            DFSwhite(g, islight, white, x + 1);
            cout<<save.getLength()<<"!!!!!";
            g[white.getEleAtPos(x).x][white.getEleAtPos(x).y].type=-2;
            islight[white.getEleAtPos(x).x][white.getEleAtPos(x).y].type = -2;
            for(int i=0;i<save.getLength();i++){
			 	g[save.getEleAtPos(i).x][save.getEleAtPos(i).y].type=-2;
			 	islight[save.getEleAtPos(i).x][save.getEleAtPos(i).y].type=-2;
			 }     
        }
    }
}
/*********************************************************/
void findway(nodes **g,int row,int col,nodes **islight){
    for(int x=row;x<m;x++){
        for (int y = col; y < n;y++){
            if(g[x][y].type>=1 && g[x][y].type<=3){
                 int count = 0;
                if(x-1>=0 && g[x-1][y].type==5  ) 
                { 
                    count++;
                }  
                if(x+1<m&& g[x+1][y].type==5 )
                {
                    count++;
                }
                if(y-1>=0 &&g[x][y-1].type==5)
                { 
                    count++;
                }  
                if(y+1<n&&g[x][y+1].type==5)
                {
                    count++;
                }  
                cout<<g[x][y].type-count<<"!";
                switch(g[x][y].type-count){
                    case 0:
                        break;
                    case 1:
                        DFS1(x, y, g,islight);
                        break;
                    case 2:
                         DFS2(x,y,g,islight);
                        break;
                    case 3:
                        DFS3(x, y, g,islight);
                        break;
                }
            }
        }
    }
    VecList<stack> white;
    for (int i = 0; i < m;i++){
        for(int j=0;j<n;j++){
            if(islight[i][j].type==-2){
            	stack aa;
            	aa.x=i;aa.y=j;
            	white.insertLast(aa);
            }
        }
    }
    DFSwhite(g,islight,white,0);
    return;
}
/*******************************/
void boarderAndmark(nodes **s,int row,int col,nodes **islight){
	
    int count = 0;
    int ismark[4]={0};
    if(row-1>=0 && (s[row-1][col].type==-2 ||s[row-1][col].type==5))
     {
         ismark[0] = 1;  
         count++;
     }  
    if(row+1<m&&(s[row+1][col].type==-2 || s[row+1][col].type==5))
        {
            ismark[1] = 1;
            count++;
        }
    if(col-1>=0 &&(s[row][col-1].type==-2 || s[row][col-1].type==5))
      {
          count++;
          ismark[2] = 1;
      }  
    if(col+1<n&&(s[row][col+1].type==-2 || s[row][col+1].type==5))
    {
          count++;
          ismark[3] = 1;
      }  
    if(count==s[row][col].type){
        for (int j = 0; j < 4;j++){
            if(ismark[j]==1){
                switch(j){
                    case 0:
                        s[row - 1][col].type = 5;
                        islight[row - 1][col].type = 5;
                        for (int i = row - 2; i >= 0;i--){
                            if(s[i][col].type==-2){
                                s[i][col].type = -3;//??????
                                islight[i][col].type = 6; //???????
                            }else if(s[i][col].type==5 || s[i][col].type==-3){
                                if(s[i][col].type==-3)
                                    islight[i][col].type = 6;
                            } //????????????  
                                else 
                                    break; //??? ,?????
                        }
                        for (int i = col - 1; i >= 0;i--){ //??
                            if(s[row-1][i].type==-2){
                                s[row-1][i].type = -3;
                                islight[row-1][i].type = 6;
                            }else if(s[row-1][i].type==5 || s[row-1][i].type==-3){
                                if(s[row-1][i].type==-3)
                                    islight[row-1][i].type = 6;
                            }
                                else
                                    break;
                        }
                        for (int i = col + 1;i<n;i++){//??
                            if(s[row-1][i].type==-2){
                                s[row-1][i].type = -3;
                                islight[row-1][i].type = 6;
                            }else if(s[row-1][i].type==5 || s[row-1][i].type==-3){
                                if(s[row-1][i].type==-3)
                                    islight[row-1][i].type = 6;
                            }
                                else
                                    break;
                            }
                         break;
                    case 1:
                        s[row + 1][col].type = 5; //???????????
                        islight[row + 1][col].type = 5; //??
                        for (int i = row + 2;i<m;i++){ //??
                            if(s[i][col].type==-2){
                                s[i][col].type = -3;//??????
                                islight[i][col].type = 6; //???????
                            }else if(s[i][col].type==5 || s[i][col].type==-3){
                                if(s[i][col].type==-3)
                                    islight[i][col].type = 6;
                            }
                                else 
                                    break; //??? ,?????
                        }
                        for (int i = col - 1; i >= 0;i--){ //??
                            if(s[row+1][i].type==-2){
                                s[row+1][i].type = -3;
                                islight[row+1][i].type = 6;
                            }else if(s[row+1][i].type==5 || s[row+1][i].type==-3){
                                if(s[row+1][i].type==-3)
                                    islight[row+1][i].type = 6;
                            }
                                else
                                    break;
                        }
                        for (int i = col + 1;i<n;i++){//??
                            if(s[row+1][i].type==-2){
                                s[row+1][i].type = -3;
                                islight[row+1][i].type = 6;
                            }else if(s[row+1][i].type==5 || s[row+1][i].type==-3){
                                if(s[row+1][i].type==-3)
                                    islight[row+1][i].type = 6;
                            }
                                else
                                    break;
                            }                       
                        break;
                    case 2:
                        s[row ][col-1].type = 5; //???????????
                        islight[row][col-1].type = 5; //??
                        for (int i = row-1; i >= 0;i--){ //????
                            if(s[i][col-1].type==-2){
                                s[i][col-1].type = -3;//??????
                                islight[i][col-1].type = 6; //???????
                            }else if(s[i][col-1].type==5 || s[i][col-1].type==-3){
                                if(s[i][col-1].type==-3)
                                    islight[i][col-1].type = 6;
                            } //????????????  
                                else 
                                    break; //??? ,?????
                        }
                        for (int i = row+1;i<m;i++){ //??
                            if(s[i][col-1].type==-2){
                                s[i][col-1].type = -3;//??????
                                islight[i][col-1].type = 6; //???????
                            }else if(s[i][col-1].type==5 || s[i][col-1].type==-3){
                                if(s[i][col-1].type==-3)
                                    islight[i][col-1].type= 6;
                            }
                                else 
                                    break; //??? ,?????
                        }
                        for (int i = col - 2; i >= 0;i--){ //??
                            if(s[row][i].type==-2){
                                s[row][i].type = -3;
                                islight[row][i].type = 6;
                            }else if(s[row][i].type==5 || s[row][i].type==-3){
                                if(s[row][i].type==-3)
                                    islight[row][i].type = 6;
                            }
                                else
                                    break;
                        }                         
                        break;
                    case 3:
                        s[row][col+1].type = 5; //???????????
                        islight[row][col+1].type = 5; //??
                        for (int i = row-1; i >= 0;i--){ //????
                            if(s[i][col+1].type==-2){
                                s[i][col+1].type = -3;//??????
                                islight[i][col+1].type = 6; //???????
                            }else if(s[i][col+1].type==5 || s[i][col+1].type==-3){
                                 if(s[i][col+1].type==-3)
                                    islight[i][col+1].type = 6;
                            } //????????????  
                                else 
                                    break; //??? ,?????
                        }
                        for (int i = row+1;i<m;i++){ //??
                            if(s[i][col+1].type==-2){
                                s[i][col+1].type = -3;//??????
                                islight[i][col+1].type = 6; //???????
                            }else if(s[i][col+1].type==5 || s[i][col+1].type==-3){
                                if(s[row][i].type==-3)
                                    islight[i][col+1].type = 6;
                            }
                                else 
                                    break; //??? ,?????
                        }
                        for (int i = col + 2;i<n;i++){//??
                            if(s[row][i].type==-2){
                                s[row][i].type = -3;
                                islight[row][i].type = 6;
                            }else if(s[row][i].type==5 || s[row][i].type==-3){
                                if(s[row][i].type==-3)
                                    islight[row][i].type = 6;
                            }
                                else
                                    break;
                            }                           
                        break;
                     }
                }
            }
        }

}
/*******************************/
void solveAkari(nodes **g){  
	nodes** mark;
	mark=new nodes *[m];
	for(int i=0;i<m;i++)
		mark[i]=new nodes[n];
	copy(g,mark);
    nodes** islight;
    islight=new nodes *[m];
	for(int i=0;i<m;i++)
		islight[i]=new nodes[n];
	copy(g,islight);
	VecList<stack> help;
        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++)
                if (g[i][j].type== 0){
                    if (i - 1 >= 0 && g[i-1][j].type==-2)
                        g[i - 1][j].type = -3;
                    if (i + 1 < m && g[i+1][j].type==-2)
                        g[i + 1][j].type = -3;
                    if (j - 1 >= 0&&  g[i][j-1].type==-2)
                        g[i][j - 1].type = -3;
                    if (j + 1 < n&& g[i][j+1].type==-2)
                        g[i][j + 1].type = -3;
                }
        }
            if(issame(g,mark)){
                for (int i = 0; i < m; i++){
                    for (int j = 0; j < n; j++){
                        boarderAndmark(g, i, j, islight);
                    }
                }
            } 
            while (issame(g, mark) == false)
            {	cout<<"1";
            	copy(g,mark);
            	//printR(g);
                for (int i = 0; i < m; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        boarderAndmark(g, i, j, islight);
                    }
                }
        }
        
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
                cout << islight[i][j].type << " ";
            cout << "\n";
        }

        cout << "\n\n";
                for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
                cout << g[i][j].type << " ";
            cout << "\n";
        }
        findway(g,0,0,islight);
		printR(g);
}
/*******************************/
int main(){
	cin>>m>>n;
	result=new nodes *[m];
	for(int i=0;i<m;i++)
		result[i]=new nodes[n];
	char t[m*n];
	for(int i=0;i<m*n;i++){
		cin>>t[i];
	}
	buildR(t,result);
	printR(result);
	solveAkari(result);
	printR(result);
}
