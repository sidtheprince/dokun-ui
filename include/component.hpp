#pragma once

#ifndef COMPONENT_HPP_DOKUN // can be set to an entity as a part of a piece of data
#define COMPONENT_HPP_DOKUN	

#include "types.hpp" // custom data types
#include "string.hpp" // dokun string
#include "vector.hpp" // vector class
#include "factory.hpp" // for storing components

#ifdef __cplusplus
#include <iostream>
#include <string>
#include <functional>
#if defined(__cplusplus) && (__cplusplus >= 201703L)
#include <any> // std::any (C++17)
#endif
#include <type_traits> // decltype
#include <lua.hpp>

/*union*/struct Component // a part or attribute of an entity; This class is essential if you want to add custom class members
{
	Component();
	Component(const std::string& name);
	Component(const std::string& name, int value, bool is_boolean_ = false);
	Component(const std::string& name, double value);
	Component(const std::string& name, const std::string& value);
	Component(const std::string& name, const String& value);
	Component(const std::string& name, const Vector2& value);
	Component(const std::string& name, const Vector3& value);
	Component(const std::string& name, const Vector4& value);
	Component(const std::string& name, const void * value);
	Component(const std::string& name, lua_CFunction value);
	Component(const std::string& name, std::function<void (void)> function);
	~Component();
	// normal
	static Component * create();                                        static int create(lua_State *L);// creates a new component
	static Component * create(const std::string& name);
    static Component * create(const std::string& name, int value, bool is_boolean_ = false);
	static Component * create(const std::string& name, double value);
    static Component * create(const std::string& name, const std::string& value);
	static Component * create(const std::string& name, const String& value);
	static Component * create(const std::string& name, const Vector2& value);
	static Component * create(const std::string& name, const Vector3& value);
	static Component * create(const std::string& name, const Vector4& value);
	static Component * create(const std::string& name, const void * value);
	static Component * create(const std::string& name, lua_CFunction value);
	static Component * create(const std::string& name, std::function<void (void)> value);
	void destroy();                                                     static int destroy(lua_State *L);// destroys a component
	void call();                                                        static int call(lua_State *L);// calls a function
 	// setters
	void set_name(const std::string& name);                             static int set_name(lua_State *L); // set the name of the component
	void set_value(int value, bool is_boolean_ = false); // can be a boolean_ or an integer                 //static int set_value(lua_State *L);// set the value of the component
	void set_value(double value); // a decimal number (float, double, etc.)
	void set_value(const std::string& value); // must use 'std::string(value)' instead of 'value'
	void set_value(const String& value);
	void set_value(const Vector2& value);
	void set_value(const Vector3& value);
	void set_value(const Vector4& value);
	void set_value(const void * value);
	void set_value(lua_CFunction value);
	void set_value(std::function<void (void)> value);
	private:
	void set_type(int type);                   static int set_type(lua_State *L);
    public:	
    // setters
    template<typename V> void set(V val) {
        if (std::is_same<V, bool>::value) {
            this->boolean_ = val;
        }    
        if ((std::is_same<V, double>::value) || (std::is_same<V, float>::value) || (std::is_same<V, int>::value)) {
            this->number = val;
        }        
        // std::string will not work with "typename V". This will cause an error (works for integers only)
        //if (std::is_same<V, std::string>::value) {}

        /*if (std::is_same<V, ?>::value) { 
            std::cout << "V is a \n";
        }*/    
    }	    
    template<typename V> void set(const std::string& val) {
        if((std::is_same<V, std::string>::value) || (std::is_same<V, String>::value)) { 
            this->string = val;
        } 
    }
    template<typename V> void set(void * val) {
        if (std::is_same<V, void *>::value) { 
            this->pointer = val;
        }
    }
    template<typename V> void set(const Vector4& val) {
        if (std::is_same<V, Vector4>::value) { 
            this->vector = val;
        }
    }
    template<typename V> void set(lua_CFunction val) {
        if (std::is_same<V, lua_CFunction>::value) { 
            this->lua_function = val;
        }    
    }
    template<typename V> void set(std::function<void (void)> val) {
        if (std::is_same<V, std::function<void (void)>>::value) { 
            this->function = val;
        }   
    }
    // todo: set(std::function) {}
    //-------------------------------
	// getters
    //#if defined(__cplusplus) && (__cplusplus < 201703L)
    template<typename T> T get() {
        if (std::is_same<T, bool>::value) {
            std::cout << "T is a boolean GET\n";
            //return this->boolean_;
        }    
        if ((std::is_same<T, double>::value) || (std::is_same<T, float>::value) || (std::is_same<T, int>::value)) {
            std::cout << "T is a number GET\n";
            //return this->number;
        }   
        // std::string will not work with "typename V". This will cause an error (works for integers only)
        //if(std::is_class<T>::value) {
        /*if (std::is_same<T, std::string>::value) { 
            std::cout << "T is an string GET\n";
            return this->string.str(); // doesn't work :/
        }*/
        //}
        /*if (std::is_same<T, ?>::value) { 
            std::cout << "T is a \n";
        }*/    
        //return t;
        /*
        	double number; // int, float, double, etc.
	String string; // std::string or const char *
	int boolean_;   // bool
	void * pointer; // void *, SomeClass *
	Vector4 vector; // Vector2, Vector3, Vector4
	std::function<void (void)> function; // void (*f)()
	lua_CFunction lua_function;
        */
    }	
    /*template<typename T> std::string get(bool is_string) {    
        if((std::is_same<T, std::string>::value) || (std::is_same<T, String>::value)) { 
            return this->string.str();
        }
    }*/           
    //-------------------------------
    /*// Works but only with C++17 :(
    template<typename T> T get() {  
        // if constexpr is a C++17 feature :/  
        if constexpr ((std::is_same<T, std::string>::value) || (std::is_same<T, String>::value)) { 
            return this->string.str();
        }    
        if constexpr (std::is_same<T, bool>::value) {
            std::cout << "T is a boolean GET\n";
            return this->boolean_;
        }    
        if constexpr ((std::is_same<T, double>::value) || (std::is_same<T, float>::value) || (std::is_same<T, int>::value)) {
            std::cout << "T is a number GET\n";
            return this->number;
        }            
    }*/	 
    //-------------------------------
    template<class T> T get_class() { // there's no difference between class and typename
        if((std::is_same<T, std::string>::value) || (std::is_same<T, String>::value)) { 
            return this->string.str();
        } 
        /*if (std::is_same<T, ?>::value) { 
            std::cout << "T is a \n";
        }*/    
        //return t;
    }	    
    //#endif
    /*#if defined(__cplusplus) && (__cplusplus >= 201703L)	
    template<typename T>
    std::any get() {
        if (std::is_same<T, bool>::value) {
            std::cout << "T is a boolean GET\n";
            std::any return_boolean = this->boolean_;
            return return_boolean;
        }    
        if ((std::is_same<T, double>::value) || (std::is_same<T, float>::value) || (std::is_same<T, int>::value)) {
            std::cout << "T is a number GET\n";
            std::any return_number = this->number;
            return return_number;
        }        
        if (std::is_same<T, std::string>::value) { 
            std::cout << "T is an string GET\n";
            std::any return_str = this->string.str();
            //return std::any_cast<std::string>(return_str);//this->string.str(); // doesn't work :/
        }
    }		
    #endif*/
    /* Usage:
    Component * component = new Component();
    
    component->set_name("age");
    component->set<int>(14);
    std::cout << "age: " << component->get<int>() << std::endl;
    
    component->set_name("name");
    component->set<std::string>("Sid");
    std::cout << "name: " << component->get_class<std::string>() << std::endl;
    
    component->set_name("function");
    auto some_void_function = []() { return; };
    component->set<std::function<void (void)>>(some_void_function);  
    //std::cout << "name: " << component->get_class<std::string>() << std::endl;  
    */    
	int get_type()  const;                     static int get_type(lua_State *L); // get data type              
	void * get_value();                        static int get_value(lua_State *L);
	// other getters
	std::string get_name();                    static int get_name(lua_State *L);
	int get_id();                              static int get_id(lua_State *L);
	// conversion
	int to_integer() const;
	double to_double() const;
	float to_float() const;
	std::string to_string() const;
	bool to_boolean() const;	
	Vector4 to_vector() const;
	void * to_pointer() const;	
	std::function<void (void)> to_function() const;
	// boolean_
	//////////
	// operator overrides
	//////////
	friend std::ostream& operator << (std::ostream& os, Component * component) // String s; std::cout << s ;
	{   	   
		if(component->get_type() == -1)
		{
			os << std::string("no value");
		}
		if(component->get_type() == 0)
		{
			os << component->to_integer();
		}
		if(component->get_type() == 1)
		{
			os << component->to_double();
		}
		if(component->get_type() == 2)
		{
			os << component->to_string();
		}
		if(component->get_type() == 3)
		{
			os << component->to_vector();
		}
		if(component->get_type() == 4)
		{
			os << component->to_pointer();
		}
		if(component->get_type() == 5)
		{
			os << &component->function;
		}
		return (os);
	} 
	friend std::ostream& operator << (std::ostream& os, const Component& component) // String s; std::cout << s ;
	{ 
		if(component.get_type() == -1)
		{
			os << std::string("no value");
		}
		if(component.get_type() == 0)
		{
			os << component.to_integer();
		}
		if(component.get_type() == 1)
		{
			os << component.to_double();
		}
		if(component.get_type() == 2)
		{
			os << component.to_string();
		}
		if(component.get_type() == 3)
		{
			os << component.to_vector();
		}
		if(component.get_type() == 4)
		{
			os << component.to_pointer();
		}
		if(component.get_type() == 5)
		{
			os << &component.function;//
		}
		return (os);	
	}	
	//////////
	//////////
	// properties
	std::string name;
	int type;
	//////////////
	//union value {
	double number; // int, float, double, etc.
	String string; // std::string or const char *
	int boolean_;   // bool
	void * pointer; // void *, SomeClass *
	Vector4 vector; // Vector2, Vector3, Vector4
	std::function<void (void)> function; // void (*f)()
	lua_CFunction lua_function;
	//};
	//////////////
};
/*
NOTE: Components have names so they can be easily accessed through their names and id as well.

Setting and Getting Components:
    Entity * player = new Entity();
    
	player->set_component(new Component("level"));
    player->set_component(new Component("name"));
	player->set_component(Component::create("self"));
	
	player->get_component("level")->set_value(23);
   	player->get_component("name")->set_value(String("Sid"));
	player->get_component("self")->set_value(new Model());
	
	std::cout << player->get_component("level")->to_integer() << std::endl;
	std::cout << player->get_component("name")->to_string() << std::endl;
	std::cout << player->get_component("self")->to_pointer() << std::endl;

	// create an entity
	Sprite * player = new Sprite();
	// add a new component called 'name'
	player->set_component(new Component("name"));
	// set 'name' component's value
	player->get_component("name")->set_value(String("Sid"));
	// print 'name' component's value
	std::cout << player->get_component("name")->to_string() << std::endl;
	
	
Calling Functions:
    void eat()
    {
	    std::cout << "I am eating" << std::endl;
    }    

    Sprite * player = new Sprite();
    player->set_component(Component::create("function", eat));	
	
	player->get_component("function")->call();	
	
	
USAGE:
    // create entity with a Model component	
    Entity * entity = new Entity();
	// set component 'cube' to (new Model())
	entity->set_component(*new Component("monkey", new Model("monkey.obj")));
	// get component 'cube'
	Model * m = reinterpret_cast<Model *>(entity->get_component("monkey")->get_value_ptr());
	if(m)
	{
		m->draw();
	}
	------------
    // create entity with a integer component	
    Entity * entity = new Entity();
	// set component 'power' to 10
	entity->set_component(*new Component("power", 10));
	// get component 'power'
	int power = entity->get_component("power")->get_value();
    std::cout << power << std::endl;	
*/
#endif
#endif
