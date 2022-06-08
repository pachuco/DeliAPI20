// deliapi_playerhelper.cpp
// $Id: deliapi_playerhelper.cpp 125 2004-08-28 21:55:54Z florian $

//#include <afxole.h>
#include <assert.h>
#include "../helper/deliapi_playerhelper.h"
#include "../includes/ideliapi.h"

#ifdef _DEBUG
	#pragma comment(lib, "mfc42d.lib")
	#pragma comment(lib, "mfcs42d.lib")
#else
	#pragma comment(lib, "mfc42.lib")
	#pragma comment(lib, "mfcs42.lib")
#endif

CODeliPlayerHelper::CODeliPlayerHelper()
 :	cRefs( 0 )
{
}
CODeliPlayerHelper::~CODeliPlayerHelper()
{
}

STDMETHODIMP CODeliPlayerHelper::QueryInterface( REFIID riid, PPVOID ppv )
{
	HRESULT hr = E_NOINTERFACE;

	*ppv = NULL;
	if(		IID_IUnknown				== riid )
		*ppv = static_cast<IUnknown*>(this);	
	else if(	IID_IDeliPluginPlayer	== riid )
		*ppv =  static_cast<IDeliPluginPlayer*>(this);

	if( NULL != *ppv )
	{
		((LPUNKNOWN)*ppv)->AddRef();
		hr = NOERROR;
	}

	return hr;
}
STDMETHODIMP_(ULONG) CODeliPlayerHelper::AddRef( void )
{
//	ULONG local_cRefs;
//	local_cRefs = ++this->cRefs;
//	return local_cRefs;
	return InterlockedIncrement( &this->cRefs );
}
STDMETHODIMP_(ULONG) CODeliPlayerHelper::Release( void )
{
	ULONG local_cRefs;
//	local_cRefs = --this->m_cRefs;
	local_cRefs = InterlockedDecrement( &this->cRefs );
	if( 0 == local_cRefs )
	{
		this->cRefs++;
		delete this;
	}
	return local_cRefs;
}

//
// default implementations for all methods so you don't have to provide your own if you don't want to.
//

STDMETHODIMP_(DELIResult) CODeliPlayerHelper::InitPlugin( PVOID arg_socket )
{
	assert( arg_socket );

	pDeliSocket = (IDeliSocketPlayer*) arg_socket;

	return DELI_RESULT_OK;
}
STDMETHODIMP_(void) CODeliPlayerHelper::EndPlugin( void )
{
	assert( pDeliSocket );

	pDeliSocket->Release();
	
	pDeliSocket	 = NULL;
}

