
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

  ResourceLoader(const LoaderFunc& func, const std::string& id) : m_func(func), m_id(id) {}

  std::unique_ptr<ResourceType> load() const { return m_func(); }

  const std::string& getId() { return m_id; }

private:
  LoaderFunc m_func;
  std::string m_id;
};

}  // namespace el

#endif  // ELASTIC_RESOURCES_RESOURCE_LOADER_H_
