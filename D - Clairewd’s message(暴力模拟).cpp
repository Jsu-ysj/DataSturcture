/**题目简介：
给你有26个字母的密码表，a[i]表示第i个字母经过密码表转变成的密码字符。（如a[2]==‘c’，表示字母‘b’加密后变成‘c’）
现在有一条信息，前一半为经过加密的字符，后一半为前一半加密前的字符。不过由于某些原因，后一半的部分内容消失了，你现在的任务是，恢复整条信息的内容。
Input
The first line contains only one integer T, which is the number of test cases.
Each test case contains two lines. The first line of each test case is the conversion table S.
S[i] is the ith latin letter's cryptographic letter. The second line is the intercepted text which has n letters that you should recover. 
It is possible that the text is complete.
Hint
Range of test data:
T<= 100 ;
n<= 100000;
Output
For each test case, output one line contains the shorest possible complete text.
Sample Input
2
abcdefghijklmnopqrstuvwxyz
abcdab
qwertyuiopasdfghjklzxcvbnm
qwertabcde
Sample Output
abcdabcd
qwertabcde
**/

/**思路：
先解码， 再用解开的码， 来从中间开始遍历s2， 用密码匹配， 得到最长；
for(int i=mid; i<len; i++) {
			if(s1[s2[i]-'a']!=s2[l]) continue;
			else {
				flag=0;
				l ++;
				for(int j=i+1; j<len; j++)
					if(s1[s2[j]-'a']!=s2[l++]) {
						flag=1;
						break;
					}
				if(flag==0){
					okcnt = i; 
					break;
				}   
			}
		}
**/

// 具体代码：
#include<bits/stdc++.h> 
using namespace std;
int main() {
	int n, len, i, j, flag;
	string s1, s2;
	cin >> n;
	while(n--) {
		cin >> s1 >> s2;
		len=s2.length();
		int l = 0;
		int okcnt = 0;
		//int mid = (len+1)/2;
		int mid = (len+1) >> 1;
		for(int i=mid; i<len; i++) {
			if(s1[s2[i]-'a']!=s2[l]) continue;
			else {
				flag=0;
				l ++;
				for(int j=i+1; j<len; j++)
					if(s1[s2[j]-'a']!=s2[l++]) {
						flag=1;
						break;
					}
				if(flag==0){
					okcnt = i; 
					break;
				}   
			}
		}
		for(int i = 0; i < okcnt; i ++)
			printf("%c",s2[i]);
		for(int i = 0; i < okcnt; i ++) {
			for(j = 0; j < 26; j ++)
				if(s2[i]==s1[j])
					printf("%c",j+'a');
		}
		cout << endl;
	}
	return 0;
}
