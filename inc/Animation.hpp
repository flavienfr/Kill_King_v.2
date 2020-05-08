#ifndef ANIMATION_HPP
# define ANIMATION_HPP

class Animation
{
public:
	Animation();
	Animation(unsigned int index, unsigned int numFrames, unsigned int animationSpeed);
	~Animation();

	unsigned int index;//private with accesor
	unsigned int numFrames;//private with accesor
	unsigned int animationSpeed;//private with accesor
};

#endif