/*
STDMETHODIMP_(DELIResult) CODeliPlayerHelper::Check( DELIFile )
{
	return DELI_RESULT_ERROR_NOTIMPLEMENTED;
}
STDMETHODIMP_(DELIResult) CODeliPlayerHelper::InitModule( DELIFile )
{
	return DELI_RESULT_ERROR_NOTIMPLEMENTED;
}
STDMETHODIMP_(void) CODeliPlayerHelper::EndModule( void )
{
}
STDMETHODIMP_(DELIResult) CODeliPlayerHelper::InitSong( int songindex )
{
	return DELI_RESULT_ERROR_NOTIMPLEMENTED;
}
STDMETHODIMP_(void) CODeliPlayerHelper::EndSong( void )
{
}
*/
STDMETHODIMP_(DELIResult) CODeliPlayerHelper::StartPlay( void )
{
	return DELI_RESULT_OK;//DELI_RESULT_ERROR_NOTIMPLEMENTED;
}
STDMETHODIMP_(void) CODeliPlayerHelper::StopPlay( void )
{
}
STDMETHODIMP_(DELIResult) CODeliPlayerHelper::StartSkip( void )
{
	return DELI_RESULT_OK;//DELI_RESULT_ERROR_NOTIMPLEMENTED;
}
STDMETHODIMP_(void) CODeliPlayerHelper::StopSkip( void )
{
}
/*
STDMETHODIMP_(DELIResult) CODeliPlayerHelper::RenderFrame( void )
{
	return DELI_RESULT_ERROR_NOTIMPLEMENTED;
}
*/
STDMETHODIMP_(DELIResult) CODeliPlayerHelper::SetPosition( double )
{
	return DELI_RESULT_ERROR_NOTIMPLEMENTED;
}
STDMETHODIMP_(DeliTag*) CODeliPlayerHelper::PluginInformation( void )
{
	return NULL;
}
////STDMETHODIMP_(DELIResult)	PluginSignature)( DELIPLUGINSIGNATURE* );
STDMETHODIMP_(DeliTag*) CODeliPlayerHelper::SongInformation( int index )
{
	return NULL;
}
STDMETHODIMP_(DeliTag*) CODeliPlayerHelper::InstrumentInformation( int songindex, int instrumentindex )
{
	return NULL;
}
STDMETHODIMP_(DeliTag*) CODeliPlayerHelper::SampleInformation( int songindex, int sampleindex )
{
	return NULL;
}
STDMETHODIMP_(DeliTag*) CODeliPlayerHelper::MessageInformation( int songindex, int messageindex )
{
	return NULL;
}
STDMETHODIMP_(DeliTag*) CODeliPlayerHelper::FormatInformation( int index )
{
	return NULL;
}
STDMETHODIMP_(DeliTag*) CODeliPlayerHelper::FileExtensionInformation( int index )	
{
	return NULL;
}
STDMETHODIMP_(DELIResult) CODeliPlayerHelper::SetVariable( int index, DeliNamedVariableValue )
{
	return DELI_RESULT_ERROR_NOTIMPLEMENTED;
}
STDMETHODIMP_(DELIResult) CODeliPlayerHelper::GetVariable( int index, DeliNamedVariableValue* )
{
	return DELI_RESULT_ERROR_NOTIMPLEMENTED;
}
STDMETHODIMP_(void) CODeliPlayerHelper::SetVariablesApplyMode( int )
{
}
STDMETHODIMP_(void) CODeliPlayerHelper::Notify( unsigned int event, unsigned int data1, unsigned int data2 )
{
}
STDMETHODIMP_(HWND) CODeliPlayerHelper::ConfigDialogOpen( void )
{
	return NULL;
}
STDMETHODIMP_(void) CODeliPlayerHelper::ConfigDialogClose( void )
{
}
STDMETHODIMP_(void) CODeliPlayerHelper::ConfigDialogApply( void )
{
}
STDMETHODIMP_(void) CODeliPlayerHelper::ConfigDialogRestore( void )
{
}
STDMETHODIMP_(void) CODeliPlayerHelper::ConfigDefault( void )
{
}
STDMETHODIMP_(void) CODeliPlayerHelper::ConfigApply( void* newcfg )
{
}
STDMETHODIMP_(DELIResult)	CODeliPlayerHelper::ConfigSave( void )
{
	return DELI_RESULT_OK;//DELI_RESULT_ERROR_NOTIMPLEMENTED;
}
STDMETHODIMP_(DELIResult)	CODeliPlayerHelper::ConfigLoad( void )	
{
	return DELI_RESULT_OK;//DELI_RESULT_ERROR_NOTIMPLEMENTED;
}
STDMETHODIMP_(DELIBool)		CODeliPlayerHelper::ConfigChanged( void )
{
	return DELI_FALSE;
}


STDMETHODIMP CODeliPluginContainerHelper::QueryInterface( REFIID riid, PPVOID ppv )
{
	HRESULT hr = E_NOINTERFACE;

	*ppv = NULL;
	if(		IsEqualIID( IID_IUnknown, riid ))
		*ppv = static_cast<IUnknown*>(this);	
	else if(	IsEqualIID( IID_IDeliPluginContainer, riid ))
		*ppv =  static_cast<IDeliPluginContainer*>(this);

	if( NULL != *ppv )
	{
		((LPUNKNOWN)*ppv)->AddRef();
		hr = NOERROR;
	}

	return hr;
}
STDMETHODIMP_(ULONG) CODeliPluginContainerHelper::AddRef( void )
{
	return 2;
}

STDMETHODIMP_(ULONG) CODeliPluginContainerHelper::Release( void )
{
	return 1;
}

CODeliPluginContainerHelper plugincontainer;

DELI_DLLExportC
DELIResult GetDeliPluginContainer( REFIID riid, PPVOID ppv )
{
	DELIResult DELIResult = DELI_RESULT_ERROR_NOINTERFACE;
	*ppv = NULL;
	if( IsEqualIID( IID_IDeliPluginContainer, riid ))
		*ppv = static_cast<IDeliPluginContainer*>(&plugincontainer);	

	if( NULL != *ppv )
	{
		((LPUNKNOWN)*ppv)->AddRef();
		DELIResult = DELI_RESULT_OK;
	}

	return DELIResult;
}

STDMETHODIMP_(REFIID) CODeliPluginContainerHelper::GetIID( int pluginindex )
{
	// works only for player plugins that provide one player
	// must be overloaded by non player plugins and plugins that contain two or more players/plugins

	if( pluginindex == 0 )
	{
		return IID_IDeliPluginPlayer;
	}
	// DeliPlayer will ask for as many IIDs as plugins are promised in the container information array (DATA_Container_NumPlugins)

	static const IID nulliid = {0};	// any IID that is not defined in the DeliPlayer API header 
	return nulliid;
}
// TODO: if you get a C1010 error here, open the project settings and turn off precompiles headers for this file