#include <iostream>
#include <string>
using namespace std;

class Animal {
	private:
		string _name;
		string _sound;
	public:
		Animal(string name, string sound) {
			_name = name;
			_sound = sound;
		}
		void verse() {
			cout << _name << " goes " << _sound << endl;
		}
};

class Song {
	private:
		Animal** _animals;
		const int _size = 5;
	public:
		Song() {
			_animals = new Animal* [_size];
			_animals[0] = new Animal("Dog", "woof");
			_animals[1] = new Animal("Cat", "meow");
			_animals[2] = new Animal("Bird", "tweet");
			_animals[3] = new Animal("Mouse", "squeak");
			_animals[4] = new Animal("Cow", "moo");
		}
		~Song() {
			for (int i = 0; i < _size; i++)
				delete _animals[i];		
			delete [] _animals;		
		}

		void display() {
			for (int i = 0; i < _size; i++)
				_animals[i]->verse();
		}
};

int main() {
	Song song;
	song.display();
	return 0;
}
