// ideliapi.h
// $Id: ideliapi.h 90 2004-08-28 21:01:13Z florian $
//
// DeliPlayer V2.5 player plugin API
// Copyright 2004 by Florian Vorberger and Peter Kunath
// http://www.deliplayer.com
//
// tabsize=3
// ----------------------------------------------------------------------------
#ifndef IDELIAPI_H
#define IDELIAPI_H

#include <windows.h>	//<winnt.h>	// <rpcndr.h>

#ifndef LPVOID
typedef void* LPVOID;
#endif

#ifndef PPVOID
typedef LPVOID* PPVOID;
#endif

#define DELI_TRUE		(1)
#define DELI_FALSE	(0)

#define DELI_DLLExport __declspec( dllexport )
#define DELI_DLLExportC extern "C" DELI_DLLExport

#define DELI_IID extern "C" const GUID __declspec(selectany)

DELI_IID IID_IDeliPluginContainer	= { 0x47fce110, 0x7617, 0x4679, { 0x9b, 0x99, 0x4e, 0x44, 0xac, 0x1c, 0xb1, 0xc0 }};
DELI_IID IID_IDeliPlugin				= { 0x47fce111, 0x7617, 0x4679, { 0x9b, 0x99, 0x4e, 0x44, 0xac, 0x1c, 0xb1, 0xc0 }};
DELI_IID IID_IDeliPluginPlayer		= { 0x47fce120, 0x7617, 0x4679, { 0x9b, 0x99, 0x4e, 0x44, 0xac, 0x1c, 0xb1, 0xc0 }};
DELI_IID IID_IDeliSocketPlayer		= { 0x47fce130, 0x7617, 0x4679, { 0x9b, 0x99, 0x4e, 0x44, 0xac, 0x1c, 0xb1, 0xc0 }};

#define DELI_RESULT_OK												( 0)
#define DELI_RESULT_ERROR_FAILED									(-1)
#define DELI_RESULT_ERROR_NOTIMPLEMENTED						(-1)
#define DELI_RESULT_ERROR_NOINTERFACE							(-2)
#define DELI_RESULT_ERROR_FORMATNOTSTANDARD					(-3)
#define DELI_RESULT_ERROR_FORMATCORRUPT						(-4)
#define DELI_RESULT_ERROR_FILENOTFOUND							(-5)
#define DELI_RESULT_ERROR_REPLAY_ALREADYINITIALIZED		(-6)
#define DELI_RESULT_ERROR_REPLAY_NOTINITIALIZED				(-7)
#define DELI_RESULT_ERROR_REPLAY_CHANNELINDEXOUTOFRANGE	(-8)
#define DELI_RESULT_ERROR_REPLAY_NUMCHANNELSOUTOFRANGE	(-9)
#define DELI_RESULT_ERROR_NAMEDVARIABLE_UNKNOWNID			(-10)
#define DELI_RESULT_ERROR_NAMEDVARIABLE_INVALIDVALUE		(-11)

typedef char				DELIBool;
typedef void*				DELIFile;
typedef int					DELIResult;
typedef void*				DELIFile;
typedef int					DELITagId;
typedef unsigned int		DELITagValue;
typedef DELITagValue*	PDELITagValue;
typedef unsigned int		DELIVersion;

typedef struct
{
	DELITagId		id;
	DELITagValue	value;
} DeliTag;

#define DELI_TAGARRAY_END	(0)

typedef struct
{
	const char* name;
	int			type;			// DELI_VarType_*
	int			varid;		// anything except 0
} DeliNamedVariable;

#ifdef __cplusplus
union DeliNamedVariableValue
{
	int	int_value;			// use with DELI_VarType_Int and DELI_VarType_Bool
	float	float_value;
	char* cptr_value;

	DeliNamedVariableValue() : cptr_value( NULL ) {}
	DeliNamedVariableValue( DeliNamedVariableValue& other ) : cptr_value( other.cptr_value ) {}
	DeliNamedVariableValue( int	arg_value ) : int_value( arg_value ) {}
	DeliNamedVariableValue( float	arg_value ) : float_value( arg_value ) {}
	DeliNamedVariableValue( char*	arg_value ) : cptr_value( arg_value ) {}
};
#else
typedef union
{
	int	int_value;			// use with DELI_VarType_Int and DELI_VarType_Bool
	float	float_value;
	char* cptr_value;
} DeliNamedVariableValue;
#endif

