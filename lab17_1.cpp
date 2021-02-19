#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string file, vector<string> &name, vector<int> &scores, vector<char> &grades){
    string textline;
    ifstream import;
    import.open(file);
    char readname[100];
    int a,b,c;
    while(getline(import,textline)){
      const char *text = textline.c_str();
      sscanf(text,"%[^:]: %d %d %d", readname, &a, &b, &c);
      name.push_back(readname);
      scores.push_back(a+b+c);
      grades.push_back(score2grade(a+b+c));
    }
    import.close();
}

void getCommand(string &comman, string &key){
  cout << "Please input your command: ";
  string input;
  char a[100],b[100];
  getline(cin,input);
  sscanf(input.c_str(),"%s %[^\n]",a,b);
  comman = a;key = b;
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
  int find;
  int detect = 0;
  cout << "---------------------------------\n";
  for(unsigned int i=0;i<names.size();i++){
    if(toUpperStr(names[i]) == key){
      find = i;
      detect++;
    }
    if(i == names.size()-1 && detect == 0){
      cout << "Cannot found." << endl;
      cout << "---------------------------------\n";
      return;
    }
  }
  cout << names[find] << "'s score = " << scores[find] << endl;
  cout << names[find] << "'s grade = " << grades[find] << endl;
  cout << "---------------------------------\n";
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
  cout << "---------------------------------\n";
  const char * find = key.c_str();
  int detect = 0;
  for(unsigned int i=0;i<names.size();i++){
    if(grades[i] == *find){
      cout << names[i] << " (" << scores[i] << ")" << endl;
      detect++;
    }
    if(i == names.size()-1 && detect == 0){
      cout << "Cannot found." << endl;
    }
  }
  cout << "---------------------------------\n";
}



int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}