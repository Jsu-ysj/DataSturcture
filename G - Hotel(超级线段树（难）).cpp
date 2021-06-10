/**
题目简介：
题目描述
奶牛们最近的旅游计划，是到苏必利尔湖畔，享受那里的湖光山色，以及明媚的阳光。作为整个旅游的策划者和负责人，
贝茜选择在湖边的一家著名的旅馆住宿。这个巨大的旅馆一共有N 间客房，它们在同一层楼中顺次一字排开，在任何一个
房间里，只需要拉开窗帘，就能见到波光粼粼的湖面。
贝茜一行，以及其他慕名而来的旅游者，都是一批批地来到旅馆的服务台，希望能订到D_i (1 <= D_i <= N)间连续的房间。
服务台的接待工作也很简单：如果存在r满足编号为r..r+D_i-1的房间均空着，他就将这一批顾客安排到这些房间入住；如果
没有满足条件的r，他会道歉说没有足够的空房间，请顾客们另找一家宾馆。如果有多个满足条件的r，服务员会选择其中最
小的一个。
旅馆中的退房服务也是批量进行的。每一个退房请求由2个数字X_i、D_i描述，表示编号为X_i..X_i+D_i-1 (1 <= X_i <= N-D_i+1)
房间中的客人全部离开。退房前，请求退掉的房间中的一些，甚至是所有，可能本来就无人入住。

而你的工作，就是写一个程序，帮服务员为旅客安排房间。你的程序一共需要处理M 个按输入次序到来的住店或退房的请求。
第一个请求到来前，旅店中所有房间都是空闲的。

输入格式
第一行输入n，m ，n代表有n个房间，编号为1---n，开始都为空房，m表示以下有m行操作，以下 每行先输入一个数 i ，
表示一种操作：
若i为1，表示查询房间，再输入一个数x，表示在1--n 房间中找到长度为x的连续空房，输出连续x个房间中左端的房间号，
尽量让这个房间号最小，然后入住。若找不到长度为x的连续空房，输出0。

若i为2，表示退房，再输入两个数 x，y 代表 房间号 x---x+y-1 退房，即让房间为空。

输出格式
对于每一个入住请求，输出查询出可以入住的最小房间号，如果不能安排入住输出0；

样例输入
10 6
1 3
1 3
1 3
1 3
2 5 5
1 6
样例输出
1
4
7
0
5
数据范围
1 <= N <= 50,000； 1 <= M < 50,000
**/


/**思路：
题意就是给你一段区间，让你每次标记一段，或者去掉一段的标记，
但是不能重复标记标记过的，每次标记给你一个长度x，要求长度为x的连续一段都要是空的，然后输出左端点。
难就难在：怎么统计连续的区间和跨越左右子树的区间。
因此需要维护三个值：
int sum;
int liftSum;
int rightSum;

这是比较麻烦的地方

然后用lazy 标记来更新下放值
lazy ==  0 表示不变
lazy == 1 表示全部为1
lazy == 2 表示全部为0

最后还需要关流即可（cin , cout >> 
**/

// 具体代码：
#include<iostream>
using namespace std;
const int N = 5*1e4 + 10;
struct tree {
	int sum;
	int liftSum;
	int rightSum;
	int l, r;
	int lazy;
} t[10*N];
int n, m;

void pushUp(int k) {
	t[k].liftSum = t[k<<1].liftSum;
	if(t[k<<1].liftSum == t[k<<1].r - t[k<<1].l + 1){
		t[k].liftSum += t[k<<1|1].liftSum;
	}
	
	t[k].rightSum = t[k<<1|1].rightSum;
	if(t[k<<1|1].rightSum == t[k<<1|1].r - t[k<<1|1].l + 1){
		t[k].rightSum += t[k<<1].rightSum; 
	}
	
	t[k].sum = max(t[k<<1].sum, t[k<<1|1].sum);
	t[k].sum = max(t[k].sum, t[k<<1|1].liftSum + t[k<<1].rightSum);
}
//初始化
void build(int k, int l, int r) {
	t[k].l = l, t[k].r = r;
	t[k].liftSum = t[k].rightSum = t[k].sum = r - l + 1;
	t[k].lazy = 0;
	if(l == r) {
		return ;
	}
	int mid = (t[k].l + t[k].r) >> 1;
	build(k << 1, l, mid);
	build(k<<1|1, mid+1, r);
}

//下放lazy标记
void pushDown(int k) {
	if(t[k].l == t[k].r) {
		return ;
	}
	if(t[k].lazy == 1) {
		t[k<<1].liftSum = t[k<<1].rightSum = t[k<<1].sum = t[k<<1].r - t[k<<1].l + 1;
		t[k<<1|1].liftSum = t[k<<1|1].rightSum = t[k<<1|1].sum = t[k<<1|1].r - t[k<<1|1].l + 1;
		t[k<<1].lazy = t[k<<1|1].lazy = t[k].lazy;
	} else if(t[k].lazy == 2) {
		t[k<<1].liftSum = t[k<<1].rightSum = t[k<<1].sum = 0;
		t[k<<1|1].liftSum = t[k<<1|1].rightSum = t[k<<1|1].sum = 0;
		t[k<<1].lazy = t[k<<1|1].lazy = t[k].lazy;
	}
	t[k].lazy = 0;
}


//更新房间状态
void upDate(int k, int l, int r, int lazy) {
	pushDown(k);
	if(t[k].l >=l && t[k].r <= r) {
		if(lazy == 1) {
			t[k].liftSum = t[k].rightSum = t[k].sum = t[k].r - t[k].l + 1;
		} else {
			t[k].liftSum = t[k].rightSum = t[k].sum = 0;
		}
		t[k].lazy = lazy;
		return ;
	}
	int mid = (t[k].l + t[k].r) >> 1;
	if(r <= mid) {
		upDate(k << 1, l, r, lazy);
	} else if(l > mid) {
		upDate(k << 1 | 1, l, r, lazy);
	} else {
		upDate(k << 1, l, mid, lazy);
		upDate(k << 1 | 1, mid + 1, r, lazy);
	}
//	if(l <= mid){
//		upDate(k << 1, l, r, lazy);
//	}
//	if(r > mid){
//		upDate(k << 1 | 1, l, r, lazy); 
//	}
	pushUp(k);
}


//查询房间标记
int query(int k, int d) {
	if(t[k].l == t[k].r) {
		return t[k].l;
	}
	pushDown(k);
	int mid = (t[k].l + t[k].r) >> 1;
	
	if(t[k << 1].sum >= d) {
		return query(k << 1, d);
	} else if(t[k<<1].rightSum + t[k<<1|1].liftSum >= d) {
		return mid - t[k<<1].rightSum + 1;
	} else {
		return query(k<<1|1, d);
	}
}


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	build(1, 1, n);
	for(int i = 1; i <= m; i ++) {
		int op;
		cin >> op;
		if(op == 1) {
			int d;
			cin >> d;
			//操作2表示全部改成0
			if(t[1].sum < d) {
				cout << 0 << endl;
			} else {
				int r =  query(1, d);
				cout << r << endl;
				upDate(1, r, r+d-1, 2);
			}
		} else if(op == 2) {
			int st, d;
			cin >> st >> d;
			// 操作数字1表示该范围内都是1
			upDate(1, st, st+d-1, 1);
		}
	}
	return 0;
}
