/**
有n只小动物，每只都有一个独特的编号，分别从1到n。现在他们从左到右依次排在一条直线上，顺序是乱的。
现在，我们只知道每个位置前面有几个比他小的数。请你根据给出的信息计算出每个位置上的数是多少。
n<=80000。
Input
输入第一行是一个正整数n，表示小动物的数量。
接下来有n-1个数，第i个数表示在第i+1个位置以前有多少个比第i+1个位置上的数小的数。
Output
输出n行，每行一个整数，表示对应位置小动物的编号。
Sample Input
5
1
2
1
0
Sample Output
2
4
5
3
1
样例解释
输入表示第2个位置前有1个比第3个位置小。
第3个位置前有2个比第3个位置小。
第4个位置前有1个比第4个位置小。
第5个位置前有0个比第5个位置小。
**/

// 没有什么思路， 就直接暴力就好
#include<iostream>
using namespace std;
const int N = 8*1e4 + 10;
int a[N];
int b[N];
int vis[N];
int main(){
	int n; cin >> n;
	a[1] = 0;
	for(int i = 2; i <= n; i ++){
		cin >> a[i];
	}
	for(int i = n; i >= 1; i --){
		int temp = a[i]+1;
		for(int j = 1; j <= temp; j ++){
			if(vis[j] == 1){
				temp ++;
			}
		} 
		b[i] = temp;
		vis[temp] = 1;
	}
	for(int i = 1; i <= n; i ++){
		cout << b[i] << endl;
	}
	return 0;
}
