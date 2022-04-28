#include "score.hpp"


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

void display_scoreboard(p6::Context &ctx){
    std::vector<int> scoreboard;
    get_scoreboard(scoreboard);
    ctx.background({0.f, 0.f, 0.f});
    ctx.fill = {1., 1., 1., 1};
    std::vector<std::u16string> scores;
    for(int i = 0; i < scoreboard.size(); i++) {
        std::string score_string = std::to_string(scoreboard[i]);
    std::u16string score_u16string = std::u16string(score_string.begin(),
                                                    score_string.end());
        scores.push_back(score_u16string);
    }
    ctx.text_size = 0.04f;
    ctx.text(u"Scoreboard", p6::Center{0.f, 0.4f});
    ctx.text(u"1: "+ scores[0], p6::Center{0.f, 0.2f});
    ctx.text(u"2: "+ scores[1], p6::Center{0.f, 0.f});
    ctx.text(u"3: "+ scores[2], p6::Center{0.f, -0.2f});

    ctx.text_size = 0.02f;
    ctx.text(u"retour:M", p6::Center{0.8f, 0.9f});



    
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