

## [What are CLOSE_WAIT and TIME_WAIT states?](https://superuser.com/questions/173535/what-are-close-wait-and-time-wait-states)

Due to the way TCP/IP works, connections can not be closed immediately. Packets may arrive out of order or be retransmitted after the connection has been closed. CLOSE_WAIT indicates that the remote endpoint (other side of connection ) has closeded the connection. TIME_WAIT indicates that local endpoint (this side) has closed the connection. The connection is being kept around so that any delayed packets can be matched to the connection and handled appropriately. The connections will be removed when they time out within four minutes.

[Transmission Control Protocol](https://en.wikipedia.org/wiki/Transmission_Control_Protocol)