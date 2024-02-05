#define BOOST_NO_AUTO_PTR
#pragma once
#include <boost/python.hpp>
#include <random>
namespace bpmod::maker {
class Maker {
private:
    int seed;
    int amountToRun;
    int currentRun;
    std::mt19937 generator;
    std::uniform_int_distribution<int> distribution;
public:
    Maker();
    Maker(const int &seed, const int &amountToRun);
    Maker(const Maker &o);
    Maker &operator=(const Maker &o);
    Maker(Maker &&o);
    Maker &operator=(Maker &&o);
    ~Maker();
public:
    void setSeed(const int &seed);
    int getSeed() const;
    void setAmountToRun(const int &amountToRun);
    int getAmountToRun() const;
    boost::python::object run();
};
} // namespace bpmod::maker
