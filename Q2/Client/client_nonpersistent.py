import socket, sys                  

# Creating a socket object
s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)             
host = ""
port = 8080              

# Connect to server on network
try:
    s.connect((host, port))
    print("connected")
except:
    print("Error in connecting")
    sys.exit(1)

# num is the number of files to be sent
files=sys.argv[1:]
num=len(files)
if(num == 0):
    print("Correct usage: python client_nonpersistent.py [file names]")
    sys.exit(1)
# send data
try:
    s.send(str(num))
except:
    print("Error in sending")
    sys.exit(1)
try:
    g1 = s.recv(1024)
except:
    print("Error in receiving data")
ind=0

while(ind < num):
    # name of file to be sent    
    flag = 0
    filename = files[ind]
    try:
        s.send(filename)
    except:
        print("Error in sending")
    with open(filename, 'wb') as f:
        print 'file opened'
        while True:
            print('receiving data...')
            try:
                data = s.recv(1024)
                if(data[len(data)-1] == '$'):
                    print("Wrong file name")
                    break
            except:
                print("Error in receiving data")
                sys.exit(1)
            print('data=%s', (data))

            # checking if the end character is null that means EOF.
            try:
                if data[len(data)-1] == '\0':
                    data = data[0:len(data)-1]
                    f.write(data)
                    break
                flag = 1
            except:
                print("Error in getting data, check the name of all the files")
                break
            # write data to a file
            try:
                f.write(data)
            except:
                print("Error in writing to file")
                sys.exit(1)

        try:
            f.close()
        except:
            print("Error in closing file")
            sys.exit(1)
    ind = ind + 1
    if(flag == 1):
        print('Successfully get the file')
    # close connection
    try:
        s.close()
    except:
        print("Error in closing socket")
        sys.exit(1)
    print('connection closed')
    if(ind < num):
        s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        s.connect((host, port))
        print("connected")

