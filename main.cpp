#include<iostream>
#include<cstring>
using namespace std;


class Animal
{

    public:
        Animal(const string &type, const string &name, const int &age);
        void printAnimal()
	    {
            cout<<"Type:"<<type<<" name:"<<name<<" age:"<<age;
        }
        Animal& operator=(Animal& other)       
        {
            // Verificam daca referinta obiectul other este diferita de cea a obiectului this -> item 11
            if(this != &other)
            {
                this->type= other.type;
                this->name = other.name;
                this->age = other.age;
            }
            else
            {
                cout<<"This and other have the same reference";
            }

            // Facem return *this pentru a ne asigura ca se pastrea referinta obiectului apelat -> item 10
            return *this;          
        }


    private:
        string type;
        string name;
        int age;
};
//Am creeat constructorul cu member initialization list in interiorul acesteia->itemul 4
Animal::Animal(const string &type, const string &name, const int &age)
    :type(type),
    name(name),
    age(age)
{}

/*In clasa WildAnimals nu avem declarati de noi constructor, destructor, copy constructor si copy assignment operator deoarece ne asteptam ca C++ sa declare un copy constructor,copy
assignment operator, destructor si default contructor ->itemul 5*/
class WildAnimal{
    public:
        void printAnimal()
	{
            cout<<"Wild Animal";
    }
};
// Am creat clasa Uncopyable unde am pus pe privat copy constructorul si copy assigment operatorul
class Uncopyable{
    protected:
        Uncopyable(){}
        ~Uncopyable(){}

    private:
        Uncopyable(const Uncopyable&);  //copy constructor
        Uncopyable &operator = (const Uncopyable&); //copy assignment operator

};
//In clasa Pets dorim sa nu avem declarat un copy constructor sau un copy assignment operator
//Pt ca Pets mosteneste Uncopyable, compilatorul nu creeaza opy constructorul si copy assigment operatorul pentru ca nu are acces la ele->item 6
class Pet: Uncopyable{
    public:
        Pet(string name);
        void printAnimals()
        {
            cout<<pet_name<<endl;
        }
    private:
        string pet_name;

};
Pet::Pet(string name)
{
   pet_name=name;
}

class Dog: public Animal{
    public:
    Dog(const string &type, const string &name, const int &age, const string &breed); 
    Dog& operator=(Dog& rhs);
    void printDog()
	{
            Animal::printAnimal();
            cout<<" breed:"<<breed;
    }

    private:
    string breed;
};
// M-am folosit de constructorul clasei de baza pentru a initializa atributele mostenite din acea clasa -> item 12
Dog::Dog(const string &type, const string &name, const int &age, const string &breed)
:Animal(type,name,age),       
breed(breed)
{}

// M-am folosit de copy assignmentul de la clasa de baza pentru a fi sigur ca o sa copiem toate partile obiectului -> item 12
Dog&Dog::operator=(Dog& rhs){
    Animal::operator=(rhs);               
    breed = rhs.breed;
    return *this;
}



int main()
{
    //Item 4: sa initializam toate obiectele
    Animal animal1("Mammalian","Wolf",13);
    Pet pet1("Dog");
    animal1.printAnimal();

    //Item 5: In clasa WildAnimal nu are constructor, destructor, copy constructor si copy assignment operator dar sunt creeate de compilator
    WildAnimal wildanimal1; //Se apeleaza default constructorul
    WildAnimal wildanimal2(wildanimal1);  //Se apeleaza copy constructor
    wildanimal2 = wildanimal1; // Se apeleaza copy assignment
    wildanimal1.~WildAnimal(); //Se apeleaza destructorul
    //Item 6: Vrem sa nu lasam compilatorul sa creeze copy constructor si copy assignment operator
    // Pet pet2(pet1);
    // Pet pet2 = pet1;
    //Prin cele 2 linii de sus am vrut sa verific daca pet-ul nu poate accesa copy constructor si copy assignment operator

    Animal animal2("Mammalian","Lion",5);
    Animal animal3("Mammalian","Bear",2);
    Animal animal4("Mammalian","Tiger",6);
    //Item 10/11: Datorita "return *this" cele 3 obiecte o sa aibe aceeasi valoare dar fiecare o sa isi pastreze referinta diferita
    animal2=animal3=animal4;

    Dog dog1("Mammalian","Dog",3,"Pug");
    dog1.printDog();



    return 0;
}