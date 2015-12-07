#ifndef __SEGYREADER_H__
#define __SEGYREADER_H__

#include <iostream>
#include <string>

using namespace std;

//parameter: 40 * 80, EBCDIC charater set
#define TEXT_HEADER_SIZE 3200
//binary header
#define BIN_HEADER_SIZE 400

//trace header
#define TRACE_HEADER_SIZE 240

#ifndef UINT_8
#define UINT_8
typedef unsigned char uint_8; //should be one byte
#endif

#ifndef UINT_16
#define UINT_16
typedef short int_16; //should be 2 bytes
#endif

#ifndef UINT_32
#define UINT_32
typedef unsigned long int_32; //should be 4 bytes
#endif

typedef struct SegyTextHeader{
	uint_8 text_header[TEXT_HEADER_SIZE];
} SegyTextHeader;

// binary header, 400 bytes total
typedef struct SegyBinaryHeader{					// Bytes		Length		Description									Translation
	int_32 job_id_number;							// 3201-3204	4			Job identification number					��ҵ��ʶ��
	int_32 line_number;								// 3205-3208	4			Line number									���ߺţ�ÿ��ֻ�ܼ�һ���ߣ�
	int_32 reel_number;								// 3209-3212	4			Reel number									���
	int_16 traces_per_record;						// 3213-3214	2			data traces per record						ÿ����¼�����ݵ����������յ��ͳ������
	int_16 aux_traces_per_record;					// 3215-3216	2			aux traces per record						ÿ����¼�ĸ�������
	int_16 sample_data_interval_ms;					// 3217-3218	2			sample interval(microseconds) for reel		�������(��s)
	int_16 original_data_interval_ms;				// 3219-3220	2			sample interval(microseconds) for field		��΢������ԭʼҰ���¼�Ĳ������
	int_16 samples_per_trace;						// 3221-3222	2			number samples per data trace for reel		������ÿ�����ݵ��Ĳ�������
	int_16 original_samples_per_trace;				// 3223-3224	2			number samples per data trace for field		Ұ��ԭʼ��¼ÿ�����ݵ��Ĳ�������
	int_16 data_sample_format_code;					// 3225-3226	2			data sample format code						���ݲ�����ʽ�룺1-���㣨4�ֽڣ���2-���㣨4�ֽڣ���3-���㣨2�ֽڣ���4-����������Ķ��㣨4�ֽڣ�,������ÿ��������ͬ�����ֽ���
	int_16 CDP_fold;								// 3227-3228	2			CDP fold									CDP���Ǵ���
	int_16 trace_sorting_code;						// 3229-3230	2			trace sorting code							����ѡ�룺1-ԭʼ��¼���ڼ�����2-CDP������3-���θ������棻4-ˮƽ����
	int_16 vertical_sum_code;						// 3231-3232	2			vertical sum code							��ֱ���Ӵ��룺1-δ���ӣ�2-���ε��ӣ�������n-n�ε���
	int_16 sweep_frequency_start_hz;				// 3233-3234	2			sweep frequently at start					��ʼɨ��Ƶ�ʣ�Hz��
	int_16 sweep_frequency_end_hz;					// 3235-3236	2			sweep frequently at end						����ɨ��Ƶ�ʣ�Hz��
	int_16 sweep_length_ms;							// 3237-3238	2			sweep lenth (milliseconds)_					ɨ�賤�ȣ�ms��
	int_16 sweep_type_code;							// 3239-3240	2			sweep type code								ɨ�����ʹ��룺1-���ԣ�2-�����ߣ�3-ָ����4-����
	int_16 trace_number_of_sweep_channel;			// 3241-3242	2			trace number of sweep chanel				ɨ��ͨ���ĵ���
	int_16 sweep_trace_taper_length_start_ms;		// 3243-3244	2			sweep trace taper length at start (ms)		�����б�£�Ϊ��ʼʱ��ɨ��б�³��ȣ�ms����б�������ʱ���㣩
	int_16 sweep_trace_taper_length_end_ms;			// 3245-3246	2			sweep trace taper length at end (ms)		����ʱ��б�³��ȣ�б�����Ϊɨ�賤�ȼ�β����б�³���
	int_16 taper_type_code;							// 3247-3248	2			taper type									б�����ͣ�1-���Σ�2-COS^2��3-����
	int_16 correlated_data_traces_flag;				// 3249-3250	2			corellated data traces						������ݵ����룺1-δ��أ�2-���
	int_16 binary_gain_recovered_flag;				// 3251-3252	2			binary gain recoverd						����������ָ���1-�ָ���2-δ�ָ�
	int_16 amplitude_recovery_method_code;			// 3253-3254	2			amplitude recovery method					����ָ���ʽ��1-δ�ָ���2-������ɢ��3-AGC��4-����
	int_16 measurement_system;						// 3255-3256	2			measuriment system (1-m/2-feet)				���ȵ�λ��1-�ף�2-Ӣ��
	int_16 impulse_signal_polarity;					// 3257-3258	2			impulse signal								�����źż��ԣ�1-�Ŵ��ϵĸ�ֵΪѹ�����ӻ�첨��������2-�Ŵ��ϵ���ֵΪѹ�����ӻ�첨������
	int_16 vibratory_polarity_code;					// 3259-3260	2			vibratory polarity code						�ɿ���Դ���Դ���
	uint_8 buffer[340];								// 3261-3600	340			reserved									12 bytes + 12 bytes + 36 bytes + 340 buffer bytes = REEL_HDR_SIZE  // 3261-3600   340  Ԥ�����û��Զ���
} SegyBinaryHeader;


