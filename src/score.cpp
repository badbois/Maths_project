#include "score.hpp"
#include <sstream>

void get_scoreboard(std::vector<int>& scoreboard) {
    std::ifstream file;
    try{
        file.open("./assets/scoreboard.txt", std::ios::in);
        int score;
        while(file >> score){
            scoreboard.push_back(score);
        }
        file.close();
    }
    catch(std::exception &e){
        std::cout << "Error while opening file" << std::endl;
    }
} 


void add_new_score(const int score){
    std::vector<int> scoreboard;
    get_scoreboard(scoreboard);
    for(int i=0; i<scoreboard.size(); i++){
        if(scoreboard[i]<score){
            scoreboard.insert(scoreboard.begin()+i,score);
            break;
        }
    }

    std::ofstream file;
    try{
        file.open("./assets/scoreboard.txt", std::ios::out);
        for(int i=0; i<3; i++){
            file << scoreboard[i] << std::endl;
        }
        file.close();
    }
    catch(std::exception &e){
        std::cout << "Error while opening file" << std::endl;
    }
}