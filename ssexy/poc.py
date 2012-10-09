import socket

s = socket.create_connection(('localhost', 9001))
s.send('eindbazen;cat ~/.tmux.conf')
s.send('eindbazen')
print s.recv(512)
