
/**
你工作以后, KPI 就是你的全部了. 我开发了一个服务，取得了很大的知名度。数十亿的请求被推到一个大管道后同时服务从管头拉取请求。
让我们来定义每个请求都有一个重要值。我的KPI是由当前管道内请求的重要值的中间值来计算。现在给你服务记录，有时我想知道当前管道内请求的重要值得中间值。
Input
有大约100组数据。

每组数据第一行有一个$n (1 \leq n \leq 10000)$，代表服务记录数。

接下来有n行，每一行有3种形式
  "in x": 代表重要值为$x (0 \leq x \leq 10^9)$的请求被推进管道。
  "out": 代表服务拉取了管道头部的请求。
  "query: 代表我想知道当前管道内请求重要值的中间值. 那就是说，如果当前管道内有m条请求, 我想知道，升序排序后第$floor(m/2)+1_{th}$ 条请求的重要值.

为了让题目简单，所有的x都不同，并且如果管道内没有值，就不会有"out"和"query"操作。
Output
对于每组数据，先输出一行

Case #i:
然后每一次"query"，输出当前管道内重要值的中间值。
Sample Input
6
in 874
query
out
in 24622
in 12194
query
Sample Output
Case #1:
874
24622
**/

/**
1： 离散化我们记下所有的操作 pre[1~n]，顺便存下所有元素（排好序）now[1~sum];
   #sum:in的数量
2：接着，建树 tree[1~maxn<<2]
   #tree[i] 存的是 tree[i] 这个区间中元素个数
2：然后，按照顺序执行操作：
   in（pre[i]>=0）:找到插入的数（pre[i]）在树上的位置（lower_bound） tmp;
                  在树上tmp位置+1，表示tmp位置上有数;
                  push_up;
   out(pre[i]==-1):找到队首（q.front()）在树上的位置 tmp;
                   在树上tmp位置-1，表示tmp位置上的数没了;
                   push_up;
                   q.pop();
   query(pre[i]==-2):寻找在队中间（q.size()/2+1）位置的元素在树上的位置 res;
                     输出now[res];

**/


// 具体代码
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>

const int maxn  = 100005;
using namespace std;
int now[maxn];
int pre[maxn];
int tree[maxn<<2];
int cnt, n;

void push_up(int k) {
	tree[k]=tree[k<<1]+tree[k<<1|1];
}

void build(int k,int l,int r) {
	if(l==r) {
		tree[k]=0;
		return ;
	}
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	push_up(k);
}

void updata(int k,int l,int r,int tmp,int flag) {
	if(l==r) {
		tree[k]+=flag;
		return;
	}
	int mid=(l+r)>>1;
	if(tmp<=mid) updata(k<<1,l,mid,tmp,flag);
	else updata(k<<1|1,mid+1,r,tmp,flag);
	push_up(k);
}

int query(int k,int l,int r,int tmp) {
	if(l==r) return l;
	int mid=(l+r)>>1;
	if(tree[k<<1]>=tmp) return query(k<<1,l,mid,tmp);
	else return query(k<<1|1,mid+1,r,tmp-tree[k<<1]);
}

void work() {

}

int main() {
	while(~scanf("%d",&n)) {
		
		queue <int> q;
		for(int i = 1; i <= n; i ++) {
			char s[10];
			scanf("%s",&s);
			if(s[0]=='i') scanf("%d",&pre[i]);
			else if(s[0]=='o') pre[i]=-1;
			else pre[i]=-2;
		}
		int sum=0;
		for(int i = 1; i <= n ; i ++) {
			if(pre[i]<0) continue;
			now[++sum]=pre[i];
		}
		sort(now+1,now+sum+1);
		build(1,1,sum);
		printf("Case #%d:\n", ++cnt);
		for(int i = 1; i <= n; i ++) {
			if(pre[i]>=0) {
				int tmp=lower_bound(now+1,now+sum+1,pre[i])-now;
				updata(1,1,sum,tmp,1);
				q.push(pre[i]);
			} else if(pre[i]==-1) {
				int ret=q.front();
				int tmp=lower_bound(now+1,now+sum+1,ret)-now;
				updata(1,1,sum,tmp,-1);
				q.pop();
			} else {
				int res=query(1,1,sum,q.size()/2+1);
				printf("%d\n",now[res]);
			}
		}
	}
	return 0;
}
