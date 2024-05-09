#include "entities.h"

void Entity::CreateEntity(std::string TextureName, sf::IntRect textureRect)
{
	tex->loadFromFile(TextureName);
	entity.setTexture(tex);
	entity.setTextureRect(textureRect);
}

