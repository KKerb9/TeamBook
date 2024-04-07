#include "../main-template/main.cpp"

struct decompos {
    int size, block_size;
    vector<int> add;
    vector<int> max_el;
    vector<int> arr;
    decompos (vector<int>& src) {
        arr = src;
        size = arr.size();
        block_size = sqrt(size);
        add.resize((size + block_size - 1) / block_size, 0);
        max_el.resize((size + block_size - 1) / block_size, 0);
    }

    void add (int l, int r) { // [l, r)   l in [0;n)
        --r;
        for (int i = l; i % block_size != 0 && i <= r; ++i) {
                ++arr[i];
                max_el[i / block_size] = max(max_el[i / block_size], arr[i]);
            }
        for(int i = r; ((l / block_size) != (r/block_size) || l % block_size == 0) && i % block_size != (block_size - 1) && i >= l; --i){
            ++arr[i];
            max_el[r / block_size] = max(max_el[r / block_size], arr[i]);
        }
        for(int block = (l + block_size - 1) / block_size; block < ((r + 1) / block_size); ++block) {
            ++add[block];
            ++max_el[block];
        }
    }

    int getmax(int l, int r) { // [l, r)   l in [0;n)
        --r;
        int ans = INT_MIN;
        if (add[l / block_size] != 0) {
            for (int i = (l / block_size) * block_size; i / block_size == l / block_size && i < size; ++i)
                arr[i] += add[l / block_size];
            add[l / block_size] = 0;
        } 
        if (add[r / block_size] != 0) {
            for (int i = (r / block_size) * block_size; i / block_size == r / block_size && i < size; ++i)
                arr[i] += add[r / block_size];
            add[r / block_size] = 0;
        } 
        for (int i = l; i % block_size != 0 && i <= r; ++i)
            ans = max(ans, arr[i]);
        for(int i = r; i % block_size != (block_size - 1) && i >= l; --i)
            ans = max(ans, arr[i]);
        for(int block = (l + block_size - 1) / block_size; block < ((r + 1) / block_size); ++block)
            ans = max(ans, max_el[block]);
    }
};