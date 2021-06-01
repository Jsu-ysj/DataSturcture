/**题目简介：
HUEL_ACM队的队长给出了一个序列，想让学妹帮队长干活，作为学妹（或者想帮助某个漂亮的学妹）的你需要处理如下两种情况。

"C a b c"表示给[a, b]区间中的值全部增加c (-10000 ≤ c ≤ 10000)。

"Q a b" 询问[a, b]区间中所有值的和。

Input
第一行包含两个整数N, Q。1 ≤ N,Q ≤ 100000.

第二行包含n个整数，表示初始的序列A (-1000000000 ≤ Ai ≤ 1000000000)。

接下来Q行询问，格式如题目描述。

Output
对于每一个Q开头的询问，你需要输出相应的答案，每个答案一行。

Sample Input
10 5
1 2 3 4 5 6 7 8 9 10
Q 4 4
Q 1 10
Q 2 4
C 3 6 3
Q 2 4
Sample Output
4
55
9
15
**/
线段树模板题， 经典的树状数组区间修改和区间查询的题目， 使用lazy标记， 减少时间；
用cin cout 要关流，不然会超时
**/

//具体代码：
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL N = 2*1e5+5;
struct node{
	LL l, r;
	LL sum;
	LL lazy;
}t[4*N];
void add(LL k){
	t[k].sum = t[k<<1].sum + t[k<<1|1].sum;
}

void buildTree(LL l, LL r, LL k){
	t[k].l = l; t[k].r = r; t[k].lazy = 0;
	if(t[k].l == t[k].r){
		cin >> t[k].sum;
		return ;
	}
	LL mid = (t[k].l+t[k].r)>>1;
	buildTree(l, mid, k<<1);
	buildTree(mid+1, r, k<<1|1);
	add(k);
}

void pushDown(LL k){
	if(t[k].lazy){
		t[k<<1].lazy += t[k].lazy;
		t[k<<1|1].lazy += t[k].lazy;
		t[k<<1].sum += t[k].lazy*(t[k<<1].r - t[k<<1].l+1);
		t[k<<1|1].sum += (t[k<<1|1].r - t[k<<1|1].l+1)*t[k].lazy;
		t[k].lazy = 0;
	}
}
void upDate(LL l, LL r, LL k, LL d){
	if(l <= t[k].l && r >= t[k].r){
		t[k].lazy += d;
		t[k].sum += d*(t[k].r - t[k].l + 1);
		return ;
	}
	pushDown(k);
	LL mid = (t[k].r+t[k].l)>>1;
	if(l <= mid){
		upDate(l, r, k<<1, d);
	}
	if(mid < r){
		upDate(l, r, k<<1|1, d); 
	}
	add(k);
}

LL query(LL l, LL r, LL k){
	if(t[k].l >= l&&t[k].r <= r){
		return t[k].sum;
	}
	pushDown(k);
	LL mid = (t[k].l + t[k].r)>>1;
	LL res = 0;
	if(l <= mid){
		res += query(l, r, k<<1);
	}
	 if(r>mid) res += query(l, r, k<<1|1);
	return res;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	LL n, m;
	cin >> n >> m;
	buildTree(1, n, 1);
	while(m --){
		char op;
		LL l, r;
		cin >> op >> l >> r;
		if(op=='Q'){
			cout << query(l, r, 1) << endl;
		}else{
			LL d;
			cin >> d;
			upDate(l, r, 1, d); 
		}
	}
	return 0;
}
