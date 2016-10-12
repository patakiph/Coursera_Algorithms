#include <iostream>
#include <vector>
#include <fstream>
#define SIZE 100000
using namespace std;
long long cnt = 0;

vector<int> merge(vector<int> & left, vector<int> & right) {
	int i = 0, j = 0;
	int n = left.size();
	int m = right.size();
	vector<int> merged(n + m);
	for (int k = 0; k < n + m; k++) {
		if (j >= m || (i < n && left[i] <= right[j])) {
			merged[k] = left[i];
			i++;
		}
		else { //right[j] < left[i]
			merged[k] = right[j];
			j++;
			cnt += left.size() - i;
		}
	}
	return merged;
}

vector<int> mergeSort(vector<int> & a) {
	if (a.size() == 1) return a;
	vector<int> left(a.size() / 2);
	vector<int> right(a.size() - left.size());
	for (int i = 0; i < left.size(); i++) {
		left[i] = a[i];
	}
	for (int i = left.size(); i < a.size(); i++) {
		right[i - left.size()] = a[i];
	}
	left = mergeSort(left);
	right = mergeSort(right);
	return merge(left, right);
}

int main() {
	vector<int> v(SIZE);
	char buf[7];
	ifstream fin("coursera_task1.txt");
	if (!fin.is_open()) // если файл не открыт
		cout << "Файл не может быть открыт!\n"; // сообщить об этом
	for (int i = 0; i < SIZE; i++) {
		fin >> buf;
		v[i] = atoi(buf);
	}
	v = mergeSort(v);
	cout << endl;
	cout << cnt;
	fin.close();
	return 0;
}