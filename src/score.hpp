#pragma once

#include <p6/p6.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>


void get_scoreboard(std::vector<int>& scoreboard);
void display_scoreboard(p6::Context &ctx);
void add_new_score(const int scores);
