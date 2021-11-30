
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

#include <vector>
template <class T, class name, class Compare>
size_t heap<T, name, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    
    return 1;
}

template <class T, class name, class Compare>
size_t heap<T, name, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    if (currentIdx*2 >= _elems.size()) {
        return -1;
    }
    return currentIdx*2;
}

template <class T, class name, class Compare>
size_t heap<T, name, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    if (currentIdx*2 + 1 >= _elems.size()) {
        return -1;
    }
    return currentIdx*2 + 1;
}

template <class T, class name, class Compare>
size_t heap<T, name, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    return (int)currentIdx/2;
}

template <class T, class name, class Compare>
bool heap<T, name, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    int siz = _elems.size();
    if ((int)currentIdx*2 < siz) {
        return true;
    }
    return false;
}

template <class T, class name, class Compare>
size_t heap<T, name, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    if (!hasAChild(currentIdx)) {
        return -1;
    }
    int lefti = leftChild(currentIdx);
    int righti = rightChild(currentIdx);
    if (righti == -1) {
        return lefti;
    }
    T leftc = _elems[lefti];
    T rightc = _elems[righti];
    if (higherPriority(leftc, rightc)) {
        return lefti;
    }
    return righti;
}

template <class T, class name, class Compare>
void heap<T, name, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    int index = maxPriorityChild(currentIdx);
    if (index == -1) {
        return;
    }
    if (higherPriority(_elems[index], _elems[currentIdx])) {
        std::swap(_elems[currentIdx], _elems[index]);
        posTrack[_elems[currentIdx].first] = currentIdx;
        posTrack[_elems[index].first] = index;
        heapifyDown(index);
    }
}

template <class T, class name, class Compare>
void heap<T, name, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        posTrack[_elems[currentIdx].first] = currentIdx;
        posTrack[_elems[index].first] = index;
        heapifyUp(parentIdx);
    }
}

template <class T, class name, class Compare>
heap<T, name, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
    _elems = std::vector<T>();
    _elems.push_back(T());
}

template <class T, class name, class Compare>
heap<T, name, Compare>::heap(const std::vector<T>& elems) 
{
    // @TODO Construct a heap using the buildHeap algorithm
    _elems.push_back(T());
    for (T i : elems) {
        _elems.push_back(i);
    }
    for (int i = _elems.size() - 1; i > 0; i--) {
        heapifyDown(i);
    }
}

template <class T, class name, class Compare>
T heap<T, name, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    T re = _elems[1];
    std::swap(_elems[1], _elems[_elems.size() - 1]);
    _elems.pop_back();
    heapifyDown(1);
    return re;
}

template <class T, class name, class Compare>
T heap<T, name, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    if (_elems.size() <= 1) {
        return T();
    }
    return _elems[1];
}

template <class T, class name, class Compare>
void heap<T, name, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}

template <class T, class name, class Compare>
void heap<T, name, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    _elems[idx] = elem;
    heapifyDown(idx);
    heapifyUp(idx);

}


template <class T, class name, class Compare>
bool heap<T, name, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    if (_elems.size() <= 1) {
        return true;
    }
    return false;
}

template <class T, class name, class Compare>
void heap<T, name, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
