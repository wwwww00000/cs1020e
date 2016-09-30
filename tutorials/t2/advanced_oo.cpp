#include <iostream>
using namespace std;

/*
 * Tutorial Part 1. Advanced OO
 *
 * (a) attributes under the protected keyword are accessible from subclasses,
 * thus enabling inheritance.
 *
 * (b) the method is inherited by the subclass
 *
 * (c) the makeSound(), fly() and stop() methods are overridden to make the
 * behaviour of the function specific to the invoking class.
 */

class Animal { // error (missing class keyword)
	protected: // error (inserted protected)
		string _name; // e.g. Cow
		string _sound; // e.g. moo
	public:
		Animal(string name, string sound) { _name = name; _sound = sound; }
		// virtual ~Animal() {};
		string getName() { return _name; }
		virtual void makeSound() { cout << _name << " goes " << _sound << endl;}
};

class Flyer : public Animal {
	protected:
		// string _name; error (no need to declare attributes of superclass)
		// string _sound;
		bool _isFlying;
	public:
		Flyer(string name, string sound)
		: Animal(name, sound), _isFlying(false) {}
		void makeSound() {
			if(_isFlying) cout << getName() << " goes flap flap" << endl;
			else Animal::makeSound();
		}
		void fly() { _isFlying = true; }
		void stop() { _isFlying = false; }
};

class Glider : public Flyer { // error (inserted public)
	private:
		bool _isGliding;
	public:
		Glider(string name, string sound)
		: Flyer(name, sound), _isGliding(false) {}
		void glide() { if(_isFlying) _isGliding = true; }
		void stop() { _isFlying = false; _isGliding = false; }
		void makeSound() {
			if(_isGliding) cout << getName() << " goes whoosh" << endl;
			else Flyer::makeSound(); // error (call method of superclass)
		}
};

/*
 * Tutorial Part 2. Inheritance & Polymorphism
 *
 * (a) _farm[0] holds a Animal* type. _farm is defined as an array of pointers
 *
 * (b) a simple dereference returns a instance of an Animal, which does not
 * possess the fly() method. Thus the typescast (Flyer*) is required.
 *
 * (c) the polymorphism will not work as we are working with pointers to the
 * generic subclass of Animals and the overridden methods are statically bound.
 * the virtual keyword would be required to allow for polymorphism.
 */

class OldMcDonald {
	private:
	Animal** _farm; // Old McDonald had a farm (still has now)
	const int _size; // Fixed farm size of 5
	public:
		OldMcDonald() : _size(5) {
			_farm = new Animal* [_size];	
		}
		~OldMcDonald() {
			for (int i = 0; i < _size; i++)
				delete _farm[i];
			delete [] _farm;
		}
		void makeSomeNoise() {
			for (int i = 0; i < _size; i++)
				_farm[i]->makeSound();
		}
		void fillThisFarm() {
			_farm[0] = new Flyer("Parrot", "squak");
			_farm[1] = new Animal("Cow", "moo");
			_farm[2] = new Flyer("Mosquito", "buzz");
			((Flyer*)_farm[2])->fly();
			_farm[3] = new Animal("Sheep", "mehh");
			_farm[4] = new Animal("Fish", "blurp");
		}
};

int main() {
	OldMcDonald hadAFarm;
	hadAFarm.fillThisFarm();
	hadAFarm.makeSomeNoise();

	return 0;	
}
