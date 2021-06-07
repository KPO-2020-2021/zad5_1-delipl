#include "doctest.h"
#include <fstream>
#include "config.hpp"
#include "Object.hpp"

TEST_CASE("1. Transform constructor"){
    CHECK_NOTHROW(Transform trans);
    Transform trans;
    CHECK(trans.position == Vector3());
    CHECK(trans.rotation == MatrixRot());
    // CHECK(trans.pinned == nullptr);
    CHECK(trans.scale == Vector3({1, 1, 1}));
}
TEST_CASE("2. Object constriuctor, open file and read data"){
    CHECK_NOTHROW(Object rect("prostokat.dat"));
    Object rect("prostokat.dat");
    std::cout << rect << std::endl;
    CHECK(rect.Name() == "0_prostokat.dat");
    CHECK(rect.CountPoints() == 5);

    CHECK(rect[0] == Vector3({60, 60, 60}));
    CHECK(rect[1] == Vector3({210, 60, 60}));
    CHECK(rect[2] == Vector3({210, 160, 60}));
    CHECK(rect[3] == Vector3({60, 160, 60}));
    CHECK_THROWS(rect[5] == Vector3());

    CHECK_THROWS_AS(Object rect("nonExistsFile.dat"), std::exception);

    Object rect2(rect);
    CHECK(rect2[0] == Vector3({60, 60, 60}));
    CHECK(rect2[1] == Vector3({210, 60, 60}));
    CHECK(rect2[2] == Vector3({210, 160, 60}));
    CHECK(rect2[3] == Vector3({60, 160, 60}));
}


TEST_CASE("4. Object 8 actualPoints rotate"){
    CHECK_NOTHROW(Object rect("prostopadloscian.dat"));
    Object rect("prostokat.dat");
    rect.Rotate(0, VectorZ);
    rect.Update();
    CHECK(rect[0] == Vector3({60, 60, 60}));

    rect.Rotate(90, VectorZ);
    rect.Update();
    CHECK(rect[0] == Vector3({-60, 60, 60}));

    rect.Rotate(-90, VectorZ);
    rect.Update();
    CHECK(rect[0] == Vector3({60, 60, 60}));

    

    rect.Rotate(-90, VectorZ);
    rect.Update();
    CHECK(rect[0] == Vector3({60, -60, 60}));

    Object rect1("line.dat");
    rect1.Rotate(90, VectorX);
    rect1.Update();
    CHECK(rect1[0] == Vector3({100, 0, 0}));

    rect1.Rotate(90, VectorY);
    rect1.Update();
    CHECK(rect1[0] == Vector3({0, 0, -100}));

    rect1.Rotate(-90, VectorX);
    rect1.Update();
    CHECK(rect1[0] == Vector3({0, 0, -100}));


    Object line("line.dat");
    line.Rotate(90, VectorX);
    line.Update();
    CHECK(line[0] == Vector3({100, 0, 0}));

    line.Rotate(90, VectorY);
    line.Update();
    CHECK(line[0] == Vector3({0, 0, -100}));

    line.Rotate(90, VectorX);
    line.Update();
    CHECK(line[0] == Vector3({0, 0, -100}));
}


TEST_CASE("10. Object ID"){
    CHECK(Object::HowManyObjects() == 0);
    Object rect1("line.dat");
    CHECK(Object::HowManyObjects() == 1);
    Object rect2("line.dat");
    Object rect3("line.dat");
    Object rect4("line.dat");
    // Object rect5("line.dat", 1);

    CHECK(rect1.SeflID() == 0);
    CHECK(rect2.SeflID() == 1);
    CHECK(rect3.SeflID() == 2);
    CHECK(rect4.SeflID() == 3);
    CHECK(Object::HowManyObjects() == 4);
}
// TEST_CASE("11.Object Read and write file"){
//     Object obj("line.dat");
//     Object obj1("line.dat");
//     std::ifstream tmpFile(std::string(TMP_FOLDER + obj.Name()));


//     tmpFile >> obj1;

//     for (std::size_t i = 0; i < obj.CountPoints(); ++i)
//         CHECK(obj1[i] == obj[i]);
// }

TEST_CASE("Object scale test"){
    Object obj("line.dat", {0, 0, 0}, {1, 1, 1});
    Object obj1("line.dat", {0, 0, 0}, {0.5, 0.5, 0.5});

    CHECK(obj1[0] == obj[0]* 0.5);
}