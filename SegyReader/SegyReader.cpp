#include "SegyReader.h"

SegyReader* SegyReader::instance = nullptr;

SegyReader::SegyReader( const string _file_name ){
	
	if ( nullptr == (segy_file = fopen( _file_name.c_str(), "rb" )) ){
		fprintf( stdout, "ReadSegy: Cannot open segy file - %s\n", _file_name.c_str() );
	} else {
		file_name = _file_name;
	}
}

SegyReader* SegyReader::getInstance( const string file_name ){
	if ( nullptr == instance ){
		instance = new SegyReader( file_name );
		return instance;
	} else {
		return instance;
	}
}

const SegyBinaryHeader* SegyReader::getSegyBinaryHeader(){

}
