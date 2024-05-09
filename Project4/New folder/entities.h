#pragma once
#include"includes.h"
struct Entity
{
	sf::RectangleShape entity;
	sf::Texture* tex = new sf::Texture;
	sf::IntRect tr;
	void CreateEntity(std::string TextureName, sf::IntRect textureRect);
};