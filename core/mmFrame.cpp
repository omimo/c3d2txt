/**
*
*  @file mmFrame.cpp
*  @brief MotionMachine source file for Frame class.
*  @copyright Numediart Institute, UMONS (c) 2014-2015
*
*/

#include "mmFrame.h"

using namespace std;
using namespace arma;

MoMa::Frame::Frame( void ) {
    
    _hasRotation = false;
    _hasTime = false; _time = 0.0f;
    
    hasNodeList = false; nodeList = NULL;
    hasBoneList = false; boneList = NULL;
    // hasSynoList = false; synoList = NULL;
}

MoMa::Frame::Frame( arma::mat cartesianData, arma::mat rotationData, arma::mat rotOffset ) {
    
    _hasRotation = false;
    _hasTime = false; _time = 0.0f;
    
    hasNodeList = false; nodeList = NULL;
    hasBoneList = false; boneList = NULL;
    // hasSynoList = false; synoList = NULL;
    
    position = cartesianData;
    rotation = rotationData;
    rotationOffset = rotOffset;
}

MoMa::Frame::Frame( arma::mat cartesianData, arma::mat rotationData ) {
    
    _hasRotation = false;
    _hasTime = false; _time = 0.0f;
    
    hasNodeList = false; nodeList = NULL;
    hasBoneList = false; boneList = NULL;
    // hasSynoList = false; synoList = NULL;
    
    position = cartesianData;
    rotation = rotationData;
}

MoMa::Frame::Frame( arma::mat cartesianData ) {
    
    _hasRotation = false;
    _hasTime = false; _time = 0.0f;
    
    hasNodeList = false; nodeList = NULL;
    hasBoneList = false; boneList = NULL;
    // hasSynoList = false; synoList = NULL;
    
    position = cartesianData;
}

void MoMa::Frame::setPositionData( arma::mat cartesianData ) {
    
    position = cartesianData;
}

void MoMa::Frame::setRotationData( arma::mat rotationData, arma::mat rotOffset ) {
    
    _hasRotation = true;
    rotation = rotationData;
    rotationOffset = rotOffset;
}

void MoMa::Frame::setNodeList( MoMa::NodeList *nList ) {

    hasNodeList = true;
    nodeList = nList;
}

void MoMa::Frame::setBoneList( MoMa::BoneList *bList ) {

    hasBoneList = true;
    boneList = bList;
}

void MoMa::Frame::setSynoList( MoMa::SynoList *sList ) {

    // hasSynoList = true;
    // synoList = sList;
}

void MoMa::Frame::setTime( double t ) {

    _hasTime = true;
    _time = t;
}

mat MoMa::Frame::matrix( void ) {

    mat frame;

    if( hasRotation() ) {
        
        frame = arma::join_rows( position, rotation );
    
    } else {
        
        frame = position;
    }
    
    return( frame );
}

int MoMa::Frame::index( std::string name ) {
    
    int nIdx = -1;
    
    if( hasNodeList ) {
        
        nIdx = nodeList->index( name );
        
        if( nIdx <= -1 ) cout << "Frame::index: Node not found" << endl;
    
    } else {
    
        cout << "Frame::index(): No node name list" << endl;
    }
    
    return( nIdx );
    
    /*
    int nIdx = -1; // Initialise
    bool isFound = false; // Flag

    if( hasNodeList ) {

        for( int n=0; n<nodeList->size(); n++ ) {

            // If we find a matching name, we save index
            if( nodeList->name(n).compare( name ) == 0 ) {

                isFound = true; nIdx = n;
            }
        }
        
        if( hasSynoList && !isFound ) {

            for( int n=0; n<nodeList->size(); n++ ) {

                string nNameQuery = "nq"; // Synonym of name query
                string nFromList = "fl"; // Synonym of nth in list

                synoList->search( name, nNameQuery ); // Search name
                synoList->search( nodeList->name(n), nFromList ); // & list

                if( nFromList.compare( nNameQuery ) == 0 ) {
                    
                    nIdx = n; // :)
                    isFound = true;
                }
            }
        }

        if( !isFound ) {
            
            cout << "Frame::index: Node not found" << endl;
        }

    } else {

        cout << "Frame::index: No node name list" << endl;
    }
    */
}

int MoMa::Frame::nOfNodes( void ) const {

    return( (int)std::max( (float)(position.n_cols), (float)(rotation.n_cols) ) );
}

void MoMa::Frame::print( void ) {

    cout << "--- # of nodes: " << nOfNodes();
    if( hasTime() ) cout << " | time = " << _time;
    cout << " ---" << endl;

    for( int n=0; n<nOfNodes(); n++ ) {

        cout << position( X,n) << "\t";
        cout << position( Y,n ) << "\t";
        cout << position( Z,n ) << "\t";

        if( hasRotation() ) {

            cout << rotation( 0,n ) << "\t";
            cout << rotation( 1,n ) << "\t";
            cout << rotation( 2,n ) << "\t";
            cout << rotation( 3,n ) << "\t";
        }

        if( hasTime() ) {

            cout << "(" << this->time() << ")\t";
        }

        cout << endl;
    }
}
