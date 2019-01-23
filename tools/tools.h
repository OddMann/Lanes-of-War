//
// Created by Kringla on 15.12.2018.
//

#ifndef KAPPAPRIDE_TOOLS_H
#define KAPPAPRIDE_TOOLS_H

#include <vector>
#include <stdio.h>
#include <memory>
#include <iostream>

namespace tl {

    class tools {
    };

    int iParent(int i);
    int iLeftChild(int i);

    template<class Payload>
    void shiftDown(std::vector<std::pair<float, Payload>> &A, int start, int end);



    template<class Payload>
    void maxHeapify(std::vector<std::pair<float, Payload>> &A, int count) {

        int start = iParent(count - 1);

        while (start >= 0) {
            shiftDown(A, start, count - 1);
            start--;
        }
    }

    template<class Payload>
    void shiftDown(std::vector<std::pair<float, Payload>> &A, int start, int end) {
        if (start < 0 || (size_t) end >= A.size())
            std::cerr << "wants to access beyond array" << std::endl;
        int root = start;
        while (iLeftChild(root) <= end) {
            int child = iLeftChild(root);
            int swap = root;

            if (A[swap].first < A[child].first)
                swap = child;
            if (child + 1 <= end)
                if (A[swap].first < A[child + 1].first)
                    swap = child + 1;
            if (swap == root)
                return;
            else {
                std::swap(A[root], A[swap]);
                root = swap;
            }
        }
    }



    template<class Payload>
    class maxHeap {
    public:
        maxHeap() {
            size = 0;
            count = 0;
        }

        maxHeap(int size) {
            this->size = size;
            count = 0;
        }

        ~maxHeap() = default;

        void add(float d, Payload p) {
            if (count < size) {
                arr.emplace_back(d, p);
                count++;
                if (count == size) {
                    maxHeapify(arr, size);
                }

            } else {
                if (d < arr.front().first) {
                    arr.front().first = d;
                    arr.front().second = p;
                    shiftDown(arr, 0, count - 1);
                }
            }
        }
        Payload pop() {
            Payload extract = arr.front().second;
            if (count > 1) {

                std::swap(arr.front(), arr.back());
            }
            arr.pop_back();
            count--;
            if (count > 1) {
                shiftDown(arr, 0, count - 1);
            }

            return extract;
        }

        void resize(int i) {
            size = i;
        }

        void reset() {
            count = 0;
            arr.clear();

        }

        int Size() const { return size; }

        bool empty() const { return count == 0; }

    private:
        int count;
        int size;
        std::vector<std::pair<float, Payload>> arr;
    };

}
#endif //KAPPAPRIDE_TOOLS_H
