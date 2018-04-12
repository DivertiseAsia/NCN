#include "Parser.hpp"
#include "Element.hpp"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <iterator>
#include <cstring>


ElementInt* ElementCreator::create(int value){
	auto e = new ElementInt();
	e->value = value;
	return e;
}
ElementString* ElementCreator::create(const char* value){
	auto e = new ElementString();
	e->value = value;
	return e;
}
ElementString* ElementCreator::create(std::string value){
	auto e = new ElementString();
	e->value = std::move(value);
	return e;
}
ElementBoolean* ElementCreator::create(bool value){
	auto e = new ElementBoolean();
	e->value = value;
	return e;
}
ElementArray* ElementCreator::array(){
	auto e = new ElementArray();
	return e;
}
ElementObject* ElementCreator::object(){
	auto e = new ElementObject();
	return e;
}
ElementArray* ElementCreator::add(ElementArray* e, Element* value){
	e->values.push_back(value);
	return e;
}
ElementObject* ElementCreator::put(ElementObject* e, const char* key, Element* value){
	e->values[new std::string(key)] = value;
	return e;
}
ElementDouble* ElementCreator::create(double value){
	auto e = new ElementDouble();
	e->value = value;
	return e;
}
ElementCreator::ElementCreator() = default;
ElementCreator::~ElementCreator() = default;
