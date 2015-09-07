#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

void display(int, vector<int>, vector< vector<int> >);
void convert(int, vector<int>, vector< vector<int> >);
void display_moore(int, vector<int>, vector< vector<int> >);
void display_mealy(int, vector< vector<int> >, vector< vector<int> >);

int main() {
	string line;
	int start;
	vector<int> out;
	vector< vector<int> >mat;
	ifstream fin("mre_to_mly.txt");

	if(fin.is_open()) {
		getline(fin, line);
		start = line[0] - '0';
		while(getline(fin, line)) {
			vector<int> row;
			for(int i=0;i<line.length();i++) {
				if(i == line.length() - 1) {
					out.push_back(line[i] - '0');
				} else {
					if(line[i] != ' ') {
						row.push_back(line[i] - '0');
					}
				}
			}
			mat.push_back(row);
		}
	}

	display_moore(start, out, mat);

	convert(start, out, mat);

	return 0;
}

void display_moore(int start, vector<int> out, vector< vector<int> >mat) {
	cout<<endl;
	cout<<"Initial state: "<<start<<endl;
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

void display_mealy(int start, vector< vector<int> >out, vector< vector<int> >mat) {
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


void convert(int start, vector<int> out, vector< vector<int> >mat) {
	vector< vector<int> >out_ml;
	for(int i=0;i<mat.size();i++) {
		vector<int> row = mat[i];
		vector<int> row_ml;
		for(int j=0;j<row.size();j++) {
			 row_ml.push_back(out[row[j]]);
		}
		out_ml.push_back(row_ml);
	}
	display_mealy(start, out_ml, mat);
}