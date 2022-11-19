# MagicQ Trakers

This project is about the Chamsys MagicQ Trakers science.

Sidenote: MQ Track protocol use UDP protocol on port 6549 with the following message format:   
\<x>\,\<y>\,\<z>\,\<tracker id>\,\<tracker name>\
Where <tracker id> is zero based - 0 for Tracker 1, 1 for Tracker 2.  
For example, sending tracker 2 named "Bob" with position x of 2.5m, y of 3m and z of 3.5m the data in the UDP message would be
2.5,3,3.5,1,Bob

To use it:
- Connect any blue hardware to MagicQ (you need to go out from demo-mode)
- Under Setup > View Settings > Network set your IP Address, and set the option Tracker rx to "MQ Track"
- Under Setup > View System > Trackers you can see all the trakers data available for the system
- Select your heads and record a position palette. Than select it and click the soft button "View Palette", Set Traker, Traker and write the Tracker ID  
  Now the UDP client message will feed palette XYZ information, so the heads will move following the tracker.
  
## AIM:
  You can build a piece of hardware with a camera, or ir sensor, to collect position information of an object and send them via UDP datagram to MagicQ in order to build a followspot

## Folder Content:
  - UDPClient.c and UDPClient: The source file and the exec file for the UDP Client. It works on all POSIX compatible systems (Linux distros and Mac OS)
  - UDPServer.c and UDPServer: The source file and the exec file for the UDP Server. You can use it to test the client, and see the UDP message sent on the port 
