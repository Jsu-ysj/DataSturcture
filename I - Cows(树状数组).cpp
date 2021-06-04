/**
Farmer John's cows have discovered that the clover growing along the ridge of the hill (which we can 
think of as a one-dimensional number line) in his field is particularly good.

Farmer John has N cows (we number the cows from 1 to N). Each of Farmer John's N cows has a range of 
clover that she particularly likes (these ranges might overlap). The ranges are defined by a closed interval [S,E].

But some cows are strong and some are weak. Given two cows: cow i and cow j, their favourite clover 
range is [Si, Ei] and [Sj, Ej]. If Si <= Sj and Ej <= Ei and Ei - Si > Ej - Sj, we say that cow i is stronger than cow j.

For each cow, how many cows are stronger than her? Farmer John needs your help!
题目翻译

农夫约翰的牛发现，他的田地里沿着山脊生长的三叶草（我们可以将其视为一维数字线）特别好。

农夫约翰有N头母牛（我们将母牛的编号从1到N）。每位农夫约翰的N头母牛都有她特别喜欢的三叶草范围（这些范围可能重叠）。范围由闭合间隔[S，E]定义。

但是有些母牛很强壮，有些却很弱。给定两个母牛：母牛i和母牛j，它们最喜欢的三叶草范围是[Si，Ei]和[Sj，Ej]。如果Si <= Sj并且Ej <= Ei并且Ei-Si> Ej-Sj，我们说母牛i比母牛j强。

对于每头母牛，有几头母牛比她强？农夫约翰需要您的帮助！

输入项

输入包含多个测试用例。

对于每个测试用例，第一行是整数N（1 <= N <= 10 ^ 5），它是母牛的数量。然后是N行，其第i行包含两个整数：S和E（0 <= S<=E<=1e5 )

输入的末尾包含单个0。

输出量

对于每个测试用例，输出一行包含n个以空格分隔的整数，其中第i个数字指定比母牛i强的母牛的数量。

Sample Input

3

1 2

0 3

3 4

0

Sample Output

1 0 0

Hint

Huge input and output,scanf and printf is recommended.

Input
The input contains multiple test cases.
For each test case, the first line is an integer N (1 <= N <= 10 5), which is the number of cows. Then come N lines, the i-th of which contains two integers: S and E(0 <= S < E <= 10 5) specifying the start end location respectively of a range preferred by some cow. Locations are given as distance from the start of the ridge.

The end of the input contains a single 0.
Output
For each test case, output one line containing n space-separated integers, the i-th of which specifying the number of cows that are stronger than cow i.
Sample Input
3
1 2
0 3
3 4
0
Sample Output
1 0 0
**/

/**思路：
将区段按照结尾段进行排序，这样根据尾时间只要查询前面的数即可；
bool cmp(node x1, node x2) {
	if(x1.e == x2.e) {
		return x1.s < x2.s;
	}
	return x1.e > x2.e;
}
然后就是树状数组更新前缀和；
还要注意不要从0开始
//具体代码：
/**
	树状数组题目
**/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 1e5 + 10;
struct node {
	int e, s, id;
} niu[N];
int t[N];
int ans[N];
int n;

bool cmp(node x1, node x2) {
	if(x1.e == x2.e) {
		return x1.s < x2.s;
	}
	return x1.e > x2.e;
}

int lowbit(int x) {
	return x&-x;
}

int getsum(int x) {
	int sum = 0;
	while(x > 0) {
		sum += t[x];
		x -= lowbit(x);
	}
	return sum;
}

void add(int x) {
	while(x < N) {
		t[x] += 1;
		x += lowbit(x);
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	while(cin >> n) {
		if(n == 0){
			break;
		}
		memset(t, 0, sizeof(t));
		memset(ans, 0, sizeof(ans));
		for(int i = 1; i <= n; i ++) {
			cin >> niu[i].s >> niu[i].e;
			niu[i].s ++;
			niu[i].e ++; // 避免0出现，干扰数组运行
			niu[i].id = i; //记下序号
		}
		sort(niu + 1, niu + 1 + n, cmp);
		ans[niu[1].id] = getsum(niu[1].s);
		add(niu[1].s);
		for(int i = 2; i <= n; i ++) {
			if(niu[i].e == niu[i-1].e && niu[i].s == niu[i-1].s) {
				ans[niu[i].id] = ans[niu[i-1].id];
			} else {
				ans[niu[i].id] = getsum(niu[i].s);
			}
			add(niu[i].s);
		}
		for(int i = 1; i <= n; i ++) {
			cout << ans[i] << " ";
		}
		cout<<endl;
	}
	return 0;
}