#define DELI_VARTYPE_Int					(1)
#define DELI_VARTYPE_Bool					(2)
#define DELI_VARTYPE_Float					(3)
#define DELI_VARTYPE_String				(4)
#define DELI_VARTYPE_NotifyingInt		(0x8000|DELI_VARTYPE_Int)
#define DELI_VARTYPE_NotifyingBool		(0x8000|DELI_VARTYPE_Bool)
#define DELI_VARTYPE_NotifyingFloat		(0x8000|DELI_VARTYPE_Float)
#define DELI_VARTYPE_NotifyingString	(0x8000|DELI_VARTYPE_String)

#define DELI_APPLYMODE_AutoOff			(1)
#define DELI_APPLYMODE_AutoOn				(2)
#define DELI_APPLYMODE_ApplyNnow			(3)

DECLARE_INTERFACE_(IDeliPluginContainer, IUnknown)
{
	STDMETHOD_(DELIResult,	Initialize)(THIS							) PURE;
	STDMETHOD_(DeliTag*,		Information)(THIS							) PURE;
	STDMETHOD_(REFIID,		GetIID)(THIS_								int pluginindex ) PURE;
	STDMETHOD_(DELIResult,	CreateInstance)(THIS_					int pluginindex, REFIID, PPVOID ) PURE;
	STDMETHOD_(void,			Cleanup)(THIS								) PURE;
};

DECLARE_INTERFACE_(IDeliPlugin, IUnknown)
{
	STDMETHOD_(DELIResult,	InitPlugin)(THIS_							PVOID socket ) PURE;
	STDMETHOD_(void,			EndPlugin)(THIS							) PURE;

	STDMETHOD_(DeliTag*,		PluginInformation)(THIS					) PURE;

	STDMETHOD_(DELIResult,	SetVariable)(THIS_						int varid, DeliNamedVariableValue value ) PURE;
	STDMETHOD_(DELIResult,	GetVariable)(THIS_						int varid, DeliNamedVariableValue* pValue ) PURE;
	STDMETHOD_(void,			SetVariablesApplyMode)(THIS_			int ) PURE;

	STDMETHOD_(void,			Notify)(THIS_								unsigned int event, unsigned int data1, unsigned int data2 ) PURE;

	STDMETHOD_(HWND,			ConfigDialogOpen)(THIS					) PURE;
	STDMETHOD_(void,			ConfigDialogClose)(THIS					) PURE;
	STDMETHOD_(void,			ConfigDialogApply)(THIS					) PURE;
	STDMETHOD_(void,			ConfigDialogRestore)(THIS				) PURE;
	STDMETHOD_(void,			ConfigDefault)(THIS						) PURE;
	STDMETHOD_(void,			ConfigApply)(THIS_						void* newcfg ) PURE;
	STDMETHOD_(DELIResult,	ConfigSave)(THIS							) PURE;
	STDMETHOD_(DELIResult,	ConfigLoad)(THIS							) PURE;
	STDMETHOD_(DELIBool,		ConfigChanged)(THIS						) PURE;
};

DECLARE_INTERFACE_(IDeliPluginPlayer, IDeliPlugin)
{
	STDMETHOD_(DELIResult,	Check)(THIS_								DELIFile ) PURE;
	STDMETHOD_(DELIResult,	InitModule)(THIS_							DELIFile ) PURE;
	STDMETHOD_(void,			EndModule)(THIS							) PURE;
	STDMETHOD_(DELIResult,	InitSong)(THIS_							int songindex ) PURE;
	STDMETHOD_(void,			EndSong)(THIS								) PURE;
	STDMETHOD_(DELIResult,	StartPlay)(THIS							) PURE;
	STDMETHOD_(void,			StopPlay)(THIS								) PURE;
	STDMETHOD_(DELIResult,	StartSkip)(THIS							) PURE;
	STDMETHOD_(void,			StopSkip)(THIS								) PURE;
	STDMETHOD_(DELIResult,	RenderFrame)(THIS_						) PURE;
	STDMETHOD_(DELIResult,	SetPosition)(THIS_						double ) PURE;

	STDMETHOD_(DeliTag*,		SongInformation)(THIS_					int index ) PURE;
	STDMETHOD_(DeliTag*,		InstrumentInformation)(THIS_			int songindex, int instrumentindex ) PURE;
	STDMETHOD_(DeliTag*,		SampleInformation)(THIS_				int songindex, int sampleindex ) PURE;
	STDMETHOD_(DeliTag*,		MessageInformation)(THIS_ 				int songindex, int messageindex ) PURE;
	STDMETHOD_(DeliTag*,		FormatInformation)(THIS_				int index ) PURE;
	STDMETHOD_(DeliTag*,		FileExtensionInformation)(THIS_		int index ) PURE;	
};

