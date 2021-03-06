/*
 * Run with
 *
 *    -i iterations
 *
 * to do a stress test for the given number of iterations.
 */

#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <utility>
#include "map.hpp"

template <typename K, typename V>
class test_map : public std::map<K, V> {
private:
    using base_t = std::map<K, V>;
public:
    using Iterator = typename std::map<K, V>::iterator;
    typename base_t::iterator insert(const std::pair<const K, V> &p) {
        return this->base_t::insert(p).first;
    }
};

template <typename K, typename V>
using map_t = cs540::Map<K, V>;
//using map_t = test_map<K, V>;

/*
 * Person class.
 */

class Person {
public:
    friend bool operator<(const Person &p1, const Person &p2) {
        return p1.name < p2.name;
    }
    friend bool operator==(const Person &p1, const Person &p2) {
        return p1.name == p2.name;
    }
    Person(const char *n) : name(n) {}
    void print() const {
        printf("Name: %s\n", name.c_str());
    }
    const std::string name;
    Person &operator=(const Person &) = delete;
};

void
print(const std::pair<const Person, int> &p) {
    p.first.print();
    printf("    %d\n", p.second);
}

/*
 * MyClass class.
 */

struct MyClass {
    friend bool operator<(const MyClass &o1, const MyClass &o2) {
        return o1.num < o2.num;
    }
    friend bool operator==(const MyClass &o1, const MyClass &o2) {
        return o1.num == o2.num;
    }
    MyClass(double n) : num(n) {}
    double num;
};

void
print(const std::pair<const int, std::string> &p) {
    printf("%d, %s; ", p.first, p.second.c_str());
}


/*
 * Stress class.
 */

struct Stress {
    friend bool operator<(const Stress& o1, const Stress& o2) {
        return o1.val < o2.val;
    }
    friend bool operator==(const Stress& o1, const Stress& o2) {
        return o1.val == o2.val;
    }
    Stress(int _v) : val(_v){}
    int val;
};
using it_t = map_t<const Stress, double>::Iterator;
// Helper function for stress testing.
inline bool
less(const it_t &lhs, const it_t &rhs) {
    return (*lhs).first.val < (*rhs).first.val;
}

/*
 * Additional test functions for BST.
 */

void traverse(const map_t<const Person, int> &, int level);
void traverse2(int level);
void check(const map_t<const Stress, double> &, const std::map<const Stress, double> &mirror);

/*
 * Main.
 */

