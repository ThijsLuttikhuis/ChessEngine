//
// Created by thijs on 09-03-21.
//

#ifndef CHESSENGINE_RANDOMENGINE_H
#define CHESSENGINE_RANDOMENGINE_H

#include <random>
#include "../Engine.h"


class MTGenerator {
private:
    std::mt19937 mersenne;
public:
    explicit MTGenerator(int seed) {
        mersenne = std::mt19937(seed);         //initialize Mersenne twister with seed
    }

    void setSeed(int seed_) {
        mersenne = std::mt19937(seed_);
    }

    /// get random number between 0 and 1
    double rand() {
        std::uniform_real_distribution<double> distribution{0.0, 1.0}; // range [0,1)
        return distribution(mersenne);  //The Mersenne twister built in function
    }

    /// get random number from range [min, max)
    double randr(double min, double max) {
        double r = this->rand();
        return min + (max - min) * r;
    }

    /// get random integer from range [min, max)  # if there is only one argument, min = 0, max = arg-1
    int randri(int min, int max = -1) {
        if (max == -1) {
            max = min;
            min = 0;
        }
        double r = this->rand();
        return min + (int) ((max - min) * r);
    }


    /// get n random numbers
    std::vector<double> randr(int n, double min = 0, double max = 1) {
        std::vector<double> rs(n);
        for (int i = 0; i < n; i++) {
            rs[i] = this->randr(min, max);
        }
        return rs;
    }
};

class RandomEngine : public Engine {
private:
    MTGenerator rng = MTGenerator(42);
public:
    explicit RandomEngine(bool white) : Engine(white) {};

    Move move(Board* board) override;

};

#endif //CHESSENGINE_RANDOMENGINE_H
