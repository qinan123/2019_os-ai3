#include <iostream>
#include <algorithm>
using namespace std;
 
const int N=5;   
int Money[N]={5,2,2,3,5};  
int Value[N]={1,5,10,50,100}; 
 
int min(int x,int y){
	if(x>y)
		return y;
	else
		return x;
} 

int solve(int money){
	int num=0;
	for(int i=N-1;i>=0;i--){
		//cΪʹ��ֽ�ҵ�����������Ҫ����ֵΪvaule[i]������������������ѡȡ��С�ģ�
		int c=min(money/Value[i],Money[i]);
		money=money-Value[i]*c;		
		num+=c;
	}
	if(money>0){
		num=-1;		
	}
	return num;
}

int main(){
	int money;
	printf��"����֧����Ǯ��"��;
	cin>>money;//����һ����Ҫ֧������Ǯ
	int res=solve(money);
	if(res!=-1){
		cout<<res<<endl;
	}else{
		cout<<"no"<<endl;
	}
	return 0;
 
}