int
main(int argc, char *argv[]) {
    
    int c;
    int iterations = 10000000;
    while ((c = getopt(argc, argv, "i:")) != EOF) {
        switch (c) {
            case 'i':
                iterations = atoi(optarg);
                break;
            case '?':
                fprintf(stderr, "Unrecog.\n");
                exit(1);
        }
    }
    
    srand48(1234);
    
    /*
     * Test with Person.
     */
    
    {
        Person p1("Jane");
        Person p2("John");
        Person p3("Mary");
        Person p4("Dave");
        
        map_t<const Person, int> map;
        
        // Insert people into the BST.
        auto p1_it = map.insert(std::make_pair(p1, 1));
        map.insert(std::make_pair(p2, 2));
        map.insert(std::make_pair(p3, 3));
        map.insert(std::make_pair(p4, 4));
        
        // Check iterator equality.
        {
            // Returns an iterator pointing to the first element.
            auto it1 = map.begin();
            // Returns an iterator pointing to one PAST the last element.  This
            // iterator is obviously conceptual only.  It cannot be
            // dereferenced.
            auto it2 = map.end();
            
            it1++; // Second node now.
            it1++; // Third node now.
            it2--; // Fourth node now.
            it2--; // Third node now.
            assert(it1 == it2);
            it2--; // Second node now.
            it2--; // First node now.
            assert(map.begin() == it2);
        }
        
        // Check insert return value.
        {
            printf("---- Test insert() return.\n");
            // Insert returns an interator.  If it's already in, it returns an
            // iterator to the already inserted element.
            auto it = map.insert(std::make_pair(p1, 1));
            assert(it == p1_it);
            // Now insert one that is new.
            it = map.insert(std::make_pair(Person("Larry"), 5));
            print(*it);
            map.erase(it);
        }
        
        // Print the whole thing now, to verify ordering.
        printf("---- Before erasures.\n");
        
        // Iterate through the whole map, and call print() on each Person.
        for (auto &e : map) {
            print(e);
        }
        
        // Test multiple traversals of the same map.
        printf("---- Multiple traversals\n");
        traverse(map, 4);
        
        // Test multiple BST at the same time.
        printf("---- Multiple BST\n");
        traverse2(4);
        
        /*
         * Test some erasures.
         */
        
        // Erase first element.
        map.erase(map.begin());
        auto it = map.end();
        --it; // it now points to last element.
        it--; // it now points to penultimate element.
        map.erase(it);
        
        printf("---- After erasures.\n");
        
        // Iterate through the whole map, and call print() on each Person.
        for (auto &e : map) {
            print(e);
        }
        
        // Test iterator validity.
        {
            // Iterators must be valid even when other things are inserted or
            // erased.
            printf("---- Test iterator non-invalidation\n");
            
            // Get iterator to the first.
            auto b = map.begin();
            
            // Insert element which will be at the end.
            auto it = map.insert(std::make_pair(Person("Zeke"), 10));
            
            // Iterator to the first should still be valid.
            print(*b);
            
            // Delete first, saving the actual object.
            auto tmp(*b); // Save, so we can reinsert.
            map.erase(map.begin()); // Erase it.
            
            // Check iterator for inserted.  Iterator to end should still be valid.
            print(*it); // This should still be valid.
            
            // Reinsert first element.
            map.insert(tmp);
            
            // Erase inserted last element.
            map.erase(it);
        }
    }
    
    /*
     * Test Map with MyClass.
     */
    
    {
        map_t<const MyClass, std::string> map;
        
        // Empty container, should print nothing.
        for (auto it = map.begin(); it != map.end(); ++it) {
            abort();
        }
        
        MyClass m1(0), m2(3), m3(1), m4(2);
        auto m1_it = map.insert(std::make_pair(m1, "mmm1"));
        map.insert(std::make_pair(m2, "mmm2"));
        map.insert(std::make_pair(m3, "mmm3"));
        map.insert(std::make_pair(m4, "mmm4"));
        
        // Should print 0.0 1.0 2.0 3.0
        for (auto &e : map) {
            printf("%3.1f ", e.first.num);
        }
        printf("\n");
        
        // Check return value of insert.
        {
            // Already in, so must return equal to m1_it.
            auto it = map.insert(std::make_pair(m1, "mmm1"));
            assert(it == m1_it);
        }
        
        // Erase the first element.
        map.erase(map.begin());
        // Should print "1.0 2.0 3.0".
        for (auto &e : map) {
            printf("%3.1f ", e.first.num);
        }
        printf("\n");
        
        // Erase the new first element.
        map.erase(map.begin());
        // Should print "2.0 3.0".
        for (auto &e : map) {
            printf("%3.1f ", e.first.num);
        }
        printf("\n");
        
        map.erase(--map.end());
        // Should print "2.0".
        for (auto &e : map) {
            printf("%3.1f ", e.first.num);
        }
        printf("\n");
        
        // Erase the last element.
        map.erase(map.begin());
        // Should print nothing.
        for (auto &e : map) {
            printf("%3.1f ", e.first.num);
        }
        printf("\n");
    }
    
    /*
     * Test Map with plain int.
     */
    
    {
        map_t<const int, std::string> map;
        
        // Empty container, should print nothing.
        for (auto &e : map) {
            printf("%d ", e.first);
        }
        
        auto p1(std::make_pair(4, "444"));
        auto p2(std::make_pair(3, "333"));
        auto p3(std::make_pair(0, "000"));
        auto p4(std::make_pair(2, "222"));
        auto p5(std::make_pair(1, "111"));
        
        map.insert(p1);
        map.insert(p2);
        map.insert(p3);
        map.insert(p4);
        map.insert(p5);
        
        // Should print "0 1 2 3 4".
        for (auto it = map.begin(); it != map.end(); ++it) {
            print(*it);
        }
        printf("\n");
        
        // Insert dupes.
        map.insert(p4);
        map.insert(p1);
        map.insert(p3);
        map.insert(p2);
        map.insert(p5);
        // Should print "0 1 2 3 4".
        for (auto it = map.begin(); it != map.end(); ++it) {
            print(*it);
        }
        printf("\n");
        
        // Erase the first element.
        map.erase(map.begin());
        
        // Erase the new first element.
        map.erase(map.begin());
        
        // Erase the element in the end.
        map.erase(--map.end());
        // Should print "2 3".
        for (auto &e : map) {
            print(e);
        }
        printf("\n");
        
        // Erase all elements.
        map.erase(map.begin());
        map.erase(map.begin());
        // Should print nothing.
        for (auto &e : map) {
            print(e);
        }
        printf("\n");
    }
    
    /*
     * Stress test Map.
     */
    
    if (iterations > 0) {
        
        map_t<const Stress, double> map;
        using mirror_t = std::map<const Stress, double>;
        mirror_t mirror;
        
        using iters_t = std::set<it_t, bool(*)(const it_t &lhs, const it_t &rhs)>;
        iters_t iters(&less);
        
        std::cout << "---- Starting stress test:" << std::endl;
        
        const int N = iterations;
        
        srand(9757);
        int n_inserted = 0, n_erased = 0, n_iters_changed = 0, n_empty = 0, n_dupes = 0;
        double avg_size = 0;
        
        for (int i = 0; i < N; ++i) {
            
            double op = drand48();
            
            // The probability of removal should be slightly higher than the
            // probability of insertion so that the map is often empty.
            if (op < .44) {
                
                // Insert an element.  Repeat until no duplicate.
                do {
                    // Limit the range of values of Stress so that we get some dupes.
                    auto v(std::make_pair(Stress(rand()%50000), drand48()));
                    auto find_it = map.find(v.first);
                    auto it = map.insert(v);
                    auto mir_res = mirror.insert(v);
                    if (mir_res.second) {
                        // If insert into mirror succeeded, insert into BST
                        // should also have succeeded.  It should not have
                        // found it before insert.
                        assert(find_it == map.end());
                        // Store the iterator.
                        iters.insert(it);
                        break;
                    }
                    // If insert into mirror did not succeed, insert into map
                    // should also not have succeeded, in which case, we
                    // generate another value to store.  Find should have found
                    // it, and insert should have returned same iterator.
                    assert(find_it == it);
                    n_dupes++;
                } while (true);
                
                ++n_inserted;
                
            } else if (op < .90) {
                
                // Erase an element.
                if (iters.size() != 0) {
                    
                    // Pick a random index.
                    int index = rand()%iters.size();
                    iters_t::iterator iit = iters.begin();
                    while(index--) {
                        ++iit;
                    }
                    
                    auto it = *iit;
                    // The iterator should not be end()
                    assert(it != map.end());
                    
                    Stress s((*it).first);
                    mirror.erase(s);
                    iters.erase(iit);
                    map.erase(it);
                    
                    ++n_erased;
                }
                
            } else {
                
                auto pre_or_post_inc = [&](it_t &it) {
                    if (rand()%2 == 0) {
                        it++;
                    } else {
                        ++it;
                    }
                };
                
                auto pre_or_post_dec = [&](it_t &it) {
                    if (rand()%2 == 0) {
                        it--;
                    } else {
                        --it;
                    }
                };
                
                // Increment or decrement an iterator.
                
                // Size of containers should be same
                assert(iters.size() == mirror.size());
                
                // If the container is empty, skip
                if (iters.size() != 0) {
                    
                    // Pick a random index
                    int index = rand()%iters.size();
                    iters_t::iterator iters_it = iters.begin();
                    while (index--) {
                        ++iters_it;
                    }
                    
                    auto it = *iters_it;
                    // The iterator should not be end().
                    assert(it != map.end());
                    
                    // If it is the begin(), then only increment,
                    // otherwise, pick either forward or backward.
                    if (it == map.begin()) {
                        pre_or_post_inc(it);
                        ++iters_it;
                    } else {
                        if (rand()%2 == 0) {
                            pre_or_post_inc(it);
                            ++iters_it;
                        } else {
                            pre_or_post_dec(it);
                            --iters_it;
                        }
                    }
                    // If we didn't hit the end, replace the resulting iterator
                    // in the iterator list.
                    // Note that the set is sorted.
                    if (it != map.end()) {
                        assert(it == *iters_it);
                        iters.erase(iters_it);
                        iters.insert(it);
                    }
                }
                
                ++n_iters_changed;
            }
            
            avg_size += double(iters.size())/N;
            
            if (iters.size() == 0) {
                ++n_empty;
            }
            
            check(map, mirror);
        }
        
        std::cout << "inserted: " << n_inserted << " times" << std::endl;
        std::cout << "erased: " << n_erased << " times" << std::endl;
        std::cout << "iterators changed: " << n_iters_changed << " times" << std::endl;
        std::cout << "empty count: " << n_empty << std::endl;
        std::cout << "avg size: " << avg_size << std::endl;
        std::cout << "n dupes: " << n_dupes << std::endl;
    }
}

