#pragma once

namespace mcl { namespace fp {

template<>
struct EnableKaratsuba<Ltag> {
#if CYBOZU_OS_BIT ==  32
	static const size_t minMulN = 10;
	static const size_t minSqrN = 10;
#else
	static const size_t minMulN = 8;
	static const size_t minSqrN = 6;
#endif
};

#if CYBOZU_OS_BIT == 32
	#define MCL_GMP_IS_FASTER_THAN_LLVM
#endif

#ifdef MCL_GMP_IS_FASTER_THAN_LLVM
#define MCL_DEF_MUL(n)
#else
#define MCL_DEF_MUL(n) \
template<>const void3u MulPreCore<n, Ltag>::f = &mcl_fpDbl_mulPre ## n ## L; \
template<>const void2u SqrPreCore<n, Ltag>::f = &mcl_fpDbl_sqrPre ## n ## L;
#endif

#define MCL_DEF_LLVM_FUNC(n) \
template<>const u3u AddPre<n, Ltag>::f = &mcl_fp_addPre ## n ## L; \
template<>const u3u SubPre<n, Ltag>::f = &mcl_fp_subPre ## n ## L; \
template<>const void2u Shr1<n, Ltag>::f = &mcl_fp_shr1_ ## n ## L; \
MCL_DEF_MUL(n) \
template<>const void2uI MulUnitPre<n, Ltag>::f = &mcl_fp_mulUnitPre ## n ## L; \
template<>const void4u Add<n, true, Ltag>::f = &mcl_fp_add ## n ## L; \
template<>const void4u Add<n, false, Ltag>::f = &mcl_fp_addNF ## n ## L; \
template<>const void4u Sub<n, true, Ltag>::f = &mcl_fp_sub ## n ## L; \
template<>const void4u Sub<n, false, Ltag>::f = &mcl_fp_subNF ## n ## L; \
template<>const void4u Mont<n, true, Ltag>::f = &mcl_fp_mont ## n ## L; \
template<>const void4u Mont<n, false, Ltag>::f = &mcl_fp_montNF ## n ## L; \
template<>const void3u MontRed<n, Ltag>::f = &mcl_fp_montRed ## n ## L; \
template<>const void4u DblAdd<n, Ltag>::f = &mcl_fpDbl_add ## n ## L; \
template<>const void4u DblSub<n, Ltag>::f = &mcl_fpDbl_sub ## n ## L; \

MCL_DEF_LLVM_FUNC(1)
MCL_DEF_LLVM_FUNC(2)
MCL_DEF_LLVM_FUNC(3)
MCL_DEF_LLVM_FUNC(4)
MCL_DEF_LLVM_FUNC(5)
MCL_DEF_LLVM_FUNC(6)
MCL_DEF_LLVM_FUNC(7)
MCL_DEF_LLVM_FUNC(8)
MCL_DEF_LLVM_FUNC(9)
#if CYBOZU_OS_BIT == 32 || MCL_MAX_BIT_SIZE == 768
MCL_DEF_LLVM_FUNC(10)
MCL_DEF_LLVM_FUNC(11)
MCL_DEF_LLVM_FUNC(12)
#endif
#if CYBOZU_OS_BIT == 32
MCL_DEF_LLVM_FUNC(13)
MCL_DEF_LLVM_FUNC(14)
MCL_DEF_LLVM_FUNC(15)
MCL_DEF_LLVM_FUNC(16)
MCL_DEF_LLVM_FUNC(17)
#endif

} } // mcl::fp

