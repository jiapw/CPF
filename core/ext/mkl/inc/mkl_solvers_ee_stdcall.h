/*******************************************************************************
* Copyright 2012-2021 Intel Corporation.
*
* This software and the related documents are Intel copyrighted  materials,  and
* your use of  them is  governed by the  express license  under which  they were
* provided to you (License).  Unless the License provides otherwise, you may not
* use, modify, copy, publish, distribute,  disclose or transmit this software or
* the related documents without Intel's prior written permission.
*
* This software and the related documents  are provided as  is,  with no express
* or implied  warranties,  other  than those  that are  expressly stated  in the
* License.
*******************************************************************************/

/*
*   Content:
*           Intel(R) oneAPI Math Kernel Library (oneMKL) FEAST C header file
*
*           Contains interface to FEAST.
*
********************************************************************************
*/
#include "mkl_spblas.h"

#ifndef _MKL_SOLVERS_EE_STDCALL_H_
#define _MKL_SOLVERS_EE_STDCALL_H_
#include "mkl_types.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#if defined(MKL_STDCALL)
#ifndef MKL_CALL_CONV
#define MKL_CALL_CONV __stdcall
#endif

#ifndef MKL_STDCALL_WARNING
#define MKL_STDCALL_WARNING
#pragma message("WARNING: oneMKL stdcall API has been deprecated")
#endif

#if  !defined(_Mkl_Api)
#define _Mkl_Api(rtype,name,arg)   extern rtype MKL_CALL_CONV   name    arg;
#endif

_Mkl_Api(void,feastinit,(MKL_INT* fpm))
_Mkl_Api(void,FEASTINIT,(MKL_INT* fpm))

_Mkl_Api(void,dfeast_scsrev,(const char* uplo , int uplo_len , const MKL_INT* n , const double* sa , const MKL_INT* isa , const MKL_INT* jsa , MKL_INT* fpm , double* epsout , MKL_INT* loop , const double* emin , const double* emax , MKL_INT* m0 , double* e , double* x , MKL_INT* m , double* res , MKL_INT* info))
_Mkl_Api(void,DFEAST_SCSREV,(const char* uplo , int uplo_len , const MKL_INT* n , const double* sa , const MKL_INT* isa , const MKL_INT* jsa , MKL_INT* fpm , double* epsout , MKL_INT* loop , const double* emin , const double* emax , MKL_INT* m0 , double* e , double* x , MKL_INT* m , double* res , MKL_INT* info))

_Mkl_Api(void,sfeast_sygv,(const char* uplo , int uplo_len , const MKL_INT* n , const float* a , const MKL_INT* lda , const float* b , const MKL_INT* ldb , MKL_INT* fpm , float* epsout , MKL_INT* loop , const float* emin , const float* emax , MKL_INT* m0 , float* e , float* x , MKL_INT* m , float* res , MKL_INT* info))
_Mkl_Api(void,SFEAST_SYGV,(const char* uplo , int uplo_len , const MKL_INT* n , const float* a , const MKL_INT* lda , const float* b , const MKL_INT* ldb , MKL_INT* fpm , float* epsout , MKL_INT* loop , const float* emin , const float* emax , MKL_INT* m0 , float* e , float* x , MKL_INT* m , float* res , MKL_INT* info))

_Mkl_Api(void,sfeast_scsrev,(const char* uplo , int uplo_len , const MKL_INT* n , const float* sa , const MKL_INT* isa , const MKL_INT* jsa , MKL_INT* fpm , float* epsout , MKL_INT* loop , const float* emin , const float* emax , MKL_INT* m0 , float* e , float* x , MKL_INT* m , float* res , MKL_INT* info))
_Mkl_Api(void,SFEAST_SCSREV,(const char* uplo , int uplo_len , const MKL_INT* n , const float* sa , const MKL_INT* isa , const MKL_INT* jsa , MKL_INT* fpm , float* epsout , MKL_INT* loop , const float* emin , const float* emax , MKL_INT* m0 , float* e , float* x , MKL_INT* m , float* res , MKL_INT* info))

