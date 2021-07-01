# Game-using-Semaphores
Real-Time Applications & Embedded Systems Course Project

We would like to create a multi-processing application that employs semaphores only. A
parent process will create 6 children processes named P0 . . . P5 located initially at locations
A . . . I respectively as shown in Figure 1.
The behavior of the whole system is as follows:

![Capture](https://user-images.githubusercontent.com/67745487/124186030-62be0e80-dac4-11eb-9835-53735b47b167.PNG)


1. Upon an order from the parent, processes P0, P1 and P2 start moving towards
   location G.
   
2. Once P0, P1 and P2 reach location G, they walk together to location H.

4. Once P0, P1 and P2 get to location H, processes P3 and P4 start moving towards
   location H and at the same time process P5 starts moving towards location I.
   
4. When either P3 or P4 gets to location H, P0 starts moving back to location G. When
   both P3 and P4 get to location H, P1 . . . P4 start moving to location I.
   
5. When processes P1 . . . P5 reach location I, process P0 starts moving back to location
   A.
   
6. Once process P0 gets to location A, P1, P2, P3 and P4 start moving back to location
   H while process P5 starts moving back to location F.
   
7. Once process P5 gets to location F, process P3 starts moving back to location D while
   process P4 starts moving back to location E.
   
8. When either P3 gets to location D or process P4 gets to location E, processes P1 and
   P2 start moving to location G.9. When both process P3 is back to location D and process P4 is back to location E,
   process P1 starts moving back to location B and process P2 starts moving back to
   location C.
   
 9. When both process P3 is back to location D and process P4 is back to location E,
    process P1 starts moving back to location B and process P2 starts moving back to
    location C.
   
10. Once process P1 is back to location B and process P2 is back to location C (meaning
   we’re back to the original configuration where each process is back to its home
   location), go back to step 1 above unless the above behavior has been done for 10
   times.
   
11. The parent process must kill all its children, free the semaphores facility it is using
    and exit.
