#include<iostream>
#include <map>

using namespace std;

map <long long int, long long int> m;


int findDp(long long int num) {
	// cout << "finding dp of num " << num << endl;
	if (m.find(num) != m.end())
		return m[num];
	int cycle;
	if(num%2 == 0) {
		cycle = findDp(num/2);
	} else {
		cycle = findDp(3*num+1);
	}
	m[num] = cycle + 1;
	return m[num];
}

int findMax(long long int num1, long long int num2) {
	long long int ans = 0;
	if (num1 > num2)
		swap(num1, num2);
	for(long long int i = num1; i <= num2; i++) {
		if (m.find(i) == m.end()) {
			m[i] = findDp(i);
		}
		// cout << " dp of i " << i << " " << m[i] << endl;
		ans = max(ans, m[i]);
	}
	return ans;
}

int main() {
	m[0] = 0;
	m[1] = 1;
	long long int num1, num2;
	while (scanf("%lld %lld", &num1, &num2) != EOF) {
		long long int ans = findMax(num1, num2);
		printf("%lld %lld %lld\n", num1, num2, ans);
	}
	return 0;
}