_Mkl_Api(void,zfeast_hbgv,(const char* uplo , int uplo_len , const MKL_INT* n , const MKL_INT* kla , const MKL_Complex16* a , const MKL_INT* lda , const MKL_INT* klb , const MKL_Complex16* b , const MKL_INT* ldb , MKL_INT* fpm , double* epsout , MKL_INT* loop , const double* emin , const double* emax , MKL_INT* m0 , double* e , MKL_Complex16* x , MKL_INT* m , double* res , MKL_INT* info))
_Mkl_Api(void,ZFEAST_HBGV,(const char* uplo , int uplo_len , const MKL_INT* n , const MKL_INT* kla , const MKL_Complex16* a , const MKL_INT* lda , const MKL_INT* klb , const MKL_Complex16* b , const MKL_INT* ldb , MKL_INT* fpm , double* epsout , MKL_INT* loop , const double* emin , const double* emax , MKL_INT* m0 , double* e , MKL_Complex16* x , MKL_INT* m , double* res , MKL_INT* info))

_Mkl_Api(void,zfeast_hcsrev,(const char* uplo , int uplo_len , const MKL_INT* n , const MKL_Complex16* sa , const MKL_INT* isa , const MKL_INT* jsa , MKL_INT* fpm , double* epsout , MKL_INT* loop , const double* emin , const double* emax , MKL_INT* m0 , double* e , MKL_Complex16* x , MKL_INT* m , double* res , MKL_INT* info))
_Mkl_Api(void,ZFEAST_HCSREV,(const char* uplo , int uplo_len , const MKL_INT* n , const MKL_Complex16* sa , const MKL_INT* isa , const MKL_INT* jsa , MKL_INT* fpm , double* epsout , MKL_INT* loop , const double* emin , const double* emax , MKL_INT* m0 , double* e , MKL_Complex16* x , MKL_INT* m , double* res , MKL_INT* info))

_Mkl_Api(void,cfeast_hbev,(const char* uplo , int uplo_len , const MKL_INT* n , const MKL_INT* kla , const MKL_Complex8* a , const MKL_INT* lda , MKL_INT* fpm , float* epsout , MKL_INT* loop , const float* emin , const float* emax , MKL_INT* m0 , float* e , MKL_Complex8* x , MKL_INT* m , float* res , MKL_INT* info))
_Mkl_Api(void,CFEAST_HBEV,(const char* uplo , int uplo_len , const MKL_INT* n , const MKL_INT* kla , const MKL_Complex8* a , const MKL_INT* lda , MKL_INT* fpm , float* epsout , MKL_INT* loop , const float* emin , const float* emax , MKL_INT* m0 , float* e , MKL_Complex8* x , MKL_INT* m , float* res , MKL_INT* info))

_Mkl_Api(void,zfeast_heev,(const char* uplo , int uplo_len , const MKL_INT* n , const MKL_Complex16* a , const MKL_INT* lda , MKL_INT* fpm , double* epsout , MKL_INT* loop , const double* emin , const double* emax , MKL_INT* m0 , double* e , MKL_Complex16* x , MKL_INT* m , double* res , MKL_INT* info))
_Mkl_Api(void,ZFEAST_HEEV,(const char* uplo , int uplo_len , const MKL_INT* n , const MKL_Complex16* a , const MKL_INT* lda , MKL_INT* fpm , double* epsout , MKL_INT* loop , const double* emin , const double* emax , MKL_INT* m0 , double* e , MKL_Complex16* x , MKL_INT* m , double* res , MKL_INT* info))

_Mkl_Api(void,zfeast_hcsrgv,(const char* uplo , int uplo_len , const MKL_INT* n , const MKL_Complex16* sa , const MKL_INT* isa , const MKL_INT* jsa , const MKL_Complex16* sb , const MKL_INT* isb , const MKL_INT* jsb , MKL_INT* fpm , double* epsout , MKL_INT* loop , const double* emin , const double* emax , MKL_INT* m0 , double* e , MKL_Complex16* x , MKL_INT* m , double* res , MKL_INT* info))
_Mkl_Api(void,ZFEAST_HCSRGV,(const char* uplo , int uplo_len , const MKL_INT* n , const MKL_Complex16* sa , const MKL_INT* isa , const MKL_INT* jsa , const MKL_Complex16* sb , const MKL_INT* isb , const MKL_INT* jsb , MKL_INT* fpm , double* epsout , MKL_INT* loop , const double* emin , const double* emax , MKL_INT* m0 , double* e , MKL_Complex16* x , MKL_INT* m , double* res , MKL_INT* info))

