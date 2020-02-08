

#include "sphere.h"

#include <vector>
#include <map>

struct TriangleIndices ;
struct Point3D ;

/**
 * Create a sphere mesh, using icosphere rules
 *
 * @link http://blog.andreaskahler.com/2009/06/creating-icosphere-mesh-in-code.html
 *
 */
class Sphere : public Shape {

  private :
    std::vector<Point3D> positions ;
    std::vector<int> indices ;

  protected:

    // return index of point in the middle of p1 and p2
    int getMiddlePoint(int p1, int p2, std::map<long,int> &cache )
    {
        // first check if we have it already
        boolean firstIsSmaller = p1 < p2;
        long smallerIndex = firstIsSmaller ? p1 : p2;
        int greaterIndex = firstIsSmaller ? p2 : p1;
        long key = (smallerIndex << 20) + greaterIndex;

        Integer mp = cache.get( key ) ;
        if( mp != null ) {
            return mp;
        }

        // not in cache, calculate it
        Point3D point1 = positions[p1];
        Point3D point2 = positions[p2];
        int i = addVertex( 
                (point1.x + point2.x) / 2.f,
                (point1.y + point2.y) / 2.f,
                (point1.z + point2.z) / 2.f
                );

        // store it, return index
        cache.put( key, i ) ;
        return i ;
    }


  public :
    void makeVertexData( float *vertices ) {
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
        std::vector<TriangleIndices> faces() ;

        // 5 faces around point 0
        faces.emplace_back( 0, 11, 5 );
        faces.emplace_back( 0, 5, 1 );
        faces.emplace_back( 0, 1, 7 );
        faces.emplace_back( 0, 7, 10 );
        faces.emplace_back( 0, 10, 11 );

        // 5 adjacent faces
        faces.emplace_back( 1, 5, 9 );
        faces.emplace_back( 5, 11, 4 );
        faces.emplace_back( 11, 10, 2 );
        faces.emplace_back( 10, 7, 6 );
        faces.emplace_back( 7, 1, 8 );

        // 5 faces around point 3
        faces.emplace_back( 3, 9, 4 );
        faces.emplace_back( 3, 4, 2 );
        faces.emplace_back( 3, 2, 6 );
        faces.emplace_back( 3, 6, 8 );
        faces.emplace_back( 3, 8, 9 );

        // 5 adjacent faces
        faces.emplace_back( 4, 9, 5 );
        faces.emplace_back( 2, 4, 11 );
        faces.emplace_back( 6, 2, 10 );
        faces.emplace_back( 8, 6, 7 );
        faces.emplace_back( 9, 8, 1 );

        // refine triangles
        for( int i=0 ; i < recursionLevel; i++ )
        {
            std::vector<TriangleIndices> faces2() ; 
            faces2.reserve( 4 * faces.size() ) ;

            for( auto tri : faces )  {
                // replace triangle by 4 triangles
                int a = getMiddlePoint(tri.v1, tri.v2, cache );
                int b = getMiddlePoint(tri.v2, tri.v3, cache );
                int c = getMiddlePoint(tri.v3, tri.v1, cache );

                faces2.emplace_back( tri.v1, a, c );
                faces2.emplace_back( a, tri.v2, b );
                faces2.emplace_back( c, b, tri.v3 );
                faces2.emplace_back( a, b, c );
            }
            faces = faces2;
        }

        int ix = 0 ;
        for( auto point : positions ) {
            vertices[ix++] = point.x ;
            vertices[ix++] = point.y ;
            vertices[ix++] = point.z ;
        }

        for( auto tri : faces )
        {
            triangleIndices.add( tri.v1 ) ;
            triangleIndices.add( tri.v2 ) ;
            triangleIndices.add( tri.v3 ) ;
        }
    }


void Sphere::initVertexData() {
    size_t verticesSize = numVertices * BytesPerVertex ;

    float vertexData[ numVertices * FloatsPerVertex ] ;
    makeVertexData( vertexData ) ;
    glGenVertexArrays( 1, &VAO ) ;
    glGenBuffers( 1, &VBO ) ;
    
    glBindVertexArray( VAO ) ;
    glBindBuffer( GL_ARRAY_BUFFER, VBO ) ;
    glBufferData( GL_ARRAY_BUFFER, verticesSize, vertexData, GL_STATIC_DRAW ) ;

    glEnableVertexAttribArray( 0 ) ;  // location(0) = aPos
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, BytesPerVertex, PositionOffset ) ;

    glEnableVertexAttribArray( 1 ) ;  // location(1) = normal
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, BytesPerVertex, NormalOffset ) ;

    glEnableVertexAttribArray( 2 ) ;  // location(2) = texture
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, BytesPerVertex, TextureOffset ) ;

    this->indices = new unsigned short[ numVertices ] ;

    for( unsigned short i=0 ; i<numVertices ; i++ ) {
        this->indices[i] = i ;
    }
}


struct TriangleIndices {
    final public int v1;
    final public int v2;
    final public int v3;

    public TriangleIndices(int v1, int v2, int v3) {
            this.v1 = v1;
            this.v2 = v2;
            this.v3 = v3;
    }
}

struct Point3D {
    const float x ;
    const float y ;
    const float z ;

    Point3D( const float x, const float y, const float z ) :
        x(x) ,
        y(y) ,
        z(z) {} 

    Point3D &normalize() {
        float len = (float)Math.sqrt( x*x + y*y + z*z ) ;
        return Point3D( x/len, y/len, z/len ) ;
    }
} ;

