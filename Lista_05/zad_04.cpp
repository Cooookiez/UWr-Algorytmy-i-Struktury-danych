#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>
#include <string>

using namespace std;


class Priority_queue {
public:
    Priority_queue(int max_size) {
        _heap.push_back(-1);
    }

    Priority_queue(vector<double> data) {
        build_heap(data);
    }

    void put(double newElement) {
        _heap.push_back(newElement);
        int i = _heap.size() - 1;
        while (i > 1 && _heap[i/2] < _heap[i]) {
            swap(_heap[i/2], _heap[i]);
            i = i/2;
        }
    }

    double get_max() {
        return _heap[1];
    }

    double extract_max() {
        if (_heap.size() > 1) {
            double toExtract = _heap[1];
            _heap[1] = _heap.back();
            _heap.pop_back();
            max_heapify(1);
            return toExtract;
        } else {
            throw string("heap is empty");
        }
    }

    bool is_empty() {
        return _heap.size() == 1;
    }

    bool is_full() {
        return false; // never is full
    }

    void build_heap(vector<double>& data) {
        _heap.push_back(-1);
        _heap.insert(_heap.end(), data.begin(), data.end());
        for (int i = data.size()/2; i >= 1; i--) {
            max_heapify(i);
        }
    }

    void max_heapify(int i) {
        int n = _heap.size() - 1;

        int l = 2*i;
        int r = 2*i + 1;
        int largest = i;
        if (l <= n && _heap[l] > _heap[largest]) largest = l;
        if (r <= n && _heap[r] > _heap[largest]) largest = r;

        if (largest != i) {
            swap(_heap[i], _heap[largest]);
            max_heapify(largest);
        }
    }

    void print() const {
        for(int i = 1; i < _heap.size(); i++) {
            cout << _heap[i] << " ";
        }
        cout << endl;
    }

private:
    vector<double> _heap;
    int max_size;
};

int main() {

    double arr[] = {1.0, 2.0, 3.0};

    Priority_queue myPrio;

    for( int i = 0; i < sizeof(arr)/sizeof(double); i++) {
        myPrio.put(arr[i]);
    }

    myPrio.print();
    return 0;
}