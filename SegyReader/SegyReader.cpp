#include "SegyReader.h"

SegyReader* SegyReader::instance = nullptr;
const unsigned int data_bytes[] = { 4, 4, 2, 4, 4, 1 };
 
void swapByte2( int_16 *data ){
	unsigned char tmp = 0;
	tmp = data[0];
	data[0] = data[1];
	data[1] = tmp;
}

void swapByte4( int_32 *data ){
	unsigned char tmp = 0;
	tmp = data[0];
	data[0] = data[3];
	data[3] = tmp;

	tmp = data[1];
	data[1] = data[2];
	data[2] = tmp;
}


//two methods to make the SegyBinaryHeader in a correct byte order for microcomputer
/*
*first one: swap the member of the SegyBinaryHeader struct one by one.
*the second one: we can swap one block of memory once a time. It may lead to an error causing by the byte alignment operating by ths OS.
*So I choose the first one.
*/
void SegyReader::swapSegyBinaryHeader( SegyBinaryHeader* segy_bin_hdr ) const{
	convertBinary( &(segy_bin_hdr->job_id_number), 4 );
	convertBinary( &(segy_bin_hdr->line_number), 4 );
	convertBinary( &(segy_bin_hdr->reel_number), 4 );
	convertBinary( &(segy_bin_hdr->traces_per_record), 2 );
	convertBinary( &(segy_bin_hdr->aux_traces_per_record), 2 );
	convertBinary( &(segy_bin_hdr->sample_data_interval_ms), 2 );
	convertBinary( &(segy_bin_hdr->original_data_interval_ms), 2 );
	convertBinary( &(segy_bin_hdr->samples_per_trace), 2 );
	convertBinary( &(segy_bin_hdr->original_samples_per_trace), 2 );
	convertBinary( &(segy_bin_hdr->data_sample_format_code), 2 );
	convertBinary( &(segy_bin_hdr->CDP_fold), 2 );
	convertBinary( &(segy_bin_hdr->trace_sorting_code), 2 );
	convertBinary( &(segy_bin_hdr->vertical_sum_code), 2 );
	convertBinary( &(segy_bin_hdr->sweep_frequency_start_hz), 2 );
	convertBinary( &(segy_bin_hdr->sweep_frequency_end_hz), 2 );
	convertBinary( &(segy_bin_hdr->sweep_length_ms), 2 );
	convertBinary( &(segy_bin_hdr->sweep_type_code), 2 );
	convertBinary( &(segy_bin_hdr->trace_number_of_sweep_channel), 2 );
	convertBinary( &(segy_bin_hdr->sweep_trace_taper_length_start_ms), 2 );
	convertBinary( &(segy_bin_hdr->sweep_trace_taper_length_end_ms), 2 );
	convertBinary( &(segy_bin_hdr->taper_type_code), 2 );
	convertBinary( &(segy_bin_hdr->correlated_data_traces_flag), 2 );
	convertBinary( &(segy_bin_hdr->binary_gain_recovered_flag), 2 );
	convertBinary( &(segy_bin_hdr->amplitude_recovery_method_code), 2 );
	convertBinary( &(segy_bin_hdr->measurement_system), 2 );
	convertBinary( &(segy_bin_hdr->impulse_signal_polarity), 2 );
	convertBinary( &(segy_bin_hdr->vibratory_polarity_code), 2 );
}