DECLARE_INTERFACE_(IDeliSocket, IUnknown)
{
	STDMETHOD_(DELIResult,	SetVariable)(THIS_						char* pluginname, char* varname, DeliNamedVariableValue data ) PURE;
	STDMETHOD_(DELIResult,	GetVariable)(THIS_						char* pluginname, char* varname, DeliNamedVariableValue* pData ) PURE;
	STDMETHOD_(DELIResult,	GetVariableBuffer)(THIS_				char* pluginname, char* varname, char* pData, int length ) PURE;
	STDMETHOD_(DELIResult,	SetVariableBuffer)(THIS_				char* pluginname, char* varname, char* pData, int length ) PURE;
	STDMETHOD_(void,			NotifyVariableChanged)(THIS_			int varid, DeliNamedVariableValue data ) PURE;
};

// IDeliSocketPlayer::InitReplay() flags
#define DELI_SONGEND_ATENDOFFRAME (1<<0)

DECLARE_INTERFACE_(IDeliSocketPlayer, IDeliSocket)
{
	STDMETHOD_(DELIResult,	InitReplay)(THIS_							unsigned int nChannels, int maxFrequency, int maxVolume, int maxPanning, int periodBase, int timerBase, int timerSpeed, unsigned int flags ) PURE;
	STDMETHOD_(void,			InitChannel)(THIS_						unsigned int iChannel, int numchannels, int resolution, int frequency, int volume, int leftrightpan, int frontbackpan ) PURE;
	STDMETHOD_(void,			SetStateData)(THIS_						void* statedata ) PURE;
	STDMETHOD_(void*,			GetStateData)(THIS						) PURE;
	STDMETHOD_(void,			SetConfigData)(THIS_						void* configdata ) PURE;
	STDMETHOD_(void*,			GetConfigData)(THIS						) PURE;
	STDMETHOD_(int,			GetOutputFrequency)(THIS				) PURE;
	STDMETHOD_(void,			SetTotalFileSize)(THIS_					double nBytes ) PURE;
	STDMETHOD_(void,			SetTotalRealSize)(THIS_					double nBytes ) PURE;
	STDMETHOD_(void,			ReplayInformationChanged)(THIS_		int eWhat, unsigned int value ) PURE;
	STDMETHOD_(void,			ReplaySetSpeed)(THIS_					int speed ) PURE;
	STDMETHOD_(void,			ReplayNotifySongEnd)(THIS_				int songendflags ) PURE;
	STDMETHOD_(void,			ReplaySetSample)(THIS_					int iChannel, int numChannels, int resolution, void* pSamples, unsigned int nSamples ) PURE;
	STDMETHOD_(void,			ReplayStopSample)(THIS_					int iChannel ) PURE;
	STDMETHOD_(void,			ReplaySetRepeat)(THIS_					int iChannel, void* pSamples, unsigned int nSamples, int looptype ) PURE;
	STDMETHOD_(void,			ReplayFinishRepeat)(THIS_				int iChannel ) PURE;
	STDMETHOD_(void,			ReplaySetVolume)(THIS_					int iChannel, int volume ) PURE;
	STDMETHOD_(void,			ReplaySetPan)(THIS_						int iChannel, int leftrighpan, int frontbackpan ) PURE;
	STDMETHOD_(void,			ReplaySetFrequency)(THIS_				int iChannel, int frequency ) PURE;
	STDMETHOD_(void,			ReplayInvertPlayingDirection)(THIS_ int iChannel ) PURE;
	STDMETHOD_(DELIFile,		FileLoad)(THIS_							const char* filename ) PURE;
	STDMETHOD_(double,		FileSeek)(THIS_							DELIFile, double newposition, int disposition ) PURE;
	STDMETHOD_(unsigned int,FileRead)(THIS_							DELIFile file, void* buffer, unsigned int numbytes ) PURE;
	STDMETHOD_(double,		FileTell)(THIS_							DELIFile ) PURE;
	STDMETHOD_(DELIFile,		FileGet)(THIS_								int index ) PURE;
	STDMETHOD_(DELIFile,		FileAlloc)(THIS_							int buffersize, const char* filename, int wallsize ) PURE;
	STDMETHOD_(void,			FileUnload)(THIS_							DELIFile file ) PURE;
	STDMETHOD_(DELIResult,	FileGetData)(THIS_						DELIFile file, void** pData, unsigned int* pSize ) PURE;
	STDMETHOD_(DELIResult,	FileGetName)(THIS_						DELIFile file, char* namebuffer, int namebufferlen ) PURE;
};

