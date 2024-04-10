# Stream Control Transmission Protocol
A sample implementation of sctp handshake using C socket programming.
## Steps involved 
1.TCP fourway handshake using 4 CHUNKS(INIT(1),INIT ACK(2),COOKIE ECHO(10),COOKIE SENT(11)).
2.Transferring of data using CHUNK 0(DATA).
3.Sending CHUNK 4(HEARTBEAT RRQUEST) and receiving CHUNK 5(HEARTBEAT ACK).
4.Using CHUNK 6(ABORT).

![image](https://github.com/MaruvarKuzhali/sctp/assets/68425273/14ea126a-36e2-4f61-acaa-8a99889ef34e)
