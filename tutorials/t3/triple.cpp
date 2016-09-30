#include <iostream>
#include <string>
using namespace std;

template <typename TL, typename TR>
class Pair {
	TL* _objLeft; TR* _objRight;
	public:
		Pair(TL* pobjLeft, TR* pobjRight) :
			_objLeft(pobjLeft), _objRight(pobjRight) {}
		TL* getLeft() { return _objLeft; }
		TR* getRight() { return _objRight; }
};

template <typename TL, typename TM, typename TR>
class TemplateTripleInherit : public Pair<TL,TR> {
	TM* _objMiddle;	
	public:
		TemplateTripleInherit(TL* pobjLeft, TM* pobjMiddle, TR* pobjRight) :
			_objMiddle(pobjMiddle), Pair<TL,TR>(pobjLeft, pobjRight) {}
		TR* getMiddle() { return _objMiddle; }
};

template <typename TL, typename TM, typename TR>
class TemplateTripleComposite {
	Pair<Pair<TL,TR>,TM>* _triple;
	public:
		TemplateTripleComposite(TL* pobjLeft, TM* pobjMiddle, TR* pobjRight) {
			Pair<TL,TR>* LR_Pair = new Pair<TL,TR>(pobjLeft, pobjRight);
			_triple = new Pair<Pair<TL,TR>,TM>(LR_Pair, pobjMiddle);
		}
		~TemplateTripleComposite() {
			// TODO: delete stuff
		}
		TM* getMiddle() { return _triple->getRight(); }
		TL* getLeft() { return _triple->getLeft()->getLeft(); }
		TR* getRight() { return _triple->getLeft()->getRight(); }
};

class PersonInherit : public TemplateTripleInherit<string,double,double> {
	public:
		PersonInherit(string name, double weight, double height) : 
			TemplateTripleInherit(&name, &weight, &height) {}
		string getName() { return *getLeft(); }
		double getWeight() { return *getMiddle(); }
		double getHeight() { return *getRight(); }
};

class PersonComposite {
	private:
		TemplateTripleComposite<string,double,double> _info;
	public:
		PersonComposite(string name, double weight, double height) : 
			_info(TemplateTripleComposite<string,double,double>(&name, &weight,
			&height)) {}
		string getName() { return *(_info.getLeft()); }
		double getWeight() { return *(_info.getMiddle()); }
		double getHeight() { return *(_info.getRight()); }
};

int main() {
	return 0;
}
