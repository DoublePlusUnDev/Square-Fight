//#define CPORTA
#ifdef CPORTA
#include "test.h"
#include "gtest_lite.h"
#include "memtrace.h"

#include "transform.h"
#include "collider.h"

#include "core.h"
#include "physicsObject.h"

#include "mapmanager.h"

#include <iostream>
#include <limits>

void TestRunner::start() 
{
    GTINIT(std::cin);

    runVector2Tests();

    runTransformTests();

    runColliderTests();

    runPhysicsTests();

    runMapTests();

    GTEND(std::cerr);
}

void TestRunner::runVector2Tests()
{
    //vector2 konstruktor teszt
    TEST (Vector2, konstruktor)
    {
        Vector2 v1;
        EXPECT_DOUBLE_EQ(v1.x, 0.0);
        EXPECT_DOUBLE_EQ(v1.y, 0.0);

        Vector2 v2(3.0, 4.0);
        EXPECT_DOUBLE_EQ(v2.x, 3.0);
        EXPECT_DOUBLE_EQ(v2.y, 4.0);
    } END

    //vector2 összeadás teszt
    TEST (Vector2, osszeadas)
    {
        Vector2 v1(1.0, 2.0);
        Vector2 v2(3.0, 4.0);

        Vector2 v4 = v1 + v2;
        EXPECT_DOUBLE_EQ(v4.x, 4.0);
        EXPECT_DOUBLE_EQ(v4.y, 6.0);
    
        Vector2 v3(-3, -4);
        Vector2 v5 = v1 + v3;
        EXPECT_DOUBLE_EQ(v5.x, -2.0);
        EXPECT_DOUBLE_EQ(v5.y, -2.0);
    } END

    //vector2 kivonás teszt
    TEST (Vector2, kivonas)
    {
        Vector2 v1(5.0, 7.0);
        Vector2 v2(3.0, 4.0);

        Vector2 v3 = v1 - v2;
        EXPECT_DOUBLE_EQ(v3.x, 2.0);
        EXPECT_DOUBLE_EQ(v3.y, 3.0);

        Vector2 v4(-3, -4);
        Vector2 v5 = v1 - v4;
        EXPECT_DOUBLE_EQ(v5.x, 8.0);
        EXPECT_DOUBLE_EQ(v5.y, 11.0);
    } END

    //vector2 szorzás teszt
    TEST (Vector2, szorzas)
    {
        Vector2 v1(2.0, 3.0);

        Vector2 v2 = v1 * 2.0;
        EXPECT_DOUBLE_EQ(v2.x, 4.0);
        EXPECT_DOUBLE_EQ(v2.y, 6.0);

        Vector2 v3 = v1 * -1.0;
        EXPECT_DOUBLE_EQ(v3.x, -2.0);
        EXPECT_DOUBLE_EQ(v3.y, -3.0);

        Vector2 v4 = v1 * 0.0;
        EXPECT_DOUBLE_EQ(v4.x, 0.0);
        EXPECT_DOUBLE_EQ(v4.y, 0.0);

        Vector2 v5 = v1 * 0.5;
        EXPECT_DOUBLE_EQ(v5.x, 1.0);
        EXPECT_DOUBLE_EQ(v5.y, 1.5);
    } END

    //vector2 osztás teszt
    TEST (Vector2, osztas)
    {
        Vector2 v1(4.0, 8.0);

        Vector2 v2 = v1 / 2.0;
        EXPECT_DOUBLE_EQ(v2.x, 2.0);
        EXPECT_DOUBLE_EQ(v2.y, 4.0);

        Vector2 v3 = v1 / -1.0;
        EXPECT_DOUBLE_EQ(v3.x, -4.0);
        EXPECT_DOUBLE_EQ(v3.y, -8.0);

        Vector2 v4 = v1 / 0.5;
        EXPECT_DOUBLE_EQ(v4.x, 8.0);
        EXPECT_DOUBLE_EQ(v4.y, 16.0);
    } END
}

