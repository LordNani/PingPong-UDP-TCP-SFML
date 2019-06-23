#pragma once
#include <map>
#include <SFML/Graphics.hpp>
class ResourceManager {
public:
	ResourceManager();
	static ResourceManager* getInstance() {
		static ResourceManager instance;
		return &instance;
	}
	~ResourceManager();
	void clearTextures();
	void clearImages();
	sf::Texture* RequestTexture(std::string texId);
	sf::Image* RequestImage(std::string imgId);
	bool addTextureFromFile(const std::string fileName, const std::string texId);
	bool addImageFromFile(const std::string fileName, const std::string imgId);
	bool addTextureFromImage(sf::Image &sourceImg, const std::string texId);
	bool addImageFromColor(unsigned int width, unsigned int  height, sf::Color& color, std::string imgId);
private:
	std::map<std::string, sf::Texture*> m_Textures;
	std::map<std::string, sf::Image*> m_Images;
};