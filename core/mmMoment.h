#ifndef __mmMoment__
#define __mmMoment__

#include <iostream>

namespace MoMa {
    
    class Moment {
    
      public:
        
        Moment( void );
        Moment( double time, double frameRate );
        Moment( unsigned int idx, double frameRate );
        
        inline double time( void ) { return( _time ); }
        inline unsigned int index( void ) { return( _index ); }
        
        double frameRate( void ) { return( _frameRate ); }
        void setFrameRate( double frameRate );
        
        void setTime( double time, double frameRate );
        void setIndex( unsigned int idx, double frameRate );
        void setIndex( int idx, double frameRate );
        
        void setTime( double time );
        void setIndex( unsigned int idx );
        void setIndex( int idx );
        
      protected:
        
        double _frameRate;
        unsigned int _index;
        double _time;
    };
}

#endif
