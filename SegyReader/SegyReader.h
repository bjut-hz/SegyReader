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
	int_32 job_id_number;							// 3201-3204	4			Job identification number					作业标识号
	int_32 line_number;								// 3205-3208	4			Line number									测线号（每卷只能记一条线）
	int_32 reel_number;								// 3209-3212	4			Reel number									卷号
	int_16 traces_per_record;						// 3213-3214	2			data traces per record						每个记录的数据道数（包括空道和冲零道）
	int_16 aux_traces_per_record;					// 3215-3216	2			aux traces per record						每个记录的辅助道数
	int_16 sample_data_interval_ms;					// 3217-3218	2			sample interval(microseconds) for reel		采样间隔(μs)
	int_16 original_data_interval_ms;				// 3219-3220	2			sample interval(microseconds) for field		以微秒计算的原始野外记录的采样间隔
	int_16 samples_per_trace;						// 3221-3222	2			number samples per data trace for reel		本卷上每个数据道的采样个数
	int_16 original_samples_per_trace;				// 3223-3224	2			number samples per data trace for field		野外原始记录每个数据道的采样个数
	int_16 data_sample_format_code;					// 3225-3226	2			data sample format code						数据采样格式码：1-浮点（4字节）；2-定点（4字节）；3-定点（2字节）；4-带有增益码的定点（4字节）,辅助道每个样点用同样的字节数
	int_16 CDP_fold;								// 3227-3228	2			CDP fold									CDP覆盖次数
	int_16 trace_sorting_code;						// 3229-3230	2			trace sorting code							道分选码：1-原始记录（炮集）；2-CDP道集；3-单次覆盖剖面；4-水平迭加
	int_16 vertical_sum_code;						// 3231-3232	2			vertical sum code							垂直迭加代码：1-未迭加；2-二次迭加；……；n-n次迭加
	int_16 sweep_frequency_start_hz;				// 3233-3234	2			sweep frequently at start					起始扫描频率（Hz）
	int_16 sweep_frequency_end_hz;					// 3235-3236	2			sweep frequently at end						终了扫描频率（Hz）
	int_16 sweep_length_ms;							// 3237-3238	2			sweep lenth (milliseconds)_					扫描长度（ms）
	int_16 sweep_type_code;							// 3239-3240	2			sweep type code								扫描类型代码：1-线性；2-抛物线；3-指数；4-其他
	int_16 trace_number_of_sweep_channel;			// 3241-3242	2			trace number of sweep chanel				扫描通道的道号
	int_16 sweep_trace_taper_length_start_ms;		// 3243-3244	2			sweep trace taper length at start (ms)		如果有斜坡，为起始时的扫描斜坡长度（ms）（斜坡起点在时间零）
	int_16 sweep_trace_taper_length_end_ms;			// 3245-3246	2			sweep trace taper length at end (ms)		结束时的斜坡长度（斜坡起点为扫描长度减尾部的斜坡长）
	int_16 taper_type_code;							// 3247-3248	2			taper type									斜坡类型：1-线形；2-COS^2；3-其他
	int_16 correlated_data_traces_flag;				// 3249-3250	2			corellated data traces						相关数据道代码：1-未相关；2-相关
	int_16 binary_gain_recovered_flag;				// 3251-3252	2			binary gain recoverd						二进制增益恢复：1-恢复；2-未恢复
	int_16 amplitude_recovery_method_code;			// 3253-3254	2			amplitude recovery method					振幅恢复方式：1-未恢复；2-球面扩散；3-AGC；4-其他
	int_16 measurement_system;						// 3255-3256	2			measuriment system (1-m/2-feet)				长度单位：1-米；2-英尺
	int_16 impulse_signal_polarity;					// 3257-3258	2			impulse signal								脉冲信号极性：1-磁带上的负值为压力增加或检波器上跳；2-磁带上的正值为压力增加或检波器上跳
	int_16 vibratory_polarity_code;					// 3259-3260	2			vibratory polarity code						可控震源极性代码
	uint_8 buffer[340];								// 3261-3600	340			reserved									12 bytes + 12 bytes + 36 bytes + 340 buffer bytes = REEL_HDR_SIZE  // 3261-3600   340  预留，用户自定义
} SegyBinaryHeader;


