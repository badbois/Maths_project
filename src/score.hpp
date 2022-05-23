#pragma once

#include <p6/p6.h>
#include <vector>

void display_scoreboard(p6::Context &ctx);
void add_new_score(const int scores);
std::vector<int> get_scoreboard();