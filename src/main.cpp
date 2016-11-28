#include <iostream>
#include <Window/Window.h>
#include <Image/Image.h>
#include <xml/xml.h>

#include <iostream>
#include <vector>
#include <functional>
#include <chrono>
#include <string>
#include <map>
#include <set>

#include <functional>

template<class R, class... Args>
struct Signal {
	std::vector<std::function<R(Args...)>> vec;
	int Subscribe(std::function<R(Args...)>(f))
	{
		vec.push_back(f);

		return vec.size()-1;
	}

	void Release(int index) {
		vec[index] = nullptr;
	}

	void Emit(Args... args) {
		for (const auto& fun : vec)
			if(fun != nullptr)
				fun(args...);
	}
};

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
	Signal<void, std::string, int, int> Event;

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