typedef struct SegyTraceHeader{
	int_32 trace_sequence_number_within_line;								// 1-4     4   一条测线的道序号，如果一条线有多卷带，道序号是连续增加的
	int_32 trace_sequence_number_within_reel;								// 5-8     4   本卷带的道序号。每卷带从序号1开始
	int_32 original_field_record_number;									// 9-12    4*  原始野外记录号(炮号)
	int_32 trace_sequence_number_within_original_field_record;				// 13-16   4   原始野外记录的道号
	int_32 energy_source_point_number;										// 17-20   4   震源点号
	int_32 cdp_ensemble_number;												// 21-24   4*  CDP号(或CMP, CRP)
	int_32 trace_sequence_number_within_cdp_ensemble;						// 25-28   4*  在CDP道集中的道号。每个道集的起始道号为1

	int_16 trace_identification_code;										// 29-30   2   道识别
	int_16 number_of_vertically_summed_traces_yielding_this_trace;			// 31-32   2   垂直叠加字，本道由多少道叠加而成
	int_16 number_of_horizontally_stacked_traced_yielding_this_trace;		// 33-34   2   CDP覆盖次数
	int_16 data_use;														// 35-36   2   数据性质，1=成果，2=实验

	int_32 distance_from_source_point_to_receiver_group;					// 37-40   4*  炮点到检波点距离（负值表示与测线放炮方向相反）
	int_32 receiver_group_elevation;										// 41-44   4   检波器的高度；在海平面以上为正，以下为负
	int_32 surface_elevation_at_source;										// 45-48   4   震源的水平高度
	int_32 source_depth_below_surface;										// 49-52   4   震源在水平下的深度（是一个正数）
	int_32 datum_elevation_at_receiver_group;								// 53-56   4   检波器的海拔
	int_32 datum_elevation_at_source;										// 57-60   4   震源的海拔
	int_32 water_depth_at_source;											// 61-64   4   震源的水深
	int_32 water_depth_at_receiver_group;									// 65-68   4   检波器的水深

	int_16 scalar_for_elevations_and_depths;								// 69-70   2   比例因子，对字节41~68的高程和深度使用比例因子后求得真值。比例因子为1、±10、±100、±1000或±10000，如果为正，乘上
	int_16 scalar_for_coordinates;											// 71-72   2   比例因子，对字节73～88、199～206的高程和深度使用比例因子后求得真值。比例因子为1、±10、±100、±1000或±10000，如果为正，乘上比例因子；如果为负，除以比例因子。
	
	int_32 x_source_coordinate;												// 73-76   4   震源的坐标-X
	int_32 y_source_coordinate;												// 77-80   4   震源的坐标-Y
	int_32 x_receiver_group_coordinate;										// 81-84   4   检波器的坐标-X
	int_32 y_receiver_group_coordinate;										// 85-88   4   检波器的坐标-Y

	int_16 coordinate_units;												// 89-90   2   坐标单位：1=长度（米或英尺） 2=弧度的秒
	int_16 weathering_velocity;												// 91-92   2   风化层速度
	int_16 subweathering_velocity;											// 93-94   2   降速层速度
	int_16 uphole_time_at_source;											// 95-96   2   在震源处的井口时间
	int_16 uphole_time_at_group;											// 97-98   2   在检波点处的井口时间
	int_16 source_static_correction;										// 99-100  2   炮点静校正
	int_16 group_static_correction;											// 101-102 2   检波器静校正
	int_16 total_static_applied;											// 103-104 2   应用的总静校正量（如果未使用，则为零）
	int_16 lag_time_a;														// 105-106 2   延迟时间A（ms）。记录的第一个样点和时间信号之间的时间。240字节道标识头与时间信号之间的时间。如果为正，时间信号出现在道标识头结束之后；如果为负，时间信号出现在道标识头结束之前
	int_16 lag_time_b;														// 107-108 2   延迟时间B（ms）。时间信号和震源起爆时间之间的时间
	int_16 delay_according_time;											// 109-110 2   延迟记录时间（ms）。震源起爆时间和开始记录采样时间之间的时间（深水时使用）
	int_16 mute_time_start;													// 111-112 2   起始切除时间  //brute_time_start
	int_16 mute_time_end;													// 113-114 2   终了切除时间
	int_16 samples_in_this_trace;											// 115-116 2*  本道采样点数
	int_16 sample_intervall;												// 117-118 2*  采样间隔
	int_16 gain_type_instruments;											// 119-120 2   野外仪器的增益类型：1=固定 2=二进制 3=浮点型 4=可选的其它
	int_16 igc;																// 121-122 2   仪器增益常数
	int_16 igi;																// 123-124 2   仪器早期和最初的增益
	int_16 corr;															// 125-126 2   相关性：1=没有 2=有
	int_16 sfs;																// 127-128 2   在开始时的扫描频率
	int_16 sfe;																// 129-130 2   在结束时的扫描频率
	int_16 slen;															// 131-132 2   扫描长度以毫秒为单位
	int_16 styp;															// 133-134 2   扫描类型  1 线性 2抛物线性 3指数型
	int_16 stas;															// 135-136 2   在开始时的扫描道长
	int_16 stae;															// 137-138 2   在结束时的扫描道长
	int_16 tatyp;															// 139-140 2   扫描类型  1 线性 2抛物线性 3指数型
	int_16 afilf;															// 141-142 2   Alias滤波器频率，如果使用了
	int_16 afils;															// 143-144 2   Alias滤波器斜率
	int_16 nofilf;															// 145-146 2   陷波滤波器频率
	int_16 nofils;															// 147-148 2   陷波滤波器斜率
	int_16 lcf;																// 149-150 2   低切频
	int_16 hcf;																// 151-152 2   高切频
	int_16 lcs;																// 153-154 2   低切斜
	int_16 hcs;																// 155-156 2   高切斜率
	int_16 year;															// 157-158 2   记录的年
	int_16 day;																// 159-160 2   这年的第几天
	int_16 hour;															// 161-162 2   这天的第几小时
	int_16 minute;															// 163-164 2   这个小时的第几分
	int_16 sec;																// 165-166 2   这分的第几秒
	int_16 timbas;															// 167-168 2	  时间码 I = local.	2 = GMT. 3 = other.
	int_16 trwf;															// 169-170 2   trace weighting factor
	int_16 grnors;															// 171-172 2   geophone group number of roll switch position one
	int_16 grnofr;															// 173-174 2   geophone group number of trace one within original field record
	int_16 grnlof;															// 175-176 2   geophone group number of last trace within original field record
	int_16 gaps;															// 177-178 2   gap size (total number of groups dropped)
	int_16 otrav;															// 179-180 2   overtravel taper code: 1 = down (or behind) 2 = up (or ahead)
	uint_8 user_define[60];													// 181-240 60  预留，用户自定义

	//uint8_t buffer[120];   //old,替换为上面更详细字段
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