_Mkl_Api(void,sfeast_scsrgv,(const char* uplo , int uplo_len , const MKL_INT* n , const float* sa , const MKL_INT* isa , const MKL_INT* jsa , const float* sb , const MKL_INT* isb , const MKL_INT* jsb , MKL_INT* fpm , float* epsout , MKL_INT* loop , const float* emin , const float* emax , MKL_INT* m0 , float* e , float* x , MKL_INT* m , float* res , MKL_INT* info))
_Mkl_Api(void,SFEAST_SCSRGV,(const char* uplo , int uplo_len , const MKL_INT* n , const float* sa , const MKL_INT* isa , const MKL_INT* jsa , const float* sb , const MKL_INT* isb , const MKL_INT* jsb , MKL_INT* fpm , float* epsout , MKL_INT* loop , const float* emin , const float* emax , MKL_INT* m0 , float* e , float* x , MKL_INT* m , float* res , MKL_INT* info))

_Mkl_Api(void,dfeast_srci,(MKL_INT* ijob , const MKL_INT* n , MKL_Complex16* ze , double* work , MKL_Complex16* workc , double* aq , double* sq , MKL_INT* fpm , double* epsout , MKL_INT* loop , const double* emin , const double* emax , MKL_INT* m0 , double* lambda , double* q , MKL_INT* m , double* res , MKL_INT* info))
_Mkl_Api(void,DFEAST_SRCI,(MKL_INT* ijob , const MKL_INT* n , MKL_Complex16* ze , double* work , MKL_Complex16* workc , double* aq , double* sq , MKL_INT* fpm , double* epsout , MKL_INT* loop , const double* emin , const double* emax , MKL_INT* m0 , double* lambda , double* q , MKL_INT* m , double* res , MKL_INT* info))

_Mkl_Api(void,sfeast_sbev,(const char* uplo , int uplo_len , const MKL_INT* n , const MKL_INT* kla , const float* a , const MKL_INT* lda , MKL_INT* fpm , float* epsout , MKL_INT* loop , const float* emin , const float* emax , MKL_INT* m0 , float* e , float* x , MKL_INT* m , float* res , MKL_INT* info))
_Mkl_Api(void,SFEAST_SBEV,(const char* uplo , int uplo_len , const MKL_INT* n , const MKL_INT* kla , const float* a , const MKL_INT* lda , MKL_INT* fpm , float* epsout , MKL_INT* loop , const float* emin , const float* emax , MKL_INT* m0 , float* e , float* x , MKL_INT* m , float* res , MKL_INT* info))

_Mkl_Api(void,dfeast_sygv,(const char* uplo , int uplo_len , const MKL_INT* n , const double* a , const MKL_INT* lda , const double* b , const MKL_INT* ldb , MKL_INT* fpm , double* epsout , MKL_INT* loop , const double* emin , const double* emax , MKL_INT* m0 , double* e , double* x , MKL_INT* m , double* res , MKL_INT* info))
_Mkl_Api(void,DFEAST_SYGV,(const char* uplo , int uplo_len , const MKL_INT* n , const double* a , const MKL_INT* lda , const double* b , const MKL_INT* ldb , MKL_INT* fpm , double* epsout , MKL_INT* loop , const double* emin , const double* emax , MKL_INT* m0 , double* e , double* x , MKL_INT* m , double* res , MKL_INT* info))

_Mkl_Api(void,cfeast_hegv,(const char* uplo , int uplo_len , const MKL_INT* n , const MKL_Complex8* a , const MKL_INT* lda , const MKL_Complex8* b , const MKL_INT* ldb , MKL_INT* fpm , float* epsout , MKL_INT* loop , const float* emin , const float* emax , MKL_INT* m0 , float* e , MKL_Complex8* x , MKL_INT* m , float* res , MKL_INT* info))
_Mkl_Api(void,CFEAST_HEGV,(const char* uplo , int uplo_len , const MKL_INT* n , const MKL_Complex8* a , const MKL_INT* lda , const MKL_Complex8* b , const MKL_INT* ldb , MKL_INT* fpm , float* epsout , MKL_INT* loop , const float* emin , const float* emax , MKL_INT* m0 , float* e , MKL_Complex8* x , MKL_INT* m , float* res , MKL_INT* info))

