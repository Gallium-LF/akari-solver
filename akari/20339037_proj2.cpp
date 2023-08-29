#include<iostream>
#include<ctime>
using namespace std;
/*******************************/
struct nodes{
	int type;
	int whiteAr;
	int lightAr;
	void operator=(const nodes &D){ 
		type=D.type;
    }
    bool operator ==(const nodes &d){
		if(type==d.type)return true;
		else return false;
	}
	bool operator !=(const nodes &d){
		if(type==d.type)return false;
		else return true;
	}
};
/*******************************/
struct black{
	int x,y;
	int type;
	bool operator ==(const black &d){
		if(type==d.type&&x==d.x&&y==d.y)return true;
		else return false;
	}
};
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
        deleteEle(T x){
        	deleteEleAtPos(locateEle(x));
		}
};
/*******************************/
nodes **result;
VecList<black> blackList;
int m,n;
bool finish;
void copy(nodes **a,nodes **b);
bool complete(nodes **r);
void buildR(char *t,nodes **r);
void buildList(nodes **r);
void countLightWhiteAround(nodes **r);
void easysolve(nodes **r);
int findwhite(int l,nodes **r);
bool hardsolve(int deep,nodes **r);
bool isSame(nodes **a,nodes **b);
void lightup(nodes **tmp,int x,int y);
bool setbarrier(nodes **tmp,int x,int y);
bool white(int k,nodes **r);
bool canPutLight(nodes **tmp,int x,int y);
/*******************************/
void buildR(char *t,nodes **r){//构造题目 
	int i,j;
	int blacktimes=0;
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			switch(t[i*n+j]){
				case '.':{
					r[i][j].type=-2;//white
					r[i][j].whiteAr=-1;
					break;
				}
				case 'X':{
					r[i][j].type=-1;//black
					r[i][j].whiteAr=-1;
					break;
				}
				case '0':{
					r[i][j].type=0;//0 black
					r[i][j].whiteAr=-1;
					break;
				}
				case '1':{
					r[i][j].type=1;//1 black
					r[i][j].whiteAr=-1;
					break;
				}
				case '2':{
					r[i][j].type=2;//2 black
					r[i][j].whiteAr=-1;
					break;
				}
				case '3':{
					r[i][j].type=3;//3 black
					r[i][j].whiteAr=-1;
					break;
				}
				case '4':{
					r[i][j].type=4;//4 black
					r[i][j].whiteAr=-1;
					break;
				}
			}
		}
	}
}
/***************************/
void countLightWhiteAround(nodes **r){//重新计算黑格子旁边的灯和空格子的数量 
	for(int x=0;x<blackList.getLength();x++){
		black tmp=blackList.getEleAtPos(x);
		int i=tmp.x,j=tmp.y;
		int countW=0,countL=0;
		if(i-1>=0&&r[i-1][j].type==5)
			countL++;
		if(j-1>=0&&r[i][j-1].type==5)
			countL++;
		if(i+1<m&&r[i+1][j].type==5)
			countL++;
		if(j+1<n&&r[i][j+1].type==5)
			countL++;
		if(i-1>=0&&r[i-1][j].type==-2)
			countW++;
		if(j-1>=0&&r[i][j-1].type==-2)
			countW++;
		if(i+1<m&&r[i+1][j].type==-2)
			countW++;
		if(j+1<n&&r[i][j+1].type==-2)
			countW++;
		r[i][j].lightAr=countL;
		r[i][j].whiteAr=countW;
	}
}
/***************************/
void printR(nodes **a){//输出函数 
	int i,j;
	cout<<"-";
	for(int i=0;i<n+1;i++)
		cout<<"--";
	cout<<endl;
	for(i=0;i<m;i++){
		cout<<"| ";
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
	cout<<"-";
	for(int i=0;i<n+1;i++)
		cout<<"--";
	cout<<endl;
}
/******************************/
bool setbarrier(nodes **tmp,int x,int y){//设置地方不能放置灯泡 
	//printR(tmp);
	if(x<0||x>=m||y<0||y>=n) return true;//超出边界则返回 
	
	if(tmp[x][y].type==5) return false;//存在灯泡返回false 
	
	else if(tmp[x][y].type==-2){
		tmp[x][y].type=-3;//barrier;
	}
	countLightWhiteAround(tmp);
	return true;
}
/****************************/
void lightup(nodes **tmp,int x,int y){//在格子上放置灯泡 
	//printR(tmp);
	tmp[x][y].type=5;//放置灯泡 
	
    for(int i=x+1;i<m&&(tmp[i][y].type<=-2||tmp[i][y].type==6);i++)//到边缘或者碰到黑格子 
        tmp[i][y].type=6;//点亮下 
        
    for(int i=x-1;i>=0&&(tmp[i][y].type<=-2||tmp[i][y].type==6);i--)
        tmp[i][y].type=6;//点亮上 
        
    for(int j=y+1;j<n&&(tmp[x][j].type<=-2||tmp[x][j].type==6);j++)
        tmp[x][j].type=6;//点亮右 
        
    for(int j=y-1;j>=0&&(tmp[x][j].type<=-2||tmp[x][j].type==6);j--)
        tmp[x][j].type=6;//点亮左
	
}
/**************************/
bool complete(nodes **r){//判断题目是否还有未点亮的格子 
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++){
			if(r[i][j].type<=-2)return false;
		}
	return true;
}
/****************************/
void easysolve(nodes **r){//首先解决无需猜测的格子 
		//printR(r);	
		for(int i=0;i<blackList.getLength();i++){
			black index=blackList.getEleAtPos(i);
			int x=index.x,y=index.y;
			if(r[x][y].type==r[x][y].whiteAr+r[x][y].lightAr&&r[x][y].lightAr<r[x][y].type){//若数字黑格子周围可放置灯的区域等于该数字则放置灯 
				if(x-1>=0&&r[x-1][y].type==-2)
					lightup(r,x-1,y);
				if(y-1>=0&&r[x][y-1].type==-2)
					lightup(r,x,y-1);
				if(x+1<m&&r[x+1][y].type==-2)
					lightup(r,x+1,y);
				if(y+1<n&&r[x][y+1].type==-2)
					lightup(r,x,y+1);
				countLightWhiteAround(r); 
			}
		}
}
/****************************/
int findwhite(int l,nodes **r){ //寻找未被点亮的格子 
        int x=(l+1)/n;
        int y=(l+1)%n;
        //cout<<"("<<x<<","<<y<<")"<<endl;
        for(int i=x;i<m;i++){
        	int j;
        	if(i==x)j=y;//从计算出的点开始往后遍历 
        	else j=0; 
			for(;j<n;j++)
                if (r[i][j].type==-2){
                    return i*n+j;//类似数独，用i*n+j表示第几个格子没有光 
                }
		}
        return -1;//说明没有没被点亮的格子 
}
/***************************/
bool white(int k,nodes **r){//在剩余格子放置灯 
		//printR(r);
        if(finish)return true;//结束回溯 
        bool f=false;
        nodes **cp;
        if(complete(r)){//判断是否完成题目 
            copy(r,result);
            finish=true;
            return true;
        }
        if(k==-1)//若k==-1则说明此时不符合题意，开始回溯 
            return false;
        //cout<<"k:"<<k<<endl; 
		cp=new nodes *[m];
		for(int i=0;i<m;i++)
			cp[i]=new nodes[n];
		copy(r,cp);
		canPutLight(cp,k/n,k%n);
		//printR(cp);
		f=white(findwhite(k,cp),cp);//继续判断是否符合题意 
        if(!f){//不合符题意则在下一个位置放置 
            copy(r,cp);
            f=white(findwhite(k,cp),cp);
        }
        
        for(int i=0;i<m;i++)//删除临时空间 
        	delete [] cp[i];
        delete []cp;
        return f;
}
/**************************/
void buildList(nodes **r){//创建黑色格子向量表 
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			if(r[i][j].type==0){//若为0则在周围放置barrier 
				setbarrier(r,i-1,j);setbarrier(r,i+1,j);setbarrier(r,i,j+1);setbarrier(r,i,j-1); 
			}
		}
	}
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			if(r[i][j].type==4){//若为4则在周围放置灯 
				lightup(r,i-1,j);lightup(r,i+1,j);lightup(r,i,j+1);lightup(r,i,j-1);
			}
		}
	}
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			if(r[i][j].type==3){//3入队 
				black tmp;
				tmp.x=i;tmp.y=j;
				tmp.type=3;
				blackList.insertLast(tmp);
			}
		}
	}
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){//2入队 
			if(r[i][j].type==2){
				black tmp;
				tmp.x=i;tmp.y=j;
				tmp.type=2;
				blackList.insertLast(tmp);
			}
		}
	}
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){//1入队 
			if(r[i][j].type==1){
				black tmp;
				tmp.x=i;tmp.y=j;
				tmp.type=1;
				blackList.insertLast(tmp);
			}
		}
	}
}
/****************************/
void copy(nodes **a,nodes **b){//复制题目 
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++)
			b[i][j]=a[i][j];
	}	
}
/***************************/
bool isSame(nodes **a,nodes **b){//判断是否相同 
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			if(a[i][j]!=b[i][j])return false;
		}
	}
	return true;
}
/***************************/
bool canPutLight(nodes **tmp,int x,int y){
	if(x<0||x>=m||y<0||y>=n) return false;//超出边界则返回 
	
	if(tmp[x][y].type!=-2&&tmp[x][y].type!=5){
		return false;	
	}//已被点亮或不是空格返回false 
	
	else if(tmp[x][y].type==5)return true;//已存在灯泡返回true 
	lightup(tmp,x,y);
	return true;
}
/****************************/
bool canSetBarrier(nodes **tmp,int x,int y){
	if(x<0||x>=m||y<0||y>=n) return true;//超出边界则返回 
	if(tmp[x][y].type==5) return false;//存在灯泡返回false 
	return true;
}
/***************************/
bool hardsolve(int deep,nodes **r){//对1,2,3进行尝试。 
		if(finish) return true;//结束回溯 
		if(deep<blackList.getLength()){//deep代表进行到哪一个黑格子
			black index=blackList.getEleAtPos(deep);
			int x=index.x,y=index.y;
			bool f=false;
			nodes **tmp;
			tmp=new nodes *[m];
			for(int i=0;i<m;i++)
				tmp[i]=new nodes[n];
			copy(r,tmp);
			switch(index.type){
				case 3:{//printR(tmp);
					if(canPutLight(tmp,x,y-1)&&canPutLight(tmp,x-1,y)&&setbarrier(tmp,x+1,y)&&canPutLight(tmp,x,y+1)) 
						f=hardsolve(deep+1,tmp);//点亮左上右 
					copy(r,tmp);
					if(!finish&&canPutLight(tmp,x,y+1)&&setbarrier(tmp,x-1,y)&&canPutLight(tmp,x+1,y)&&canPutLight(tmp,x,y-1))
						f=hardsolve(deep+1,tmp);//点亮左下右 
					copy(r,tmp);
					if(!finish&&canPutLight(tmp,x+1,y)&&canPutLight(tmp,x-1,y)&&setbarrier(tmp,x,y+1)&&canPutLight(tmp,x,y-1))
						f=hardsolve(deep+1,tmp);//点亮上左下 
					copy(r,tmp);
					if(!finish&&canPutLight(tmp,x-1,y)&&canPutLight(tmp,x+1,y)&&canPutLight(tmp,x,y+1)&&setbarrier(tmp,x,y-1))
						f=hardsolve(deep+1,tmp);//点亮上右下 
					copy(r,tmp);
					break;
				}
				case 2:{//printR(tmp);
					if(canPutLight(tmp,x,y-1)&&canPutLight(tmp,x-1,y)&&setbarrier(tmp,x+1,y)&&setbarrier(tmp,x,y+1)) 
						f=hardsolve(deep+1,tmp);//点亮左上 
					copy(r,tmp);
					if(!finish&&canPutLight(tmp,x,y-1)&&canPutLight(tmp,x+1,y)&&setbarrier(tmp,x-1,y)&&setbarrier(tmp,x,y+1))
						f=hardsolve(deep+1,tmp);//点亮左下 
					copy(r,tmp);
					if(!finish&&canPutLight(tmp,x-1,y)&&canPutLight(tmp,x,y+1)&&setbarrier(tmp,x,y-1)&&setbarrier(tmp,x+1,y))
						f=hardsolve(deep+1,tmp);//点亮右上 
					copy(r,tmp);
					if(!finish&&canPutLight(tmp,x+1,y)&&canPutLight(tmp,x,y+1)&&setbarrier(tmp,x-1,y)&&setbarrier(tmp,x,y-1))
						f=hardsolve(deep+1,tmp);//点亮右下 
					copy(r,tmp);
					if(!finish&&canPutLight(tmp,x+1,y)&&canPutLight(tmp,x-1,y)&&setbarrier(tmp,x,y+1)&&setbarrier(tmp,x,y-1))
						f=hardsolve(deep+1,tmp);//点亮上下 
					copy(r,tmp);
					if(!finish&&canPutLight(tmp,x,y+1)&&canPutLight(tmp,x,y-1)&&setbarrier(tmp,x+1,y)&&setbarrier(tmp,x-1,y))
						f=hardsolve(deep+1,tmp);//点亮左右 
					copy(r,tmp);
					break;
				}
				case 1:{//printR(tmp);
					if(canPutLight(tmp,x,y-1)&&setbarrier(tmp,x-1,y)&&setbarrier(tmp,x+1,y)&&setbarrier(tmp,x,y+1)) 
						f=hardsolve(deep+1,tmp);//点亮左 
					copy(r,tmp);
					if(!finish&&canPutLight(tmp,x,y+1)&&setbarrier(tmp,x-1,y)&&setbarrier(tmp,x+1,y)&&setbarrier(tmp,x,y-1))
						f=hardsolve(deep+1,tmp);//点亮右 
					copy(r,tmp);
					if(!finish&&canPutLight(tmp,x+1,y)&&setbarrier(tmp,x-1,y)&&setbarrier(tmp,x,y+1)&&setbarrier(tmp,x,y-1))
						f=hardsolve(deep+1,tmp);//点亮下 
					copy(r,tmp);
					if(!finish&&canPutLight(tmp,x-1,y)&&setbarrier(tmp,x+1,y)&&setbarrier(tmp,x,y+1)&&setbarrier(tmp,x,y-1))
						f=hardsolve(deep+1,tmp);//点亮上 
					copy(r,tmp);
					break;
				}
			}
			for(int i=0;i<m;i++)//删除临时空间，防止爆内存 
        		delete [] tmp[i];
        	delete []tmp;
			return f;
		}
		else{//进行完数字黑格子周围放置灯泡之后寻找还未被照亮的地方 
			return white(findwhite(-1,r),r);
		}
}
/***************************/
int main(){
	finish=false;
	cin>>m>>n;
	nodes **question;
	question=new nodes *[m];
	for(int i=0;i<m;i++)
		question[i]=new nodes[n];
	result=new nodes *[m];
	for(int i=0;i<m;i++)
		result[i]=new nodes[n];
		
	char t[m*n];
	for(int i=0;i<m*n;i++)
		cin>>t[i];
		
	/*long start,end;
    double duration;*/
    
	buildR(t,question);
	buildList(question);
	countLightWhiteAround(question);
	/*for(int i=0;i<blackList.getLength();i++){
		cout<<i<<":"<<blackList.getEleAtPos(i).type<<" "<<blackList.getEleAtPos(i).whiteAr<<endl;
	}*/
	cout<<"The question is:"<<endl;
	printR(question);
	nodes **tmp;
	tmp=new nodes *[m];
	for(int i=0;i<m;i++)
		tmp[i]=new nodes[n];
	while(!isSame(tmp,question)){
		easysolve(question);
		copy(question,tmp);
	}
	//printR(question);
	//a=clock();
	copy(question,result);
	if(!complete(result)){
		hardsolve(0,result);
	}
	//b= clock();
	cout<<endl<<"The solve is:"<<endl;
	printR(result);
	
	//c=(b-a);
	//cout<<"time use:"<<c<<"ms";
	return 0;
}
