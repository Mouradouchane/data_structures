
#include <string>

// objects for testing 
class tobj {
public:
	std::string data = "";
	tobj(std::string const& dt) {
		this->data = dt;
	}
	tobj() { }
	~tobj() { }

	tobj& operator = (tobj const& new_data) {
		this->data = new_data.data;
		return *this;
	}

	void operator = (std::string new_value) {
		this->data = new_value;
	}

	void operator = (int const& index) {
		this->data = "";
	}

	bool operator != (tobj const& other) {
		return (this->data != other.data) ? true : false;
	}

	bool operator == (tobj const& other) {
		return (this->data == other.data) ? true : false;
	}
};
