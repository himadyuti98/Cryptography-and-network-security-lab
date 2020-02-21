import socket                
import os
from Crypto.PublicKey import RSA
import ast

if __name__ == '__main__':
	s = socket.socket()          
	port = 6095

	s.connect(('127.0.0.1', port))
	os.system("openssl genrsa -out private_key_proxy.pem 1024")
	os.system("openssl rsa -in private_key_proxy.pem -pubout -out public_key_proxy.pem")
	f = open("public_key_proxy.pem", 'r')
	public_key = f.read()
	s.send(public_key.encode('utf-8'))

	public_key = RSA.importKey(public_key)
	private_key = RSA.importKey(open("private_key_proxy.pem").read())
	
	s1 = socket.socket()
	port1 = 6055

	s1.bind(('127.0.0.2', port1))
	s1.listen(5)

	b, baddr = s1.accept()
	b_public_key_string = b.recv(1024)
	b_public_key = RSA.importKey(b_public_key_string.decode('utf-8'))

	while True:
		enc_msg = s.recv(1024)
		part_enc_msg = private_key.decrypt(ast.literal_eval(enc_msg.decode()))
		encrypted = b_public_key.encrypt(part_enc_msg, 32)
		b.send(encrypted.encode())
		#b.send(enc_msg)

	s.close()       
	s1.close()