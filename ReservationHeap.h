#ifndef ReservationHeap_H
#define ReservationHeap_H

#include "ReservationNode.h"
#include <vector>

using namespace std;

// Heap class
class ReservationHeap {
private:
    vector<ReservationNode> heap;

    // Helper function
    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    // to get reservations
    vector<ReservationNode>& getReservations();

    // insert into heap
    void insertReservation(int patronID, int priorityNumber);

    // check if heap is empty
    bool isEmpty() const;

    // get top reservation
    ReservationNode getTopPriority() const;

    // remove reservation
    void removeTopPriority();
};

#endif