void TestRunner::runTransformTests()
{
    //transform konstruktor teszt
    TEST (Transform, konstruktor)
    {
        Transform t1;
        EXPECT_DOUBLE_EQ(t1.getPosition().x, 0.0);
        EXPECT_DOUBLE_EQ(t1.getPosition().y, 0.0);
        EXPECT_DOUBLE_EQ(t1.getScale().x, 1.0);
        EXPECT_DOUBLE_EQ(t1.getScale().y, 1.0);
        EXPECT_EQ(t1.getParent(), nullptr);
        EXPECT_EQ(t1.countChildren(), 0);

        Transform t2(nullptr, {2.0, 3.0}, {4.0, 5.0});
        EXPECT_DOUBLE_EQ(t2.getPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t2.getPosition().y, 3.0);
        EXPECT_DOUBLE_EQ(t2.getScale().x, 4.0);
        EXPECT_DOUBLE_EQ(t2.getScale().y, 5.0);
        EXPECT_EQ(t2.getParent(), nullptr);
        EXPECT_EQ(t2.countChildren(), 0);
    } END

    //transform set teszt
    TEST (Transform, set)
    {
        Transform t1;
        t1.setPosition({2.0, 3.0});
        EXPECT_DOUBLE_EQ(t1.getPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t1.getPosition().y, 3.0);
        EXPECT_DOUBLE_EQ(t1.getLocalPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t1.getLocalPosition().y, 3.0);

        t1.setLocalPosition({-1.0, -2.0});
        EXPECT_DOUBLE_EQ(t1.getPosition().x, -1.0);
        EXPECT_DOUBLE_EQ(t1.getPosition().y, -2.0);
        EXPECT_DOUBLE_EQ(t1.getLocalPosition().x, -1.0);
        EXPECT_DOUBLE_EQ(t1.getLocalPosition().y, -2.0);

        t1.setScale({4.0, 5.0});
        EXPECT_DOUBLE_EQ(t1.getScale().x, 4.0);
        EXPECT_DOUBLE_EQ(t1.getScale().y, 5.0);
        EXPECT_DOUBLE_EQ(t1.getLocalScale().x, 4.0);
        EXPECT_DOUBLE_EQ(t1.getLocalScale().y, 5.0);

        t1.setLocalScale({-2.0, 3.0});
        EXPECT_DOUBLE_EQ(t1.getScale().x, -2.0);
        EXPECT_DOUBLE_EQ(t1.getScale().y, 3.0);
        EXPECT_DOUBLE_EQ(t1.getLocalScale().x, -2.0);
        EXPECT_DOUBLE_EQ(t1.getLocalScale().y, 3.0);
    } END

    //transform másolás teszt
    TEST (Transform, masolas)
    {
        Transform t1;
        t1.setPosition({2.0, 3.0});
        t1.setScale({4.0, 5.0});

        Transform t2 = t1;
        EXPECT_DOUBLE_EQ(t2.getPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t2.getPosition().y, 3.0);
        EXPECT_DOUBLE_EQ(t2.getScale().x, 4.0);
        EXPECT_DOUBLE_EQ(t2.getScale().y, 5.0);

        t1.setPosition({-1.0, -2.0});
        EXPECT_DOUBLE_EQ(t1.getPosition().x, -1.0);
        EXPECT_DOUBLE_EQ(t1.getPosition().y, -2.0);
        EXPECT_DOUBLE_EQ(t2.getPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t2.getPosition().y, 3.0);
    } END

    //transform értékadás teszt
    TEST (Transform, ertekadas)
    {
        Transform t1;
        t1.setPosition({2.0, 3.0});
        t1.setScale({4.0, 5.0});

        Transform t2;
        t2 = t1;
        EXPECT_DOUBLE_EQ(t2.getPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t2.getPosition().y, 3.0);
        EXPECT_DOUBLE_EQ(t2.getScale().x, 4.0);
        EXPECT_DOUBLE_EQ(t2.getScale().y, 5.0);

        t1.setPosition({-1.0, -2.0});
        EXPECT_DOUBLE_EQ(t1.getPosition().x, -1.0);
        EXPECT_DOUBLE_EQ(t1.getPosition().y, -2.0);
        EXPECT_DOUBLE_EQ(t2.getPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t2.getPosition().y, 3.0);
    } END

    //transform elmozdítás teszt
    TEST (Transform, elmozditas)
    {
        Transform t1;
        t1.move({2.0, 3.0});
        EXPECT_DOUBLE_EQ(t1.getPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t1.getPosition().y, 3.0);

        t1.move({-1.0, -2.0});
        EXPECT_DOUBLE_EQ(t1.getPosition().x, 1.0);
        EXPECT_DOUBLE_EQ(t1.getPosition().y, 1.0);
    } END

    //transform hierarchia teszt
    TEST (Transform, hierarchia)
    {
        Transform t1(nullptr, {0.0, 0.0}, {1.0, 1.0});
        Transform t2(&t1, {2.0, 3.0}, {4.0, 5.0});

        EXPECT_EQ(t1.countChildren(), 1);
        EXPECT_EQ(t2.getParent(), &t1);
        
        EXPECT_DOUBLE_EQ(t2.getPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t2.getPosition().y, 3.0);
        EXPECT_DOUBLE_EQ(t2.getScale().x, 4.0);
        EXPECT_DOUBLE_EQ(t2.getScale().y, 5.0);

        t2.changeParent(nullptr);
        EXPECT_EQ(t1.countChildren(), 0);
        EXPECT_EQ(t2.getParent(), nullptr);
    } END

    //transform hierachia teszt (több gyerek)
    TEST (Transform, hierarchia_gyerek_tobb)
    {
        Transform t1;
        Transform t2(&t1, {2.0, 3.0}, {4.0, 5.0});
        Transform t3(&t1, {6.0, 7.0}, {8.0, 9.0});

        EXPECT_EQ(t1.countChildren(), 2);
        EXPECT_EQ(t2.getParent(), &t1);
        EXPECT_EQ(t3.getParent(), &t1);

        t2.changeParent(nullptr);
        EXPECT_EQ(t1.countChildren(), 1);
        EXPECT_EQ(t2.getParent(), nullptr);

        t3.changeParent(nullptr);
        EXPECT_EQ(t1.countChildren(), 0);
        EXPECT_EQ(t3.getParent(), nullptr);
    } END

    //transform hierarchia teszt (mély)
    TEST (Transform, hierarchia_mely)
    {
        Transform t1;
        Transform t2(&t1, {2.0, 3.0}, {4.0, 5.0});
        Transform t3(&t2, {6.0, 7.0}, {8.0, 9.0});
        Transform t4(&t3, {10.0, 11.0}, {12.0, 13.0});
        Transform t5(&t4, {14.0, 15.0}, {16.0, 17.0});

        EXPECT_EQ(t1.countChildren(), 1);
        EXPECT_EQ(t2.countChildren(), 1);
        EXPECT_EQ(t3.countChildren(), 1);
        EXPECT_EQ(t4.countChildren(), 1);
        EXPECT_EQ(t5.countChildren(), 0);

        EXPECT_EQ(t1.getParent(), nullptr);
        EXPECT_EQ(t2.getParent(), &t1);
        EXPECT_EQ(t3.getParent(), &t2);
        EXPECT_EQ(t4.getParent(), &t3);
        EXPECT_EQ(t5.getParent(), &t4);
    } END

    //transform hierarchia teszt (gyerek mozgatása)
    TEST (Transform, hierarchia_gyerek_mozgatas)
    {
        Transform t1(nullptr, {0.0, 0.0}, {1.0, 1.0});
        Transform t2(&t1, {2.0, 3.0}, {1.0, 1.0});
        Transform t3(&t2, {6.0, 7.0}, {1.0, 1.0});

        t3.move({1.0, 1.0});
        EXPECT_DOUBLE_EQ(t2.getPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t2.getPosition().y, 3.0);
        EXPECT_DOUBLE_EQ(t2.getLocalPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t2.getLocalPosition().y, 3.0);

        EXPECT_DOUBLE_EQ(t3.getPosition().x, 9.0);
        EXPECT_DOUBLE_EQ(t3.getPosition().y, 11.0);
        EXPECT_DOUBLE_EQ(t3.getLocalPosition().x, 7.0);
        EXPECT_DOUBLE_EQ(t3.getLocalPosition().y, 8.0);
        
    } END

    //transform hierarchia teszt (szülő mozgatása)
    TEST (Transform, hierarchia_szulo_mozgatas)
    {
        Transform t1(nullptr, {0.0, 0.0}, {1.0, 1.0});
        Transform t2(&t1, {2.0, 3.0}, {1.0, 1.0});
        Transform t3(&t2, {6.0, 7.0}, {1.0, 1.0});

        EXPECT_DOUBLE_EQ(t1.getPosition().x, 0.0);
        EXPECT_DOUBLE_EQ(t1.getPosition().y, 0.0);
        EXPECT_DOUBLE_EQ(t1.getLocalPosition().x, 0.0);
        EXPECT_DOUBLE_EQ(t1.getLocalPosition().y, 0.0);

        EXPECT_DOUBLE_EQ(t2.getPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t2.getPosition().y, 3.0);
        EXPECT_DOUBLE_EQ(t2.getLocalPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t2.getLocalPosition().y, 3.0);

        EXPECT_DOUBLE_EQ(t3.getPosition().x, 8.0);
        EXPECT_DOUBLE_EQ(t3.getPosition().y, 10.0);
        EXPECT_DOUBLE_EQ(t3.getLocalPosition().x, 6.0);
        EXPECT_DOUBLE_EQ(t3.getLocalPosition().y, 7.0);

        t1.move({1.0, 1.0});

        EXPECT_DOUBLE_EQ(t1.getPosition().x, 1.0);
        EXPECT_DOUBLE_EQ(t1.getPosition().y, 1.0);
        EXPECT_DOUBLE_EQ(t1.getLocalPosition().x, 1.0);
        EXPECT_DOUBLE_EQ(t1.getLocalPosition().y, 1.0);

        EXPECT_DOUBLE_EQ(t2.getPosition().x, 3.0);
        EXPECT_DOUBLE_EQ(t2.getPosition().y, 4.0);
        EXPECT_DOUBLE_EQ(t2.getLocalPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t2.getLocalPosition().y, 3.0);

        EXPECT_DOUBLE_EQ(t3.getPosition().x, 9.0);
        EXPECT_DOUBLE_EQ(t3.getPosition().y, 11.0);
        EXPECT_DOUBLE_EQ(t3.getLocalPosition().x, 6.0);
        EXPECT_DOUBLE_EQ(t3.getLocalPosition().y, 7.0);
    
    } END

    //transform hierarchia teszt (szülő, gyerek mozgatása)
    TEST (Transform, hierarchia_szulo_gyerek_mozgatas)
    {
        Transform t1(nullptr, {0.0, 0.0}, {1.0, 1.0});
        Transform t2(&t1, {2.0, 3.0}, {1.0, 1.0});
        Transform t3(&t2, {6.0, 7.0}, {1.0, 1.0});

        EXPECT_DOUBLE_EQ(t1.getPosition().x, 0.0);
        EXPECT_DOUBLE_EQ(t1.getPosition().y, 0.0);
        EXPECT_DOUBLE_EQ(t1.getLocalPosition().x, 0.0);
        EXPECT_DOUBLE_EQ(t1.getLocalPosition().y, 0.0);
    
        EXPECT_DOUBLE_EQ(t2.getPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t2.getPosition().y, 3.0);
        EXPECT_DOUBLE_EQ(t2.getLocalPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t2.getLocalPosition().y, 3.0);

        EXPECT_DOUBLE_EQ(t3.getPosition().x, 8.0);
        EXPECT_DOUBLE_EQ(t3.getPosition().y, 10.0);
        EXPECT_DOUBLE_EQ(t3.getLocalPosition().x, 6.0);
        EXPECT_DOUBLE_EQ(t3.getLocalPosition().y, 7.0);

        t1.move({1.0, 1.0});
        t3.move({-1.0, -1.0});

        EXPECT_DOUBLE_EQ(t1.getPosition().x, 1.0);
        EXPECT_DOUBLE_EQ(t1.getPosition().y, 1.0);
        EXPECT_DOUBLE_EQ(t1.getLocalPosition().x, 1.0);
        EXPECT_DOUBLE_EQ(t1.getLocalPosition().y, 1.0);

        EXPECT_DOUBLE_EQ(t2.getPosition().x, 3.0);
        EXPECT_DOUBLE_EQ(t2.getPosition().y, 4.0);
        EXPECT_DOUBLE_EQ(t2.getLocalPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t2.getLocalPosition().y, 3.0);

        EXPECT_DOUBLE_EQ(t3.getPosition().x, 8.0);
        EXPECT_DOUBLE_EQ(t3.getPosition().y, 10.0);
        EXPECT_DOUBLE_EQ(t3.getLocalPosition().x, 5.0);
        EXPECT_DOUBLE_EQ(t3.getLocalPosition().y, 6.0);
    
    } END

    //transform hierarchia teszt (gyerek méretének megváltoztatása)
    TEST (Transform, hierarchia_gyerek_meretezes)
    {
        Transform t1(nullptr, {0.0, 0.0}, {1.0, 1.0});
        Transform t2(&t1, {0.0, 0.0}, {1.0, 1.0});
        Transform t3(&t2, {0.0, 0.0}, {1.0, 1.0});

        EXPECT_DOUBLE_EQ(t1.getScale().x, 1.0);
        EXPECT_DOUBLE_EQ(t1.getScale().y, 1.0);
        EXPECT_DOUBLE_EQ(t2.getScale().x, 1.0);
        EXPECT_DOUBLE_EQ(t2.getScale().y, 1.0);
        EXPECT_DOUBLE_EQ(t3.getScale().x, 1.0);
        EXPECT_DOUBLE_EQ(t3.getScale().y, 1.0);

        t3.setScale({2.0, 2.0});

        EXPECT_DOUBLE_EQ(t1.getScale().x, 1.0);
        EXPECT_DOUBLE_EQ(t1.getScale().y, 1.0);
        EXPECT_DOUBLE_EQ(t2.getScale().x, 1.0);
        EXPECT_DOUBLE_EQ(t2.getScale().y, 1.0);
        EXPECT_DOUBLE_EQ(t3.getScale().x, 2.0);
        EXPECT_DOUBLE_EQ(t3.getScale().y, 2.0);
    
    } END

    //transform hierarchia teszt (szülő méretének megváltoztatása)
    TEST (Transform, hierarchia_szulo_meretezes)
    {
        Transform t1(nullptr, {0.0, 0.0}, {1.0, 1.0});
        Transform t2(&t1, {0.0, 0.0}, {1.0, 1.0});

        EXPECT_DOUBLE_EQ(t1.getScale().x, 1.0);
        EXPECT_DOUBLE_EQ(t1.getScale().y, 1.0);
        EXPECT_DOUBLE_EQ(t1.getLocalScale().x, 1.0);
        EXPECT_DOUBLE_EQ(t1.getLocalScale().y, 1.0);

        EXPECT_DOUBLE_EQ(t2.getScale().x, 1.0);
        EXPECT_DOUBLE_EQ(t2.getScale().y, 1.0);
        EXPECT_DOUBLE_EQ(t2.getLocalScale().x, 1.0);
        EXPECT_DOUBLE_EQ(t2.getLocalScale().y, 1.0);

        t1.setScale({2.0, 2.0});

        EXPECT_DOUBLE_EQ(t1.getScale().x, 2.0);
        EXPECT_DOUBLE_EQ(t1.getScale().y, 2.0);
        EXPECT_DOUBLE_EQ(t1.getLocalScale().x, 2.0);
        EXPECT_DOUBLE_EQ(t1.getLocalScale().y, 2.0);

        EXPECT_DOUBLE_EQ(t2.getScale().x, 2.0);
        EXPECT_DOUBLE_EQ(t2.getScale().y, 2.0);
        EXPECT_DOUBLE_EQ(t2.getLocalScale().x, 1.0);
        EXPECT_DOUBLE_EQ(t2.getLocalScale().y, 1.0);
    
    } END

    //transform hierarchia teszt (szülő és gyerek méretének megváltoztatása)
    TEST (Transform, hierarchia_szulo_gyerek_meretezes)
    {
        Transform t1(nullptr, {0.0, 0.0}, {2.0, 2.0});
        Transform t2(&t1, {0.0, 0.0}, {3.0, 3.0});
        Transform t3(&t2, {0.0, 0.0}, {4.0, 4.0});
        Transform t4(&t3, {0.0, 0.0}, {5.0, 5.0});

        EXPECT_DOUBLE_EQ(t1.getScale().x, 2.0);
        EXPECT_DOUBLE_EQ(t1.getScale().y, 2.0);
        EXPECT_DOUBLE_EQ(t1.getLocalScale().x, 2.0);
        EXPECT_DOUBLE_EQ(t1.getLocalScale().y, 2.0);

        EXPECT_DOUBLE_EQ(t2.getScale().x, 6.0);
        EXPECT_DOUBLE_EQ(t2.getScale().y, 6.0);
        EXPECT_DOUBLE_EQ(t2.getLocalScale().x, 3.0);
        EXPECT_DOUBLE_EQ(t2.getLocalScale().y, 3.0);

        EXPECT_DOUBLE_EQ(t3.getScale().x, 24.0);
        EXPECT_DOUBLE_EQ(t3.getScale().y, 24.0);
        EXPECT_DOUBLE_EQ(t3.getLocalScale().x, 4.0);
        EXPECT_DOUBLE_EQ(t3.getLocalScale().y, 4.0);

        EXPECT_DOUBLE_EQ(t4.getScale().x, 120.0);
        EXPECT_DOUBLE_EQ(t4.getScale().y, 120.0);
        EXPECT_DOUBLE_EQ(t4.getLocalScale().x, 5.0);
        EXPECT_DOUBLE_EQ(t4.getLocalScale().y, 5.0);
    } END

    //transform hierarchia teszt (szülő mozgatása és méretének megváltoztatása)
    TEST (Transform, hierarchia_szulo_mozgatas_meretezes)
    {
        Transform t1(nullptr, {0.0, 0.0}, {1.0, 1.0});
        Transform t2(&t1, {1.0, 1.0}, {1.0, 1.0});

        EXPECT_DOUBLE_EQ(t1.getPosition().x, 0.0);
        EXPECT_DOUBLE_EQ(t1.getPosition().y, 0.0);
        EXPECT_DOUBLE_EQ(t1.getScale().x, 1.0);
        EXPECT_DOUBLE_EQ(t1.getScale().y, 1.0);

        EXPECT_DOUBLE_EQ(t2.getPosition().x, 1.0);
        EXPECT_DOUBLE_EQ(t2.getPosition().y, 1.0);
        EXPECT_DOUBLE_EQ(t2.getScale().x, 1.0);
        EXPECT_DOUBLE_EQ(t2.getScale().y, 1.0);

        t1.move({1.0, 1.0});
        t1.setScale({2.0, 2.0});

        EXPECT_DOUBLE_EQ(t1.getPosition().x, 1.0);
        EXPECT_DOUBLE_EQ(t1.getPosition().y, 1.0);
        EXPECT_DOUBLE_EQ(t1.getLocalPosition().x, 1.0);
        EXPECT_DOUBLE_EQ(t1.getLocalPosition().y, 1.0);

        EXPECT_DOUBLE_EQ(t1.getScale().x, 2.0);
        EXPECT_DOUBLE_EQ(t1.getScale().y, 2.0);
        EXPECT_DOUBLE_EQ(t1.getLocalScale().x, 2.0);
        EXPECT_DOUBLE_EQ(t1.getLocalScale().y, 2.0);

        EXPECT_DOUBLE_EQ(t2.getPosition().x, 3.0);
        EXPECT_DOUBLE_EQ(t2.getPosition().y, 3.0);
        EXPECT_DOUBLE_EQ(t2.getLocalPosition().x, 1.0);
        EXPECT_DOUBLE_EQ(t2.getLocalPosition().y, 1.0);
        
        EXPECT_DOUBLE_EQ(t2.getScale().x, 2.0);
        EXPECT_DOUBLE_EQ(t2.getScale().y, 2.0);
        EXPECT_DOUBLE_EQ(t2.getLocalScale().x, 1.0);
        EXPECT_DOUBLE_EQ(t2.getLocalScale().y, 1.0);
    } END

    //transform hierarchia teszt (szülő csere)
    TEST (Transform, hierarchia_szulo_csere)
    {
        Transform t1(nullptr, {2.0, 2.0}, {1.0, 1.0});
        Transform t2(&t1, {1.0, 1.0}, {1.0, 1.0});

        EXPECT_DOUBLE_EQ(t2.getPosition().x, 3.0);
        EXPECT_DOUBLE_EQ(t2.getPosition().y, 3.0);
        EXPECT_DOUBLE_EQ(t2.getLocalPosition().x, 1.0);
        EXPECT_DOUBLE_EQ(t2.getLocalPosition().y, 1.0);

        EXPECT_DOUBLE_EQ(t2.getScale().x, 1.0);
        EXPECT_DOUBLE_EQ(t2.getScale().y, 1.0);
        EXPECT_DOUBLE_EQ(t2.getLocalScale().x, 1.0);
        EXPECT_DOUBLE_EQ(t2.getLocalScale().y, 1.0);

        Transform t3(nullptr, {4.0, 4.0}, {2.0, 2.0});
        t2.changeParent(&t3);

        EXPECT_DOUBLE_EQ(t2.getPosition().x, 3.0);
        EXPECT_DOUBLE_EQ(t2.getPosition().y, 3.0);
        EXPECT_DOUBLE_EQ(t2.getLocalPosition().x, -0.5);
        EXPECT_DOUBLE_EQ(t2.getLocalPosition().y, -0.5);

        EXPECT_DOUBLE_EQ(t2.getScale().x, 1.0);
        EXPECT_DOUBLE_EQ(t2.getScale().y, 1.0);
        EXPECT_DOUBLE_EQ(t2.getLocalScale().x, 0.5);
        EXPECT_DOUBLE_EQ(t2.getLocalScale().y, 0.5);

        EXPECT_EQ(t1.countChildren(), 0);
        EXPECT_EQ(t2.getParent(), &t3);
        EXPECT_EQ(t3.countChildren(), 1);
    } END

    //transform hierarchia teszt (gyerek másolása)
    TEST (Transform, hierarchia_gyerek_masolas)
    {
        Transform t1(nullptr, {2.0, 2.0}, {2.0, 2.0});
        Transform t2(&t1, {1.0, 1.0}, {1.0, 1.0});

        EXPECT_DOUBLE_EQ(t1.getPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t1.getPosition().y, 2.0);
        
        EXPECT_DOUBLE_EQ(t2.getPosition().x, 4.0);
        EXPECT_DOUBLE_EQ(t2.getPosition().y, 4.0);
        EXPECT_DOUBLE_EQ(t2.getLocalPosition().x, 1.0);
        EXPECT_DOUBLE_EQ(t2.getLocalPosition().y, 1.0);

        EXPECT_DOUBLE_EQ(t2.getScale().x, 2.0);
        EXPECT_DOUBLE_EQ(t2.getScale().y, 2.0);
        EXPECT_DOUBLE_EQ(t2.getLocalScale().x, 1.0);
        EXPECT_DOUBLE_EQ(t2.getLocalScale().y, 1.0);

        Transform t3 = t2;

        EXPECT_DOUBLE_EQ(t3.getPosition().x, 4.0);
        EXPECT_DOUBLE_EQ(t3.getPosition().y, 4.0);
        EXPECT_DOUBLE_EQ(t3.getLocalPosition().x, 1.0);
        EXPECT_DOUBLE_EQ(t3.getLocalPosition().y, 1.0);
        
        EXPECT_DOUBLE_EQ(t3.getScale().x, 2.0);
        EXPECT_DOUBLE_EQ(t3.getScale().y, 2.0);
        EXPECT_DOUBLE_EQ(t3.getLocalScale().x, 1.0);
        EXPECT_DOUBLE_EQ(t3.getLocalScale().y, 1.0);

        EXPECT_EQ(t1.countChildren(), 2);
        EXPECT_EQ(t2.getParent(), &t1);
    } END

    //transform hierarchia teszt (szülő másolása)
    TEST (Transform, hierarchia_szulo_masolas)
    {
        Transform t1(nullptr, {2.0, 2.0}, {1.0, 1.0});
        Transform t2(&t1, {1.0, 1.0}, {1.0, 1.0});

        EXPECT_DOUBLE_EQ(t1.getPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t1.getPosition().y, 2.0);

        EXPECT_DOUBLE_EQ(t2.getPosition().x, 3.0);
        EXPECT_DOUBLE_EQ(t2.getPosition().y, 3.0);

        Transform t3 = t1;
        EXPECT_DOUBLE_EQ(t2.getPosition().x, 3.0);
        EXPECT_DOUBLE_EQ(t2.getPosition().y, 3.0);

        EXPECT_DOUBLE_EQ(t3.getPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t3.getPosition().y, 2.0);

        EXPECT_EQ(t1.countChildren(), 1);
        EXPECT_EQ(t3.countChildren(), 0);
    } END

    //transform hierarchia teszt (gyerek értekadás)
    TEST (Transform, hierarchia_gyerek_ertekadas)
    {
        Transform t1(nullptr, {2.0, 2.0}, {1.0, 1.0});
        Transform t2(&t1, {1.0, 1.0}, {1.0, 1.0});

        EXPECT_DOUBLE_EQ(t1.getPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t1.getPosition().y, 2.0);

        EXPECT_DOUBLE_EQ(t2.getPosition().x, 3.0);
        EXPECT_DOUBLE_EQ(t2.getPosition().y, 3.0);
        EXPECT_DOUBLE_EQ(t2.getLocalPosition().x, 1.0);
        EXPECT_DOUBLE_EQ(t2.getLocalPosition().y, 1.0);

        Transform t3;
        t3 = t2;
        EXPECT_DOUBLE_EQ(t3.getPosition().x, 3.0);
        EXPECT_DOUBLE_EQ(t3.getPosition().y, 3.0);
        EXPECT_DOUBLE_EQ(t3.getLocalPosition().x, 1.0);
        EXPECT_DOUBLE_EQ(t3.getLocalPosition().y, 1.0);

        EXPECT_EQ(t1.countChildren(), 2);
        EXPECT_EQ(t2.getParent(), &t1);
    } END

    //transform hierarchia teszt (szülő értékadás)
    TEST (Transform, hierarchia_szulo_ertekadas)
    {
        Transform t1(nullptr, {2.0, 2.0}, {1.0, 1.0});
        Transform t2(&t1, {1.0, 1.0}, {1.0, 1.0});

        EXPECT_DOUBLE_EQ(t1.getPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t1.getPosition().y, 2.0);
        EXPECT_DOUBLE_EQ(t2.getPosition().x, 3.0);
        EXPECT_DOUBLE_EQ(t2.getPosition().y, 3.0);

        Transform t3 = t1;
        EXPECT_DOUBLE_EQ(t3.getPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t3.getPosition().y, 2.0);

        EXPECT_EQ(t1.countChildren(), 1);
        EXPECT_EQ(t3.countChildren(), 0);
    } END

    //transform hierarchia teszt (gyerekes szülő értékadás)
    TEST (Transform, hierarchia_gyerekes_szulo_ertekadas)
    {
        Transform t1(nullptr, {2.0, 2.0}, {1.0, 1.0});
        Transform t2(&t1, {1.0, 1.0}, {1.0, 1.0});
        Transform t3(&t2, {6.0, 7.0}, {8.0, 9.0});

        EXPECT_DOUBLE_EQ(t1.getPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t1.getPosition().y, 2.0);

        EXPECT_DOUBLE_EQ(t2.getPosition().x, 3.0);
        EXPECT_DOUBLE_EQ(t2.getPosition().y, 3.0);

        EXPECT_DOUBLE_EQ(t3.getPosition().x, 9.0);
        EXPECT_DOUBLE_EQ(t3.getPosition().y, 10.0);

        Transform t4(nullptr, {4.0, 4.0}, {1.0, 1.0});
        t1 = t4;
        EXPECT_DOUBLE_EQ(t1.getPosition().x, 4.0);
        EXPECT_DOUBLE_EQ(t1.getPosition().y, 4.0);

        EXPECT_DOUBLE_EQ(t2.getPosition().x, 5.0);
        EXPECT_DOUBLE_EQ(t2.getPosition().y, 5.0);

        EXPECT_DOUBLE_EQ(t3.getPosition().x, 11.0);
        EXPECT_DOUBLE_EQ(t3.getPosition().y, 12.0);

        EXPECT_EQ(t1.countChildren(), 1);
        EXPECT_EQ(t2.countChildren(), 1);
        EXPECT_EQ(t3.countChildren(), 0);
        EXPECT_EQ(t4.countChildren(), 0);
    } END

    //transform hierarchia teszt (gyerek destruktor)
    TEST (Transform, hierarchia_gyerek_destruktor)
    {
        Transform* t1 = new Transform(nullptr, {2.0, 2.0}, {1.0, 1.0});
        Transform* t2 = new Transform(t1, {1.0, 1.0}, {1.0, 1.0});

        EXPECT_DOUBLE_EQ(t1->getPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t1->getPosition().y, 2.0);
        EXPECT_DOUBLE_EQ(t2->getPosition().x, 3.0);
        EXPECT_DOUBLE_EQ(t2->getPosition().y, 3.0);

        EXPECT_EQ(t1->countChildren(), 1);

        delete t2;

        EXPECT_EQ(t1->countChildren(), 0);
        EXPECT_DOUBLE_EQ(t1->getPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t1->getPosition().y, 2.0);

        EXPECT_DOUBLE_EQ(t1->getScale().x, 1.0);
        EXPECT_DOUBLE_EQ(t1->getScale().y, 1.0);

        delete t1;
    } END

    //transform hierarchia teszt (szülő destruktor)
    TEST (Transform, hierarchia_szulo_destruktor)
    {
        Transform* t1 = new Transform(nullptr, {2.0, 2.0}, {1.0, 1.0});
        Transform* t2 = new Transform(t1, {1.0, 1.0}, {1.0, 1.0});

        EXPECT_DOUBLE_EQ(t1->getPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t1->getPosition().y, 2.0);

        EXPECT_DOUBLE_EQ(t2->getPosition().x, 3.0);
        EXPECT_DOUBLE_EQ(t2->getPosition().y, 3.0);

        EXPECT_EQ(t1->countChildren(), 1);

        delete t1;

        EXPECT_EQ(t2->getParent(), nullptr);
        EXPECT_DOUBLE_EQ(t2->getPosition().x, 3.0);
        EXPECT_DOUBLE_EQ(t2->getPosition().y, 3.0);

        EXPECT_DOUBLE_EQ(t2->getScale().x, 1.0);
        EXPECT_DOUBLE_EQ(t2->getScale().y, 1.0);

        delete t2;
    } END

    //transform hierarchia teszt (mely destruktor)
    TEST (Transform, hierarchia_mely_destruktor)
    {
        Transform* t1 = new Transform(nullptr, {2.0, 2.0}, {1.0, 1.0});
        Transform* t2 = new Transform(t1, {1.0, 1.0}, {1.0, 1.0});
        Transform* t3 = new Transform(t2, {6.0, 7.0}, {1.0, 1.0});
        Transform* t4 = new Transform(t3, {8.0, 9.0}, {1.0, 1.0});

        EXPECT_DOUBLE_EQ(t1->getPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t1->getPosition().y, 2.0);

        EXPECT_DOUBLE_EQ(t2->getPosition().x, 3.0);
        EXPECT_DOUBLE_EQ(t2->getPosition().y, 3.0);

        EXPECT_DOUBLE_EQ(t3->getPosition().x, 9.0);
        EXPECT_DOUBLE_EQ(t3->getPosition().y, 10.0);

        EXPECT_DOUBLE_EQ(t4->getPosition().x, 17.0);
        EXPECT_DOUBLE_EQ(t4->getPosition().y, 19.0);

        delete t2;

        EXPECT_EQ(t1->countChildren(), 0);

        EXPECT_EQ(t3->getParent(), nullptr);
        EXPECT_EQ(t4->getParent(), t3);

        EXPECT_DOUBLE_EQ(t1->getPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t1->getPosition().y, 2.0);

        EXPECT_DOUBLE_EQ(t3->getPosition().x, 9.0);
        EXPECT_DOUBLE_EQ(t3->getPosition().y, 10.0);

        EXPECT_DOUBLE_EQ(t4->getPosition().x, 17.0);
        EXPECT_DOUBLE_EQ(t4->getPosition().y, 19.0);

        delete t3;

        EXPECT_EQ(t1->countChildren(), 0);

        EXPECT_EQ(t4->getParent(), nullptr);

        EXPECT_DOUBLE_EQ(t1->getPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t1->getPosition().y, 2.0);

        EXPECT_DOUBLE_EQ(t4->getPosition().x, 17.0);
        EXPECT_DOUBLE_EQ(t4->getPosition().y, 19.0);

        delete t4;
        delete t1;
    } END

    //transform hierarchia teszt (gyerek set globális pozíció)
    TEST (Transform, hierarchia_gyerek_set_globalis_pozicio)
    {
        Transform t1(nullptr, {2.0, 2.0}, {1.0, 1.0});
        Transform t2(&t1, {1.0, 1.0}, {1.0, 1.0});

        EXPECT_DOUBLE_EQ(t1.getPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t1.getPosition().y, 2.0);

        EXPECT_DOUBLE_EQ(t2.getPosition().x, 3.0);
        EXPECT_DOUBLE_EQ(t2.getPosition().y, 3.0);

        t2.setPosition({4.0, 4.0});

        EXPECT_DOUBLE_EQ(t1.getPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t1.getPosition().y, 2.0);

        EXPECT_DOUBLE_EQ(t2.getPosition().x, 4.0);
        EXPECT_DOUBLE_EQ(t2.getPosition().y, 4.0);
    } END

    //transform hierarchia teszt (szülő set globális pozíció)
    TEST (Transform, hierarchia_szulo_set_globalis_pozicio)
    {
        Transform t1(nullptr, {2.0, 2.0}, {1.0, 1.0});
        Transform t2(&t1, {1.0, 1.0}, {1.0, 1.0});

        EXPECT_DOUBLE_EQ(t1.getPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t1.getPosition().y, 2.0);

        EXPECT_DOUBLE_EQ(t2.getPosition().x, 3.0);
        EXPECT_DOUBLE_EQ(t2.getPosition().y, 3.0);

        t1.setPosition({4.0, 4.0});

        EXPECT_DOUBLE_EQ(t1.getPosition().x, 4.0);
        EXPECT_DOUBLE_EQ(t1.getPosition().y, 4.0);

        EXPECT_DOUBLE_EQ(t2.getPosition().x, 5.0);
        EXPECT_DOUBLE_EQ(t2.getPosition().y, 5.0);
    } END

    //transform hierarchia teszt (szülő és gyerek set globális pozíció)
    TEST (Transform, hierarchia_szulo_gyerek_set_globalis_pozicio)
    {
        Transform t1(nullptr, {2.0, 2.0}, {1.0, 1.0});
        Transform t2(&t1, {1.0, 1.0}, {1.0, 1.0});

        EXPECT_DOUBLE_EQ(t1.getPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(t1.getPosition().y, 2.0);

        EXPECT_DOUBLE_EQ(t2.getPosition().x, 3.0);
        EXPECT_DOUBLE_EQ(t2.getPosition().y, 3.0);

        t1.setPosition({4.0, 4.0});
        t2.setPosition({6.0, 6.0});

        EXPECT_DOUBLE_EQ(t1.getPosition().x, 4.0);
        EXPECT_DOUBLE_EQ(t1.getPosition().y, 4.0);

        EXPECT_DOUBLE_EQ(t2.getPosition().x, 6.0);
        EXPECT_DOUBLE_EQ(t2.getPosition().y, 6.0);
    } END

    //transform hierarchia teszt (gyerek set globális méret)
    TEST (Transform, hierarchia_gyerek_set_globalis_meret)
    {
        Transform t1(nullptr, {2.0, 2.0}, {1.0, 1.0});
        Transform t2(&t1, {1.0, 1.0}, {1.0, 1.0});

        EXPECT_DOUBLE_EQ(t1.getScale().x, 1.0);
        EXPECT_DOUBLE_EQ(t1.getScale().y, 1.0);

        EXPECT_DOUBLE_EQ(t2.getScale().x, 1.0);
        EXPECT_DOUBLE_EQ(t2.getScale().y, 1.0);

        t2.setScale({2.0, 2.0});

        EXPECT_DOUBLE_EQ(t1.getScale().x, 1.0);
        EXPECT_DOUBLE_EQ(t1.getScale().y, 1.0);

        EXPECT_DOUBLE_EQ(t2.getScale().x, 2.0);
        EXPECT_DOUBLE_EQ(t2.getScale().y, 2.0);
    } END

    //transform hierarchia teszt (szülő set globális méret)
    TEST (Transform, hierarchia_szulo_set_globalis_meret)
    {
        Transform t1(nullptr, {2.0, 2.0}, {1.0, 1.0});
        Transform t2(&t1, {1.0, 1.0}, {1.0, 1.0});

        EXPECT_DOUBLE_EQ(t1.getScale().x, 1.0);
        EXPECT_DOUBLE_EQ(t1.getScale().y, 1.0);

        EXPECT_DOUBLE_EQ(t2.getScale().x, 1.0);
        EXPECT_DOUBLE_EQ(t2.getScale().y, 1.0);

        t1.setScale({2.0, 2.0});

        EXPECT_DOUBLE_EQ(t1.getScale().x, 2.0);
        EXPECT_DOUBLE_EQ(t1.getScale().y, 2.0);

        EXPECT_DOUBLE_EQ(t2.getScale().x, 2.0);
        EXPECT_DOUBLE_EQ(t2.getScale().y, 2.0);
    } END

    //transform hierarchia teszt (szülő és gyerek set globális méret)
    TEST (Transform, hierarchia_szulo_gyerek_set_globalis_meret)
    {
        Transform t1(nullptr, {2.0, 2.0}, {1.0, 1.0});
        Transform t2(&t1, {1.0, 1.0}, {1.0, 1.0});

        EXPECT_DOUBLE_EQ(t1.getScale().x, 1.0);
        EXPECT_DOUBLE_EQ(t1.getScale().y, 1.0);

        EXPECT_DOUBLE_EQ(t2.getScale().x, 1.0);
        EXPECT_DOUBLE_EQ(t2.getScale().y, 1.0);

        t1.setScale({2.0, 2.0});
        t2.setScale({3.0, 3.0});

        EXPECT_DOUBLE_EQ(t1.getScale().x, 2.0);
        EXPECT_DOUBLE_EQ(t1.getScale().y, 2.0);

        EXPECT_DOUBLE_EQ(t2.getScale().x, 3.0);
        EXPECT_DOUBLE_EQ(t2.getScale().y, 3.0);
    } END

    //transform gyerek keresés teszt
    TEST (Transform, gyerek_kereses)
    {
        Transform t1;
        Transform t2(&t1, {2.0, 3.0}, {4.0, 5.0});
        Transform t3(&t1, {6.0, 7.0}, {8.0, 9.0});

        std::vector<Transform*> children = t1.findTypeInChildren<Transform>();
        EXPECT_EQ(children.size(), 3);
        EXPECT_EQ(children[0], &t1);
        EXPECT_EQ(children[1], &t2);
        EXPECT_EQ(children[2], &t3);
    } END

    //transform gyerek keresés leszármazással teszt
    TEST (Transform, gyerek_kereses_leszarmazassal)
    {
        class Transform2 : public Transform
        {
            public:
            Transform2(Transform* const parent = nullptr, const Vector2& position = { 0, 0 }, const Vector2& scale = { 1, 1 }) : Transform(parent, position, scale) {}
        };

        Transform t1;
        Transform2 t2(&t1);
        Transform t3(&t1);
        Transform2 t4(&t2);
        Transform t5(&t4);
        Transform2 t6(&t5);
        Transform t7(&t6);

        std::vector<Transform2*> children = t1.findTypeInChildren<Transform2>();
        EXPECT_EQ(children.size(), 3);
        EXPECT_EQ(children[0], dynamic_cast<Transform2*>(&t2));
        EXPECT_EQ(children[1], dynamic_cast<Transform2*>(&t4));
        EXPECT_EQ(children[2], dynamic_cast<Transform2*>(&t6));
    } END

    //transform hierarchia teszt (gyerek keresés leszármazással, több típus)
    TEST (Transform, gyerek_kereses_leszarmazassal_tobb_tipus)
    {
        class Transform2 : public Transform
        {
            public:
            Transform2(Transform* const parent = nullptr) : Transform(parent) {}
        };

        class Transform3 : public Transform
        {
            public:
            Transform3(Transform* const parent = nullptr) : Transform(parent) {}
        };

        Transform t1;
        Transform2 t2(&t1);
        Transform3 t3(&t1);
        Transform2 t4(&t2);

        std::vector<Transform2*> children2 = t1.findTypeInChildren<Transform2>();
        EXPECT_EQ(children2.size(), 2);
        EXPECT_EQ(children2[0], &t2);
        EXPECT_EQ(children2[1], &t4);

        std::vector<Transform3*> children3 = t1.findTypeInChildren<Transform3>();
        EXPECT_EQ(children3.size(), 1);
        EXPECT_EQ(children3[0], &t3);
    } END
}

void TestRunner::runColliderTests()
{
    //collider teszt (konstruktor pozícióval és mérettel)
    TEST(Collider, konstruktor)
    {
        Collider c1(Transform(nullptr, {2.0, 3.0}, {4.0, 5.0}));
        EXPECT_DOUBLE_EQ(c1.getPosition().x, 2.0);
        EXPECT_DOUBLE_EQ(c1.getPosition().y, 3.0);
        EXPECT_DOUBLE_EQ(c1.getScale().x, 4.0);
        EXPECT_DOUBLE_EQ(c1.getScale().y, 5.0);
    } END

    //collider teszt (masoló konstruktor, értékadás)
    TEST(Collider, copyConstructorAndAssignment)
    {
        Collider c1(Transform(nullptr, {0.0, 0.0}, {2.0, 2.0}), ColliderType::INTERACTIVE, 0.5);
        Collider c2 = c1; // Másoló konstruktor
        Collider c3(Transform(nullptr, {1.0, 1.0}, {1.0, 1.0}));
        c3 = c1; // Értékadás

        EXPECT_DOUBLE_EQ(c2.getPosition().x, 0.0);
        EXPECT_DOUBLE_EQ(c2.getPosition().y, 0.0);
        EXPECT_DOUBLE_EQ(c2.getScale().x, 2.0);
        EXPECT_DOUBLE_EQ(c2.getScale().y, 2.0);
        EXPECT_DOUBLE_EQ(c2.getBounciness(), 0.5);

        EXPECT_DOUBLE_EQ(c3.getPosition().x, 0.0);
        EXPECT_DOUBLE_EQ(c3.getPosition().y, 0.0);
        EXPECT_DOUBLE_EQ(c3.getScale().x, 2.0);
        EXPECT_DOUBLE_EQ(c3.getScale().y, 2.0);
        EXPECT_DOUBLE_EQ(c3.getBounciness(), 0.5);
    } END

    // Ütközés teszt (két Collider)
    TEST(Collider, utkozes)
    {
        Collider c1(Transform(nullptr, {0.0, 0.0}, {2.0, 2.0}));
        Collider c2(Transform(nullptr, {1.0, 1.0}, {2.0, 2.0}));
        Collider c3(Transform(nullptr, {5.0, 5.0}, {1.0, 1.0}));

        EXPECT_TRUE(Collider::checkColliders(c1, c2)); // Metszik egymást
        EXPECT_FALSE(Collider::checkColliders(c1, c3)); // Nem metszenek
    } END

    // Ütközés teszt (Egy collider + Statikus lista)
    TEST(Collider, utkozes_statikus_lista)
    {
        Collider c1(Transform(nullptr, {0.0, 0.0}, {2.0, 2.0}));
        Collider c2(Transform(nullptr, {1.0, 1.0}, {2.0, 2.0}));
        Collider c3(Transform(nullptr, {5.0, 5.0}, {1.0, 1.0}));

        std::vector<Collider*> intersections = c1.checkIntersection();

        EXPECT_EQ(intersections.size(), 1);
        EXPECT_EQ(intersections[0], &c2);
    } END

    // Ütközés teszt (Collider lista + Statikus lista)
    TEST(Collider, utkozes_lista_statikus_lista)
    {
        Collider c1(Transform(nullptr, {0.0, 0.0}, {2.0, 2.0}));
        Collider c2(Transform(nullptr, {1.0, 1.0}, {2.0, 2.0}));
        Collider c3(Transform(nullptr, {-2.0, -2.0}, {2.0, 2.0}));
        Collider c4(Transform(nullptr, {5.0, 5.0}, {1.0, 1.0}));

        std::vector<Collider*> colliders = {&c1, &c2};
        std::vector<Collider*> intersections = Collider::checkIntersectionForList(colliders);

        EXPECT_EQ(intersections.size(), 1);
        EXPECT_EQ(intersections[0], &c3);
    } END

    // Ütközés teszt (Érintkezés/átfedés)
    TEST(Collider, utkozes_erintkezes)
    {
        Collider c1(Transform(nullptr, {0.0, 0.0}, {2.0, 2.0}));
        Collider c2(Transform(nullptr, {1.0, 1.0}, {2.0, 2.0}));
        Collider c3(Transform(nullptr, {2.0, 2.0}, {2.0, 2.0})); // Érintkezés
        Collider c4(Transform(nullptr, {5.0, 5.0}, {2.0, 2.0})); // Nincs átfedés

        EXPECT_TRUE(Collider::checkColliders(c1, c2)); // Metszik egymást
        EXPECT_TRUE(Collider::checkColliders(c1, c3)); // Érintkeznek
        EXPECT_FALSE(Collider::checkColliders(c1, c4)); // Nem metszenek
    } END

    // Ütközés teszt (Passzív Collider)
    TEST(Collider, utkozes_passziv)
    {
        Collider c1(Transform(nullptr, {0.0, 0.0}, {2.0, 2.0}));
        Collider c2(Transform(nullptr, {1.0, 1.0}, {2.0, 2.0}));
        Collider c3(Transform(nullptr, {5.0, 5.0}, {2.0, 2.0}));
        Collider c4(Transform(nullptr, {0.0, 0.0}, {2.0, 2.0}), ColliderType::PASSIVE);

        std::vector<Collider*> intersections = c1.checkIntersection();

        EXPECT_EQ(intersections.size(), 1);
        EXPECT_EQ(intersections[0], &c2);
    } END

    // Ütközés teszt (Destruktor)
    TEST(Collider, utkozes_destrukor)
    {
        Collider c1(Transform(nullptr, {0.0, 0.0}, {2.0, 2.0}));
        Collider c2(Transform(nullptr, {1.0, 1.0}, {2.0, 2.0}));

        EXPECT_TRUE(Collider::checkColliders(c1, c2)); // Metszik egymást

        {
            Collider c3(Transform(nullptr, {0.5, 0.5}, {1.0, 1.0}));
            EXPECT_TRUE(Collider::checkColliders(c1, c3)); // Metszik egymást
            EXPECT_TRUE(Collider::checkColliders(c2, c3)); // Metszik egymást
        }

        std::vector<Collider*> intersections = c1.checkIntersection();
        EXPECT_EQ(intersections.size(), 1);
        EXPECT_EQ(intersections[0], &c2); // c3 már nem létezik, csak c2 maradt
        EXPECT_TRUE(Collider::checkColliders(c1, c2)); // Metszik egymást
    } END

    // Ütközés teszt (Destruktor, lista)
    TEST(Collider, utkozes_lista_destruktor)
    {
        Collider c1(Transform(nullptr, {0.0, 0.0}, {2.0, 2.0}));
        Collider c2(Transform(nullptr, {1.0, 1.0}, {2.0, 2.0}));

        std::vector<Collider*> intersections = c1.checkIntersection();
        EXPECT_EQ(intersections.size(), 1);
        EXPECT_EQ(intersections[0], &c2);

        {
            Collider c3(Transform(nullptr, {0.5, 0.5}, {1.0, 1.0}));
            intersections = c1.checkIntersection();
            EXPECT_EQ(intersections.size(), 2);
        } // c3 destruktora lefut

        intersections = c1.checkIntersection();
        EXPECT_EQ(intersections.size(), 1);
        EXPECT_EQ(intersections[0], &c2);
    }
    END
}

void TestRunner::runPhysicsTests()
{
    GameRuntime::configureMock(100, 100);

    //physics object teszt (konstruktor pozícióval és mérettel)
    TEST(PhysicsObject, konstruktor)
    {
        Transform t1(nullptr, {0.0, 0.0}, {1.0, 1.0});
        Collider c1(t1);
        std::vector<Collider*> colliders = {&c1};

        PhysicsObject po(t1, colliders);

        EXPECT_DOUBLE_EQ(po.getPosition().x, 0.0);
        EXPECT_DOUBLE_EQ(po.getPosition().y, 0.0);
        EXPECT_DOUBLE_EQ(po.getScale().x, 1.0);
        EXPECT_DOUBLE_EQ(po.getScale().y, 1.0);
        EXPECT_EQ(po.getVelocity().x, 0.0);
        EXPECT_EQ(po.getVelocity().y, 0.0);
        EXPECT_EQ(po.getAcceleration().x, 0.0);
        EXPECT_EQ(po.getAcceleration().y, 0.0);
    } END

    //physics object teszt (sebesség és gyorsulás beállítása)
    TEST(PhysicsObject, fizika_sebesseg_gyorsulas)
    {
        Transform t1(nullptr, {0.0, 0.0}, {1.0, 1.0});
        Collider c1(t1);
        std::vector<Collider*> colliders = {&c1};

        PhysicsObject po(t1, colliders);

        po.setVelocity({5.0, -3.0});
        EXPECT_DOUBLE_EQ(po.getVelocity().x, 5.0);
        EXPECT_DOUBLE_EQ(po.getVelocity().y, -3.0);

        po.setAcceleration({2.0, 1.0});
        EXPECT_DOUBLE_EQ(po.getAcceleration().x, 2.0);
        EXPECT_DOUBLE_EQ(po.getAcceleration().y, 1.0);
    } END

    //physics object teszt (sebesség)
    TEST(PhysicsObject, fizika_sebesseg)
    {
        Transform t1(nullptr, {0.0, 0.0}, {1.0, 1.0});
        Collider c1(t1);
        std::vector<Collider*> colliders = {&c1};

        PhysicsObject po(t1, colliders);
        po.setVelocity({5.0, 0.0});
        po.setGravity({0.0, 0.0});
        po.setAcceleration({0.0, 0.0});

        for (int i = 0; i < 200; ++i) // Simulate 200 cycles
        {
            po.physicsUpdate();
        }

        EXPECT_DOUBLE_EQ(po.getPosition().x, 5.0 * 200 * GameRuntime::getPhysicsDeltaTime());
        EXPECT_DOUBLE_EQ(po.getPosition().y, 0.0);
    } END

    //physics object teszt (gyorsulás)
    TEST(PhysicsObject, gyorsulas)
    {
        Transform t1(nullptr, {0.0, 0.0}, {1.0, 1.0});
        Collider c1(t1);
        std::vector<Collider*> colliders = {&c1};

        PhysicsObject po(t1, colliders);
        po.setVelocity({0.0, 0.0});
        po.setAcceleration({1.0, 0.0});
        po.setGravity({0.0, 0.0});
        po.setMaxXVelocity({-2.0, 2.0});

        for (int i = 0; i < 300; ++i)
        {
            po.physicsUpdate();
        }

        EXPECT_EQ(po.getVelocity().x, 2.0); //Nem lépheti át a max sebességet
        EXPECT_GT(po.getPosition().x, 0.0); //Horizontálisan mozgott
    } END

    //physics object teszt (gravitáció)
    TEST(PhysicsObject, fizika_gravitacio)
    {
        Transform t1(nullptr, {0.0, 10.0}, {1.0, 1.0});
        Collider c1(t1);
        std::vector<Collider*> colliders = {&c1};

        PhysicsObject po(t1, colliders);
        po.setVelocity({0.0, 0.0});
        po.setAcceleration({0.0, 0.0});
        po.setMaxYVelocity({-20, 20});

        for (int i = 0; i < 500; ++i)
        {
            po.physicsUpdate();
        }
        
        EXPECT_LT(po.getPosition().y, 10.0); // Gravitáció hatására a pozíció csökken
        EXPECT_GE(po.getVelocity().y, -20.0); // Max sebesség nincs meghaladva
    } END

    //physics object teszt (ütközés)
    TEST(PhysicsObject, fizika_utkozes)
    {
        PhysicsObject po(Transform(nullptr, {0.0, 0.0}, {1.0, 1.0}), {});
        Collider c1(Transform(&po, {0, 0}, {1.0, 1.0}));
        Transform t2(nullptr, {5.0, 0.0}, {1.0, 1.0});
        Collider c2(t2);

        po.setVelocity({10.0, 0.0});
        po.setGravity({0.0, 0.0});
        po.setAcceleration({0.0, 0.0});

        for (int i = 0; i < 100; ++i)
        {
            po.physicsUpdate();
        }

        EXPECT_FALSE(Collider::checkColliders(c1, c2)); //Nem megy bele
        EXPECT_LT(po.getVelocity().x, 5.0);
    } END

    //physics object teszt (gravitáció és ütközés)
    TEST(PhysicsObject, fizika_utkozes_gravitacio)
    {
        PhysicsObject po(Transform(nullptr, {0.0, 10.0}, {1.0, 1.0}), {});
        Collider c1(Transform(&po, {0, 0}, {1.0, 1.0}));
        Transform t2(nullptr, {0.0, 0.0}, {10.0, 1.0}); //Talaj
        Collider c2(t2);

        po.setVelocity({0.0, 0.0});
        po.setAcceleration({0.0, 0.0});

        for (int i = 0; i < 500; ++i)
        {
            po.physicsUpdate();
        }

        EXPECT_FALSE(Collider::checkColliders(c1, c2)); //Nem megy bele a talajba
        EXPECT_GE(po.getPosition().y, 1.0); //Talaj tetején áll
        EXPECT_DOUBLE_EQ(po.getVelocity().y, 0.0); //Megáll
    } END

    TEST(PhysicsObject, tobb_collider_utkozes)
    {
        PhysicsObject po(Transform(nullptr, {0.0, 10.0}, {1.0, 1.0}), {});
        Collider c1(Transform(&po, {0, 0}, {1.0, 1.0}));
        Collider c2(Transform(&po, {1.0, 0}, {1.0, 1.0})); // Második collider
        Transform t2(nullptr, {0.0, 0.0}, {10.0, 1.0}); // Talaj
        Collider c3(t2);

        po.setVelocity({0.0, 0.0});
        po.setAcceleration({0.0, 0.0});

        for (int i = 0; i < 500; ++i)
        {
            po.physicsUpdate();
        }

        EXPECT_FALSE(Collider::checkColliders(c1, c3)); // Nem megy bele a talajba
        EXPECT_FALSE(Collider::checkColliders(c2, c3)); // Második collider sem megy bele
        EXPECT_GE(po.getPosition().y, 1.0); // Talaj tetején áll
        EXPECT_DOUBLE_EQ(po.getVelocity().y, 0.0); // Megáll
    } END

    //physics object teszt (ütközés és gravitáció, bounciness)
    TEST(PhysicsObject, utkozes_bounciness)
    {
        PhysicsObject po(Transform(nullptr, {0.0, 10.0}, {1.0, 1.0}), {});
        Collider c1(Transform(&po, {0, 0}, {1.0, 1.0}));
        Transform t2(nullptr, {0.0, 0.0}, {10.0, 1.0}); // Talaj
        Collider c2(t2, ColliderType::INTERACTIVE, 0.8);

        po.setVelocity({0.0, -10.0});
        po.setAcceleration({0.0, 0.0});
        po.setGravity({0.0, 0.0});

        for (int i = 0; i < 300; ++i)
        {
            po.physicsUpdate();
       }

        EXPECT_FALSE(Collider::checkColliders(c1, c2)); // Ütközik a talajjal
        EXPECT_GT(po.getPosition().y, 10.0); // Visszapattan
        EXPECT_DOUBLE_EQ(po.getVelocity().y, 8.0); // Sebesség csökken és megfordul a bounciness miatt
    } END

    //physics object teszt (teleportálás)
    TEST(PhysicsObject, teleportalas)
    {
        PhysicsObject po(Transform(nullptr, {0.0, 10.0}, {1.0, 1.0}), {});
        Collider c1(Transform(&po, {0, 0}, {1.0, 1.0}));
        Transform t2(nullptr, {0.0, 0.0}, {10.0, 1.0}); // Talaj
        Collider c2(t2);

        po.physicsUpdate();

        EXPECT_TRUE(po.tryTeleport({5.0, 5.0})); // Érvényes pozíció
        EXPECT_DOUBLE_EQ(po.getPosition().x, 5.0);
        EXPECT_DOUBLE_EQ(po.getPosition().y, 5.0);

        EXPECT_FALSE(po.tryTeleport({0.0, 0.0})); // Ütközne a talajjal
        EXPECT_DOUBLE_EQ(po.getPosition().x, 5.0); // Nem változik
        EXPECT_DOUBLE_EQ(po.getPosition().y, 5.0);
    } END

    //physics object teszt (max sebesség beállítása)
    TEST(PhysicsObject, max_sebesseg_tobb_tengely)
    {
        PhysicsObject po(Transform(nullptr, {0.0, 0.0}, {1.0, 1.0}), {});
        po.setVelocity({50.0, 50.0});
        po.setAcceleration({10.0, 10.0});
        po.setMaxXVelocity({-30.0, 30.0});
        po.setMaxYVelocity({-20.0, 20.0});

        for (int i = 0; i < 100; ++i)
        {
            po.physicsUpdate();
        }

        EXPECT_LE(po.getVelocity().x, 30.0); // X tengelyen nem lépi túl a max sebességet
        EXPECT_LE(po.getVelocity().y, 20.0); // Y tengelyen nem lépi túl a max sebességet
    } END

    //physics object teszt (ütközés mozgó objektumokkal)
    TEST(PhysicsObject, utkozes_mozgo_objektumok)
    {
        PhysicsObject po1(Transform(nullptr, {0.0, 0.0}, {1.0, 1.0}), {});
        Collider c1(Transform(&po1, {0, 0}, {1.0, 1.0}));

        PhysicsObject po2(Transform(nullptr, {5.0, 0.0}, {1.0, 1.0}), {});
        Collider c2(Transform(&po2, {0, 0}, {1.0, 1.0}));

        po1.setVelocity({2.0, 0.0}); // Mozgás jobbra
        po2.setVelocity({-2.0, 0.0}); // Mozgás balra

        for (int i = 0; i < 100; ++i)
        {
            po1.physicsUpdate();
            po2.physicsUpdate();
        }

        EXPECT_FALSE(Collider::checkColliders(c1, c2)); // Ütköznek
        EXPECT_LE(po1.getVelocity().x, 2.0); // Sebesség csökken az ütközés miatt
        EXPECT_GE(po2.getVelocity().x, -2.0); // Sebesség csökken az ütközés miatt
    } END


    //physicsObject teszt (ütközés és tagok hozzáadása)
    TEST(PhysicsObject, utkozes_tag_hozzaadas)
    {
        PhysicsObject po(Transform(nullptr, {0.0, 10.0}, {1.0, 1.0}), {});
        Collider c1(Transform(&po, {0, 0}, {1.0, 1.0}));
        Transform t2(nullptr, {0.0, 0.0}, {10.0, 1.0}); // Talaj
        Collider c2(t2, ColliderType::INTERACTIVE, 0.0, {ColliderTag::DEADLY});

        po.setVelocity({0.0, -10.0}); // Mozgás lefelé
        po.setAcceleration({0.0, 0.0});

        for (int i = 0; i < 100; ++i)
        {
            po.physicsUpdate();
        }

        EXPECT_TRUE(po.checkTag(ColliderTag::DEADLY)); // A DEADLY tag hozzá lett adva az ütközés miatt
    } END

    //physicsObject teszt (több tag hozzáadása ütközéskor)
    TEST(PhysicsObject, utkozes_tobb_tag_hozzaadas)
    {
        PhysicsObject po(Transform(nullptr, {0.0, 10.0}, {1.0, 1.0}), {});
        Collider c1(Transform(&po, {0, 0}, {1.0, 1.0}));
        Transform t2(nullptr, {0.0, 0.0}, {10.0, 1.0}); // Talaj
        Collider c2(t2, ColliderType::INTERACTIVE, 0.0, {ColliderTag::DEADLY, ColliderTag::PLAYER});

        po.setVelocity({0.0, -10.0}); // Mozgás lefelé
        po.setAcceleration({0.0, 0.0});

        for (int i = 0; i < 100; ++i)
        {
            po.physicsUpdate();
        }

        EXPECT_TRUE(po.checkTag(ColliderTag::DEADLY)); // A DEADLY tag hozzá lett adva
        EXPECT_TRUE(po.checkTag(ColliderTag::PLAYER)); // A PLAYER tag hozzá lett adva
    } END

    //physicsObject teszt (tag eltávolítása)
    TEST(PhysicsObject, tag_eltavolitas_utkozes_utan)
    {
        PhysicsObject po(Transform(nullptr, {0.0, 10.0}, {1.0, 1.0}), {});
        Collider c1(Transform(&po, {0, 0}, {1.0, 1.0}));
        Transform t2(nullptr, {0.0, 0.0}, {10.0, 1.0}); // Talaj
        Collider c2(t2, ColliderType::INTERACTIVE, 0.0, {ColliderTag::DEADLY});

        po.setVelocity({0.0, -10.0}); // Mozgás lefelé
        po.setAcceleration({0.0, 0.0});

        for (int i = 0; i < 100; ++i)
        {
            po.physicsUpdate();
        }

        EXPECT_TRUE(po.checkTag(ColliderTag::DEADLY)); // A DEADLY tag hozzá lett adva

        po.clearTags();
        EXPECT_FALSE(po.checkTag(ColliderTag::DEADLY)); // A DEADLY tag el lett távolítva
    } END

    //physicsObject teszt (több collider ütközése különböző tagekkel)
    TEST(PhysicsObject, tobb_collider_kulonbozo_tagek)
    {
        PhysicsObject po(Transform(nullptr, {0.0, 10.0}, {1.0, 1.0}), {});
        Collider c1(Transform(&po, {0, 0}, {1.0, 1.0}));
        Transform t2(nullptr, {0.0, 0.0}, {10.0, 1.0}); // Talaj
        Collider c2(t2, ColliderType::INTERACTIVE, 0.0, {ColliderTag::DEADLY});
        Transform t3(nullptr, {0.0, 5.0}, {10.0, 1.0}); // Másik collider
        Collider *c3 = new Collider(t3, ColliderType::INTERACTIVE, 0.0, {ColliderTag::PLAYER});

        for (int i = 0; i < 200; ++i)
        {
            po.physicsUpdate();
        }
        delete c3;
        for (int i = 0; i < 200; ++i)
        {
            po.physicsUpdate();
        }

        EXPECT_TRUE(po.checkTag(ColliderTag::DEADLY)); // A DEADLY tag hozzá lett adva
        EXPECT_TRUE(po.checkTag(ColliderTag::PLAYER)); // A PLAYER tag hozzá lett adva
    } END

    //physicsObject teszt (tagek tisztítása)
    TEST(PhysicsObject, tagok_tisztitasa)
    {
        PhysicsObject po(Transform(nullptr, {0.0, 10.0}, {1.0, 1.0}), {});
        Collider c1(Transform(&po, {0, 0}, {1.0, 1.0}));
        Transform t2(nullptr, {0.0, 0.0}, {10.0, 1.0}); // Talaj
        Collider c2(t2, ColliderType::INTERACTIVE, 0.0, {ColliderTag::DEADLY, ColliderTag::PLAYER});

        po.setVelocity({0.0, -10.0}); // Mozgás lefelé
        po.setAcceleration({0.0, 0.0});

        for (int i = 0; i < 100; ++i)
        {
            po.physicsUpdate();
        }

        EXPECT_TRUE(po.checkTag(ColliderTag::DEADLY)); // A DEADLY tag hozzá lett adva
        EXPECT_TRUE(po.checkTag(ColliderTag::PLAYER)); // A PLAYER tag hozzá lett adva

        po.clearTags();

        EXPECT_FALSE(po.checkTag(ColliderTag::DEADLY)); // A DEADLY tag el lett távolítva
        EXPECT_FALSE(po.checkTag(ColliderTag::PLAYER)); // A PLAYER tag el lett távolítva
    } END
}

void TestRunner::runMapTests()
{
    //mapManager teszt (beolvasás)
    TEST(MapManager, map_beolvasas)
    {
        MapManager mapManager;

        EXPECT_STREQ(mapManager.getSerializedMapInfo(0).c_str(), "5 255 255 255 3 -5 -2 5 -2");
        EXPECT_STREQ(mapManager.getSerializedMapElement(0, 0).c_str(), "0 -5 20 1 100 100 100 0 0 1 1");
        EXPECT_STREQ(mapManager.getSerializedMapElement(0, 1).c_str(), "0 -4 1 1 100 100 100 0 0 1 1");

        EXPECT_STREQ(mapManager.getSerializedMapInfo(1).c_str(), "10 0 100 200 1 -12 -7 12 -7");
        EXPECT_STREQ(mapManager.getSerializedMapElement(1, 0).c_str(), "0 -9 10 1 250 150 50 1 0 0.95 0.8");
        EXPECT_STREQ(mapManager.getSerializedMapElement(1, 1).c_str(), "0 -10 40 1 50 150 250 0 0 1 1");
        EXPECT_STREQ(mapManager.getSerializedMapElement(1, 2).c_str(), "0 -7 4 1 100 200 100 0 1 1 1");
    } END
}
#endif