#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

void display(int, vector<int>, vector< vector< vector<int> > >);
void compute(int, vector<int>, vector< vector< vector<int> > >&);
void display_row(vector< vector<int> >);
void display_one(vector<int>);
int exists(vector< vector<int> >, vector<int>);

int main() {
    int start;
    string line;
    vector<int> final;
    vector< vector< vector<int> > > mat;
    ifstream fin("nfa.txt");
    if(fin.is_open()) {
        getline(fin, line);
        
        // Get initial state
        start = line[0] - 48;
        getline(fin, line);
        
        // Get final states
        for (int i=0; i<line.length(); i++) {
            if(line[i] != ' ') {
                final.push_back((int)(line[i] - 48));
            }
        }
        
        // Get rest of the inputs
        while(getline(fin, line)) {
            vector< vector<int> >row;
            vector<int> one;
            for (int i=0; i<line.length(); i++) {
                //cout<<"Line length: "<<line.length()<<endl;
                if(line[i] != ' ') {
                    if(line[i] == '-') {
                        one.push_back(-1);
                        //cout<<"Pushing: "<<one[one.size()-1]<<endl;
                        i++;
                    } else if(line[i] != ',') {
                        one.push_back((int)(line[i]-48));
                        //cout<<"Pushing: "<<one[one.size()-1]<<endl;
                    }
                    if(i == line.length()-1) {
                        row.push_back(one);
                    }
                } else {
                    row.push_back(one);
                    one.clear();
                }
            }
            
            mat.push_back(row);
            
        }
    }

    display(start, final, mat);
    compute(start, final, mat);
    
    fin.close();
    return 0;
}

void display(int start, vector<int> final, vector< vector< vector<int> > >mat) {
	// Print initial state
	cout<<"Inital state: "<<start<<endl;

	// Print final states
    cout<<"Final States: ";
    for (int i=0; i<final.size(); i++) {
        cout<<final[i]<<" ";
    }
    cout<<endl;
    
    // Print matrix
    cout<<"Matrix:"<<endl;
    for (int i=0; i<mat.size(); i++) {
        vector< vector<int> > row = mat[i];
        for (int j=0; j<row.size(); j++) {
            vector<int> one = row[j];
            for (int k=0; k<one.size(); k++) {
                cout<<one[k]<<",";
            }
            cout<<" ";
        }
        cout<<endl;
    } 
}

void display_row(vector< vector<int> > row) {
	cout<<"Inputting row: ";
	for (int j=0; j<row.size(); j++) {
        vector<int> one = row[j];
        for (int k=0; k<one.size(); k++) {
            cout<<one[k]<<",";
        }
        cout<<" ";
    }
    cout<<endl;
}

void display_one(vector<int> one) {
	cout<<"One: ";
	for (int k=0; k<one.size(); k++) {
        cout<<one[k]<<",";
    }
    cout<<endl;
}

int exists(vector< vector<int> > pushing, vector<int> one) {
	int flag;
	for(int i=0;i<pushing.size();i++) {
		vector<int> temp = pushing[i];
		flag = 0;
		if(temp.size() != one.size()) {
			continue;
		}
		for (int j = 0; j < temp.size(); ++j) {
			if(temp[j] == one[j]) {
				flag = 1;
			} else {
				flag = 0;
				break;
			}
		}
		if(flag == 1) {
			return 1;
		}
	}
	return 0;
}

int find_element(vector<int> one, int el) {
	for(int i=0;i<one.size();i++) {
		if(one[i] == el) {
			return 1;
		}
	}
	return 0;
}

void compute(int start, vector<int> final, vector< vector< vector<int> > >&mat) {
	cout<<endl<<"Converting to DFA"<<endl;
	vector< vector<int> > pushing;
	for (int i=0; i<mat.size(); i++) {
        vector< vector<int> > row = mat[i];
        for (int j=0; j<row.size(); j++) {
            vector<int> one = row[j];
            if(one.size() > 1) {
            	// Check if this combination has been pushed already or not
            	if(exists(pushing, one)) {
            		continue;
            	}
            	// display_one(one);
            	vector< vector<int> > temp_d;
            	int index;
            	for(int a=0;a<one.size();a++) {
            		int mat_i = one[a];
            		vector< vector<int> > temp_mat = mat[mat_i];
            		for(int b=0;b<temp_mat.size();b++) {
            			vector<int> temp_s;
            		
            			if(a != 0) {
            				temp_s = temp_d[b];
	            		}
            			vector<int> temp_row = temp_mat[b];
            			// display_one(temp_row);
            			if(a == 0) {
            				vector<int> x;
            				for(int z=0;z<temp_row.size();z++) {
            					if(temp_row[z] != -1) {
            						x.push_back(temp_row[z]);
            					}
            				}
            				temp_d.push_back(x);
            				index = temp_d.size() - 1;	
            			} else {
            				for(int c=0;c<temp_row.size();c++) {
            					if(!find_element(temp_s, temp_row[c])) {
            						if(temp_row[c] != -1) {
            							temp_s.push_back(temp_row[c]);
            						}	
            					}
            				}
            				int ti = index - 1 + b;
            				// display_one(temp_s);
            				temp_d.erase(temp_d.begin() + ti);
            				temp_d.insert(temp_d.begin() + ti, temp_s);
            			}
            			
            		}
            	}
            	// display_row(temp_d);
            	mat.push_back(temp_d);
            	// cout<<"Pushing: ";
            	// display_one(one);
            	pushing.push_back(one);
            	//one.clear();
            	//one.push_back(state);
            }
        }
    }
    display(start, final, mat);
}