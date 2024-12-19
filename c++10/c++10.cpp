#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

class Pet {
protected:
    std::string name;
public:
    Pet(const std::string& petName) : name(petName) {}
    virtual void display() const {
        std::cout << "Pet Name: " << name << std::endl;
    }
    virtual ~Pet() {}
};

class Dog : public Pet {
public:
    Dog(const std::string& dogName) : Pet(dogName) {}
    void display() const override {
        std::cout << "Dog Name: " << name << ", Characteristics: Loyal and Playful" << std::endl;
    }
};

class Cat : public Pet {
public:
    Cat(const std::string& catName) : Pet(catName) {}
    void display() const override {
        std::cout << "Cat Name: " << name << ", Characteristics: Independent and Curious" << std::endl;
    }
};

class Parrot : public Pet {
public:
    Parrot(const std::string& parrotName) : Pet(parrotName) {}
    void display() const override {
        std::cout << "Parrot Name: " << name << ", Characteristics: Talkative and Colorful" << std::endl;
    }
};

class String {
protected:
    char* str;
    size_t length;

public:
    String() : str(nullptr), length(0) {}

    String(const char* input) {
        length = std::strlen(input);
        str = new char[length + 1];
        std::strcpy(str, input);
    }

    String(const String& other) : length(other.length) {
        str = new char[length + 1];
        std::strcpy(str, other.str);
    }

    String& operator=(const String& other) {
        if (this == &other) return *this;
        delete[] str;
        length = other.length;
        str = new char[length + 1];
        std::strcpy(str, other.str);
        return *this;
    }

    size_t getLength() const {
        return length;
    }

    void clear() {
        delete[] str;
        str = nullptr;
        length = 0;
    }

    virtual ~String() {
        delete[] str;
    }

    String operator+(const String& other) const {
        char* newStr = new char[length + other.length + 1];
        std::strcpy(newStr, str);
        std::strcat(newStr, other.str);
        String result(newStr);
        delete[] newStr;
        return result;
    }

    String& operator+=(const String& other) {
        *this = *this + other;
        return *this;
    }

    bool operator==(const String& other) const {
        return std::strcmp(str, other.str) == 0;
    }

    bool operator!=(const String& other) const {
        return !(*this == other);
    }

    void display() const {
        if (str)
            std::cout << str;
        else
            std::cout << "(empty)";
        std::cout << std::endl;
    }
};

class BitString : public String {
private:
    bool isValidBitString(const char* input) {
        for (size_t i = 0; i < std::strlen(input); ++i) {
            if (input[i] != '0' && input[i] != '1') {
                return false;
            }
        }
        return true;
    }

public:
    BitString() : String() {}

    BitString(const char* input) {
        if (isValidBitString(input)) {
            length = std::strlen(input);
            str = new char[length + 1];
            std::strcpy(str, input);
        }
        else {
            str = nullptr;
            length = 0;
        }
    }

    BitString(const BitString& other) : String(other) {}

    BitString& operator=(const BitString& other) {
        String::operator=(other);
        return *this;
    }

    void negate() {
        for (size_t i = 0; i < length; ++i) {
            str[i] = (str[i] == '0') ? '1' : '0';
        }
    }

    BitString operator+(const BitString& other) const {
        return BitString((String::operator+(other)).str);
    }

    BitString& operator+=(const BitString& other) {
        *this = *this + other;
        return *this;
    }

    bool operator==(const BitString& other) const {
        return String::operator==(other);
    }

    bool operator!=(const BitString& other) const {
        return String::operator!=(other);
    }
};

int main() {
    Dog dog("Buddy");
    Cat cat("Whiskers");
    Parrot parrot("Polly");

    dog.display();
    cat.display();
    parrot.display();

    String s1("Hello ");
    String s2("World!");
    String s3 = s1 + s2;
    s3.display();

    BitString bs1("10101");
    BitString bs2("110");
    BitString bs3 = bs1 + bs2;
    bs3.display();

    bs3.negate();
    bs3.display();

    return 0;
}
