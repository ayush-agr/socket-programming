import socket,sys,time

port = 8080
# Creating a socket object
s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
host = ""
s.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
# Binding ip to port. 
# Empty string in host part 
# allows the server to listen 
# the requests coming from other 
# computers on the network
try:
    s.bind((host, port))
except:
    print("Error in binding")
    sys.exit(1)


# Socket is put in listening state
try:
    s.listen(5)
except:
    print("Error in listening")
    sys.exit(1)

print 'Server listening....'

# Connection establishing with the client
try:
    conn, addr = s.accept()
except:
    print("Error in accepting")

print 'Got connection from', addr
try:
    n = conn.recv(1024)
except:
    print("Error in recieving")
    sys.exit(1)

conn.send('message')
# num is the number of files that need to be sent
try :
    num = int(n)
except:
    print("Error converting data to int")
    sys.exit(1)
    
total_time=0
while num:
    
    try:
        data = conn.recv(1024)
    except:
        print("Error in recieving")
        sys.exit(1)
    print data
    print('Server received', repr(data))
    # name of the file to be sent
    filename = "../Data/"+data

    try:
        f = open(filename,'rb')
    except:
        print("Error in opening file")
        conn.send("$FileDoesn'tExist$")
        num = num-1
        conn.close()
        if(num):
            try:
                s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
                s.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
                s.bind((host, port))
                s.listen(5)
                conn, addr = s.accept()
            except:
                print("Error in socket connection")
        continue
    start_time=time.time()
    l = f.read(1024)
    while (l):
       conn.send(l)
       print('Sent ',repr(l))
       l = f.read(1024)
    try:
        f.close()
    except:
        print('Error in closing file')

    # \0 is used to mark the ending of the file sent
    try:
        conn.send('\0')
    except:
        print('Error in sending data')
    num = num - 1
    print('Done sending')
    conn.close()
    if(num):
        try:
            s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
            s.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
            s.bind((host, port))
            s.listen(5)
            conn, addr = s.accept()
        except:
            print("Error in socket connection")

    total_time = total_time + time.time() - start_time
print("--- %s seconds ---" % (total_time))