// values for FileSeek() argument 'disposition'
#define DELI_SEEKORIGIN_BEGIN		(0)
#define DELI_SEEKORIGIN_CURRENT	(1)
#define DELI_SEEKORIGIN_END		(2)

// values for ReplaySetRepeat() argument 'looptype'
#define DELI_LOOPTYPE_Forward		(1)
#define DELI_LOOPTYPE_Backward	(2)
#define DELI_LOOPTYPE_PingPong	(3)

// value for the DATA_Format_TextEncoding tag
#define DELI_TEXTENCODING_UTF8			(1)
#define DELI_TEXTENCODING_UTF16			(2)
#define DELI_TEXTENCODING_ANSI			(3)
#define DELI_TEXTENCODING_OEMCP			(4)

typedef DELIResult(*TGetDeliPluginContainer)(REFIID,PPVOID);
#define GetDeliPluginContainer_STRING "GetDeliPluginContainer"

#define DATA_Container_BASE				(1000)
#define DATA_Container_NumPlugins		(DATA_Container_BASE+1)

#define DATA_Plugin_BASE					(2000)
#define DATA_Plugin_Name					(DATA_Plugin_BASE+1)			// name of the player/genie
#define DATA_Plugin_Version				(DATA_Plugin_BASE+2)			// actual player/genie version & revision
#define DATA_Plugin_Creator				(DATA_Plugin_BASE+3)			// who adapted this plugin
#define DATA_Plugin_Copyright				(DATA_Plugin_BASE+4)			// who owns the copyright on the plugin
#define DATA_Plugin_Description			(DATA_Plugin_BASE+5)
#define DATA_Plugin_VariablesSize		(DATA_Plugin_BASE+6)			// players only: size of the plugin-data variables' space
#define DATA_Plugin_NamedVariables		(DATA_Plugin_BASE+7)			// ptr to a NamedVariable array
#define DATA_Plugin_QueuePriority		(DATA_Plugin_BASE+8)			// position of this plugin in the plugin specific queue

#define FLAG_Plugin_BASE					(3000)
#define FLAG_Plugin_UIThread				(FLAG_Plugin_BASE+1)			// indicates that a UI thread must be started for this DLL
#define FLAG_Plugin_NotReentrant			(FLAG_Plugin_BASE+2)			// plugin is not reentrant/threadsafe
#define FLAG_Plugin_NotThreadsafe		(FLAG_Plugin_NotReentrant)	// plugin is not reentrant/threadsafe
#define FLAG_Plugin_StreamInput			(FLAG_Plugin_BASE+3)			// plugin uses DeliPlayer's read functions to load data (required for Internet Radios)
#define FLAG_Plugin_BufferPush			(FLAG_Plugin_BASE+4)			// for loader plugins, indicates this loader pushes into the buffer itself, no asny read thread allowed

#define FLAG_Player_BASE					(3500)
#define FLAG_Player_CheckFile				(FLAG_Player_BASE+1)			// indicated that the check function can check files (fully loaded into memory) [default, if no FLAG_Player_Check* tag present]
#define FLAG_Player_CheckPartial			(FLAG_Player_BASE+2)			// indicates that the check function can check partiall loaded files (only the first 20k loaded)
#define FLAG_Player_CheckStream			(FLAG_Player_BASE+3)			// indicates that the check function can check streams (only the first 20k loaded), must also set FLAG_Plugin_StreamInput

