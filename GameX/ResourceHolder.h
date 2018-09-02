#pragma once
#include <map>
#include <memory>
#include <assert.h>
#include <SFML/Graphics.hpp>
#include "Textures.h"
template<class Resource, class Identifier>
class ResourceHolder {
public:
	void load(Identifier id, const std::string &filePath) {
		std::unique_ptr<Resource> texture(new Resource());
		if (!texture->loadFromFile(filePath)) {
			throw std::runtime_error("Error loading " + filePath);
		}
		auto inserted = mResourceMap.insert(std::make_pair(id, std::move(texture)));

		assert(inserted.second);
	}

	template<class SecondParam>
	void load(Identifier id, const std::string &filePath, SecondParam param) {
		std::unique_ptr<Resource> texture(new Resource());
		if (!texture->loadFromFile(filePath, param)) {
			throw std::runtime_error("Error loading " + filePath);
		}
		auto inserted = mResourceMap.insert(std::make_pair(id, std::move(texture)));

		assert(inserted.second);
	}

	Resource& get(Identifier id) {
		auto found = mResourceMap.find(id);
		return *(found->second);
	}

private:
	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};