void SegyReader::swapSegyTraceHeader( SegyTraceHeader* segy_trace_hdr ) const{
	convertBinary( &(segy_trace_hdr->trace_sequence_number_within_line), 4 );
	convertBinary( &(segy_trace_hdr->trace_sequence_number_within_reel), 4 );
	convertBinary( &(segy_trace_hdr->original_field_record_number), 4 );
	convertBinary( &(segy_trace_hdr->trace_sequence_number_within_original_field_record), 4 );
	convertBinary( &(segy_trace_hdr->energy_source_point_number), 4 );
	convertBinary( &(segy_trace_hdr->cdp_ensemble_number), 4 );
	convertBinary( &(segy_trace_hdr->trace_sequence_number_within_cdp_ensemble), 4 );

	convertBinary( &(segy_trace_hdr->trace_identification_code), 2 );
	convertBinary( &(segy_trace_hdr->number_of_vertically_summed_traces_yielding_this_trace), 2 );
	convertBinary( &(segy_trace_hdr->number_of_horizontally_stacked_traced_yielding_this_trace), 2 );
	convertBinary( &(segy_trace_hdr->data_use), 2 );

	convertBinary( &(segy_trace_hdr->distance_from_source_point_to_receiver_group), 4 );
	convertBinary( &(segy_trace_hdr->receiver_group_elevation), 4 );
	convertBinary( &(segy_trace_hdr->surface_elevation_at_source), 4 );
	convertBinary( &(segy_trace_hdr->source_depth_below_surface), 4 );
	convertBinary( &(segy_trace_hdr->datum_elevation_at_receiver_group), 4 );
	convertBinary( &(segy_trace_hdr->datum_elevation_at_source), 4 );
	convertBinary( &(segy_trace_hdr->water_depth_at_source), 4 );
	convertBinary( &(segy_trace_hdr->water_depth_at_receiver_group), 4 );

	convertBinary( &(segy_trace_hdr->scalar_for_elevations_and_depths), 2 );
	convertBinary( &(segy_trace_hdr->scalar_for_coordinates), 2 );

	convertBinary( &(segy_trace_hdr->x_source_coordinate), 4 );
	convertBinary( &(segy_trace_hdr->y_source_coordinate), 4 );
	convertBinary( &(segy_trace_hdr->x_receiver_group_coordinate), 4 );
	convertBinary( &(segy_trace_hdr->y_receiver_group_coordinate), 4 );

	convertBinary( &(segy_trace_hdr->coordinate_units), 2 );
	convertBinary( &(segy_trace_hdr->weathering_velocity), 2 );
	convertBinary( &(segy_trace_hdr->subweathering_velocity), 2 );
	convertBinary( &(segy_trace_hdr->uphole_time_at_source), 2 );
	convertBinary( &(segy_trace_hdr->uphole_time_at_group), 2 );
	convertBinary( &(segy_trace_hdr->source_static_correction), 2 );
	convertBinary( &(segy_trace_hdr->group_static_correction), 2 );
	convertBinary( &(segy_trace_hdr->total_static_applied), 2 );
	convertBinary( &(segy_trace_hdr->lag_time_a), 2 );
	convertBinary( &(segy_trace_hdr->lag_time_b), 2 );
	convertBinary( &(segy_trace_hdr->delay_according_time), 2 );
	convertBinary( &(segy_trace_hdr->mute_time_start), 2 );
	convertBinary( &(segy_trace_hdr->mute_time_end), 2 );
	convertBinary( &(segy_trace_hdr->samples_in_this_trace), 2 );
	convertBinary( &(segy_trace_hdr->sample_intervall), 2 );
	convertBinary( &(segy_trace_hdr->gain_type_instruments), 2 );
	convertBinary( &(segy_trace_hdr->igc), 2 );
	convertBinary( &(segy_trace_hdr->igi), 2 );
	convertBinary( &(segy_trace_hdr->corr), 2 );
	convertBinary( &(segy_trace_hdr->sfs), 2 );
	convertBinary( &(segy_trace_hdr->sfe), 2 );
	convertBinary( &(segy_trace_hdr->slen), 2 );
	convertBinary( &(segy_trace_hdr->styp), 2 );
	convertBinary( &(segy_trace_hdr->stas), 2 );
	convertBinary( &(segy_trace_hdr->stae), 2 );
	convertBinary( &(segy_trace_hdr->tatyp), 2 );
	convertBinary( &(segy_trace_hdr->afilf), 2 );
	convertBinary( &(segy_trace_hdr->afils), 2 );
	convertBinary( &(segy_trace_hdr->nofilf), 2 );
	convertBinary( &(segy_trace_hdr->nofils), 2 );
	convertBinary( &(segy_trace_hdr->lcf), 2 );
	convertBinary( &(segy_trace_hdr->hcf), 2 );
	convertBinary( &(segy_trace_hdr->lcs), 2 );
	convertBinary( &(segy_trace_hdr->hcs), 2 );
	convertBinary( &(segy_trace_hdr->year), 2 );
	convertBinary( &(segy_trace_hdr->day), 2 );
	convertBinary( &(segy_trace_hdr->hour), 2 );
	convertBinary( &(segy_trace_hdr->minute), 2 );
	convertBinary( &(segy_trace_hdr->sec), 2 );
	convertBinary( &(segy_trace_hdr->timbas), 2 );
	convertBinary( &(segy_trace_hdr->trwf), 2 );
	convertBinary( &(segy_trace_hdr->grnors), 2 );
	convertBinary( &(segy_trace_hdr->grnofr), 2 );
	convertBinary( &(segy_trace_hdr->grnlof), 2 );
	convertBinary( &(segy_trace_hdr->gaps), 2 );
	convertBinary( &(segy_trace_hdr->otrav), 2 );
}