#define DATA_Format_BASE					(4000)
#define DATA_Format_Name					(DATA_Format_BASE+1)			// name of the format this player plays
#define DATA_Format_Version				(DATA_Format_BASE+2)			// version of the format this player plays
#define DATA_Format_Creator				(DATA_Format_BASE+3)			// creator of the player-code
#define DATA_Format_Copyright				(DATA_Format_BASE+4)			// who owns the copyright on the format
#define DATA_Format_Info					(DATA_Format_BASE+5)			// information about the format, inventor, editor etc.
#define DATA_Format_TextEncoding			(DATA_Format_BASE+6)			// character encoding used by this format, all text output of the *Information() methods' will be treated acordingly. Values: DELI_TEXTENCODING_*. Default is ANSI.

#define FLAG_Format_BASE					(4500)
#define FLAG_Format_Songend				(FLAG_Format_BASE+1)			// player detects songend for this format
#define FLAG_Format_SubSongs				(FLAG_Format_BASE+2)			// format supports subsongs
#define FLAG_Format_Emulated				(FLAG_Format_BASE+3)			// replay code is not native
#define FLAG_Format_SupportsID3TAG		(FLAG_Format_BASE+4)			// format supports ID3 tagging
#define FLAG_Format_SupportsAPTETAG		(FLAG_Format_BASE+5)			// format supports APE tagging (currently ignored)
#define FLAG_Format_SupportsOGGTAG		(FLAG_Format_BASE+6)			// format supports OGG comments (currently ignored)

#define DATA_Module_BASE					(5000)
#define DATA_Module_NumSongs				(DATA_Module_BASE+1)
#define DATA_Module_NumInstruments		(DATA_Module_BASE+2)
#define DATA_Module_NumSamples			(DATA_Module_BASE+3)
#define DATA_Module_NumMessages			(DATA_Module_BASE+4)
#define DATA_Module_NumFormats			(DATA_Module_BASE+5)
#define DATA_Module_DefaultSong			(DATA_Module_BASE+6)

#define FLAG_Module_BASE					(5500)
#define FLAG_Module_SetPosition			(FLAG_Module_BASE+1)			// module supports setposition

#define DATA_Song_BASE						(6000)
#define DATA_Song_NumChannels				(DATA_Song_BASE+1)
#define DATA_Song_Author					(DATA_Song_BASE+2)
#define DATA_Song_Frequency				(DATA_Song_BASE+3)
#define DATA_Song_Resolution				(DATA_Song_BASE+4)
#define DATA_Song_Album						(DATA_Song_BASE+5)
#define DATA_Song_Interpret				(DATA_Song_BASE+6)
#define DATA_Song_Genre						(DATA_Song_BASE+7)
#define DATA_Song_TrackNum					(DATA_Song_BASE+8)
#define DATA_Song_ReleaseDate				(DATA_Song_BASE+9)
#define DATA_Song_Copyright				(DATA_Song_BASE+10)
#define DATA_Song_Name						(DATA_Song_BASE+11)
#define DATA_Song_Duration					(DATA_Song_BASE+12)
#define DATA_Song_Description				(DATA_Song_BASE+15)
#define DATA_Song_Comment					(DATA_Song_BASE+16)
#define DATA_Song_Annotation				(DATA_Song_BASE+17)
#define DATA_Song_Dedication				(DATA_Song_BASE+18)
#define DATA_Song_RecordLocation			(DATA_Song_BASE+19)
#define DATA_Song_RecordDateTime			(DATA_Song_BASE+10)
#define DATA_Song_ReleaseStatus			(DATA_Song_BASE+21)
#define DATA_Song_Location					(DATA_Song_BASE+22)
#define DATA_Song_Homepage					(DATA_Song_BASE+23)
#define DATA_Song_FormatTA					(DATA_Song_BASE+24)

