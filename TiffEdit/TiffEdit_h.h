

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Sun Oct 19 21:43:23 2014
 */
/* Compiler settings for TiffEdit.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __TiffEdit_h_h__
#define __TiffEdit_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITiffEdit_FWD_DEFINED__
#define __ITiffEdit_FWD_DEFINED__
typedef interface ITiffEdit ITiffEdit;

#endif 	/* __ITiffEdit_FWD_DEFINED__ */


#ifndef __CTiffEditDoc_FWD_DEFINED__
#define __CTiffEditDoc_FWD_DEFINED__

#ifdef __cplusplus
typedef class CTiffEditDoc CTiffEditDoc;
#else
typedef struct CTiffEditDoc CTiffEditDoc;
#endif /* __cplusplus */

#endif 	/* __CTiffEditDoc_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __TiffEdit_LIBRARY_DEFINED__
#define __TiffEdit_LIBRARY_DEFINED__

/* library TiffEdit */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_TiffEdit;

#ifndef __ITiffEdit_DISPINTERFACE_DEFINED__
#define __ITiffEdit_DISPINTERFACE_DEFINED__

/* dispinterface ITiffEdit */
/* [uuid] */ 


EXTERN_C const IID DIID_ITiffEdit;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("64E90099-2D8C-40A6-A0EF-E6B81E50C91B")
    ITiffEdit : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ITiffEditVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITiffEdit * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITiffEdit * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITiffEdit * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITiffEdit * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITiffEdit * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITiffEdit * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITiffEdit * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } ITiffEditVtbl;

    interface ITiffEdit
    {
        CONST_VTBL struct ITiffEditVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITiffEdit_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITiffEdit_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITiffEdit_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITiffEdit_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ITiffEdit_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ITiffEdit_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ITiffEdit_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ITiffEdit_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CTiffEditDoc;

#ifdef __cplusplus

class DECLSPEC_UUID("C503FA19-F1F0-488C-A662-F821D6FA732B")
CTiffEditDoc;
#endif
#endif /* __TiffEdit_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


