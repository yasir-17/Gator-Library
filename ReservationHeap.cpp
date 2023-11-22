#include <iostream>
#include <ctime>
#include "ReservationHeap.h"
#include "ReservationNode.h"

using namespace std;

// Function to return heap
vector<ReservationNode>& ReservationHeap::getReservations() {
    return heap;
}

// Functions to maintain heap structure
void ReservationHeap::heapifyUp(int index) {
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        if (heap[index].priorityNumber < heap[parentIndex].priorityNumber ||
            (heap[index].priorityNumber == heap[parentIndex].priorityNumber &&
             heap[index].timeOfReservation < heap[parentIndex].timeOfReservation)) {
            swap(heap[index], heap[parentIndex]);
            index = parentIndex;
        } else {
            break;
        }
    }
}

// Functions to maintain heap structure
void ReservationHeap::heapifyDown(int index) {
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int smallest = index;

    if (leftChild < heap.size() &&
        (heap[leftChild].priorityNumber < heap[smallest].priorityNumber ||
         (heap[leftChild].priorityNumber == heap[smallest].priorityNumber &&
          heap[leftChild].timeOfReservation < heap[smallest].timeOfReservation))) {
        smallest = leftChild;
    }

    if (rightChild < heap.size() &&
        (heap[rightChild].priorityNumber < heap[smallest].priorityNumber ||
         (heap[rightChild].priorityNumber == heap[smallest].priorityNumber &&
          heap[rightChild].timeOfReservation < heap[smallest].timeOfReservation))) {
        smallest = rightChild;
    }

    if (smallest != index) {
        swap(heap[index], heap[smallest]);
        heapifyDown(smallest);
    }
}

// function to insert reservation in heap
void ReservationHeap::insertReservation(int patronID, int priorityNumber) {
    if (heap.size() < 20) {
        time_t currentTime = time(nullptr);
        heap.emplace_back(patronID, priorityNumber, currentTime);
        heapifyUp(heap.size() - 1);
    } else {
        cout << "Reservation limit reached for this book.\n";
    }
}

// to check if heap is empty
bool ReservationHeap::isEmpty() const {
    return heap.empty();
}

// To return the top reservation
ReservationNode ReservationHeap::getTopPriority() const {
    return heap[0];
}

// function to remove reservation
void ReservationHeap::removeTopPriority() {
    if (!isEmpty()) {
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    } else {
        cout << "Heap is empty.\n";
    }
}