typedef struct SegyTraceHeader{
	int_32 trace_sequence_number_within_line;								// 1-4     4   һ�����ߵĵ���ţ����һ�����ж�������������������ӵ�
	int_32 trace_sequence_number_within_reel;								// 5-8     4   ������ĵ���š�ÿ��������1��ʼ
	int_32 original_field_record_number;									// 9-12    4*  ԭʼҰ���¼��(�ں�)
	int_32 trace_sequence_number_within_original_field_record;				// 13-16   4   ԭʼҰ���¼�ĵ���
	int_32 energy_source_point_number;										// 17-20   4   ��Դ���
	int_32 cdp_ensemble_number;												// 21-24   4*  CDP��(��CMP, CRP)
	int_32 trace_sequence_number_within_cdp_ensemble;						// 25-28   4*  ��CDP�����еĵ��š�ÿ����������ʼ����Ϊ1

	int_16 trace_identification_code;										// 29-30   2   ��ʶ��
	int_16 number_of_vertically_summed_traces_yielding_this_trace;			// 31-32   2   ��ֱ�����֣������ɶ��ٵ����Ӷ���
	int_16 number_of_horizontally_stacked_traced_yielding_this_trace;		// 33-34   2   CDP���Ǵ���
	int_16 data_use;														// 35-36   2   �������ʣ�1=�ɹ���2=ʵ��

	int_32 distance_from_source_point_to_receiver_group;					// 37-40   4*  �ڵ㵽�첨����루��ֵ��ʾ����߷��ڷ����෴��
	int_32 receiver_group_elevation;										// 41-44   4   �첨���ĸ߶ȣ��ں�ƽ������Ϊ��������Ϊ��
	int_32 surface_elevation_at_source;										// 45-48   4   ��Դ��ˮƽ�߶�
	int_32 source_depth_below_surface;										// 49-52   4   ��Դ��ˮƽ�µ���ȣ���һ��������
	int_32 datum_elevation_at_receiver_group;								// 53-56   4   �첨���ĺ���
	int_32 datum_elevation_at_source;										// 57-60   4   ��Դ�ĺ���
	int_32 water_depth_at_source;											// 61-64   4   ��Դ��ˮ��
	int_32 water_depth_at_receiver_group;									// 65-68   4   �첨����ˮ��

	int_16 scalar_for_elevations_and_depths;								// 69-70   2   �������ӣ����ֽ�41~68�ĸ̺߳����ʹ�ñ������Ӻ������ֵ����������Ϊ1����10����100����1000���10000�����Ϊ��������
	int_16 scalar_for_coordinates;											// 71-72   2   �������ӣ����ֽ�73��88��199��206�ĸ̺߳����ʹ�ñ������Ӻ������ֵ����������Ϊ1����10����100����1000���10000�����Ϊ�������ϱ������ӣ����Ϊ�������Ա������ӡ�
	
	int_32 x_source_coordinate;												// 73-76   4   ��Դ������-X
	int_32 y_source_coordinate;												// 77-80   4   ��Դ������-Y
	int_32 x_receiver_group_coordinate;										// 81-84   4   �첨��������-X
	int_32 y_receiver_group_coordinate;										// 85-88   4   �첨��������-Y

	int_16 coordinate_units;												// 89-90   2   ���굥λ��1=���ȣ��׻�Ӣ�ߣ� 2=���ȵ���
	int_16 weathering_velocity;												// 91-92   2   �绯���ٶ�
	int_16 subweathering_velocity;											// 93-94   2   ���ٲ��ٶ�
	int_16 uphole_time_at_source;											// 95-96   2   ����Դ���ľ���ʱ��
	int_16 uphole_time_at_group;											// 97-98   2   �ڼ첨�㴦�ľ���ʱ��
	int_16 source_static_correction;										// 99-100  2   �ڵ㾲У��
	int_16 group_static_correction;											// 101-102 2   �첨����У��
	int_16 total_static_applied;											// 103-104 2   Ӧ�õ��ܾ�У���������δʹ�ã���Ϊ�㣩
	int_16 lag_time_a;														// 105-106 2   �ӳ�ʱ��A��ms������¼�ĵ�һ�������ʱ���ź�֮���ʱ�䡣240�ֽڵ���ʶͷ��ʱ���ź�֮���ʱ�䡣���Ϊ����ʱ���źų����ڵ���ʶͷ����֮�����Ϊ����ʱ���źų����ڵ���ʶͷ����֮ǰ
	int_16 lag_time_b;														// 107-108 2   �ӳ�ʱ��B��ms����ʱ���źź���Դ��ʱ��֮���ʱ��
	int_16 delay_according_time;											// 109-110 2   �ӳټ�¼ʱ�䣨ms������Դ��ʱ��Ϳ�ʼ��¼����ʱ��֮���ʱ�䣨��ˮʱʹ�ã�
	int_16 mute_time_start;													// 111-112 2   ��ʼ�г�ʱ��  //brute_time_start
	int_16 mute_time_end;													// 113-114 2   �����г�ʱ��
	int_16 samples_in_this_trace;											// 115-116 2*  ������������
	int_16 sample_intervall;												// 117-118 2*  �������
	int_16 gain_type_instruments;											// 119-120 2   Ұ���������������ͣ�1=�̶� 2=������ 3=������ 4=��ѡ������
	int_16 igc;																// 121-122 2   �������泣��
	int_16 igi;																// 123-124 2   �������ں����������
	int_16 corr;															// 125-126 2   ����ԣ�1=û�� 2=��
	int_16 sfs;																// 127-128 2   �ڿ�ʼʱ��ɨ��Ƶ��
	int_16 sfe;																// 129-130 2   �ڽ���ʱ��ɨ��Ƶ��
	int_16 slen;															// 131-132 2   ɨ�賤���Ժ���Ϊ��λ
	int_16 styp;															// 133-134 2   ɨ������  1 ���� 2�������� 3ָ����
	int_16 stas;															// 135-136 2   �ڿ�ʼʱ��ɨ�����
	int_16 stae;															// 137-138 2   �ڽ���ʱ��ɨ�����
	int_16 tatyp;															// 139-140 2   ɨ������  1 ���� 2�������� 3ָ����
	int_16 afilf;															// 141-142 2   Alias�˲���Ƶ�ʣ����ʹ����
	int_16 afils;															// 143-144 2   Alias�˲���б��
	int_16 nofilf;															// 145-146 2   �ݲ��˲���Ƶ��
	int_16 nofils;															// 147-148 2   �ݲ��˲���б��
	int_16 lcf;																// 149-150 2   ����Ƶ
	int_16 hcf;																// 151-152 2   ����Ƶ
	int_16 lcs;																// 153-154 2   ����б
	int_16 hcs;																// 155-156 2   ����б��
	int_16 year;															// 157-158 2   ��¼����
	int_16 day;																// 159-160 2   ����ĵڼ���
	int_16 hour;															// 161-162 2   ����ĵڼ�Сʱ
	int_16 minute;															// 163-164 2   ���Сʱ�ĵڼ���
	int_16 sec;																// 165-166 2   ��ֵĵڼ���
	int_16 timbas;															// 167-168 2	  ʱ���� I = local.	2 = GMT. 3 = other.
	int_16 trwf;															// 169-170 2   trace weighting factor
	int_16 grnors;															// 171-172 2   geophone group number of roll switch position one
	int_16 grnofr;															// 173-174 2   geophone group number of trace one within original field record
	int_16 grnlof;															// 175-176 2   geophone group number of last trace within original field record
	int_16 gaps;															// 177-178 2   gap size (total number of groups dropped)
	int_16 otrav;															// 179-180 2   overtravel taper code: 1 = down (or behind) 2 = up (or ahead)
	uint_8 user_define[60];													// 181-240 60  Ԥ�����û��Զ���

	//uint8_t buffer[120];   //old,�滻Ϊ�������ϸ�ֶ�
} SegyTraceHeader;

