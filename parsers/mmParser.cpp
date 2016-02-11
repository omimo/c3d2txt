#include "mmParser.h"

using namespace std;
using namespace MoMa;


Parser::Parser( string const &fName, Track *tr ) {

    track = tr;
    fileName = fName;

#ifdef _WIN32
    fileName = checkFileName( fileName );
#endif

    //set trackName
    /*string shortFName;
    char* tmp = new char[fileName.size()+1];
    strncpy(tmp, fileName.c_str(),fileName.size());
    tmp[fileName.size()]=NULL;
    char* tmpName;
    _splitpath(tmp,NULL,NULL,tmpName,NULL);
    shortFName=string(tmpName);
    track->setTrackName(shortFName);*/

    size_t sep = fileName.find_last_of("\\/");
    size_t dot = fileName.find_last_of(".");    

    int previousSize = track->nOfNodes();
    extension = fileName.substr( dot + 1) ;
    transform( extension.begin(), extension.end(), extension.begin(), ::tolower );

    if( extension == "txt" ) {        

        track->setFileName( fileName.substr( sep + 1, dot-sep-1 ) );

        FlatParser flatParser( fileName,track );
		 tr->position.SetValidParam();
		 if (tr->hasRotation)
			 tr->rotation.SetValidParam();

        // Check validity of lists of bones and nodes
        if( track->nOfNodes() != previousSize && previousSize != 0 ) {

            // different number of
            // markers => different labels
            if( track->hasNodeList == true ) {

                track->hasNodeList = false;
                delete track->nodeList;
            }

            //different number of
            // markers => different skeleton
            if( track->hasBoneList == true ) {

                track->hasBoneList = false;
                delete track->boneList;
            }
        }
    }

    else if( extension == "v3d" ) {

        track->setFileName( fileName.substr( sep + 1, dot-sep-1 ) );

        V3dParser v3dParser( fileName, track );
		 tr->position.SetValidParam();
		 if (tr->hasRotation)
			 tr->rotation.SetValidParam();

        // Check validity of list of bones
        if( track->nOfNodes() != previousSize &&
            previousSize != 0 && track->hasBoneList == true ) {

                // different number of
                // markers => different skeleton
                track->hasBoneList = false;
                delete track->boneList;
        }
        tr->setJointOffsetRotation();
    }

    else if( extension == "c3d" ) {

        track->setFileName( fileName.substr( sep + 1, dot-sep-1 ) );

        C3dParser c3dParser( fileName, track );
		 tr->position.SetValidParam();
		 if (tr->hasRotation)
			 tr->rotation.SetValidParam();

        // Check validity of list of bones
        if( track->nOfNodes() != previousSize &&
            previousSize !=0 && track->hasBoneList == true ) {

                // different number of
                // markers => different skeleton
                track->hasBoneList = false;
                delete track->boneList;
        }
    }
    
    else if( extension == "bvh" ) {
        
        track->setFileName( fileName.substr( sep + 1, dot-sep-1 ) );
        
        BvhParser::load( fileName, track );
		 tr->position.SetValidParam();
		 if (tr->hasRotation)
			 tr->rotation.SetValidParam();
        // Check validity of list of bones
        if( track->nOfNodes() != previousSize &&
           previousSize !=0 && track->hasBoneList == true ) {
            
            // different number of
            // markers => different skeleton
            track->hasBoneList = false;
            delete track->boneList;
        }
        tr->setJointOffsetRotation();
    }
    else if( extension == "cmp" ) {
        
        track->setFileName( fileName.substr( sep + 1, dot-sep-1 ) );
        
        CmpParser Parser;
        Parser.load( fileName, track );
		 tr->position.SetValidParam();
		 if (tr->hasRotation)
			 tr->rotation.SetValidParam();
        // Check validity of list of bones
        if( track->nOfNodes() != previousSize &&
           previousSize !=0 && track->hasBoneList == true ) {
            
            // different number of
            // markers => different skeleton
            track->hasBoneList = false;
            delete track->boneList;
        }
//        tr->setJointOffsetRotation(true);
		
    }
    else if( extension == "kin" ) {
        
        track->setFileName( fileName.substr( sep + 1, dot-sep-1 ) );
        KinParser kinParser( fileName, track );
        // Check validity of lists of bones and nodes
		 tr->position.SetValidParam();
		 if (tr->hasRotation)
			 tr->rotation.SetValidParam();
        if( track->nOfNodes() != previousSize && previousSize != 0 ) {
            
            // different number of
            // markers => different labels
            if( track->hasNodeList == true ) {
                
                track->hasNodeList = false;
                delete track->nodeList;
            }
            
            //different number of
            // markers => different skeleton
            if( track->hasBoneList == true ) {
                
                track->hasBoneList = false;
                delete track->boneList;
            }
        }
         tr->setJointOffsetRotation();
    }

    else if( extension == "bones" ) {
        track->bones( fileName );
        tr->setJointOffsetRotation();
    }

    else if( extension == "nodes" ) track->nodes( fileName );

    else cout << "Invalid file format" << endl;
}

string Parser::checkFileName( string const &fName ) {

    string tmp;

    // Added to manage special characters (accents
    // for example) in file path (extended ASCII table)

    for( int i=0; i<fName.size(); ++i ) {

        if( fName[i] != -61 ) {

            // Basic ASCII table
            tmp.push_back( fName[i] );

        } else {

            // Manage buggy special characters (extended ASCII character) the
            // special character is divided in two characters : -61 and X (between
            // -1 and -127); to get a valid character the conversion is c = X+64

            ++i; // tmp[i] was -61
            tmp.push_back( fName[i]+64 );
        }
    }

    return tmp;
}


