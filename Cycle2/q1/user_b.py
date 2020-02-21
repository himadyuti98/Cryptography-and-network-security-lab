import socket                
import os
from Crypto.PublicKey import RSA
import ast

if __name__ == '__main__':
	s = socket.socket()
	port = 6096

	s.connect(('127.0.0.1', port))
	os.system("openssl genrsa -out private_key_b.pem 1024")
	os.system("openssl rsa -in private_key_b.pem -pubout -out public_key_b.pem")
	f = open("public_key_b.pem", 'r')
	public_key = f.read()
	s.send(public_key.encode('utf-8'))
	private_key_a = RSA.importKey(open("private_key_b.pem", 'r').read())
	s.close()
	s = socket.socket()
	port = 6055
	s.connect(('127.0.0.2', port))
	os.system("openssl genrsa -out private_key_b_proxy.pem 1024")
	os.system("openssl rsa -in private_key_b_proxy.pem -pubout -out public_key_b_proxy.pem")
	f = open("public_key_b_proxy.pem", 'r')
	public_key = f.read()
	s.send(public_key.encode('utf-8'))
	private_key_proxy = RSA.importKey(open("private_key_b_proxy.pem", 'r').read())


	while True:
		msg = s.recv(1024)
		msg = private_key_b.decrypt(ast.literal_eval(msg.decode()))
		print(private_key_a.decrypt(ast.literal_eval(msg)))
		#print(msg)

	s.close()       