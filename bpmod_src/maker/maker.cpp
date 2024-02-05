#include "maker.hpp"
#include "data/makerdata.hpp"
namespace bpmod::maker {
Maker::Maker() :
    seed(80085),
    amountToRun(5),
    currentRun(0),
    generator(seed),
    distribution(0,10)
{}
Maker::Maker(const int &seed, const int &amountToRun) :
    seed(seed),
    amountToRun(amountToRun),
    currentRun(0),
    generator(seed),
    distribution(0,10)
{}
Maker::Maker(const Maker &o){*this=o;}
Maker &Maker::operator=(const Maker &o) {
    this->seed=o.seed;
    this->amountToRun=o.amountToRun;
    this->currentRun=o.currentRun;
    this->generator=o.generator;
    this->distribution=o.distribution;
    return *this;
}
Maker::Maker(Maker &&o) :
    seed(std::move(o.seed)),
    amountToRun(std::move(o.amountToRun)),
    currentRun(std::move(o.currentRun)),
    generator(std::move(o.generator))
{
    this->distribution=std::move(o.distribution);
    o.seed=80085;
    o.amountToRun=5;
    o.currentRun=0;
    o.generator=std::mt19937(o.seed);
    o.distribution=std::uniform_int_distribution<int>(0,10);
}
Maker &Maker::operator=(Maker &&o) {
    if(this==&o) return *this;
    //clear this stuff
    this->seed=80085;
    this->amountToRun=5;
    // ...
    //move other into this
    this->seed=std::move(o.seed);
    this->amountToRun=std::move(o.amountToRun);
    this->currentRun=std::move(o.currentRun);
    this->generator=std::move(o.generator);
    this->distribution=std::move(o.distribution);
    //set to know state
    o.seed=80085;
    o.amountToRun=5;
    o.currentRun=0;
    o.generator=std::mt19937(o.seed);
    o.distribution=std::uniform_int_distribution<int>(0,10);
    return *this;
}
Maker::~Maker() {}
void Maker::setSeed(const int &seed) {
    this->seed=seed;
}
int Maker::getSeed() const {
    return this->seed;
}
void Maker::setAmountToRun(const int &amountToRun) {
    this->amountToRun=amountToRun;
}
int Maker::getAmountToRun() const {
    return this->amountToRun;
}
boost::python::object Maker::run() {
    boost::python::object result;
    if (this->currentRun<this->amountToRun) {
        constexpr std::size_t SIZE=5;
        result=boost::python::object(data::MakerData());
        data::MakerData &md = boost::python::extract<data::MakerData&>(result);
        md.values.reserve(SIZE);
        for (std::size_t i=0; i<SIZE;++i) {
            md.values.emplace_back(this->distribution(this->generator));
        }
        md.number=md.values.size();
        this->currentRun+=1;
    }
    return result;
}
} // namespace bpmod::maker