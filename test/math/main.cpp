/*
 * Some very simple tests to check if the Math utility functions are working
 * like they're supposed to. No in depth testing.
 *
 * */

#include <Math3D.h>
#include <iostream>
#include <iomanip>
#include <boost/format.hpp>
using boost::format;
using namespace gliby::Math3D;

int nSuccess = 0;
int nTotal = 0;

void test(const char* name, bool success){
    std::cout << format("%-30s %-20s") % name % (success ? "[OK]" : "[FAIL]") << std::endl;
    //std::cout << name << ":" << (success ? "[OK]" : "[FAIL]") << std::endl;
    ++nTotal;
    if(success) ++nSuccess;
}

int main(){
    Vector3f a = {2.0,2.0,2.0};
    Vector3f b = {2.0,2.0,2.0};

    test("firstPowOf2",firstPowOf2(300) == 512);
    
    Vector3f r = {1.0};
    addVectors3(r,a,b);
    test("addVectors3",r[0] == 4);

    subtractVectors3(r,r,b);
    test("subtractVectors3",r[0] == 2);

    scaleVector3(r,3);
    test("scaleVector3",r[0] == 6);

    Vector3f c1 = {3,1,0};
    Vector3f c2 = {2,1,1};
    crossProduct(r,c1,c2);
    test("crossProduct",r[0] == 1 && r[1] == -3 && r[2] == 1);

    float dotp = dotProduct(c1,c2);
    test("dotProduct",dotp == 7);

    Vector3f a1 = {3,1,2};
    Vector3f a2 = {2,1,1};
    normalizeVector(a1);
    normalizeVector(a2);
    test("normalizeVector",a1[0] > 0.801783 && a1[0] < 0.801785);

    float angle = angleBetweenVectors(a1,a2);
    test("angleBetweenVectors", angle > 0.190125 && angle < 0.190127);

    Vector3f d1 = {1,1,1};
    Vector3f d2 = {2,2,2};
    float distance = getDistance(d1,d2);
    test("getDistance",distance > 1.73204 && distance < 1.73206);

    Vector3f m = {2,2,3};
    float magnitude = getMagnitude(m);
    test("getMagnitude",magnitude > 4.12310 && magnitude < 4.12312);
    
    Matrix33f mtrx = {0};
    loadIdentity33(mtrx);
    test("loadIdentity",mtrx[0] == 1 && mtrx[4] == 1);

    Vector3f column = {9};
    getMatrixColumn33(column,mtrx,0);
    test("getMatrixColumn",column[0] == 1 && column[1] == 0 && column[2] == 0);

    // TODO: test rotation matrix
    /*Matrix44f full = {0};
    loadIdentity44(full);
    outputMatrix44(full);
    Matrix33f rotation = {0};
    extractRotationMatrix(rotation,full);
    rotation[1] = 1;
    injectRotationMatrix(full,rotation);
    outputMatrix33(rotation);
    outputMatrix44(full);*/

    Matrix44f ma = {0};
    Matrix44f mb = {0};
    Matrix44f mp = {0};
    loadIdentity44(ma);
    ma[0] = 2;
    loadIdentity44(mb);
    multiplyMatrix44(mp,ma,mb);
    test("multiplyMatrix",mp[0] == 2);

    Vector3f in = {1,1,1};
    Vector3f out = {0,0,0};
    transformVector3(out,in,ma);
    test("transformVector",out[0] == 2);

    // TODO: test rotateVector

    Matrix33f sc = {0};
    scaleMatrix33(sc,2,2,2);
    test("scaleMatrix",sc[0] == 2);

    // TODO: test creation of projection matrices

    // TODO: test creation of rotation matrix
    /*Matrix33f rm = {0};
    rotationMatrix33(rm,PI,1,1,0);
    outputMatrix33(rm);*/

    Matrix44f tm = {0};
    translationMatrix(tm,10,0,0);
    test("translationMatrix",tm[12] == 10);

    Matrix44f dm = {1,3,2,1, 2,2,1,1, 3,1,3,1, 1,1,1,1};
    test("detIJ",detIJ(dm,1,2) == -4);

    Matrix44f inverse = {0};
    invertMatrix44(inverse,tm);
    test("invertMatrix",inverse[12] == -10);

    Vector3f v1 = {0,0,1};
    Vector3f v2 = {0,1,0};
    Vector3f v3 = {1,0,0};
    Vector3f nr = {0};
    findNormal(nr,v1,v2,v3);
    test("findNormal",nr[0] == -1 && nr[1] == -1 && nr[2] == -1);

    // TODO: test get the signed distance of a point to a plane
    
    // TODO: test get plane equation from 3 points
    
    // TODO: test raySphereTest
    
    // TODO: test projectXY and projectXYZ
    
    // TODO: test catmullRom
    
    // TODO: test calculateTangentBasis
    
    test("smoothStep", smoothStep(0.0f, 5.0f, 2.5f) == 0.5);

    // TODO: test makePlanarShadowMatrix
    
    // TODO: test closestPointOnRay

    std::cout << nSuccess << " of " << nTotal << " tests succeeded." << std::endl;

    return 0;
}
