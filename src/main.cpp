#include <vector>
#include <cstdint>

struct SpatialGrid {
    int width, height, cellSize;
    int cols, rows;

    std::vector<std::vector<uint32_t>> buckets;
    // this is the constructor for our grid struct. The width(w) and height(h)
    // are like setter functions.
    
    SpatialGrid(int w, int h, int size) : width(w), height(h), cellSize(size) {
        cols = width / cellSize;
        rows = height / cellSize;
        buckets.resize(cols * rows);
    }

    int getIndex(float x, float y) {
        int cx = static_cast<int>(x) / cellSize;
        int cy = static_cast<int>(y) / cellSize;
        cx = std::max(0, std::min(cx, cols - 1));
        cy = std::max(0, std::min(cy, rows - 1));
        return cx + cy * cols;
    }

    void addEntity(uint32_t id, float x, float y) {
        buckets[getIndex(x, y)].push_back(id);
    }
    void clear() {
        for (auto& bucket : buckets) bucket.clear();
    }
};