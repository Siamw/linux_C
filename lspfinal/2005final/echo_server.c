

#if 0 

for( ; ; ; ) 
{
	 /*   clnt_sock �� accept �Լ��� ���� ���� ������
	      �� Ŭ���̾�Ʈ ���� ���� �̴�. */
	clnt_sock = accept( serv_sock,  (struct sockaddr*)&clnt_addr, 
				&clnt_addr_size );


	write( clnt_sock, message, sizeof(message ) );
	close( clnt_sock );

}

return 0;


#endif 



for( ; ; ; ) { 

	clnt_sock = accept ( serv_sock, (struct sockaddr*)&clnt_addr, 
				&clnt_addr_size );


while( ( str_len = read( clnt_sock, message, BUFSIZE) ) != 0 ) { 
	write( clnt_sock, message, str_len );
	/* �ֿܼ� ��� */
	write( 1, message, str_len );
}

close( clnt_sock );

}


