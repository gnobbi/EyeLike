#include "precompiled.h"

#include <signals/signals.h>


struct Foo {
	void bar(std::string s) {
		std::cout << s << std::endl;
	}

	void bar(std::string s, int j, int a) {
		std::cout << s << j << std::endl;
	}

	auto GetSlot() {
		return [&](auto... args) { this->bar(args...); };
	}
};


int main() {
	Foo foo;
	mybase::Signal<void, std::string, int, int> Event;

	auto index = Event.Subscribe(foo.GetSlot());
	auto index2 = Event.Subscribe(foo.GetSlot());
	auto index3 = Event.Subscribe(foo.GetSlot());
	auto index4 = Event.Subscribe(foo.GetSlot());
	auto index5 = Event.Subscribe(foo.GetSlot());

	Event.Emit("Hallo", 10, 10);

	Event.Release(index2);
	Event.Release(index3);
	Event.Release(index4);
	Event.Release(index5);

	Event.Emit("new", 10, 10);

}