/**题目简介：
很多学校流行一种比较的习惯。茜茜学姐很喜欢询问，从某某到某某当中，分数最高的是多少。
这让很多漂亮的学妹很喜欢。

不管你喜不喜欢，现在需要你做的是，就是按照茜茜学姐的要求，写一个程序，模拟茜茜学姐的询问。当然，茜茜学姐有时候需要更新某位同学的成绩。
Input
本题目包含多组测试，请处理到文件结束。
在每个测试的第一行，有两个正整数 N 和 M ( 0<N<=200000,0<M<5000 )，分别代表学生的数目和操作的数目。
学生ID编号分别从1编到N。
第二行包含N个整数，代表这N个学生的初始成绩，其中第i个数代表ID为i的学生的成绩。
接下来有M行。每一行有一个字符 C (只取'Q'或'U') ，和两个正整数A，B。
当C为'Q'的时候，表示这是一条询问操作，它询问ID从A到B(包括A,B)的学生当中，成绩最高的是多少。
当C为'U'的时候，表示这是一条更新操作，要求把ID为A的学生的成绩更改为B。
Output
对于每一次询问操作，在一行里面输出最高成绩。
Sample Input
5 6
1 2 3 4 5
Q 1 5
U 3 6
Q 3 4
Q 4 5
U 2 9
Q 1 5
Sample Output
5
6
5
9
**/

/**
思路：这就是一个线段树模板题， 不要用lazy就可以过
注意用cin 要关流
**/

//具体代码：
#include<bits/stdc++.h>
using namespace std;
struct node {
	int l, r;
	int maxn;
} t[200000*4];

void pushUp(int k) {
	t[k].maxn = max(t[k<<1].maxn, t[k<<1|1].maxn);
}

void build(int l, int r, int k) {
	t[k].l = l, t[k].r = r;
	if(t[k].l == t[k].r) {
		cin >> t[k].maxn;
		return ;
	}
	int mid = (t[k].l + t[k].r) >> 1;
	build(l, mid, k << 1);
	build(mid + 1, r, k << 1 | 1);
	pushUp(k);
}

int query(int l, int r, int k) {
	if(t[k].l == l && t[k].r == r) {
		return t[k].maxn;
	}
	int mid = (t[k].l + t[k].r) >> 1;
	if(l <= mid && r <= mid) {
		return query(l, r, k<<1);
	} else if(l > mid) {
		return query(l, r, k<<1|1);
	} else {
		return max(query(l, mid, k<<1), query(mid+1, r, k<<1|1));
	}
}

void upDate(int a, int val, int k) {
	if(t[k].l == t[k].r) {
		t[k].maxn = val;
		return ;
	}
	int mid = (t[k].l + t[k].r) >> 1;
	if(a <= mid) {
		upDate(a, val, k<<1);
	} else {
		upDate(a, val, k<<1|1);
	}
	pushUp(k);
}
int main() {	
    ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	while(cin >> n >> m) {
		build(1, n, 1);
		for(int i = 0; i < m; i++) {
			char op;
			int a, b;
			cin >> op >> a >> b;
			if(op == 'Q') {
				cout << query(min(a,b), max(a,b), 1) << endl;
			} else {
				upDate(a, b, 1);
			}
		}
	}
	return 0;
}
