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

void importDataFromFile(string filename,vector<string> &names,vector<int> &scores,vector<char> &grades){
    ifstream File(filename);
    string name;
    char Name[100];
    int a,b,c;
    char format[] = "%[^:]: %d %d %d";
    while (getline(File,name))
    {
        sscanf(name.c_str(),format,Name,&a,&b,&c);
        names.push_back(Name);
        scores.push_back(a+b+c);
        grades.push_back(score2grade(a+b+c));
    }
}

void getCommand(string &command,string &key){
    cout << "Please input your command: " ;
    string text;
    getline(cin,text);
    char format[] = "%s %[^:]";
    char textcmd[10] , textkey[100]; 
    sscanf(text.c_str(),format,textcmd,textkey);
    command = textcmd;
    key = textkey;
}

void searchName(vector<string> names,vector<int> scores,vector<char> grades,string key){
    int N = names.size();
    bool check = false;
    cout << "---------------------------------\n";
    for(int i=0;i<N;i+=1){
        if(key == toUpperStr(names[i])){
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            check = true;
        }
    }
    if(check == false){cout << "Cannot found." << endl;}
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> names,vector<int> scores,vector<char> grades,string key){
    string x;
    bool check = false;
    int N = grades.size();
    cout << "---------------------------------\n";
    for(int i=0;i<N;i+=1){
        x = grades[i];
        if(key == toUpperStr(x)){
            cout << names[i] << " (" << scores[i] << ")" << endl;
            check = true;
        }
    }if(check == false){cout << "Cannot found." << endl ;}
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
