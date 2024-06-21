#pragma once


struct web
{ 
    //set url without http/https [https://example.com] -> [example.com]
    static std::string post_request ( std::string url, std::string dir, std::string headers, std::string params );
    static std::string get_request ( std::string url, std::string dir, std::string headers, std::string params );
};