#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

void display(int, vector<int>, vector< vector<int> >);
void moore(int, vector<int>, vector< vector<int> >);

int main() {
	int start;
	vector<int> out;
	vector< vector<int> >mat;
	string line;
	ifstream fin("moore.txt");

	if(fin.is_open()) {
		getline(fin, line);
		start = line[0] - '0';
		while(getline(fin, line)) {
			vector<int> row;
			for(int i=0;i<line.length();i++) {
				if(i == line.length() - 1) {
					out.push_back(line[i] - '0');
				}
				else if(line[i] != ' ') {
					row.push_back(line[i] - '0');
				}
			}
			mat.push_back(row);
		}
	}
	display(start, out, mat);
	moore(start, out, mat);
	return 0;
}

void display(int start, vector<int> out, vector< vector<int> >mat) {
	cout<<endl;
	cout<<"Initial state: "<<start;
	cout<<"Transition Matrix:"<<endl;
	for(int i=0; i<mat.size();i++) {
		vector<int> row = mat[i];
		for(int j=0;j<row.size();j++) {
			cout<<row[j]<<" ";
		}
		cout<<endl;
	}
	cout<<"Output Matrix:"<<endl;
	for(int i=0;i<out.size();i++) {
		cout<<out[i]<<endl;
	}
}

void moore(int start, vector<int> out, vector< vector<int> >mat) {
	string line;
	cout<<"Enter string: ";
	getline(cin, line);
	int prev = 0;
	cout<<"Output: ";
	for(int i=0;i<line.length();i++) {
		int cur = line[i] - 'a';
		cout<<out[prev];
		prev = mat[prev][cur];
	}
	cout<<out[prev]<<endl;
}