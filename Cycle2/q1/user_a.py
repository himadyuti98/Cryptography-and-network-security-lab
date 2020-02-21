import socket                
import os
from Crypto.PublicKey import RSA
import ast

if __name__ == '__main__':
	s1 = socket.socket()          
	print("Socket successfully created")
	s2 = socket.socket()          
	print("Socket successfully created")
	  
	port1 = 6095
	port2 = 6096           
	  
	s1.bind(('', port1))         
	print("socket binded to %s" %(port1)) 
	  
	s1.listen(5)      
	print("socket is listening")    

	s2.bind(('', port2))         
	print("socket binded to %s" %(port2)) 
	  
	s2.listen(5)      
	print("socket is listening")            

	p, paddr = s1.accept()      
	print('Got connection from', paddr) 

	proxy_public_key = p.recv(1024)
	# f = open("proxy_public_key_with_a.pem", 'w')
	# f.write(proxy_public_key)
	# f.close()
	proxy_public_key = RSA.importKey(proxy_public_key.decode('utf-8'))

	b, baddr = s2.accept()
	print('Got connection from', baddr) 

	b_public_key = b.recv(1024)
	# f = open("b_public_key_with_a.pem", 'w')
	# f.write(b_public_key)
	# f.close()
	b_public_key = RSA.importKey(b_public_key.decode('utf-8'))
	b.close() 

	while True:
		msg = raw_input()
		print(msg)
		msg = b_public_key.encrypt(msg, 32)
		print(msg)
		msg = str(msg)
		msg = proxy_public_key.encrypt(msg, 32)
		#print(msg)
		p.send(msg.encode())

	p.close()
  	