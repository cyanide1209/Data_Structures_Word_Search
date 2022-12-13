//  Created by cyanide1209 on 11/28/22.



#include <iostream>
#include <cstdlib>
#include <unordered_set>
#include <fstream>
#include <vector>
using namespace std;

unordered_set<string> dictionarySetup(int& largest){
    largest = 0;
    unordered_set<string> u;
    ifstream file;
    file.open("words.txt");
    if(!file.is_open()){
    cout<<"Unable to open the file."<<endl;
        return u;
    }
    else{
        string line;
        bool alphaOnly;
        while(getline(file,line)){
            if(line.length()>=6){
                alphaOnly = true;
                for(int i = 0;i<line.length();i++){
                    if(isupper(line[i])){
                        tolower(line[i]);
                    }
                    if(alphaOnly){
                        alphaOnly = isalpha(line[i]);
                    }
                }
                if(alphaOnly){
                    u.insert(line);
                    if(line.length()>largest){
                        largest = line.length();
                    }
                }
            }
        }
    }
    file.close();
    return u;
}

class answer{
public:
    answer(string word_,int initfirst_,int initsecond_,int endfirst_,int endsecond_){
        word = word_;
        initfirst = initfirst_;
        initsecond = initsecond_;
        endfirst = endfirst_;
        endsecond = endsecond_;
    }
    string getWord(){return word;}
    int getInitFirst(){return initfirst;}
    int getInitSecond(){return initsecond;}
    int getEndFirst(){return endfirst;}
    int getEndSecond(){return endsecond;}
private:
    string word;
    int initfirst;
    int initsecond;
    int endfirst;
    int endsecond;

};

vector<answer> puzzleSolve(unordered_set<string> dictionary, int largest){
    //puzzle setup
    fstream file;
    int i=0,j=0;
    vector<answer> v;
    file.open("puzzle.txt");
    string s;
    getline(file,s);
    int size=0;
    for(int i = 0;i<s.length();i++){
        if(isalpha(s[i])){
            size++;
        }
    }
    char c;
    char puzzle[size][size];
    file.close();
    file.open("puzzle.txt");
    while(file >> c){
        puzzle[i][j] = c;
        j++;
        if(j>size-1){
            j=0;
            i++;
        }
    }
    //test the point
    for(int i = 0;i<size;i++){
        for(int j = 0;j<size;j++){
            bool N=false,NE=false,E=false,SE=false,S=false,SW=false,W=false,NW=false;
            for(int k = 6;k<largest;k++){
                //check N
                int a = i;
                int b = j;
                if(i>=5 && !N){
                    string test;
                    for(int l = 0;l<k && a>=0;l++){
                        test = test+puzzle[a][b];
                        a--;
                    }
                    if(dictionary.find(test)!=dictionary.end()){
                        answer temp(test,i,j,a+1,b);
                        v.push_back(temp);
                        if(a<0||a>size-1||b<0||b>size-1){
                            N = true;
                        }
                    }
                    a=i;
                    b=j;
                }
                //check NW
                if(i>=5 && j>=5 && !NW){
                    string test;
                    for(int l = 0;l<k && a>=0 && b>=0;l++){
                        test = test+puzzle[a][b];
                        a--;
                        b--;
                    }
                    if(dictionary.find(test)!=dictionary.end()){
                        answer temp(test,i,j,a+1,b+1);
                        v.push_back(temp);
                        if(a<0||a>size-1||b<0||b>size-1){
                            NW = true;
                        }
                    }
                    a=i;
                    b=j;
                }
                //check W
                if(j>=5 && !W){
                    string test;
                    for(int l = 0;l<k && b>=0;l++){
                        test = test+puzzle[a][b];
                        b--;
                    }
                    if(dictionary.find(test)!=dictionary.end()){
                        answer temp(test,i,j,a,b+1);
                        v.push_back(temp);
                        if(a<0||a>size-1||b<0||b>size-1){
                            W = true;
                        }
                    }
                    a=i;
                    b=j;
                }
                //check SW
                if(j>=5 && i<=size-6 && !SW){
                    string test;
                    for(int l = 0;l<k && a<size-1 && b>=0;l++){
                        test = test+puzzle[a][b];
                        a++;
                        b--;
                    }
                    if(dictionary.find(test)!=dictionary.end()){
                        answer temp(test,i,j,a-1,b+1);
                        v.push_back(temp);
                        if(a<0||a>size-1||b<0||b>size-1){
                            SW = true;
                        }
                    }
                    a=i;
                    b=j;
                }
                //check S
                if(i<=size-6 && !S){
                    string test;
                    for(int l = 0;l<k && a<=size-1;l++){
                        test = test+puzzle[a][b];
                        a++;
                    }
                    if(dictionary.find(test)!=dictionary.end()){
                        answer temp(test,i,j,a-1,b);
                        v.push_back(temp);
                        if(a<0||a>size-1||b<0||b>size-1){
                            S = true;
                        }
                    }
                    a=i;
                    b=j;
                }
                //check SE
                if(i<=size-6 && j<=size-6 && !SE){
                    string test;
                    for(int l = 0;l<k && a<=size-1 && b<=size-1;l++){
                        test = test+puzzle[a][b];
                        a++;
                        b++;
                    }
                    if(dictionary.find(test)!=dictionary.end()){
                        answer temp(test,i,j,a-1,b-1);
                        v.push_back(temp);
                        if(a<0||a>size-1||b<0||b>size-1){
                            SE = true;
                        }
                    }
                    a=i;
                    b=j;
                }
                //check E
                if(j<=size-6 && !E){
                    string test;
                    for(int l = 0;l<k && b<=size-1;l++){
                        test = test+puzzle[a][b];
                        b++;
                    }
                    if(dictionary.find(test)!=dictionary.end()){
                        answer temp(test,i,j,a,b-1);
                        v.push_back(temp);
                        if(a<0||a>size-1||b<0||b>size-1){
                            E = true;
                        }
                    }
                    a=i;
                    b=j;
                }
                //check NE
                if(i>=5 && j<=size-6 && !NE){
                    string test;
                    for(int l = 0;l<k && a>=0 && b<=size-1;l++){
                        test = test+puzzle[a][b];
                        a--;
                        b++;
                    }
                    if(dictionary.find(test)!=dictionary.end()){
                        answer temp(test,i,j,a+1,b-1);
                        v.push_back(temp);
                        if(a<0||a>size-1||b<0||b>size-1){
                            NE = true;
                        }
                    }
                    a=i;
                    b=j;
                }
            }
        }
    }
    return v;
}

vector<answer> insertionSort(vector<answer> input, int size){
    //end w least to greatest
    int j = 0;
    for(;j<size;j++){
        while(input[j].getWord()<input[j-1].getWord()){
            answer temp = input[j-1];
            input[j-1] = input[j];
            input[j] = temp;
            j--;
        }
    }
    return input;
}


int main(){
    int largest;
    unordered_set<string> dictionary = dictionarySetup(largest);
    vector<answer> v = puzzleSolve(dictionary, largest);
    v = insertionSort(v, v.size());
    for(int i = 0;i<v.size();i++){
        cout<<v[i].getWord()<<" was found at ["<<v[i].getInitFirst()<<"]["<<v[i].getInitSecond()<<"] to ["<<v[i].getEndFirst()<<"]["<<v[i].getEndSecond()<<"]"<<endl;
    }
    
}