#define DATA_Sample_BASE					(7000)
#define DATA_Sample_Name					(DATA_Sample_BASE+1)
#define DATA_Sample_Bits					(DATA_Sample_BASE+2)
#define DATA_Sample_Channels				(DATA_Sample_BASE+3)
#define DATA_Sample_Frequency				(DATA_Sample_BASE+4)
#define DATA_Sample_Volume					(DATA_Sample_BASE+5)
#define DATA_Sample_Type					(DATA_Sample_BASE+6)
#define DATA_Sample_Pointer				(DATA_Sample_BASE+7)
#define DATA_Sample_Length					(DATA_Sample_BASE+8)
#define DATA_Sample_LoopBeg				(DATA_Sample_BASE+9)
#define DATA_Sample_LoopLen				(DATA_Sample_BASE+10)
#define DATA_Sample_LoopType				(DATA_Sample_BASE+11)
#define DATA_Sample_HorizPanning			(DATA_Sample_BASE+12)
#define DATA_Sample_VertPanning			(DATA_Sample_BASE+13)
#define DATA_Sample_DepthPanning			(DATA_Sample_BASE+14)

#define DATA_Instrument_BASE				(8000)
#define DATA_Instrument_Name				(DATA_Instrument_BASE+1)
#define DATA_Instrument_NumSamples		(DATA_Instrument_BASE+2)

#define DATA_Message_BASE					(9000)
#define DATA_Message_Text					(DATA_Message_BASE+1)

#define DATA_Extension_BASE				(10000)
#define DATA_Extension_Prefix				(DATA_Extension_BASE+1)
#define DATA_Extension_Postfix			(DATA_Extension_BASE+2)
#define DATA_Extension_Name				(DATA_Extension_BASE+3)
#define DATA_Extension_Description		(DATA_Extension_BASE+4)
#define DATA_Extension_Type				(DATA_Extension_BASE+5)
#define DATA_Extension_Origin				(DATA_Extension_BASE+6)

#define UPDATE_BASE							(11000)
#define UPDATE_Songname						(UPDATE_BASE+1)
#define UPDATE_Artist						(UPDATE_BASE+2)
#define UPDATE_Album							(UPDATE_BASE+3)
#define UPDATE_Filename						(UPDATE_BASE+4)
#define UPDATE_Genre							(UPDATE_BASE+5)
#define UPDATE_Comment						(UPDATE_BASE+6)
#define UPDATE_Copyright					(UPDATE_BASE+7)
#define UPDATE_ReleaseDate					(UPDATE_BASE+8)
#define UPDATE_Organization				(UPDATE_BASE+9)
#define UPDATE_Contact						(UPDATE_BASE+10)
#define UPDATE_Location						(UPDATE_BASE+11)
#define UPDATE_Homepage						(UPDATE_BASE+12)
#define UPDATE_TrackNum						(UPDATE_BASE+13)

// use the DELI_GENVERSION() macro for the following tags:
//  DATA_Container_Version
//  DATA_Plugin_Version
//  DATA_Format_Version
// valid argument ranges: 
//  0 <= MAJOR <= 255
//  0 <= MINOR <= 255
//  0 <= REVISION <= 65535
#define DELI_GENVERSION(MAJOR,MINOR,REVISION) ((((MAJOR)&0xFF)<<24)+(((MINOR)&0xFF)<<16)+((REVISION)&0xFFFF))

#define DELIVERSION_MAJOR(v)    (((v)&0xFF000000)>>24)
#define DELIVERSION_MINOR(v)    (((v)&0x00FF0000)>>16)
#define DELIVERSION_REVISION(v) ( (v)&0x0000FFFF)

// values for the DATA_Extension_Type tag
#define DELI_FILEEXTTYPE_Undefined		(0)
#define DELI_FILEEXTTYPE_Archive			(1)
#define DELI_FILEEXTTYPE_Module			(2)
#define DELI_FILEEXTTYPE_AudioStream	(3)
#define DELI_FILEEXTTYPE_Auxiliary		(4)

// values for the DATA_Extension_Origin tag
#define DELI_FILEEXTORG_Official			(1)
#define DELI_FILEEXTORG_Editor			DELI_FILEEXTORG_Official
#define DELI_FILEEXTORG_Widespread		(2)
#define DELI_FILEEXTORG_Rarely			(3)

// possible values for DATA_Song_Duration
#define DELI_DURATION_UNKNOWN				(0)
#define DELI_DURATION_ENDLESS				(-1)

#endif // IDELIAPI_H
//EOF