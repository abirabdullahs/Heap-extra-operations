#include <bits/stdc++.h>
using namespace std;

class MinHeap {
private:
    vector<int> heap;

    int parent(int i){ return (i-1)/2; }
    int left(int i){ return 2*i+1; }
    int right(int i){ return 2*i+2; }

    /* ---------- Heapify Down ---------- */
    void heapifyDown(int i){
        int l = left(i);
        int r = right(i);
        int smallest = i;

        if(l < heap.size() && heap[l] < heap[smallest])
            smallest = l;

        if(r < heap.size() && heap[r] < heap[smallest])
            smallest = r;

        if(smallest != i){
            swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }

    /* ---------- Heapify Up ---------- */
    void heapifyUp(int i){
        while(i != 0 && heap[parent(i)] > heap[i]){
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

public:

    /* ---------- INSERT ---------- */
    void insert(int x){
        heap.push_back(x);
        heapifyUp(heap.size()-1);
    }

    /* ---------- GET MIN ---------- */
    int getMin(){
        if(heap.empty()) return -1;
        return heap[0];
    }

    /* ---------- EXTRACT MIN ---------- */
    int extractMin(){
        if(heap.empty()) return -1;

        int root = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);

        return root;
    }

    /* ---------- BUILD HEAP (O n) ---------- */
    void buildHeap(vector<int> arr){
        heap = arr;
        for(int i = heap.size()/2 - 1; i >= 0; i--)
            heapifyDown(i);
    }

    /* ---------- DELETE INDEX ---------- */
    void deleteKey(int i){
        if(i >= heap.size()) return;
        decreaseKey(i, INT_MIN);
        extractMin();
    }

    /* ---------- DECREASE KEY ---------- */
    void decreaseKey(int i, int val){
        heap[i] = val;
        heapifyUp(i);
    }

    /* ---------- REPLACE MIN ---------- */
    void replaceMin(int x){
        heap[0] = x;
        heapifyDown(0);
    }

    /* =====================================================
       ADVANCED OPERATIONS (LC + GFG STYLE)
       ===================================================== */

    /* ---------- MERGE TWO MIN HEAPS ---------- */
    void mergeHeap(MinHeap &other){
        for(int x : other.heap)
            heap.push_back(x);

        for(int i = heap.size()/2 - 1; i >= 0; i--)
            heapifyDown(i);
    }

    /* ---------- CHECK VALID MIN HEAP ---------- */
    bool isValidMinHeap(){
        for(int i=0;i<heap.size()/2;i++){
            if(left(i)<heap.size() && heap[i] > heap[left(i)])
                return false;
            if(right(i)<heap.size() && heap[i] > heap[right(i)])
                return false;
        }
        return true;
    }

    /* ---------- CONVERT MINHEAP → MAXHEAP ---------- */
    vector<int> convertToMaxHeap(){
        vector<int> maxHeap = heap;

        for(int i=maxHeap.size()/2-1;i>=0;i--){
            int idx=i;
            while(true){
                int l=2*idx+1;
                int r=2*idx+2;
                int largest=idx;

                if(l<maxHeap.size() && maxHeap[l]>maxHeap[largest])
                    largest=l;
                if(r<maxHeap.size() && maxHeap[r]>maxHeap[largest])
                    largest=r;

                if(largest==idx) break;
                swap(maxHeap[idx],maxHeap[largest]);
                idx=largest;
            }
        }
        return maxHeap;
    }

    /* ---------- HEAP SORT ---------- */
    vector<int> heapSort(){
        MinHeap temp = *this;
        vector<int> res;

        while(!temp.heap.empty())
            res.push_back(temp.extractMin());

        return res;
    }

    /* ---------- KTH SMALLEST ---------- */
    int kthSmallest(int k){
        MinHeap temp = *this;

        for(int i=1;i<k;i++)
            temp.extractMin();

        return temp.getMin();
    }

    /* ---------- K LARGEST ELEMENTS ---------- */
    vector<int> kLargest(int k){
        priority_queue<int, vector<int>, greater<int>> pq;

        for(int x : heap){
            pq.push(x);
            if(pq.size() > k)
                pq.pop();
        }

        vector<int> ans;
        while(!pq.empty()){
            ans.push_back(pq.top());
            pq.pop();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }

    /* ---------- PRINT ---------- */
    void print(){
        for(int x : heap)
            cout<<x<<" ";
        cout<<endl;
    }
};


/* ===================== DEMO ===================== */

int main(){

    MinHeap h1;
    h1.insert(10);
    h1.insert(4);
    h1.insert(15);
    h1.insert(20);

    MinHeap h2;
    h2.insert(2);
    h2.insert(8);

    // merge
    h1.mergeHeap(h2);

    cout<<"Merged Heap: ";
    h1.print();

    // kth smallest
    cout<<"3rd smallest: "<<h1.kthSmallest(3)<<endl;

    // heap sort
    auto sorted = h1.heapSort();
    cout<<"Sorted: ";
    for(int x:sorted) cout<<x<<" ";
    cout<<endl;

    // convert to maxheap
    auto maxH = h1.convertToMaxHeap();
    cout<<"MaxHeap array: ";
    for(int x:maxH) cout<<x<<" ";
}
