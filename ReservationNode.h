
#ifndef ReservationNode_H
#define ReservationNode_H

// Reservation node structure
struct ReservationNode
{
    int patronID;
    int priorityNumber;
    long long timeOfReservation; // Using long long for sufficient precision in timestamps
    ReservationNode(int id, int priority, long long time) : patronID(id), priorityNumber(priority), timeOfReservation(time) {}

};
 
#endif


