# Computer Networks Assignment 1

## 20161120 Himanshu Bhatia
## 20161195 Ayush Agrawal

## Instructions to run the code : 

### For CPP_Q1
   First run the server code in server directory by using following command:

   g++ server.cpp -o server
   ./server

   Then run the client code in client directory by using following command:

   g++ client.cpp -o client
   ./client [name of the file to transfer]

### For Python_Q2
   First run the server in the server directory by using the following command:

   python server_persistent.py for persistent and
   python server_nonpersistent.py for non-persistent 

   Then run the client in the client directory by using the following command:

   python client_persistent.py [name of the files to transfer] for persistent and
   python client_nonpersistent.py [name of the files to transfer] for non-persistent 

### Report for Q2
   On running the code for different files we found time in most of the cases for non persistent is more than that of the persistent.

   Example:
   
      1- for file of size 17 bytes, results were:
            persistent: 7.41481781006e-05 seconds
            non-persistent: 0.000118017196655 seconds 
      

      2- for file of size 5.6 MB, results were:
            persistent: 1.10502719879 seconds
            non-persistent:  1.13769412041 seconds 
      

      3- for file of size 111 MB, results were:
            persistent:    21.6596269608 seconds
            non-persistent: 20.8143248558  seconds
