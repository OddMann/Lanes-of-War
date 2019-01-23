//
// Created by Kringla on 25.11.2018.
//

#ifndef KAPPAPRIDE_HEAP_H
#define KAPPAPRIDE_HEAP_H

#include <vector>
#include <stdio.h>
#include <memory>
#include <iostream>
class Entity;
class heapSorter
{
public:
    static void maxHeapify(std::vector<std::pair<float, Entity*>>& A, int count)
    {

        int start = iParent(count - 1);

        while(start >= 0)
        {
            shiftDown(A, start, count - 1);
            start--;
        }
    }
    static void shiftDown(std::vector<std::pair<float, Entity*>>& A, int start, int end)
    {
        if(start < 0 || (size_t)end >= A.size())
            std::cerr << "wants to access beyond array" << std::endl;
        int root = start;
        while(iLeftChild(root) <= end)
        {
            int child = iLeftChild(root);
            int swap = root;

            if(A[swap].first < A[child].first)
                swap = child;
            if(child+1 <= end)
                if( A[swap].first < A[child+1].first)
                    swap = child + 1;
            if(swap == root)
                return;
            else
            {
                std::swap(A[root], A[swap]);
                root = swap;
            }
        }
    }
protected:
    static int iParent(int i){return (i-1)/2;}
    static int iLeftChild(int i){return 2*i+1;}
    static int iRightChild(int i){return 2*i+2;}
};

class maxHeap : public heapSorter
{
public:
    maxHeap()
    {
        size = 0;
        count = 0;
    }
    maxHeap(int size)
    {
        this->size = size;
        count = 0;
    }
    ~maxHeap()=default;

    void add(float d, Entity& e)
    {
        if(count < size)
        {
            arr.emplace_back(d,&e);
            count++;
            if(count == size)
            {
                maxHeapify(arr, size);
            }

        }
        else
        {
            if(d < arr.front().first)
            {
                arr.front().first = d;
                arr.front().second = &e;
                shiftDown(arr, 0, count-1);
            }


        }
    }
    Entity* pop()
    {
        Entity* extract = arr.front().second;
        if(count > 1)
        {

            std::swap(arr.front(),arr.back());
        }
        arr.pop_back();
        count--;
        if(count > 1)
        {
            shiftDown(arr, 0 ,count-1);
        }

        return extract;
    }
    void resize(int i)
    {
        size = i;
    }
    void reset()
    {
        count = 0;
        arr.clear();

    }
    int Size()const{return size;}
    bool empty()const{return count == 0;}
private:
    int count;
    int size;
    std::vector<std::pair<float, Entity*>> arr;
};


#endif //KAPPAPRIDE_HEAP_H