// singleton pattern
class SegyReader{
private:
	static SegyReader			*instance;
	string						file_name;
	size_t						traces;
	size_t						samples;
	size_t						data_format;
	FILE						*segy_file;

	SegyTextHeader				*segy_ebcdic_hdr;
	const SegyBinaryHeader		*segy_bin_hdr;
	//SegyTraceHeader				*segy_trace_hdr;

private:
	SegyReader(){}
	SegyReader( const string _file_name );
	~SegyReader(){}

public:
	static SegyReader			*getInstance( const string file_name );
	void						destroy();
	const SegyBinaryHeader		*getSegyBinaryHeader() const;
	const SegyTraceHeader		*getSegyTraceHeader( const size_t trace_num );
	const float					getSegyData( const size_t trace_num, const size_t sample_num );
	const size_t				getTracesNum() const;
	const size_t				getTraceSamplesNum() const;
	size_t						getTraces() const;
	size_t						getSamples() const;
	size_t						getDataFormat() const;
	const float					getSpecificData( const size_t trace_num, const size_t sample_num ) const;
	const float*				getTraceData( const size_t trace_num ) const;

private:
	bool						convertBinary( void* data, size_t size, size_t count = 1 ) const;
	void						swapSegyBinaryHeader( SegyBinaryHeader* segy_bin_hdr ) const;
	void						swapSegyTraceHeader( SegyTraceHeader* segy_trace_hdr ) const;
	size_t						_getSamples() const;
	size_t						_getTraces() const;
	size_t						_getDataFormat() const;
};
#endif