// This file is part of xsonrpc, an XML/JSON RPC library.
// Copyright (C) 2015 Erik Johansson <erik@ejohansson.se>
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by the
// Free Software Foundation; either version 2.1 of the License, or (at your
// option) any later version.
//
// This library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
// for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the Free Software Foundation,
// Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

#ifndef XSONRPC_FORMATHANDLER_H
#define XSONRPC_FORMATHANDLER_H

#include <memory>
#include <string>

namespace xsonrpc {

class Reader;
class Writer;

class FormatHandler
{
public:
  virtual ~FormatHandler() {}

  virtual bool CanHandleRequest(const std::string& path,
                                const std::string& contentType) = 0;
  virtual std::string GetContentType() = 0;
  virtual bool UsesId() = 0;
  virtual std::unique_ptr<Reader> CreateReader(std::string data) = 0;
  virtual std::unique_ptr<Writer> CreateWriter() = 0;
};

} // namespace xsonrpc

#endif
