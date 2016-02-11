//
//  main.cpp
//  C3DtoTxt
//
//  Created by Omid Alemi on 2016-02-11.
//  Copyright © 2016 Omid Alemi. All rights reserved.
//

#include <iostream>
#include "mmParser.h"

using namespace MoMa;
using namespace std;

int main(int argc, const char * argv[]) {
    cout <<"C3D to Text Converter" << endl;
    
    if (argc < 2){
        cout<<"Usage: c3d2txt filename.c3d"<<endl;
        return 1;
    }
    
    std::string inputFileName;
    std::string outputFileName;
    
    Track *track;
    
    track = new Track();
    
    // Read the C3D file name from the command line arguments
    inputFileName = argv[1];

    size_t sep = inputFileName.find_last_of("\\/");
    size_t dot = inputFileName.find_last_of(".");
    
    outputFileName = inputFileName.substr( sep + 1, dot-sep-1 );

    
    // Reading the C3D File
    cout << "Parsing the C3D file" << endl;
    track->load(inputFileName);

    // Writing the Node (Marker) Names
    cout << "There are " + std::to_string(track->nOfNodes()) + " markers in this file" << endl;
    cout << "Writing the node list in " + outputFileName + "_markers.txt" << endl;
    
    ofstream markerfile;
    markerfile.open (outputFileName + "_markers.txt");
    
    map<string,int>::const_iterator it = track->nodeList->begin();
    while( it != track->nodeList->end() ) {
        
        markerfile << it->first << ",";
        markerfile << it->second << endl;
    
        ++it;
    }
    markerfile.close();
    
    // Writing the position data
    cout << "There are " + std::to_string(track->nOfFrames()) + " frames in this file" << endl;
    cout << "Writing the position data in " + outputFileName + "_armaascii.txt" << endl;
    
    track->position.getData().save(outputFileName+"_armaascii.txt", arma::arma_ascii);
    
    cout << "Finished" << endl;
    return 0;
}
