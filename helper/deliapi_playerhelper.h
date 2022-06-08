// deliapi_playerhelper.h
// $Id: deliapi_playerhelper.h 90 2004-08-28 21:01:13Z florian $

#ifndef DELIAPI_HELPER_H
#define DELIAPI_HELPER_H

#include "../includes/ideliapi.h"

class CODeliPlayerHelper : public IDeliPluginPlayer
{
	private:
		long cRefs;
	public:
		CODeliPlayerHelper();
		virtual ~CODeliPlayerHelper();

		STDMETHODIMP			QueryInterface(	REFIID, PPVOID );
		STDMETHODIMP_(ULONG)	AddRef(				void );
		STDMETHODIMP_(ULONG)	Release(				void );

//		STDMETHODIMP_(DELIResult)	Check(							DELIFile );
//		STDMETHODIMP_(DELIResult)	InitModule(						DELIFile );
//		STDMETHODIMP_(void)			EndModule(						void );
//		STDMETHODIMP_(DELIResult)	InitSong(						int songindex );
//		STDMETHODIMP_(void)			EndSong(							void );
		STDMETHODIMP_(DELIResult)	SetPosition(					double );
		STDMETHODIMP_(DELIResult)	StartPlay(						void );
		STDMETHODIMP_(void)			StopPlay(						void );
		STDMETHODIMP_(DELIResult)	StartSkip(						void );
		STDMETHODIMP_(void)			StopSkip(						void );
//		STDMETHODIMP_(DELIResult)	RenderFrame(					void );

		STDMETHODIMP_(DELIResult)	InitPlugin(						PVOID socket );
		STDMETHODIMP_(void)			EndPlugin(						void );
		STDMETHODIMP_(DeliTag*)		PluginInformation(			void );
		STDMETHODIMP_(DeliTag*)		SongInformation(				int index );
		STDMETHODIMP_(DeliTag*)		InstrumentInformation(		int songindex, int instrumentindex );
		STDMETHODIMP_(DeliTag*)		SampleInformation(			int songindex, int sampleindex );
		STDMETHODIMP_(DeliTag*)		MessageInformation( 			int songindex, int messageindex );
		STDMETHODIMP_(DeliTag*)		FormatInformation(			int index );
		STDMETHODIMP_(DeliTag*)		FileExtensionInformation(	int index );	

		STDMETHODIMP_(DELIResult)	SetVariable(					int index, DeliNamedVariableValue value );
		STDMETHODIMP_(DELIResult)	GetVariable(					int index, DeliNamedVariableValue* pValue );
		STDMETHODIMP_(void)			SetVariablesApplyMode(		int );

		STDMETHODIMP_(void)			Notify(							unsigned int event, unsigned int data1, unsigned int data2 );

		STDMETHODIMP_(HWND)			ConfigDialogOpen(				void );
		STDMETHODIMP_(void)			ConfigDialogClose(			void );
		STDMETHODIMP_(void)			ConfigDialogApply(			void );
		STDMETHODIMP_(void)			ConfigDialogRestore(			void );
		STDMETHODIMP_(void)			ConfigDefault(					void );
		STDMETHODIMP_(void)			ConfigApply(					void* newcfg );
		STDMETHODIMP_(DELIResult)	ConfigSave(						void );
		STDMETHODIMP_(DELIResult)	ConfigLoad(						void );	
		STDMETHODIMP_(DELIBool)		ConfigChanged(					void );

	public:
		IDeliSocketPlayer*	pDeliSocket;
};

class CODeliPluginContainerHelper : public IDeliPluginContainer
{
	public:
		STDMETHODIMP			QueryInterface(	REFIID, PPVOID );
		STDMETHODIMP_(ULONG)	AddRef(				void );
		STDMETHODIMP_(ULONG)	Release(				void );

		STDMETHODIMP_(DELIResult)	Initialize(			void );
		STDMETHODIMP_(DeliTag*)		Information(		void );
		STDMETHODIMP_(REFIID)		GetIID(				int pluginindex );
		STDMETHODIMP_(DELIResult)	CreateInstance(	int pluginindex, REFIID, PPVOID );
		STDMETHODIMP_(void)			Cleanup(				void );
};

#endif // DELIAPI_HELPER_H
