#include "includes.h"
#pragma comment(lib, "wininet.lib")

int main()
{   
    std::string responce = web::get_request ( "example.com", "", "", "" );
    printf ( responce.c_str ( ) );
    return 0;
}