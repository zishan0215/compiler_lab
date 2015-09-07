#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

void print_mat(int, vector< vector<int> >, vector< vector<int> >);
void mealy(int, vector< vector<int> >, vector< vector<int> >);

int main() {
	string line;
	int start;
	vector< vector<int> >mat;
	vector< vector<int> >out;

	ifstream fin("mealy.txt");

	// Take inputs
	if(fin.is_open()) {
		getline(fin, line);
		start = line[0] - '0';
		while(getline(fin, line)) {
			vector<int> row_m;
			vector<int> row_o;
			int tr = 1;
			for(int i=0;i<line.length();i++) {
				if(line[i]!= ' ') {
					if(tr) {
						row_m.push_back(line[i] - '0');
						tr = 0;
					} else {
						row_o.push_back(line[i] - '0');
						tr = 1;
					}
				}
			}
			mat.push_back(row_m);
			out.push_back(row_o);
		}
	}

	print_mat(start, mat, out);

	mealy(start, mat, out);
}

void print_mat(int start, vector< vector<int> >mat, vector< vector<int> >out) {
	cout<<endl;
	cout<<"Inital state: "<<start<<endl;
	cout<<"Transition Matrix: "<<endl;
	for(int i=0;i<mat.size();i++) {
		vector<int> row = mat[i];
		for(int j=0;j<row.size();j++) {
			cout<<row[j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	cout<<"Output Matrix: "<<endl;
	for(int i=0;i<out.size();i++) {
		vector<int> row = out[i];
		for(int j=0;j<row.size();j++) {
			cout<<row[j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

void mealy(int start, vector< vector<int> >mat, vector< vector<int> >out) {
	string line;
	cout<<endl;
	cout<<"Enter line: ";
	getline(cin, line);
	int prev = start;
	cout<<"Output: ";
	for(int i = 0; i<line.length(); i++) {
		int cur = line[i] - 'a';
		cout<<out[prev][cur];
		prev = mat[prev][cur];
	}
	cout<<endl;
}