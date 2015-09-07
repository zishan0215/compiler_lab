#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

void print_matrix(vector< vector<int> >);

void automata(int, vector<int>, vector< vector<int> >);

int main() {
	string line;
	int start;
	vector<int> final;
	vector< vector<int> >mat;
	ifstream fin("fa.txt");
	if(fin.is_open()) {
		getline(fin, line);
		start = line[0] - '0';
		getline(fin, line);
		for(int i=0;i<line.length();i++) {
			if(line[i]!=' ' && line[i] != '\n') {
				final.push_back(line[i] - '0');
			}
		}
		while(getline(fin, line)) {
			vector<int> row;
			for(int i=0;i<line.length();i++) {
				if(line[i] == '-') {
					i+=2;
					row.push_back(-1);
				}
				if(line[i]!=' ') {
					row.push_back(line[i] - '0');
				}

			}
			mat.push_back(row);
		}
	}

	cout<<endl<<"Initial State: "<<start<<endl;
	cout<<endl<<"Final States: ";
	for(int i=0;i<final.size();i++) {
		cout<<final[i]<<" ";
	}
	cout<<endl;
	print_matrix(mat);

	automata(start, final, mat);

	return 0;
}

void print_matrix(vector< vector<int> > mat) {
	cout<<endl<<"Matrix: "<<endl;
	for(int i=0;i<mat.size();i++) {
		vector<int> v = mat[i];
		for(int j=0;j<v.size();j++) {
			cout<<v[j]<<" ";
		}
		cout<<endl;
	}
}

int find_final(vector<int> final, int next) {
	for(int i=0;i<final.size();i++) {
		if(final[i] == next) {
			return 1;
		}
	}
	return 0;
}

void automata(int start, vector<int> final, vector< vector<int> > mat) {
	string line;
	int prev = 0;
	int next;
	cout<<"Enter line: ";
	getline(cin, line);
	for(int i=0;i<line.length();i++) {
		int cur = line[i] - 'a';
		next = mat[prev][cur];
		if(i == line.length() - 1) {
			if(find_final(final, next)) {
				cout<<"Accepted"<<endl;
				break;
			} else {
				cout<<"Not accepted"<<endl;
			}
		}
		if(next == -1) {
			cout<<"Not accepted"<<endl;
		}
		prev = next;
	}
}