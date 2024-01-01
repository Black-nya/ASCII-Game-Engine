#include <random>
int getRandom(int a, int b){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(a, b); // distribution in range [a, b]
    return dist(rng);
}