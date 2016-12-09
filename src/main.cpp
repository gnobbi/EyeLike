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


//// 3_3_StdVector.cpp : Defines the entry point for the console application.
////
//
//#include "stdafx.h"
//#include <vector>
//#include <map>
//#include <list>
//#include <iostream>
//#include <string>
//#include <thread>
//#include <type_traits>
//
//template<typename StreamT, typename T>
//StreamT& operator<<(StreamT& out, const std::vector<T>& vec) {
//	if (!vec.empty())
//		for (const auto& entry : vec)
//			out << entry << " ";
//
//	return out;
//}
//
//class Job {
//public:
//	Job() = default;
//
//	template<typename Func, typename... Args>
//	void StartThread(Func func, Args&&... args) {
//		t = std::make_shared<std::thread>(func, args...);
//	}
//
//	void join() {
//		t->join();
//	}
//
//private:
//	std::shared_ptr<std::thread> t;
//};
//
//using StringEventCallback = std::function<void(const std::string&)>;
//using SizeTEventCallback = std::function<void(const size_t&)>;
//
////Fixme if c++17 use std::is_callable
//template<typename T, typename = void>
//struct is_callable : std::is_function<T> { };
//
//template<typename T>
//struct is_callable<T, typename std::enable_if<std::is_same<decltype(void(&T::operator())), void>::value>::type> : std::true_type { };
//
//
//template<typename FunctionObject>
//class Slot {
//public:
//	const size_t id;
//	const FunctionObject function;
//private:
//	Slot(size_t id, const FunctionObject& function) : id(id), function(function) {
//		static_assert(is_callable<FunctionObject>::value, "Callable object required");
//	}
//
//public:
//	static std::unique_ptr<Slot<FunctionObject>> CreateSlot(const FunctionObject& function) {
//		static size_t id = 0;
//		Slot<FunctionObject> s(id++, function);
//		return std::make_unique<Slot<FunctionObject>>(s);
//	}
//};
//
//template<typename FunctionObject>
//class Signal {
//public:
//	Signal() {
//		static_assert(is_callable<FunctionObject>::value, "Callable object required");
//	}
//	void Subscribe(const std::unique_ptr<Slot<FunctionObject>>& slot) {
//		m_subscriberSlotCollection[slot->id] = slot->function;
//	}
//
//	void Release(const std::unique_ptr<Slot<FunctionObject>>& slot) {
//		m_subscriberSlotCollection.erase(m_subscriberSlotCollection.find(slot->id));
//	}
//
//	template<typename... Args>
//	void Notify(Args&&...args) {
//		for (const auto& subscriberSlot : m_subscriberSlotCollection) {
//			subscriberSlot.second(std::forward<Args>(args)...);
//		}
//	}
//
//	std::map<size_t, FunctionObject> m_subscriberSlotCollection;
//};
//
//struct JobImpl {
//	JobImpl(const std::string& s)
//		: id(s) {}
//
//	decltype(auto) GetId() const { return id; }
//	Signal<StringEventCallback> Message;
//
//	template<typename... Args>
//	void StartThread(Args&&... args) {
//		Message.Notify("Start worker");
//		worker.StartThread(GetRunner(), args...);
//	}
//	void Join() {
//		worker.join();
//		Message.Notify("Start joined worker");
//	}
//private:
//	decltype(auto) GetRunner() const { return [&](int i) { runner(i); }; }
//	void runner(int i) const { std::cout << id << " called runner with: " << i << std::endl; }
//	std::string id;
//	Job worker;
//};
//
//int main() {
//	auto callback1 = static_cast<StringEventCallback>([](const std::string arg) {
//		std::cout << "Subscriber1: " << arg << std::endl;
//	});
//	auto callback2 = static_cast<StringEventCallback>([](const std::string arg) {
//		std::cout << "Subscriber2: " << arg << std::endl;
//	});
//
//	JobImpl xy("xy");
//	auto slot1 = Slot<StringEventCallback>::CreateSlot(callback1);
//	auto slot2 = Slot<StringEventCallback>::CreateSlot(callback2);
//	xy.Message.Subscribe(slot1);
//	xy.Message.Subscribe(slot2);
//
//	xy.StartThread(12);
//	xy.Join();
//
//	xy.Message.Release(slot2);
//	xy.StartThread(0);
//	xy.Join();
//
//	return 0;
//}


//// 1_5_IntroducingClasses.cpp : Defines the entry point for the console application.
////
//#include "stdafx.h"
//#include <iostream>
//#include <string>
//#include <list>
//#include <memory>
//
///* /brief item that can be saled and has a isbn number
//*/
//class SalesItem
//{
//	friend std::istream& operator >> (std::istream&, SalesItem&);
//	friend std::ostream& operator<<(std::ostream&, const SalesItem&);
//
//public:
//	SalesItem() = default;
//	SalesItem(const std::string &name) :
//		m_name(name), m_price(0) {}
//
//	SalesItem(std::istream &is) { is >> *this; }
//public:
//	std::string Name()const { return m_name; }
//	double Price() const { return m_price; }
//
//private:
//	std::string m_name;
//	double m_price;
//};
//
//class SalesList
//{
//	friend std::ostream& operator<<(std::ostream&, const SalesList&);
//
//public:
//	SalesList() = default;
//	SalesList& operator+=(const SalesItem&);
//
//private:
//	std::list<SalesItem> collection;
//	double totalAmount = 0.;
//};
//
//SalesList& SalesList::operator+=(const SalesItem& si) {
//	collection.push_back(si);
//	totalAmount += si.Price();
//
//	return *this;
//}
//
//int main() {
//	SalesList total;
//	SalesItem trans;
//
//	while (std::cin >> trans) {
//		total += trans;
//	}
//
//	std::cout << total << std::endl;
//
//	std::system("pause");
//	return 0;
//}
//
//std::istream& operator >> (std::istream& in, SalesItem& s) {
//	in >> s.m_name >> s.m_price;
//	// check that the inputs succeeded
//	if (!in)
//		s = SalesItem();  // input failed: reset object to default state
//	return in;
//}
//
//std::ostream&
//operator<<(std::ostream& out, const SalesItem& s) {
//	out << s.Name() << " " << s.Price() << " euro";
//	return out;
//}
//
//std::ostream& operator<<(std::ostream& out, const SalesList& sl) {
//	int id = 0;
//	for (const auto& salesItem : sl.collection)
//		out << "#" << ++id << ": " << salesItem << std::endl;
//
//	if (!sl.collection.empty())
//		out << "Total amount: " << sl.totalAmount << " euro" << std::endl;
//
//	return out;
//}