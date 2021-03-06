// Copyright 2015 Piotr Tworek. All rights reserved.
// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef QUICKSILVER_BROWSER_URL_REQUEST_CONTEXT_GETTER_QS_H_
#define QUICKSILVER_BROWSER_URL_REQUEST_CONTEXT_GETTER_QS_H_

#include "base/compiler_specific.h"
#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "content/public/browser/content_browser_client.h"
#include "net/proxy/proxy_config_service.h"
#include "net/url_request/url_request_context_getter.h"
#include "net/url_request/url_request_job_factory.h"

namespace base {
class MessageLoop;
}

namespace net {
class HostResolver;
class MappedHostResolver;
class NetworkDelegate;
class NetLog;
class ProxyConfigService;
class ProxyService;
class URLRequestContextStorage;
}

namespace QuickSilverImpl {

class URLRequestContextGetterQS : public net::URLRequestContextGetter {
 public:
  URLRequestContextGetterQS(
      bool ignore_certificate_errors,
      const base::FilePath& base_path,
      base::MessageLoop* io_loop,
      base::MessageLoop* file_loop,
      content::ProtocolHandlerMap* protocol_handlers,
      content::URLRequestInterceptorScopedVector request_interceptors,
      net::NetLog* net_log);

  // net::URLRequestContextGetter implementation.
  net::URLRequestContext* GetURLRequestContext() override;
  scoped_refptr<base::SingleThreadTaskRunner> GetNetworkTaskRunner()
      const override;

  net::HostResolver* host_resolver();

 protected:
  ~URLRequestContextGetterQS() override;

  // Used by subclasses to create their own implementation of NetworkDelegate
  // and net::ProxyService.
  virtual net::NetworkDelegate* CreateNetworkDelegate();
  virtual net::ProxyConfigService* GetProxyConfigService();
  virtual net::ProxyService* GetProxyService();

 private:
  bool ignore_certificate_errors_;
  base::FilePath base_path_;
  base::MessageLoop* io_loop_;
  base::MessageLoop* file_loop_;
  net::NetLog* net_log_;

  scoped_ptr<net::ProxyConfigService> proxy_config_service_;
  scoped_ptr<net::NetworkDelegate> network_delegate_;
  scoped_ptr<net::URLRequestContextStorage> storage_;
  scoped_ptr<net::URLRequestContext> url_request_context_;
  content::ProtocolHandlerMap protocol_handlers_;
  content::URLRequestInterceptorScopedVector request_interceptors_;

  DISALLOW_COPY_AND_ASSIGN(URLRequestContextGetterQS);
};

}  // namespace QuickSilverImpl

#endif  // QUICKSILVER_BROWSER_URL_REQUEST_CONTEXT_GETTER_QS_H_
