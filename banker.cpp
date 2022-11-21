#include <iostream>
#include <fstream>

using namespace std;

const int P = 5;
const int R = 3;

void calculateNeed(int need[P][R], int max[P][R], int alloted[P][R]){
    for(int i = 0; i < P; i++)
        for(int j = 0; j < R; j++)
            need[i][j] = max[i][j] - alloted[i][j];
}

bool safe(int processes[], int available[], int max[][R], int alloted[][R]){
    int need[P][R];
    calculateNeed(need, max, alloted);
    bool fin[P] = {0};
    int sequence[P];
    int work[R];
    for(int i = 0; i < R; i++)
        work[i] = available[i];
    int count = 0;
    while(count < P){
        bool found = false;
        for(int p = 0; p < P; p++){
            if(fin[p] == 0){
                int j;
                for(j = 0; j < R; j++)
                    if(need[p][j] > work[j])
                        break;
                if(j == R){
                    for(int k = 0; k < R; k++)
                        work[k] += alloted[p][k];
                    sequence[count++] = p;
                    fin[p] = true;
                    found = true;
                }
            }
        }
        if(found == false){
            cout << "System is not in safe state";
            return false;
        }
    }
    cout << "System is in safe state.\nSafe sequence is: ";
    for(int i = 0; i < P; i++) 
        cout << sequence[i] << " ";
    
    return true;
}

int main(){
    char input; int num;
    int processes[P]; int available[R];
    int max[P][R]; int alloted[P][R];
    ifstream file;
    file.open("input.txt");
    while(file.get(input)){
        for(int i = 0; i < P; i++){
            num = input - '0';
            processes[i] = num;
            file.get(input);
        }
        cout << endl;
        for(int i = 0; i < R; i++){
            num = input - '0';
            available[i] = num;
            file.get(input);
        }
        cout << endl;
        for(int i = 0; i < P; i++){
            for(int j = 0; j < R; j++){
                num = input - '0';
                max[i][j] = num;
                file.get(input);
            }
        }
        cout << endl;
        for(int i = 0; i < P; i++){
            for(int j = 0; j < R; j++){
                num = input - '0';
                alloted[i][j] = num;
                file.get(input);        
            }
        }
    }
    file.close();
    safe(processes, available, max, alloted);
    return 0;
    
}