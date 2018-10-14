#include "Hamster.h"


const float Hamster::scale = 0.2f;

Hamster::Hamster(sf::Vector2f position, std::string name) : points(1000), name(name), pathCounter(-1), isPathing(false)
{
	hamsterRect.setSize(sf::Vector2f(320.f * scale, 320.f * scale));
	hamsterRect.setPosition(position);
	hamsterRect.setOrigin(hamsterRect.getSize().x / 2, hamsterRect.getSize().x / 2);
	hamsterRect.setFillColor(sf::Color::Yellow);

	font.loadFromFile("Fonts/BodoniFLF-Bold.ttf");
	nameText.setString(name);
	nameText.setFont(font);
	nameText.setCharacterSize(18.f);
	nameText.setPosition(sf::Vector2f(hamsterRect.getPosition().x, hamsterRect.getPosition().y - 50.f));
	nameText.setOutlineThickness(2.f);
	nameText.setOutlineColor(sf::Color::Black);
	nameText.setOrigin(nameText.getLocalBounds().width / 2.f, 0.f);

	hamsterTexture.loadFromFile("Images/hamster2.png");
	sprite.setScale(scale, scale);
	sprite.setTexture(hamsterTexture);
	sprite.setPosition(position);
	sprite.setOrigin(sprite.getTextureRect().width / 2.f, sprite.getTextureRect().height / 2.f);

	currentNode = nullptr;
	currentDest = nullptr;
}

//copy + new name constructor
Hamster::Hamster(Hamster* hamster, std::string name) : points(1000), name(name), pathCounter(-1), isPathing(false)
{
	hamsterRect.setSize(sf::Vector2f(320.f * scale, 320.f * scale));
	hamsterRect.setPosition(hamster->getHamsterRect().getPosition());
	hamsterRect.setOrigin(hamster->getHamsterRect().getSize().x / 2, hamster->getHamsterRect().getSize().y / 2);
	hamsterRect.setFillColor(sf::Color::Yellow);

	font.loadFromFile("Fonts/BodoniFLF-Bold.ttf");
	nameText.setString(name);
	nameText.setFont(font);
	nameText.setCharacterSize(18.f);
	nameText.setPosition(sf::Vector2f(hamster->getHamsterRect().getPosition().x, hamster->getHamsterRect().getPosition().y - 50.f));
	nameText.setOutlineThickness(2.f);
	nameText.setOutlineColor(sf::Color::Black);
	nameText.setOrigin(nameText.getLocalBounds().width / 2.f, 0.f);
	
	hamsterTexture.loadFromFile("Images/hamster1.png");
	sprite.setScale(scale, scale);
	sprite.setTexture(hamsterTexture);
	sprite.setPosition(hamster->getHamsterRect().getPosition());
	sprite.setOrigin(sprite.getTextureRect().width / 2.f, sprite.getTextureRect().height / 2.f);

	currentNode = nullptr;
	currentDest = nullptr;
}


Hamster::~Hamster()
{
}

unsigned Hamster::getLVL() //figure out points later, probably adjust the numbers in this function
{
	if		(points < 2000)	return 1;
	else if	(points < 3000)	return 2;
	else if	(points < 4000)	return 3;
	else if	(points < 5000)	return 4;
	else 					return 5;
}

void Hamster::update(sf::Time dt, std::unordered_map<sf::Vector2f,Node*>)
{
	if (path.size() > 0 && currentDest != nullptr && pathCounter >= 0) //traverse path if it exists
	{
		sf::Vector2f vector = { currentDest->circle.getPosition().x - hamsterRect.getPosition().x, currentDest->circle.getPosition().y - hamsterRect.getPosition().y };
		float distance = sqrtf(vector.x * vector.x + vector.y * vector.y);
		if (distance > currentDest->circle.getRadius()) //hamster has NOT yet reached the destination
		{
			float magnitude = sqrtf(vector.x * vector.x + vector.y * vector.y);
			sf::Vector2f unitVector = { vector.x / magnitude, vector.y / magnitude };
			hamsterRect.move(unitVector * 100.f * (float)dt.asMilliseconds() / 1000.f);
		}
		else //set current to the reached dest, clear the dest node
		{
			pathCounter--;
			currentNode = currentDest;
			if(pathCounter >= 0)
				currentDest = path.at(pathCounter);
		}
	}
	else if(path.size() > 0 && pathCounter < 0) //need a new dest!
	{
		clearPath();
		std::cout << "clear path, size: " << path.size() << std::endl;
	}
	sprite.setPosition(hamsterRect.getPosition());
	nameText.setPosition(hamsterRect.getPosition().x, hamsterRect.getPosition().y - 50.f); //update text pos to rect pos
}

std::string Hamster::getName()
{
	return name;
}

void Hamster::setName(std::string name)
{
	this->name = name;
}

sf::RectangleShape& Hamster::getHamsterRect()
{
	return hamsterRect;
}

sf::Text& Hamster::getNameText()
{
	return nameText;
}

sf::Sprite& Hamster::getSprite()
{
	return sprite;
}

Node* Hamster::getCurrentNode()
{
	return currentNode;
}

Node* Hamster::getCurrentDest()
{
	return currentDest;
}

bool Hamster::getIsPathing()
{
	return isPathing;
}

void Hamster::setCurrentNode(Node * node)
{
	currentNode = node;
}

void Hamster::setCurrentDest(Node * node)
{
	currentDest = node;
}

void Hamster::traverse(Node* start, Node* finish)
{
}

void Hamster::setPath(std::vector<Node*> path)
{
	this->path = path;
	pathCounter = path.size();
	currentDest = path.at(pathCounter - 1);
	isPathing = true;
	sf::VertexArray lines(sf::LinesStrip, path.size());
	for (int i = 0; i < path.size(); i++)
	{
		lines[i].position = path.at(i)->circle.getPosition();
		lines[i].color = sf::Color::Red;
	}
	vta = lines;
}

void Hamster::clearPath()
{
	isPathing = false;
	path.clear();
	vta.clear();
	pathCounter = -1;
	currentDest = nullptr;
}

std::vector<Node*> Hamster::getPath()
{
	return path;
}