_Mkl_Api(void,zfeast_hrci,(MKL_INT* ijob , const MKL_INT* n , MKL_Complex16* ze , MKL_Complex16* work , MKL_Complex16* workc , MKL_Complex16* zaq , MKL_Complex16* zsq , MKL_INT* fpm , double* epsout , MKL_INT* loop , const double* emin , const double* emax , MKL_INT* m0 , double* lambda , MKL_Complex16* q , MKL_INT* m , double* res , MKL_INT* info))
_Mkl_Api(void,ZFEAST_HRCI,(MKL_INT* ijob , const MKL_INT* n , MKL_Complex16* ze , MKL_Complex16* work , MKL_Complex16* workc , MKL_Complex16* zaq , MKL_Complex16* zsq , MKL_INT* fpm , double* epsout , MKL_INT* loop , const double* emin , const double* emax , MKL_INT* m0 , double* lambda , MKL_Complex16* q , MKL_INT* m , double* res , MKL_INT* info))

_Mkl_Api(void,cfeast_hrci,(MKL_INT* ijob , const MKL_INT* n , MKL_Complex8* ze , MKL_Complex8* work , MKL_Complex8* workc , MKL_Complex8* zaq , MKL_Complex8* zsq , MKL_INT* fpm , float* epsout , MKL_INT* loop , const float* emin , const float* emax , MKL_INT* m0 , float* lambda , MKL_Complex8* q , MKL_INT* m , float* res , MKL_INT* info))
_Mkl_Api(void,CFEAST_HRCI,(MKL_INT* ijob , const MKL_INT* n , MKL_Complex8* ze , MKL_Complex8* work , MKL_Complex8* workc , MKL_Complex8* zaq , MKL_Complex8* zsq , MKL_INT* fpm , float* epsout , MKL_INT* loop , const float* emin , const float* emax , MKL_INT* m0 , float* lambda , MKL_Complex8* q , MKL_INT* m , float* res , MKL_INT* info))

_Mkl_Api(void,zfeast_hegv,(const char* uplo , int uplo_len , const MKL_INT* n , const MKL_Complex16* a , const MKL_INT* lda , const MKL_Complex16* b , const MKL_INT* ldb , MKL_INT* fpm , double* epsout , MKL_INT* loop , const double* emin , const double* emax , MKL_INT* m0 , double* e , MKL_Complex16* x , MKL_INT* m , double* res , MKL_INT* info))
_Mkl_Api(void,ZFEAST_HEGV,(const char* uplo , int uplo_len , const MKL_INT* n , const MKL_Complex16* a , const MKL_INT* lda , const MKL_Complex16* b , const MKL_INT* ldb , MKL_INT* fpm , double* epsout , MKL_INT* loop , const double* emin , const double* emax , MKL_INT* m0 , double* e , MKL_Complex16* x , MKL_INT* m , double* res , MKL_INT* info))

_Mkl_Api(void,sfeast_srci,(MKL_INT* ijob , const MKL_INT* n , MKL_Complex8* ze , float* work , MKL_Complex8* workc , float* aq , float* sq , MKL_INT* fpm , float* epsout , MKL_INT* loop , const float* emin , const float* emax , MKL_INT* m0 , float* lambda , float* q , MKL_INT* m , float* res , MKL_INT* info))
_Mkl_Api(void,SFEAST_SRCI,(MKL_INT* ijob , const MKL_INT* n , MKL_Complex8* ze , float* work , MKL_Complex8* workc , float* aq , float* sq , MKL_INT* fpm , float* epsout , MKL_INT* loop , const float* emin , const float* emax , MKL_INT* m0 , float* lambda , float* q , MKL_INT* m , float* res , MKL_INT* info))

_Mkl_Api(void,dfeast_scsrgv,(const char* uplo , int uplo_len , const MKL_INT* n , const double* sa , const MKL_INT* isa , const MKL_INT* jsa , const double* sb , const MKL_INT* isb , const MKL_INT* jsb , MKL_INT* fpm , double* epsout , MKL_INT* loop , const double* emin , const double* emax , MKL_INT* m0 , double* e , double* x , MKL_INT* m , double* res , MKL_INT* info))
_Mkl_Api(void,DFEAST_SCSRGV,(const char* uplo , int uplo_len , const MKL_INT* n , const double* sa , const MKL_INT* isa , const MKL_INT* jsa , const double* sb , const MKL_INT* isb , const MKL_INT* jsb , MKL_INT* fpm , double* epsout , MKL_INT* loop , const double* emin , const double* emax , MKL_INT* m0 , double* e , double* x , MKL_INT* m , double* res , MKL_INT* info))

