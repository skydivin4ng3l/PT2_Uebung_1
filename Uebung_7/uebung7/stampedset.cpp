#include <iostream>
#include <assert.h>
#include <unordered_map>
#include <set>

using namespace std;


template<class T, class stamp_type = unsigned long>
class StampedSet {
private:
	std::unordered_map<T, std::set<stamp_type>> mapObjectStampSet_;
	std::unordered_map<stamp_type, T> mapStampObject_;
	stamp_type nextStamp_;

public:
	StampedSet() : nextStamp_ {0} {}

	stamp_type add(const T& obj) {
		// is the Object already in the map
		auto search = mapObjectStampSet_.find(obj);
		// create a new Object
		if (search == mapObjectStampSet_.end()) {
			std::set<stamp_type> curObjectStampSet;
			curObjectStampSet.insert(nextStamp_);

			mapObjectStampSet_.insert({ obj,curObjectStampSet });
			mapStampObject_.insert({ nextStamp_,obj });
		}
		// Object is already in the map
		else {
			search->second.insert(nextStamp_);
			mapStampObject_.insert({ nextStamp_,obj });
		}
		
		return nextStamp_++;
	}

	void erase(const T& obj) {
		assert(this->containsObject(obj));
		auto search = mapObjectStampSet_.find(obj);
		for (auto& it : search->second) {
			mapStampObject_.erase(it);
		}
		mapObjectStampSet_.erase(obj);
	}

	void eraseStamp(const stamp_type stamp) {
		mapObjectStampSet_.at(mapStampObject_.at(stamp)).erase(stamp);
		mapStampObject_.erase(stamp);
	}

	unsigned long noOfObjects() const {
		return mapObjectStampSet_.size();
	}

	unsigned long noOfStamps() const {
		return mapStampObject_.size();
	}

	bool containsObject(const T& obj) const {
		if (mapObjectStampSet_.find(obj) != mapObjectStampSet_.end()) {
			return true;
		}
		return false;
	}

	bool containsStamp(const stamp_type& s) const {
		if (mapStampObject_.find(s) != mapStampObject_.end()) {
			return true;
		}
		return false;
	}

	const T& findObject(const stamp_type& s) const {
		assert(this->containsStamp(s));
		auto search = mapStampObject_.find(s);
		return search->second;
	}

	stamp_type lastStamp(const T& obj) const {
		assert(this->containsObject(obj));
		auto search = mapObjectStampSet_.find(obj);
		return *(search->second.rbegin());
		
	}

	stamp_type firstStamp(const T& obj) const {
		assert(this->containsObject(obj));
		auto search = mapObjectStampSet_.find(obj);
		return *(search->second.begin());
	}

	stamp_type nextStamp() const {
		return nextStamp_;
	}

	template<typename L>
	void process(const T& obj, L&& fct) {
		assert(this->containsObject(obj));
		for (auto& it : mapObjectStampSet_.at(obj)) {
			if (fct(obj, it)) 
				this->eraseStamp(it);
		}
	}

	template<typename L>
	void process(stamp_type from, stamp_type to, L&& fct) {
		assert(this->containsStamp(from) && this->containsStamp(to));
		auto from_it = mapStampObject_.find(from);
		auto to_it = mapStampObject_.find(to);
		for (auto it = from_it; it != to_it; it++) {
			if ( fct(it->second, it->first) )
				this->eraseStamp(it->first);
		}
	}

	stamp_type restart(const T& obj) {
		assert(this->containsObject(obj));
		this->erase(obj);
		return this->add(obj);
	}


};


void test() {
	StampedSet<float, int> sfs;
	float f {0.0f};
	int s {0};
	int z {0};

	// check add, containsObject, containsStamp
	f = 3.14f; s = sfs.add(f); assert(sfs.containsStamp(s)); assert(sfs.containsObject(f));
	f = 9.99f; s = sfs.add(f); assert(sfs.containsStamp(s)); assert(sfs.containsObject(f));
	f = 5.01f; s = sfs.add(f); assert(sfs.containsStamp(s)); assert(sfs.containsObject(f));
	f = 3.14f; s = sfs.add(f); assert(sfs.containsStamp(s)); assert(sfs.containsObject(f));
	f = 9.99f; s = sfs.add(f); assert(sfs.containsStamp(s)); assert(sfs.containsObject(f));
	f = 3.14f; s = sfs.add(f); assert(sfs.containsStamp(s)); assert(sfs.containsObject(f));
	f = 3.14f; s = sfs.add(f); assert(sfs.containsStamp(s)); assert(sfs.containsObject(f));
	f = 1.11f; s = sfs.add(f); assert(sfs.containsStamp(s)); assert(sfs.containsObject(f));
	f = 1.11f; s = sfs.add(f); assert(sfs.containsStamp(s)); assert(sfs.containsObject(f));

	// test process by lambda that prints contents
	sfs.process(0, sfs.nextStamp(), [](float f, int i){ cout << "(" << f << ", " << i << ") "; return false; }); cout << endl;

	// check erase
	f = 8.12f; s = sfs.add(f); sfs.erase(f); assert(!sfs.containsStamp(s)); assert(!sfs.containsObject(f));

	// test assignment of next stamp to next added object
	z = sfs.nextStamp(); f = 2.22f; s = sfs.add(f); assert(s == z);

	// test restart
	f = 2.22f; sfs.add(f); sfs.add(f); z = sfs.nextStamp(); s = sfs.restart(f); assert(s == z);

	// check first/last stamps
	f = 2.33f; s = sfs.add(f); assert(s == sfs.firstStamp(f)); assert(s == sfs.lastStamp(f));
	f = 2.44f; s = sfs.add(f); z = sfs.add(f); assert(s == sfs.firstStamp(f)); assert(z == sfs.lastStamp(f));

	// check find object
	f = 2.55f; s = sfs.add(f); assert(f == sfs.findObject(s));

	int N {0};
	sfs.process(0, 100, [&N](float f, int i){ N++; return false; }); cout << "N: " << N << ", stamps: " << sfs.noOfStamps() << endl; assert(N == sfs.noOfStamps());

	// test process deletion
	f = 3.14f; sfs.process(f, [](float f, int i){ return true; }); assert(sfs.lastStamp(f) == 18);
	sfs.process(1, 7, [](float f, int i){ return f < 6.0f; }); assert(sfs.lastStamp(5.01f) == 19); assert(sfs.firstStamp(9.99f) == 1); assert(sfs.firstStamp(1.11f) == 8);

	// check different instantiations
	StampedSet<string, int> sss;
	StampedSet<char, unsigned long> scs;
}


int main(int,char**) {
	test();
	return 0;
}
