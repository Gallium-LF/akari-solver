#include<iostream>
#include<ctime>
using namespace std;
/*******************************/
struct nodes{
	int type;
	bool light;
	void operator=(const nodes &D){ 
		type=D.type;light=D.light;
    }
};
/*******************************/
struct black{
	int x,y;
	int type;
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
};
/*******************************/
nodes **result;
VecList<black> blackList;
int m,n;
bool finish;
/*******************************/
void buildR(char *t,nodes **r){//������Ŀ 
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
/***************************/
void printR(nodes **a){//������� 
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
			}
		}
		cout<<"|"<<endl;
	}
	for(int i=0;i<n+1;i++)
		cout<<"__";
	cout<<endl;
}
/***************************/
void buildList(nodes **r){//��0,4,3,2,1�����ν��������� 
	int i,j;
	
	for(i=0;i<m;i++){//ֻ��һ����������ȴ��� 
		for(j=0;j<n;j++){
			if(r[i][j].type==0){
				black tmp;
				tmp.type=0;
				tmp.x=i;tmp.y=j;
				blackList.insertLast(tmp);
			}
		}
	}
	
	for(i=0;i<m;i++){//��0һ�� 
		for(j=0;j<n;j++){
			if(r[i][j].type==4){
				black tmp;
				tmp.type=4;
				tmp.x=i;tmp.y=j;
				blackList.insertLast(tmp);
			}
		}
	}
	
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			if(r[i][j].type==3){
				black tmp;
				tmp.type=3;
				tmp.x=i;tmp.y=j;
				blackList.insertLast(tmp);
			}
		}
	}
	
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			if(r[i][j].type==1){
				black tmp;
				tmp.type=1;
				tmp.x=i;tmp.y=j;
				blackList.insertLast(tmp);
			}
		}
	}
	
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			if(r[i][j].type==2){
				black tmp;
				tmp.type=2;
				tmp.x=i;tmp.y=j;
				blackList.insertLast(tmp);
			}
		}
	}
}
/***************************/
bool complete(nodes **r){//�ж���Ŀ�Ƿ���δ�����ĸ��� 
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++){
			if(r[i][j].type<=-2&&r[i][j].light==false)return false;
		}
	return true;
}
/***************************/
bool setbarrier(nodes **tmp,int x,int y){//���õط����ܷ��õ��� 
	//printR(tmp);
	if(x<0||x>=m||y<0||y>=n) return true;//�����߽��򷵻� 
	
	if(tmp[x][y].type==5) return false;//���ڵ��ݷ���false 
	
	else if(tmp[x][y].type==-2&&tmp[x][y].light==false){
		tmp[x][y].type=-3;//barrier;
	}
	
	return true;
}
/***************************/
bool lightup(nodes **tmp,int x,int y){//�ڸ����Ϸ��õ��� 
	//printR(tmp);
	if(x<0||x>=m||y<0||y>=n) return false;//�����߽��򷵻� 
	
	if(tmp[x][y].type!=-2&&tmp[x][y].type!=5||tmp[x][y].light==true){
		return false;	
	}//�ѱ��������ǿո񷵻�false 
	
	else if(tmp[x][y].type==5)return true;//�Ѵ��ڵ��ݷ���true 
	tmp[x][y].type=5;//���õ��� 
	
    for(int i=x+1;i<m&&(tmp[i][y].type<=-2||tmp[i][y].light==true);i++)//����Ե���������ڸ��� 
        tmp[i][y].light=true;//������ 
        
    for(int i=x-1;i>=0&&(tmp[i][y].type<=-2||tmp[i][y].light==true);i--)
        tmp[i][y].light=true;//������ 
        
    for(int j=y+1;j<n&&(tmp[x][j].type<=-2||tmp[x][j].light==true);j++)
        tmp[x][j].light=true;//������ 
        
    for(int j=y-1;j>=0&&(tmp[x][j].type<=-2||tmp[x][j].light==true);j--)
        tmp[x][j].light=true;//������
		 
    return true;
}
/***************************/
void copy(nodes **a,nodes **b){//������Ŀ 
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++)
			b[i][j]=a[i][j];
	}	
}
/****************************/
int findwhite(int l,nodes **r){ //Ѱ��δ�������ĸ��� 
        int row=(l+1)/n;
        int col=(l+1)%n;
        //cout<<"("<<row<<","<<col<<")"<<endl;
        int i,j;
        for(i=row;i<m;i++){
        	if(i==row)j=col;//�Ӽ�����ĵ㿪ʼ������� 
        	else j=0; 
			for(;j<n;j++)
                if (r[i][j].type==-2&&r[i][j].light==false){
                    return i*n+j;//������������i*n+j��ʾ�ڼ�������û�й� 
                }
		}
        return -1;//˵��û��û�������ĸ��� 
}
/***************************/
bool white(int k,nodes **r) {//��ʣ����ӷ��õ� 
        if(finish)return true;//�������� 
        bool f=false;
        nodes **cp;
		cp=new nodes *[m];
		for(int i=0;i<m;i++)
			cp[i]=new nodes[n];
		copy(r,cp);
		
        if(complete(r)){//�ж��Ƿ������Ŀ 
            copy(r,result);
            finish=true;
            return true;
        }
        if(k==-1)//��k==-1��˵����ʱ���������⣬��ʼ���� 
            return false;
        //cout<<"k:"<<k<<endl; 
		lightup(cp,k/n,k%n);//���� 
		//printR(cp);
		f=white(findwhite(k,cp),cp);//�����ж��Ƿ�������� 
		
        if(!f){//���Ϸ�����������һ��λ�÷��� 
            copy(r,cp);
            f=white(findwhite(k,cp),cp);
        }
        
        for(int i=0;i<m;i++)//ɾ����ʱ�ռ� 
        	delete [] cp[i];
        delete []cp;
        
        return f;
}
/***************************/
bool solve(int deep,nodes **r){//���ȶ�0,4����barrier��light��Ȼ���1,2,3���г��ԡ� 
		if(finish) return true;//�������� 
		
		if(deep<blackList.getLength()){//deep������е���һ���ڸ���
			black index=blackList.getEleAtPos(deep);
			int x=index.x,y=index.y;
			bool f=false;
			nodes **tmp;
			tmp=new nodes *[m];
			for(int i=0;i<m;i++)
				tmp[i]=new nodes[n];
			//cout<<"1"; 
			copy(r,tmp);
			switch(index.type){
				
				case 4:{//printR(tmp);
					if(lightup(tmp,x-1,y)&&lightup(tmp,x+1,y)&&lightup(tmp,x,y+1)&&lightup(tmp,x,y-1))
						f=solve(deep+1,tmp);
					break;
				}
				
				case 3:{//printR(tmp);
					if(lightup(tmp,x,y-1)&&lightup(tmp,x-1,y)&&setbarrier(tmp,x+1,y)&&lightup(tmp,x,y+1)) 
						f=solve(deep+1,tmp);//���������� 
					copy(r,tmp);
					if(!finish&&lightup(tmp,x,y+1)&&setbarrier(tmp,x-1,y)&&lightup(tmp,x+1,y)&&lightup(tmp,x,y-1))
						f=solve(deep+1,tmp);//���������� 
					copy(r,tmp);
					if(!finish&&lightup(tmp,x+1,y)&&lightup(tmp,x-1,y)&&setbarrier(tmp,x,y+1)&&lightup(tmp,x,y-1))
						f=solve(deep+1,tmp);//���������� 
					copy(r,tmp);
					if(!finish&&lightup(tmp,x-1,y)&&lightup(tmp,x+1,y)&&lightup(tmp,x,y+1)&&setbarrier(tmp,x,y-1))
						f=solve(deep+1,tmp);//���������� 
					copy(r,tmp);
					break;
				}
				
				case 2:{//printR(tmp);
					if(lightup(tmp,x,y-1)&&lightup(tmp,x-1,y)&&setbarrier(tmp,x+1,y)&&setbarrier(tmp,x,y+1)) 
						f=solve(deep+1,tmp);//�������� 
					copy(r,tmp);
					if(!finish&&lightup(tmp,x,y-1)&&lightup(tmp,x+1,y)&&setbarrier(tmp,x-1,y)&&setbarrier(tmp,x,y+1))
						f=solve(deep+1,tmp);//�������� 
					copy(r,tmp);
					if(!finish&&lightup(tmp,x-1,y)&&lightup(tmp,x,y+1)&&setbarrier(tmp,x,y-1)&&setbarrier(tmp,x+1,y))
						f=solve(deep+1,tmp);//�������� 
					copy(r,tmp);
					if(!finish&&lightup(tmp,x+1,y)&&lightup(tmp,x,y+1)&&setbarrier(tmp,x-1,y)&&setbarrier(tmp,x,y-1))
						f=solve(deep+1,tmp);//�������� 
					copy(r,tmp);
					if(!finish&&lightup(tmp,x+1,y)&&lightup(tmp,x-1,y)&&setbarrier(tmp,x,y+1)&&setbarrier(tmp,x,y-1))
						f=solve(deep+1,tmp);//�������� 
					copy(r,tmp);
					if(!finish&&lightup(tmp,x,y+1)&&lightup(tmp,x,y-1)&&setbarrier(tmp,x+1,y)&&setbarrier(tmp,x-1,y))
						f=solve(deep+1,tmp);//�������� 
					copy(r,tmp);
					break;
				}
				
				case 1:{//printR(tmp);
					if(lightup(tmp,x,y-1)&&setbarrier(tmp,x-1,y)&&setbarrier(tmp,x+1,y)&&setbarrier(tmp,x,y+1)) 
						f=solve(deep+1,tmp);//������ 
					copy(r,tmp);
					if(!finish&&lightup(tmp,x,y+1)&&setbarrier(tmp,x-1,y)&&setbarrier(tmp,x+1,y)&&setbarrier(tmp,x,y-1))
						f=solve(deep+1,tmp);//������ 
					copy(r,tmp);
					if(!finish&&lightup(tmp,x+1,y)&&setbarrier(tmp,x-1,y)&&setbarrier(tmp,x,y+1)&&setbarrier(tmp,x,y-1))
						f=solve(deep+1,tmp);//������ 
					copy(r,tmp);
					if(!finish&&lightup(tmp,x-1,y)&&setbarrier(tmp,x+1,y)&&setbarrier(tmp,x,y+1)&&setbarrier(tmp,x,y-1))
						f=solve(deep+1,tmp);//������ 
					copy(r,tmp);
					break;
				}
				
				case 0:{//printR(tmp);
					if(setbarrier(tmp,x-1,y)&&setbarrier(tmp,x+1,y)&&setbarrier(tmp,x,y+1)&&setbarrier(tmp,x,y-1))
						f=solve(deep+1,tmp);
					break;
				}
			}
			for(int i=0;i<m;i++)//ɾ����ʱ�ռ䣬��ֹ���ڴ� 
        		delete [] tmp[i];
        	delete []tmp;
        	//cout<<"2";
			return f;
		}
		
		else{//���������ֺڸ�����Χ���õ���֮��Ѱ�һ�δ�������ĵط� 
			return white(findwhite(-1,r),r);
		}
}
/***************************/
int main(){
	finish=false;
	cin>>m>>n;
	result=new nodes *[m];
	for(int i=0;i<m;i++)
		result[i]=new nodes[n];
		
	char t[m*n];
	for(int i=0;i<m*n;i++)
		cin>>t[i];
		
	long start,end;
    double duration;
    
	buildR(t,result);
	buildList(result);
	printR(result);
	start = clock();
	solve(0,result);
	end = clock();
	printR(result);
	duration  =(end - start);
	cout<<"time use:"<<duration<<"ms";
	return 0;
}