_Mkl_Api(void,sfeast_syev,(const char* uplo , int uplo_len , const MKL_INT* n , const float* a , const MKL_INT* lda , MKL_INT* fpm , float* epsout , MKL_INT* loop , const float* emin , const float* emax , MKL_INT* m0 , float* e , float* x , MKL_INT* m , float* res , MKL_INT* info))
_Mkl_Api(void,SFEAST_SYEV,(const char* uplo , int uplo_len , const MKL_INT* n , const float* a , const MKL_INT* lda , MKL_INT* fpm , float* epsout , MKL_INT* loop , const float* emin , const float* emax , MKL_INT* m0 , float* e , float* x , MKL_INT* m , float* res , MKL_INT* info))

_Mkl_Api(void,cfeast_hcsrev,(const char* uplo , int uplo_len , const MKL_INT* n , const MKL_Complex8* sa , const MKL_INT* isa , const MKL_INT* jsa , MKL_INT* fpm , float* epsout , MKL_INT* loop , const float* emin , const float* emax , MKL_INT* m0 , float* e , MKL_Complex8* x , MKL_INT* m , float* res , MKL_INT* info))
_Mkl_Api(void,CFEAST_HCSREV,(const char* uplo , int uplo_len , const MKL_INT* n , const MKL_Complex8* sa , const MKL_INT* isa , const MKL_INT* jsa , MKL_INT* fpm , float* epsout , MKL_INT* loop , const float* emin , const float* emax , MKL_INT* m0 , float* e , MKL_Complex8* x , MKL_INT* m , float* res , MKL_INT* info))

_Mkl_Api(void,zfeast_hbev,(const char* uplo , int uplo_len , const MKL_INT* n , const MKL_INT* kla , const MKL_Complex16* a , const MKL_INT* lda , MKL_INT* fpm , double* epsout , MKL_INT* loop , const double* emin , const double* emax , MKL_INT* m0 , double* e , MKL_Complex16* x , MKL_INT* m , double* res , MKL_INT* info))
_Mkl_Api(void,ZFEAST_HBEV,(const char* uplo , int uplo_len , const MKL_INT* n , const MKL_INT* kla , const MKL_Complex16* a , const MKL_INT* lda , MKL_INT* fpm , double* epsout , MKL_INT* loop , const double* emin , const double* emax , MKL_INT* m0 , double* e , MKL_Complex16* x , MKL_INT* m , double* res , MKL_INT* info))

_Mkl_Api(void,dfeast_sbgv,(const char* uplo , int uplo_len , const MKL_INT* n , const MKL_INT* kla , const double* a , const MKL_INT* lda , const MKL_INT* klb , const double* b , const MKL_INT* ldb , MKL_INT* fpm , double* epsout , MKL_INT* loop , const double* emin , const double* emax , MKL_INT* m0 , double* e , double* x , MKL_INT* m , double* res , MKL_INT* info))
_Mkl_Api(void,DFEAST_SBGV,(const char* uplo , int uplo_len , const MKL_INT* n , const MKL_INT* kla , const double* a , const MKL_INT* lda , const MKL_INT* klb , const double* b , const MKL_INT* ldb , MKL_INT* fpm , double* epsout , MKL_INT* loop , const double* emin , const double* emax , MKL_INT* m0 , double* e , double* x , MKL_INT* m , double* res , MKL_INT* info))

_Mkl_Api(void,cfeast_hbgv,(const char* uplo , int uplo_len , const MKL_INT* n , const MKL_INT* kla , const MKL_Complex8* a , const MKL_INT* lda , const MKL_INT* klb , const MKL_Complex8* b , const MKL_INT* ldb , MKL_INT* fpm , float* epsout , MKL_INT* loop , const float* emin , const float* emax , MKL_INT* m0 , float* e , MKL_Complex8* x , MKL_INT* m , float* res , MKL_INT* info))
_Mkl_Api(void,CFEAST_HBGV,(const char* uplo , int uplo_len , const MKL_INT* n , const MKL_INT* kla , const MKL_Complex8* a , const MKL_INT* lda , const MKL_INT* klb , const MKL_Complex8* b , const MKL_INT* ldb , MKL_INT* fpm , float* epsout , MKL_INT* loop , const float* emin , const float* emax , MKL_INT* m0 , float* e , MKL_Complex8* x , MKL_INT* m , float* res , MKL_INT* info))

