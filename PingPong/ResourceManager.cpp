#include "ResourceManager.h"

ResourceManager::ResourceManager() {

}


sf::Texture* ResourceManager::RequestTexture(std::string texId) {
	if (m_Textures[texId]) return m_Textures[texId];

	return nullptr;
}
sf::Image* ResourceManager::RequestImage(std::string imgId) {
	if (m_Images[imgId]) return m_Images[imgId];

	return nullptr;
}

bool ResourceManager::addTextureFromFile(const std::string fileName, const std::string texId) {
	sf::Texture *tex = new(sf::Texture);
	if (!tex->loadFromFile("assets\\" + fileName))
		return false;
	m_Textures.insert(std::pair< std::string, sf::Texture*>(texId,tex));
	return true;
}

bool ResourceManager::addImageFromFile(std::string fileName, std::string imgId) {
	sf::Image* img = new(sf::Image);
	if (!img->loadFromFile("assets\\" + fileName))
		return false;
	m_Images.insert(std::pair< std::string, sf::Image*>(imgId, img));
	return true;
}

bool ResourceManager::addTextureFromImage(sf::Image &sourceImg, const std::string texId) {
	sf::Texture* tex = new(sf::Texture);
	if(!tex->loadFromImage(sourceImg))
		return false;
	m_Textures.insert(std::pair< std::string, sf::Texture*>(texId, tex));
	return true;
}

bool ResourceManager::addImageFromColor( unsigned int width, unsigned int  height, sf::Color &color,std::string imgId) {
	sf::Image* img = new(sf::Image);
	img->create(width, height, color);
	m_Images.insert(std::pair< std::string, sf::Image*>(imgId, img));
	return true;
}

void ResourceManager::clearTextures() {
	for (auto& i : m_Textures) {
		delete i.second;
		i.second = nullptr;
	}
}
void ResourceManager::clearImages() {
	for (auto& i : m_Images) {
		delete i.second;
		i.second = nullptr;
	}
}

ResourceManager::~ResourceManager() {}