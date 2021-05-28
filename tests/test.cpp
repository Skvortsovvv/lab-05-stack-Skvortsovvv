// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>
#include <header.hpp>


class Object {
private:
    int age;
    std::string name;
    Object(Object&) = delete;
    Object& operator=(Object&) = delete;

public:
    Object(int Age, std::string Name) : age(Age), name(Name) {}
    Object(Object&& obj) : age(obj.age), name(obj.name) {
        obj.age = 0;
        obj.name = "";
        }
    Object& operator=(Object&& obj) noexcept {
        this->age = obj.age;
        this->name = obj.name;
        obj.age = 0;
        obj.name = "";
        return *this;
        }
    std::string Stats() {
        return (std::to_string(age) + ' ' + name);
    }
    bool operator==(const Object& obj)const {
        return (age == obj.age) && (name == obj.name);
    }
};


TEST(Push_pop, Test) {
    Stack<Object> mystack;

    //Push
    Object First(1, "1");
    Object Second(2, "2");
    Object Third(3, "3");
    mystack.push(std::move(First));
    mystack.push(std::move(Second));
    mystack.push(std::move(Third));

    //Pop
    Object temp = mystack.pop();
    ASSERT_EQ("3 3", temp.Stats());
    temp = mystack.pop();
    ASSERT_EQ("2 2", temp.Stats());
    temp = mystack.pop();
    ASSERT_EQ("1 1", temp.Stats());
}

TEST(TESTING, TESTING) {
    Stack<Object> mystack;

    //Push_emplace
    mystack.push_emplace(4, "4");
    mystack.push_emplace(5, "5");
    mystack.push_emplace(6, "6");

    Object temp = mystack.pop();
    ASSERT_EQ("6 6", temp.Stats());
    temp = mystack.pop();
    ASSERT_EQ("5 5", temp.Stats());
    temp = mystack.pop();
    ASSERT_EQ("4 4", temp.Stats());
}

TEST(PUSH_EMPLACE, PE) {
    Stack<Object> mystack;

    //Push and emplace
    mystack.push_emplace(0, "zero");
    mystack.push_emplace(1, "one");
    Object three(3, "three");
    mystack.push(std::move(three));

    ASSERT_EQ(Object(3, "three"), mystack.head());
    mystack.pop();
    ASSERT_EQ(Object(1, "one"), mystack.head());
    mystack.pop();
    ASSERT_EQ(Object(0, "zero"), mystack.head());
    mystack.pop();
}
