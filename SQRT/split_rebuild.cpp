#include "../main-template/main.cpp"

using namespace std;

typedef int T;
const T T_MAX = INT_MAX;
struct split_rebuild { // Обрабатывает запросы вставки перед i-м (i in [1;n], если i=0, то вставка в начало) элементом, удаления элемента и значения i-го элемента в данный момент.
    vector<pair<int, vector<T>>> arr; // {cnt; block}
    vector<int> cnt_to_ind; // block cnt to index in arr
    int max_cnt;
    int block_size;
    int size;
    vector<int> ind_to_cnt; // element index to block cnt
    vector<T> min_element; 
    vector<pair<int, int>> border_index;

    split_rebuild (int k) : block_size(k) {
        max_cnt = 0;
        size = 0;
        cnt_to_ind = {0};
        ind_to_cnt = {0};
        arr = {{0, vector<T>()}};
        border_index = {{1, 0}};
        min_element = {T_MAX};
    }

    void insert(int pos, T val) {
        int block_cnt = ind_to_cnt[pos];
        arr[cnt_to_ind[block_cnt]].second.insert(arr[cnt_to_ind[block_cnt]].second.begin() + (pos - border_index[block_cnt].first + 1),val);
        int i = border_index[block_cnt].second + 1;
        ++size;
        ind_to_cnt.push_back(arr.back().first);
        ++border_index[block_cnt].second;
        ind_to_cnt[i] = block_cnt;
        for (int ind = cnt_to_ind[block_cnt] + 1; ind < arr.size(); ++ind) {
            ++border_index[arr[ind].first].first;
            ++border_index[arr[ind].first].second;
            ind_to_cnt[border_index[arr[ind].first].second] = arr[ind].first;
        }
        min_element[block_cnt] = std::min(val, min_element[block_cnt]);
        if (arr[cnt_to_ind[block_cnt]].second.size() == 2 * block_size) {
            ++max_cnt;
            int curr_size = arr[cnt_to_ind[block_cnt]].second.size();
            arr.emplace(arr.begin() + cnt_to_ind[block_cnt] + 1, max_cnt, vector<T>());
            cnt_to_ind.push_back(cnt_to_ind[block_cnt] + 1);
            for (int index = cnt_to_ind.back() + 1; index < arr.size(); ++index) {
                ++cnt_to_ind[arr[index].first];
            }
            int i = border_index[block_cnt].second + 1;
            i -= block_size;
            for (int block_ind = block_size; block_ind < curr_size; ++block_ind, ++i) {
                ind_to_cnt[i] = max_cnt;
                arr[cnt_to_ind.back()].second.push_back(arr[cnt_to_ind[block_cnt]].second[block_ind]);
            }
            arr[cnt_to_ind[block_cnt]].second.resize(block_size);
            min_element.push_back(arr[cnt_to_ind.back()].second[0]);
            for (int i = 1; i < arr[cnt_to_ind.back()].second.size(); ++i) {
                min_element[max_cnt] = std::min(arr[cnt_to_ind.back()].second[i], min_element[max_cnt]);
            }
            int block_ind = cnt_to_ind[block_cnt];
            min_element[block_cnt] = arr[block_ind].second[0];
            for (int i = 1; i < arr[block_ind].second.size(); ++i) {
                min_element[block_cnt] = std::min(arr[block_ind].second[i], min_element[block_cnt]);
            }
            border_index.emplace_back(border_index[block_cnt].second - block_size + 1, border_index[block_cnt].second);
            border_index[block_cnt].second -= block_size;
        }
    }

    void erase(int pos) { // pos in [1;n]
        int block_cnt = ind_to_cnt[pos];
        int block_ind = cnt_to_ind[block_cnt];
        arr[block_ind].second.erase(arr[block_ind].second.begin() + pos - border_index[block_cnt].first);
        --size;
        ind_to_cnt.pop_back();
        --border_index[block_cnt].second;
        for (int ind = block_ind + 1; ind < arr.size(); ++ind) {
            --border_index[arr[ind].first].first;
            --border_index[arr[ind].first].second;
            ind_to_cnt[border_index[arr[ind].first].first] = arr[ind].first;
        }
        if (arr[block_ind].second.size() == 0) {
            auto it = arr.erase(arr.begin() + block_ind);
            for(; it != arr.end(); ++it) {
                --cnt_to_ind[it->first];
            } 
        }
    }

    T& get(int pos) { // pos in [1;n]
        return arr[cnt_to_ind[ind_to_cnt[pos]]].second[pos - border_index[ind_to_cnt[pos]].first];
    }
};
