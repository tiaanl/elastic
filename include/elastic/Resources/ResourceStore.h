
#ifndef ELASTIC_RESOURCES_RESOURCE_STORE_H_
#define ELASTIC_RESOURCES_RESOURCE_STORE_H_

#include <unordered_map>

#include "elastic/Resources/ResourceLoader.h"
#include "nucleus/Macros.h"

namespace el {

template <typename ResourceType, typename IdType>
// ResourceType: The type of resource we are storing.
// IdType: The type used to identify resources in the store.
class ResourceStore {
public:
  ResourceStore() {}

  // Load the resource and insert it in the store.  Returns false if the
  // resource could not be loaded.
  bool load(const IdType& id, const ResourceLoader<ResourceType>& loader) {
    ResourceEntry newEntry{loader.load(), loader};
    if (!newEntry.resource) {
      return false;
    }

    // Insert the resource into the store.
    m_resources.insert(std::make_pair(id, std::move(newEntry)));

    // Success.
    return true;
  }

  ResourceType* get(const IdType& id) {
    auto it = m_resources.find(id);
    if (it == std::end(m_resources)) {
      return nullptr;
    }

    return it->second.resource.get();
  }

private:
  struct ResourceEntry {
    // The resource we own.
    std::unique_ptr<ResourceType> resource;

    // The loader used to create the resource.
    ResourceLoader<ResourceType> loader;

    ResourceEntry(std::unique_ptr<ResourceType> resource, const ResourceLoader<ResourceType>& loader)
      : resource(std::move(resource)), loader(loader) {}

    ResourceEntry(ResourceEntry&& other) : resource(std::move(other.resource)), loader(other.loader) {}
  };

  // Id's mapped to resource entries.
  std::unordered_map<IdType, ResourceEntry> m_resources;

  DISALLOW_COPY_AND_ASSIGN(ResourceStore);
};

}  // namespace el

#endif  // ELASTIC_RESOURCES_RESOURCE_STORE_H_
