"# MFC-socket" 

**1. Create a chatroom that allows multiple clients to connect to the server**
  
  Server: 
  
    a. Build the Synchronous Communication
    
    b. Main Thread is UI thread, Second Thread is blocking in accepting new socket, Other thread is blocking in receive state after connect to Client.
  
    c. Save the client socket to a array
  
  Client: 
  
  Main thread is UI control, second thread is blocking in connect state until connect to Server.After connecting to Server, blocking in recieve state.
  
**2. Display both incoming and outgoing content on the same window in the server using List Control**

    a. provide send button for sending the message, limit 20 words.
    
    b. save the message in a buffer.
    
    c. UI would get this buffer and upload to ListCtrl
    
    d. clear the buffer after upload

**3. The server needs to display a list of connected clients**

    a. when array add a member, add the info to CListCtrl

**4. The server can disconnect clients using a button**

    a. provide a delete button. Remove the array member and CListCtrl member
    
    b. Critical section.
    
    Because when disconnect, socket would send -1 value data
    
    if Client disconnect initiative, Server call Remove API
    
    Server disconnect initiative, Server call Remove API. but socket would send -1 value data, Server's rcv state thread call Remove API again
    
    solve this problem by locking.
    

**5. Use the example file of perfmon in the attachment to collect CPU/memory data during the server chatroom is running**

    a. To start the collection: the administrator opens cmd and runs the PerfMonStart_2008.cmd file.
  
    b. To end the collection: run the PerfMonEnd.cmd file.
