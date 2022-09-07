#include<functional>
#include<barrier>
#include<thread>
#include "utils.hpp"

using namespace mv;

enum class map_mode {
    Chunk,
    Cyclic
};

class Map{

public:
    Map(int dim, map_mode mode, int pardegree, const std::function<void(mv::Vector&, int, int)>& f);
    void execute(int nIter, mv::Vector &xk);

private:
    std::vector<std::tuple<int, int>> idxs;
    std::function<void(mv::Vector&, int, int)> f;
    int nw;
    int dim;
    map_mode mode;
    std::vector<std::tuple<int, int>> generateBlocks();
};