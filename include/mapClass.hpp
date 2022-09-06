#include<functional>
#include<tuple>
#include<barrier>
#include<thread>
#include "matrix.hpp"

enum class map_mode {
    Chunk,
    Cyclic
};

class Map{

public:
    Map(int dim, map_mode mode, int pardegree, std::function<void(std::vector<float>&, int, int)> f);
    void execute(int nIter, std::vector<float> &xk);

private:
    std::vector<std::tuple<int, int>> idxs;
    std::function<void(std::vector<float>&, int, int)> f;
    int nw;
    int dim;
    map_mode mode;
    std::vector<std::tuple<int, int>> generateBlocks();
};