void
check(const map_t<const Stress, double> &map, const std::map<const Stress, double> &mirror) {
    
    // Check if the reference container and stress container is identical
    auto it = map.begin();
    auto mit = mirror.begin();
    
    for( ; it != map.end() && mit != mirror.end(); ++it, ++mit) {
        
        if ((*it).first == (*mit).first) {
            if ((*it).second == (*mit).second) {
                continue;
            }
        }
        fprintf(stderr, "Reference tree and test tree differ.\n");
        abort();
    }
    
    if (it != map.end() || mit != mirror.end()) {
        fprintf(stderr, "Reference tree and test tree differ.\n");
        abort();
    }
}

// Test single list being traversed by multiple iterators simultaneously.
void
traverse(const map_t<const Person, int> &m, int level) {
    for (auto it = m.begin(); it != m.end(); ++it) {
        print(*it);
        if (level != 0) {
            traverse(m, level - 1);
        }
    }
}

// Test multiple lists and multiple iterators.
void
traverse2(int level) {
    
    map_t<const Person, int> map;
    
    for (int i = 0; i < 4; i++) {
        char name[30];
        sprintf(name, "Jane%d", int(10000*drand48()));
        printf("Generated name: %s\n", name);
        map.insert(std::make_pair(Person(name), 10*level + i));
    }
    
    for (auto &e : map) {
        print(e);
        if (level != 0) {
            traverse2(level - 1);
        }
    }
}