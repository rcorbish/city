

#include "sphere.h"

struct TriangleIndices {
    const int v1;
    const int v2;
    const int v3;

    TriangleIndices(int v1, int v2, int v3) :
            v1(v1) ,
            v2(v2) ,
            v3(v3) {}
} ;


int Sphere::getMiddlePoint(int p1, int p2, std::map<long,int> &cache )
{
    // first check if we have it already
    bool firstIsSmaller = p1 < p2;
    long smallerIndex = firstIsSmaller ? p1 : p2;
    int greaterIndex = firstIsSmaller ? p2 : p1;
    long key = (smallerIndex << 20) + greaterIndex;

    auto it = cache.find( key ) ;
    if( it != cache.end() ) {
        return it->second ;
    }

    // not in cache, calculate it
    Vertex &v1 = vertexData[p1];
    Vertex &v2 = vertexData[p2];
    
    int i = addVertex( 
            (v1.x + v2.x) / 2.f,
            (v1.y + v2.y) / 2.f,
            (v1.z + v2.z) / 2.f
            );

    // indices.push_back( i ) ;

    // store it, return index
    cache[key] = i ;
    return i ;
}


void Sphere::makeVertexData() {
    std::map<long,int> middlePointIndexCache ;

    // create 12 vertices of a icosahedron
    float t = (1.f + (float)std::sqrt(5.0)) / 2.f;

    addVertex(-1,  t,  0 );
    addVertex( 1,  t,  0 );
    addVertex(-1, -t,  0 );
    addVertex( 1, -t,  0 );

    addVertex( 0, -1,  t );
    addVertex( 0,  1,  t );
    addVertex( 0, -1, -t );
    addVertex( 0,  1, -t );

    addVertex( t,  0, -1 );
    addVertex( t,  0,  1 );
    addVertex(-t,  0, -1 );
    addVertex(-t,  0,  1 );

    // create 20 triangles of the icosahedron
    auto faces = new std::vector<TriangleIndices>() ;
    faces->reserve( 20 ) ;

    // 5 faces around point 0
    faces->emplace_back( 0, 11, 5 );
    faces->emplace_back( 0, 5, 1 );
    faces->emplace_back( 0, 1, 7 );
    faces->emplace_back( 0, 7, 10 );
    faces->emplace_back( 0, 10, 11 );

    // 5 adjacent faces
    faces->emplace_back( 1, 5, 9 );
    faces->emplace_back( 5, 11, 4 );
    faces->emplace_back( 11, 10, 2 );
    faces->emplace_back( 10, 7, 6 );
    faces->emplace_back( 7, 1, 8 );

    // 5 faces around point 3
    faces->emplace_back( 3, 9, 4 );
    faces->emplace_back( 3, 4, 2 );
    faces->emplace_back( 3, 2, 6 );
    faces->emplace_back( 3, 6, 8 );
    faces->emplace_back( 3, 8, 9 );

    // 5 adjacent faces
    faces->emplace_back( 4, 9, 5 ) ;
    faces->emplace_back( 2, 4, 11 ) ;
    faces->emplace_back( 6, 2, 10 ) ;
    faces->emplace_back( 8, 6, 7 ) ;
    faces->emplace_back( 9, 8, 1 ) ;

    // refine triangles
    for( int i=0 ; i < recursionLevel; i++ )
    {
        auto faces2 = new std::vector<TriangleIndices>() ;
        faces2->reserve( 4 * faces->size() ) ;

        for( auto & tri : *faces )  {
            // replace triangle by 4 triangles
            int a = getMiddlePoint( tri.v1, tri.v2, middlePointIndexCache ) ;
            int b = getMiddlePoint( tri.v2, tri.v3, middlePointIndexCache ) ;
            int c = getMiddlePoint( tri.v3, tri.v1, middlePointIndexCache ) ;

            faces2->emplace_back( tri.v1, a, c ) ;
            faces2->emplace_back( a, tri.v2, b ) ;
            faces2->emplace_back( c, b, tri.v3 ) ;
            faces2->emplace_back( a, b, c ) ;
        }

        delete faces ;
        faces = faces2;
    }

    for( auto & tri : *faces )
    {
        indices.push_back( tri.v1 ) ;
        indices.push_back( tri.v2 ) ;
        indices.push_back( tri.v3 ) ;
    }

    delete faces ;
}

int Sphere::addVertex(  float x,  float y,  float z ) {
    float len = std::sqrt( x*x + y*y + z*z ) ;
    return Shape::addVertex( x/len, y/len, z/len ) ;
}
