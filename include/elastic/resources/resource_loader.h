// Copyright (c) 2015, Tiaan Louw
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
// OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef ELASTIC_RESOURCES_RESOURCE_LOADER_H_
#define ELASTIC_RESOURCES_RESOURCE_LOADER_H_

#include <functional>
#include <memory>

namespace el {

template <typename ResourceType>
// ResourceType: The resource we are loading.
class ResourceLoader {
public:
  using LoaderFunc = std::function<std::unique_ptr<ResourceType>()>;

  ResourceLoader(const LoaderFunc& func, const std::string& id)
    : m_func(func), m_id(id) {}

  std::unique_ptr<ResourceType> load() const { return m_func(); }

  const std::string& getId() { return m_id; }

private:
  LoaderFunc m_func;
  std::string m_id;
};

}  // namespace el

#endif  // ELASTIC_RESOURCES_RESOURCE_LOADER_H_
