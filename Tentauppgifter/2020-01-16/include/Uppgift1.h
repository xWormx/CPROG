#ifndef UPPGIFT1_h
#define UPPGIFT1_h

#include <string>
#include <map>
#include <stdexcept>
class Person
{
	public:
		Person(std::string n) : name(n) {}
		std::string getName() const { return name; }


	private:
		std::string name;
		int refCount = 0; // Används av objekt av Pointer-klassen
		friend class Pointer;	// Pointer objekt får åtkomst till private data
};


class Pointer
{
	public:
		Pointer(Person* p = 0) : pers(p) {
			if(pers != nullptr)
				pers->refCount++;
		}

		Pointer(const Pointer& other){
			if(other.pers != nullptr){
				pers = other.pers;
				other->refCount++;
			}
		}

		Person* operator->() const{
			if( pers == nullptr)
				throw std::logic_error("Null pointer!");
			else	
				return pers;
		}
		
		const Pointer& operator=(const Pointer& other){
			if(pers != other.pers){
				if(--pers->refCount == 0)
					delete pers;
				pers = other.pers;
				other->refCount++;
			}
			return *this;
		}

	
	private:
		Person* pers;
};

#endif