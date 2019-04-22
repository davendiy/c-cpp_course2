// Created by David Zashkolny on 21.04.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main(){
    fstream file("input.txt", ios::in | ios::out);

    if (!file.is_open()){
        cout << "Could not open the file";
        return 0;
    }

    int new_high_score;
    cout << "New high score: ";
    cin >> new_high_score;

    streampos pre_score_pos = file.tellg();
    int cur_score;
    while(file >> cur_score){
        if (cur_score < new_high_score){
            break;
        }
        pre_score_pos = file.tellg();
    }

    if (file.fail() && !file.eof()){
        cout << "Bad score/read--exiting";
        return 0;
    }

    file.clear();
    file.seekg(pre_score_pos);

    vector<int> scores;
    while (file >> cur_score){
        scores.push_back(cur_score);
    }

    if (!file.eof()){
        cout << "Bad score/read--exiting";
        return 0;
    }

    file.seekp(pre_score_pos);
    if (pre_score_pos != std::streampos(0)){
        file << endl;
    }
    file << new_high_score << endl;

    for (vector<int>::iterator itr = scores.begin(); itr != scores.end(); ++itr){
        file << *itr << endl;
    }

}
