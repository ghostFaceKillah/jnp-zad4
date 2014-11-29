#include <typeinfo>
#include <cassert>
#include <iostream>

#include "shipwreck.hh"

typedef add_gear<Cannon, Mast>::type sloop;
typedef add_gear<multiply_gear<Cannon, 10>::type, multiply_gear<Oar, 20>::type>::type galley;

int main() {
    Squad<Mast> s1; // pojedynczy jednomasztowiec
    Squad<galley> s2(20); // banda 20 galer
    Squad<galley> s3(s2); // druga banda 20 galer
    Squad<Cannon> s4; // pływająca armata

    // łączymy sprzęt ,,na sucho''
    assert(typeid(Squad<add_gear<Cannon, Mast>::type>::gear_type) == typeid(sloop)); 

    // łączymy statki
    assert(join_ships(s1, s4).get_count() == 1);
    assert(typeid(join_ships(s1, s4).gear) == typeid(sloop));

    // sumujemy bandy
    // assert((s1 + s2).get_count() == 21); // to się nie powinno kompilować
    assert((s2 + s3).get_count() == 40);
    // assert((s3 += s4).get_count == 21); // to też nie
    assert((s2 += s2).get_count() == 40);
    assert(s2.get_count() == 40);

    // rozpraszamy bandy (przerabiamy okręty na mniejsze)
    assert(s2 > s3);
    assert(typeid(split_ships(s3).gear) 
            == typeid(add_gear<multiply_gear<Cannon, 5>::type, 
                multiply_gear<Oar, 10>::type>::type));
    assert(split_ships(s3).get_count() == 20);

    assert(typeid(split_ships(split_ships(s3)).gear) 
            == typeid(add_gear<multiply_gear<Cannon, 2>::type, 
                multiply_gear<Oar, 5>::type>::type));
    assert(split_ships(split_ships(s3)).get_count() == 20);

    // odejmujemy bandy
    assert((s2 - s3).get_count() == 20);
    assert((s3 - s2).get_count() == 0); // sic!

    // wyznaczamy łup w przypadku konfliktu dwóch band
    assert(typeid(expected_booty(s2, s4).gear) 
            == typeid(Cannon));
    assert(expected_booty(s2, s4).get_count() == 1);

    std::cout << "all ok!" << std::endl;
}
