//------------------------------------------------------------------------------
// GrB_Matrix_extract: C<M> = accum (C, A(I,J)) or A(J,I)'
//------------------------------------------------------------------------------

// SuiteSparse:GraphBLAS, Timothy A. Davis, (c) 2017-2019, All Rights Reserved.
// http://suitesparse.com   See GraphBLAS/Doc/License.txt for license.

//------------------------------------------------------------------------------

// parallel: not here, but in GB_subref_numeric.

#include "GB.h"

GrB_Info GrB_Matrix_extract     // C<M> = accum (C, A(I,J))
(
    GrB_Matrix C,               // input/output matrix for results
    const GrB_Matrix M,         // optional mask for C, unused if NULL
    const GrB_BinaryOp accum,   // optional accum for Z=accum(C,T)
    const GrB_Matrix A,         // first input:  matrix A
    const GrB_Index *I,         // row indices
    GrB_Index ni,               // number of row indices
    const GrB_Index *J,         // column indices
    GrB_Index nj,               // number of column indices
    const GrB_Descriptor desc   // descriptor for C, M, and A
)
{ 

    //--------------------------------------------------------------------------
    // check inputs
    //--------------------------------------------------------------------------

    GB_WHERE ("GrB_Matrix_extract (C, M, accum, A, I, ni, J, nj, desc)") ;

    GB_RETURN_IF_NULL_OR_FAULTY (C) ;
    GB_RETURN_IF_FAULTY (M) ;
    GB_RETURN_IF_NULL_OR_FAULTY (A) ;

    // get the descriptor
    GB_GET_DESCRIPTOR (info, desc, C_replace, Mask_comp, A_transpose, xx1, xx2);

    //--------------------------------------------------------------------------
    // do the work in GB_extract
    //--------------------------------------------------------------------------

    return (GB_extract (
        C,      C_replace,          // output matrix C and its descriptor
        M,      Mask_comp,          // mask and its descriptor
        accum,                      // optional accum for Z=accum(C,T)
        A,      A_transpose,        // A and its descriptor
        I, ni,                      // row indices
        J, nj,                      // column indices
        Context)) ;
}

