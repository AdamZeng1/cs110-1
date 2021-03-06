/**
 * File: request-handler.h
 * -----------------------
 * Defines the HTTPRequestHandler class, which fully proxies and
 * services a single client request.  
 */

#ifndef _request_handler_
#define _request_handler_

#include <utility>
#include <string>
#include "request.h"
#include "response.h"
#include "cache.h"
#include "blacklist.h"
#include <socket++/sockstream.h> // for sockbuf, iosockstream

class HTTPRequestHandler {
  public:
    HTTPRequestHandler() throw (HTTPProxyException);
    void serviceRequest(const std::pair<int, std::string>& connection) throw();
    void clearCache();
    void setCacheMaxAge(long maxAge);
    void setProxy(const std::string& server, unsigned short port);

  private:
    HTTPBlacklist blacklist;
    HTTPCache cache;
    bool usingProxy;
    std::string proxyServer;
    unsigned short proxyPortNumber;

    void ingestRequest(std::istream& instream, const std::string& clientIPAddress, HTTPRequest& request);
    void ingestResponse(std::istream& instream, const HTTPRequest& request, HTTPResponse& response);
    HTTPResponse createErrorResponse(int code, const std::string& message);
    void sendRequest(std::ostream& outstream, const HTTPRequest& request);
    void sendResponse(std::ostream& outstream, const HTTPResponse& response);
    bool findCircularProxyChain(const std::string& ipList, const std::string& ip);
};

#endif
