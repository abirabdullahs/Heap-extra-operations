#include <vector>
#include <stdexcept>
#include <iostream>
#include <algorithm>

// Assume MinHeap class already defined with heap array, size, siftUp, siftDown etc.

class MinHeap {
private:
    int* heap;
    int capacity;
    int size;

    void siftUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (heap[parent] > heap[i]) {
                std::swap(heap[parent], heap[i]);
                i = parent;
            } else break;
        }
    }

    void siftDown(int i) {
        int minIndex = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && heap[left] < heap[minIndex]) minIndex = left;
        if (right < size && heap[right] < heap[minIndex]) minIndex = right;

        if (minIndex != i) {
            std::swap(heap[i], heap[minIndex]);
            siftDown(minIndex);
        }
    }

public:
    MinHeap(int cap = 1000) : capacity(cap), size(0) {
        heap = new int[capacity];
    }

    ~MinHeap() {
        delete[] heap;
    }

    void insert(int val) {
        if (size == capacity) throw std::overflow_error("Heap full");
        heap[size] = val;
        siftUp(size);
        size++;
    }

    int extractMin() {
        if (size == 0) throw std::underflow_error("Heap empty");
        int minVal = heap[0];
        heap[0] = heap[size - 1];
        size--;
        siftDown(0);
        return minVal;
    }

    int findMin() const { return size > 0 ? heap[0] : throw std::underflow_error("Heap empty"); }

    int getSize() const { return size; }

    // --- New operations ---

    // Merge with another MinHeap
    void merge(const MinHeap& other) {
        if (size + other.size > capacity) throw std::overflow_error("Not enough capacity to merge");
        for (int i = 0; i < other.size; ++i) {
            heap[size + i] = other.heap[i];
        }
        size += other.size;
        // Heapify whole array (bottom-up)
        for (int i = (size / 2) - 1; i >= 0; --i) {
            siftDown(i);
        }
    }

    // Update key at index i to newVal (can increase or decrease)
    void updateKey(int i, int newVal) {
        if (i < 0 || i >= size) throw std::out_of_range("Index out of range");
        int oldVal = heap[i];
        heap[i] = newVal;
        if (newVal < oldVal) siftUp(i);
        else siftDown(i);
    }

    // Find kth smallest element (k starts from 1)
    int kthSmallest(int k) {
        if (k <= 0 || k > size) throw std::out_of_range("k out of range");
        // Copy heap to temp heap to avoid modifying original
        MinHeap tempHeap(*this); // You need copy constructor for deep copy
        int result;
        for (int i = 0; i < k; ++i) {
            result = tempHeap.extractMin();
        }
        return result;
    }

    // Copy constructor for deep copy (needed for kthSmallest)
    MinHeap(const MinHeap& other) : capacity(other.capacity), size(other.size) {
        heap = new int[capacity];
        for (int i = 0; i < size; ++i) heap[i] = other.heap[i];
    }

    // Iterator class to traverse heap elements (level order)
    class Iterator {
    private:
        int* ptr;
        int index;
        int size;
    public:
        Iterator(int* p, int idx, int sz) : ptr(p), index(idx), size(sz) {}
        bool operator!=(const Iterator& other) const { return index != other.index; }
        int operator*() const { return ptr[index]; }
        Iterator& operator++() { ++index; return *this; }
    };

    Iterator begin() { return Iterator(heap, 0, size); }
    Iterator end() { return Iterator(heap, size, size); }
};

// Example usage
int main() {
    MinHeap h;
    h.insert(10);
    h.insert(4);
    h.insert(15);
    h.insert(1);

    std::cout << "Min: " << h.findMin() << "\n"; // 1

    h.updateKey(2, 0); // update index 2 value to 0

    std::cout << "After updateKey, Min: " << h.findMin() << "\n"; // 0

    MinHeap h2;
    h2.insert(7);
    h2.insert(3);

    h.merge(h2);
    std::cout << "After merge, Min: " << h.findMin() << "\n"; // 0

    std::cout << "3rd smallest element: " << h.kthSmallest(3) << "\n"; // example output

    std::cout << "Heap elements: ";
    for (auto it = h.begin(); it != h.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    return 0;
}