bool SegyReader::convertBinary( void* data, size_t size ) const{
	switch (size){
	case 2:
		swapByte2( (int_16*)data );
		return true;
		break;
	case 4:
		swapByte4( (int_32*) data );
		return true;
		break;
	default:
		return false;
	}
}

void SegyReader::destroy(){
	delete this;
}

SegyReader::SegyReader( const string _file_name ) : 
segy_ebcdic_hdr( nullptr ), segy_bin_hdr( nullptr ), segy_trace_hdr( nullptr ){
	if ( nullptr == (segy_file = fopen( _file_name.c_str(), "rb" )) ){
		fprintf( stderr, "ReadSegy: Cannot open segy file - %s\n", _file_name.c_str() );
	} else {
		file_name = _file_name;
		segy_bin_hdr = getSegyBinaryHeader();
		samples = _getSamples();
		traces = _getTraces();
		data_format = _getDataFormat();
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

const SegyBinaryHeader* SegyReader::getSegyBinaryHeader() const{
	SegyBinaryHeader *segy_bin_hdr = new SegyBinaryHeader();
	if ( 0 != fseek( segy_file, 3600, SEEK_SET ) ){
		if (0 != fread( segy_bin_hdr, BIN_HEADER_SIZE, 1, segy_file )){
			swapSegyBinaryHeader( segy_bin_hdr );
			return segy_bin_hdr;
		} else {
			fprintf( stderr, "getSegyBinaryHeader(): Read segy file error.\n" );
			return nullptr;
		}
	} else {
		fprintf( stderr, "getSegyBinaryHeader(): Seek segy file error.\n" );
		return nullptr;
	}
	return nullptr;
}

size_t SegyReader::_getSamples() const{
	const SegyBinaryHeader *segy_bin_hdr = getSegyBinaryHeader();
	if ( segy_bin_hdr ){
		size_t samples = segy_bin_hdr->samples_per_trace;
		delete segy_bin_hdr;
		return samples;
	} else {
		delete segy_bin_hdr;
		return 0;
	}
}

size_t SegyReader::_getTraces() const{
	const size_t samples = _getSamples();
	const size_t data_format = _getDataFormat();

	//set file pointer point to the last trace header
	if ( 0 != fseek( segy_file, samples * data_bytes[data_format] + 240, SEEK_END ) ){

		SegyTraceHeader *segy_trace_hdr = new SegyTraceHeader();

		if (0 != fread( segy_trace_hdr, TEXT_HEADER_SIZE, 1, segy_file )){
			swapSegyTraceHeader( segy_trace_hdr );
			size_t result = segy_trace_hdr->trace_sequence_number_within_cdp_ensemble;
			delete segy_trace_hdr;
			return result;
		} else {
			fprintf( stderr, "_getTraces(): Read segy file error.\n" );
			delete segy_trace_hdr;
			return 0;
		}
	}
}

size_t SegyReader::_getDataFormat() const{
	const SegyBinaryHeader *segy_bin_hdr = getSegyBinaryHeader( );
	if (segy_bin_hdr){
		size_t data_format = segy_bin_hdr->data_sample_format_code;
		delete segy_bin_hdr;
		return data_format;
	} else {
		delete segy_bin_hdr;
		return 0;
	}
}



size_t SegyReader::getSamples() const{
	return samples;
}
size_t SegyReader::getTraces( ) const{
	return traces;
}

const SegyTraceHeader *SegyReader::getSegyTraceHeader( const size_t trace_num ){
	if ( trace_num <= traces ){
		SegyTraceHeader* segy_trace_hdr = new SegyTraceHeader();

	} else {
		fprintf( stderr, "getSegyTraceHeader(): Out of traces.\n" );
		return nullptr;
	}
	

}