_Mkl_Api(void,cfeast_heev,(const char* uplo , int uplo_len , const MKL_INT* n , const MKL_Complex8* a , const MKL_INT* lda , MKL_INT* fpm , float* epsout , MKL_INT* loop , const float* emin , const float* emax , MKL_INT* m0 , float* e , MKL_Complex8* x , MKL_INT* m , float* res , MKL_INT* info))
_Mkl_Api(void,CFEAST_HEEV,(const char* uplo , int uplo_len , const MKL_INT* n , const MKL_Complex8* a , const MKL_INT* lda , MKL_INT* fpm , float* epsout , MKL_INT* loop , const float* emin , const float* emax , MKL_INT* m0 , float* e , MKL_Complex8* x , MKL_INT* m , float* res , MKL_INT* info))

_Mkl_Api(void,sfeast_sbgv,(const char* uplo , int uplo_len , const MKL_INT* n , const MKL_INT* kla , const float* a , const MKL_INT* lda , const MKL_INT* klb , const float* b , const MKL_INT* ldb , MKL_INT* fpm , float* epsout , MKL_INT* loop , const float* emin , const float* emax , MKL_INT* m0 , float* e , float* x , MKL_INT* m , float* res , MKL_INT* info))
_Mkl_Api(void,SFEAST_SBGV,(const char* uplo , int uplo_len , const MKL_INT* n , const MKL_INT* kla , const float* a , const MKL_INT* lda , const MKL_INT* klb , const float* b , const MKL_INT* ldb , MKL_INT* fpm , float* epsout , MKL_INT* loop , const float* emin , const float* emax , MKL_INT* m0 , float* e , float* x , MKL_INT* m , float* res , MKL_INT* info))

_Mkl_Api(void,cfeast_hcsrgv,(const char* uplo , int uplo_len , const MKL_INT* n , const MKL_Complex8* sa , const MKL_INT* isa , const MKL_INT* jsa , const MKL_Complex8* sb , const MKL_INT* isb , const MKL_INT* jsb , MKL_INT* fpm , float* epsout , MKL_INT* loop , const float* emin , const float* emax , MKL_INT* m0 , float* e , MKL_Complex8* x , MKL_INT* m , float* res , MKL_INT* info))
_Mkl_Api(void,CFEAST_HCSRGV,(const char* uplo , int uplo_len , const MKL_INT* n , const MKL_Complex8* sa , const MKL_INT* isa , const MKL_INT* jsa , const MKL_Complex8* sb , const MKL_INT* isb , const MKL_INT* jsb , MKL_INT* fpm , float* epsout , MKL_INT* loop , const float* emin , const float* emax , MKL_INT* m0 , float* e , MKL_Complex8* x , MKL_INT* m , float* res , MKL_INT* info))

_Mkl_Api(void,dfeast_syev,(const char* uplo , int uplo_len , const MKL_INT* n , const double* a , const MKL_INT* lda , MKL_INT* fpm , double* epsout , MKL_INT* loop , const double* emin , const double* emax , MKL_INT* m0 , double* e , double* x , MKL_INT* m , double* res , MKL_INT* info))
_Mkl_Api(void,DFEAST_SYEV,(const char* uplo , int uplo_len , const MKL_INT* n , const double* a , const MKL_INT* lda , MKL_INT* fpm , double* epsout , MKL_INT* loop , const double* emin , const double* emax , MKL_INT* m0 , double* e , double* x , MKL_INT* m , double* res , MKL_INT* info))

_Mkl_Api(void,dfeast_sbev,(const char* uplo , int uplo_len , const MKL_INT* n , const MKL_INT* kla , const double* a , const MKL_INT* lda , MKL_INT* fpm , double* epsout , MKL_INT* loop , const double* emin , const double* emax , MKL_INT* m0 , double* e , double* x , MKL_INT* m , double* res , MKL_INT* info))
_Mkl_Api(void,DFEAST_SBEV,(const char* uplo , int uplo_len , const MKL_INT* n , const MKL_INT* kla , const double* a , const MKL_INT* lda , MKL_INT* fpm , double* epsout , MKL_INT* loop , const double* emin , const double* emax , MKL_INT* m0 , double* e , double* x , MKL_INT* m , double* res , MKL_INT* info))

#endif /* MKL_STDCALL */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _MKL_SOLVERS_EE_STDCALL_H_ */
