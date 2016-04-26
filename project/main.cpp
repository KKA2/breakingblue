// main.cpp
// driver program for gameplay
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Master.h"
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand (time(NULL));
    Master master;
    master.play();

    return 0;
}
