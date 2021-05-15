
//creation d'une application transfert de fichier en utilisant la connection a distance ssh  est le protocole de transfert des fichier sftp par youssef abdoul / driss echahraoui/achraf bekkali / walid bouwechma
/*les biblio necessaire */
#include <iostream>
#include <libssh/libssh.h>
#include <libssh/sftp.h>
#include <stdlib.h>
#include <stdio.h> 
#include<stdlib.h>
#include <stdio.h>

using namespace std;
int main()
{// creation dune session ssh 
	ssh_session mysession;
	int rc;
	int port = 22;
	int verbosity = SSH_LOG_PROTOCOL;
	char password[]="password";
	// session-open est initialisation des parametre du session 
	mysession = ssh_new();
	if (mysession == NULL)
		exit(-1);
	ssh_options_set(mysession, SSH_OPTIONS_HOST, "192.168.1.6");
	ssh_options_set(mysession, SSH_OPTIONS_USER, "youssef");
	ssh_options_set(mysession, SSH_OPTIONS_LOG_VERBOSITY, &verbosity);
	ssh_options_set(mysession, SSH_OPTIONS_CIPHERS_C_S, "");

	//ssh_options_set(my_ssh_session, SSH_OPTIONS_PORT, &port);
	// Connect to server
	rc = ssh_connect(mysession);
	if (rc != SSH_OK)
	{
		ssh_free(mysession);
		exit(-1);
	}

//password 	
	rc = ssh_userauth_password(mysession, NULL, password);
	if (rc != SSH_AUTH_SUCCESS)
	{
			ssh_get_error(mysession));
		ssh_disconnect(mysession);
		ssh_free(mysession);
		exit(-1);
	}


	
	char buffer[256];
	unsigned int nbytes;

	
	int access_type = O_WRONLY | O_CREAT | O_TRUNC;
	const char *helloworld = "Hello, World!\n";
	int length = strlen(helloworld);


	sftp = sftp_new(mysession);
	if (sftp == NULL)
	{
		fprintf(stderr, "Error allocating SFTP session: %s\n",
			ssh_get_error(mysession));
		return SSH_ERROR;
	}
	
	rc = sftp_init(sftp);
	if (rc != SSH_OK)
	{
			sftp_get_error(sftp));
		sftp_free(sftp);
		return rc;
	}

	
	file = sftp_open(sftp, "entrer la direction de fichier ici", access_type, 1);
	if (file == NULL)
	{
		return SSH_ERROR;
	}

	nwritten = sftp_write(file, helloworld, length);
	if (nwritten != length)
	{
			ssh_get_error(mysession));
		sftp_close(file);
		return SSH_ERROR;
	}
}