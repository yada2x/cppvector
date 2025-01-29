#include <string>
#include <stdexcept>
#include "../Catch2/catch_amalgamated.cpp"
#include "Vector.h"

TEST_CASE("Vector default constructor", "[Vector][constructor]") {
    Vector<int> vec;
    REQUIRE(vec.Size() == 0);
    REQUIRE(vec.Capacity() == DEFAULT_VECTOR_SIZE);
}

TEST_CASE("Vector constructor with initial size and values", "[Vector][constructor]") {
    Vector<int> vec(5, -1);
    REQUIRE(vec.Size() == 5);
    REQUIRE(vec.Capacity() == 10);
    
    for (int i = 0; i < vec.Size(); ++i) {
        REQUIRE(vec[i] == -1);
    }
}

TEST_CASE("Vector constructor with invalid initial size", "[Vector][constructor]") {
    REQUIRE_THROWS_AS(Vector<int>(-1, 20), std::bad_array_new_length);
}

TEST_CASE("Vector copy constructor", "[Vector][constructor]") {
    Vector<int> vec1;
    vec1.Push_back(0);
    vec1.Push_back(1);
    vec1.Push_back(2);
    vec1.Push_back(3);
    
    Vector<int> vec(vec1);
    REQUIRE(vec.Size() == vec1.Size());
    REQUIRE(vec.Capacity() == vec1.Capacity());
    REQUIRE(vec[0] == 0);
    REQUIRE(vec[1] == 1);
    REQUIRE(vec[2] == 2);
    REQUIRE(vec[3] == 3);
}

TEST_CASE("Vector move constructor", "[Vector][constructor]") {
    Vector<int> temp;
    temp.Push_back(0);
    temp.Push_back(2);
    temp.Push_back(4);
    temp.Push_back(16);

    Vector<int> vec(std::move(temp));
    REQUIRE(vec.Size() == 4);
    REQUIRE(vec[0] == 0);
    REQUIRE(vec[1] == 2);
    REQUIRE(vec[2] == 4);
    REQUIRE(vec[3] == 16);

    REQUIRE(temp.Size() == 0);
    REQUIRE(temp.Capacity() == 0);
    REQUIRE_THROWS_AS(temp[0], std::out_of_range);
}

TEST_CASE("Vector push back", "[Vector][Push_back]") {
    Vector<int> vec(2, 0);

    REQUIRE(vec[0] == 0);
    REQUIRE(vec[1] == 0);

    vec.Push_back(0);
    vec.Push_back(1);
    REQUIRE(vec.Size() == vec.Capacity());
    REQUIRE(vec.Capacity() == 4);
}

TEST_CASE("Vector push back with move semantics", "[Vector][Push_back]") {
    Vector<std::string> vec;
    vec.Push_back("Nuts");
    vec.Push_back(std::move("Balls"));

    std::string temp = "Lemonade";
    vec.Push_back(std::move(temp));

    REQUIRE(vec.Size() == 3);
    REQUIRE(vec[0] == "Nuts");
    REQUIRE(vec[1] == "Balls");
    REQUIRE(vec[2] == "Lemonade");

    REQUIRE(temp.size() == 0);
}

TEST_CASE("Vector pop back", "[Vector][Pop_back]") {
    Vector<int> vec(3, 10);
    REQUIRE(vec.Size() == 3);

    vec.Pop_back();
    REQUIRE(vec.Size() == 2);
    REQUIRE(vec[0] == 10);
    REQUIRE(vec[1] == 10);

    vec.Pop_back();
    vec.Pop_back();
    REQUIRE(vec.Size() == 0);

    REQUIRE_NOTHROW(vec.Pop_back());
}

TEST_CASE("Vector erase", "[Vector][Erase]") {
    Vector<int> vec;
    vec.Push_back(10);
    vec.Push_back(20);
    vec.Push_back(30);
    vec.Push_back(40);

    vec.Erase(2);
    REQUIRE(vec.Size() == 3);
    REQUIRE(vec[0] == 10);
    REQUIRE(vec[1] == 20);
    REQUIRE(vec[2] == 40);

    REQUIRE_THROWS_AS(vec.Erase(5), std::out_of_range);
    REQUIRE_THROWS_AS(vec.Erase(-1), std::out_of_range);
}

TEST_CASE("Vector insert", "[Vector][Insert]") {
    Vector<int> vec;
    vec.Push_back(10);
    vec.Push_back(20);

    vec.Insert(1, 15);
    REQUIRE(vec.Size() == 3);
    REQUIRE(vec[0] == 10);
    REQUIRE(vec[1] == 15);
    REQUIRE(vec[2] == 20);

    vec.Insert(3, std::move(25));
    REQUIRE(vec.Size() == 4);
    REQUIRE(vec[3] == 25);

    REQUIRE_THROWS_AS(vec.Insert(5, 30), std::out_of_range);
}

TEST_CASE("Vector shrink to fit", "[Vector][Shrink_to_fit]") {
    Vector<int> vec(50, 1);
    REQUIRE(vec.Capacity() > vec.Size());

    vec.Shrink_to_fit();
    REQUIRE(vec.Size() == 50);
    REQUIRE(vec.Capacity() == vec.Size());
}

TEST_CASE("Vector clear", "[Vector][Clear]") {
    Vector<int> vec(3, 10);
    REQUIRE(vec.Size() == 3);

    vec.Clear();
    REQUIRE(vec.Size() == 0);
    REQUIRE(vec.Capacity() > 0);
}

TEST_CASE("Vector out-of-range access", "[Vector][Access]") {
    Vector<int> vec(3, 10);

    REQUIRE_THROWS_AS(vec[3], std::out_of_range);
    REQUIRE_THROWS_AS(vec[-1], std::out_of_range);

    const Vector<int> const_vec(3, 20);
    REQUIRE_THROWS_AS(const_vec[3], std::out_of_range);
    REQUIRE_THROWS_AS(const_vec[-1], std::out_of_range);
}

TEST_CASE("Vector copy assignment", "[Vector][Assignment]") {
    Vector<int> vec1(3, 10);
    Vector<int> vec2;

    vec2 = vec1;
    REQUIRE(vec2.Size() == 3);
    REQUIRE(vec2.Capacity() == vec1.Capacity());
    REQUIRE(vec2[0] == 10);
    REQUIRE(vec2[1] == 10);
    REQUIRE(vec2[2] == 10);

    vec1.Clear();
    REQUIRE(vec2.Size() == 3);
}

TEST_CASE("Vector move assignment", "[Vector][Assignment]") {
    Vector<int> vec1(3, 10);
    Vector<int> vec2;

    vec2 = std::move(vec1);
    REQUIRE(vec2.Size() == 3);
    REQUIRE(vec2[0] == 10);
    REQUIRE(vec2[1] == 10);
    REQUIRE(vec2[2] == 10);

    REQUIRE(vec1.Size() == 0);
    REQUIRE(vec1.Capacity() == 0);
    REQUIRE_THROWS_AS(vec1[0], std::out_of_range);
}

TEST_CASE("Vector iterators", "[Vector][Iterator]") {
    Vector<int> vec;
    vec.Push_back(1);
    vec.Push_back(2);
    vec.Push_back(3);

    int i = 1;
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        REQUIRE(*it == i);
        ++i;
    }

    i = 3;
    for (auto it = vec.rbegin(); it != vec.rend(); --it) {
        REQUIRE(*it == i);
        --i;
    }
}
