#include "../includes.h"


std::string web::post_request ( std::string url, std::string dir, std::string headers, std::string params )
{
	HINTERNET hInternet = InternetOpenA( ( "WinINet" ), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0 );
	if ( hInternet == NULL )
	{
		return std::string ( );
	}

	HINTERNET hConnect = InternetConnectA ( hInternet, url.c_str(), INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0 );
	if ( hConnect == NULL )
	{
		InternetCloseHandle ( hInternet );
		return std::string ( );
	}

	HINTERNET hRequest = HttpOpenRequestA ( hConnect, ( "POST" ), dir.data ( ) ? dir.c_str ( ) : ( "/" ), NULL, NULL, NULL, INTERNET_FLAG_SECURE | INTERNET_FLAG_NO_COOKIES, 0 );
	if ( hRequest == NULL )
	{
		InternetCloseHandle ( hConnect );
		InternetCloseHandle ( hInternet );
		return std::string ( );
	}

	if ( !HttpSendRequestA ( hRequest, headers.c_str ( ), static_cast< DWORD >( headers.length ( ) ), const_cast< CHAR* >( params.c_str ( ) ), static_cast< DWORD >( params.length ( ) ) ) )
	{
		InternetCloseHandle ( hRequest );
		InternetCloseHandle ( hConnect );
		InternetCloseHandle ( hInternet );
		return std::string ( );
	}

	const int BUFFER_SIZE = 10000;
	char buffer [ BUFFER_SIZE ];
	DWORD bytesRead = 0;
	std::string response;

	while ( InternetReadFile ( hRequest, buffer, BUFFER_SIZE, &bytesRead ) && bytesRead > 0 )
	{
		response.append ( buffer, bytesRead );
	}

    InternetCloseHandle ( hRequest );
	InternetCloseHandle ( hConnect );
	InternetCloseHandle ( hInternet );

	return response;
}

std::string web::get_request ( std::string url, std::string dir, std::string headers, std::string params )
{
	HINTERNET hInternet = InternetOpenA ( ( "WinINet" ), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0 );
	if ( hInternet == NULL )
	{
		return std::string ( );
	}

	HINTERNET hConnect = InternetConnectA ( hInternet, url.c_str ( ), INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0 );
	if ( hConnect == NULL )
	{
		InternetCloseHandle ( hInternet );
		return std::string ( );
	}

	HINTERNET hRequest = HttpOpenRequestA ( hConnect, ( "GET" ), dir.data ( ) ? dir.c_str ( ) : ( "/" ), NULL, NULL, NULL, INTERNET_FLAG_SECURE | INTERNET_FLAG_NO_COOKIES, 0 );
	if ( hRequest == NULL )
	{
		InternetCloseHandle ( hConnect );
		InternetCloseHandle ( hInternet );
		return std::string ( );
	}

	if ( !HttpSendRequestA ( hRequest, headers.c_str ( ), static_cast< DWORD >( headers.length ( ) ), const_cast< CHAR* >( params.c_str ( ) ), static_cast< DWORD >( params.length ( ) ) ) )
	{
		InternetCloseHandle ( hRequest );
		InternetCloseHandle ( hConnect );
		InternetCloseHandle ( hInternet );
		return std::string ( );
	}

	const int BUFFER_SIZE = 10000;
	char buffer [ BUFFER_SIZE ];
	DWORD bytesRead = 0;
	std::string response;

	while ( InternetReadFile ( hRequest, buffer, BUFFER_SIZE, &bytesRead ) && bytesRead > 0 )
	{
		response.append ( buffer, bytesRead );
	}

	InternetCloseHandle ( hRequest );
	InternetCloseHandle ( hConnect );
	InternetCloseHandle ( hInternet );

	return response;
}

