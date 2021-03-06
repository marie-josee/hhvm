/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010-2013 Facebook, Inc. (http://www.facebook.com)     |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#ifndef incl_HPHP_RUNTIME_SERVER_FASTCGI_SESSION_H_
#define incl_HPHP_RUNTIME_SERVER_FASTCGI_SESSION_H_

#include "hphp/runtime/server/fastcgi/protocol-session-handler.h"
#include "folly/io/IOBuf.h"

namespace HPHP {

////////////////////////////////////////////////////////////////////////////////

class ProtocolSession {
public:
  class Callback {
  public:
    virtual ~Callback() {}

    virtual std::shared_ptr<ProtocolSessionHandler>
      newSessionHandler(int handler_id) = 0;
    virtual void onSessionEgress(std::unique_ptr<folly::IOBuf> chain) = 0;
    virtual void onSessionError() = 0;
    virtual void onSessionClose() = 0;
  };

  virtual ~ProtocolSession() {}

  virtual size_t onIngress(const folly::IOBuf* chain) = 0;
  void setCallback(Callback* callback) {
    m_callback = callback;
  }

protected:
  Callback* m_callback;
};

////////////////////////////////////////////////////////////////////////////////
}

#endif // incl_HPHP_RUNTIME_SERVER_FASTCGI_SESSION_H_

