# Copyright (C) 2005-2011 MaNGOS <http://www.getmangos.com/>
#
# Copyright (C) 2008-2011 Trinity <http://www.trinitycore.org/>
#
# Copyright (C) 2010-2011 Project SkyFire <http://www.projectskyfire.org/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

set(StormLib_SRCS
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/adpcm/adpcm.cpp
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/huffman/huff.cpp
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/jenkins/lookup3.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/sparse/sparse.cpp
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/StormLib.h
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/StormPort.h
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/FileStream.cpp
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/SBaseCommon.cpp
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/SBaseFileTable.cpp
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/SCompression.cpp
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/SFileAddFile.cpp
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/SFileAttributes.cpp
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/SFileCompactArchive.cpp
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/SFileCreateArchive.cpp
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/SFileExtractFile.cpp
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/SFileFindFile.cpp
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/SFileListFile.cpp
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/SFileOpenArchive.cpp
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/SFileOpenFileEx.cpp
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/SFilePatchArchives.cpp
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/SFileReadFile.cpp
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/SFileVerify.cpp
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/hashes/hash_memory.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/hashes/md5.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/hashes/sha1.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/math/ltm_desc.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/math/multi.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/math/rand_prime.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/misc/base64_decode.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/misc/crypt_argchk.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/misc/crypt_find_hash.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/misc/crypt_find_prng.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/misc/crypt_hash_descriptor.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/misc/crypt_hash_is_valid.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/misc/crypt_libc.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/misc/crypt_ltc_mp_descriptor.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/misc/crypt_prng_descriptor.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/misc/crypt_prng_is_valid.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/misc/crypt_register_hash.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/misc/crypt_register_prng.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/misc/zeromem.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/asn1/der_decode_bit_string.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/asn1/der_decode_boolean.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/asn1/der_decode_choice.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/asn1/der_decode_ia5_string.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/asn1/der_decode_integer.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/asn1/der_decode_object_identifier.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/asn1/der_decode_octet_string.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/asn1/der_decode_printable_string.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/asn1/der_decode_sequence_ex.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/asn1/der_decode_sequence_flexi.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/asn1/der_decode_sequence_multi.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/asn1/der_decode_short_integer.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/asn1/der_decode_utctime.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/asn1/der_decode_utf8_string.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/asn1/der_length_bit_string.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/asn1/der_length_boolean.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/asn1/der_length_ia5_string.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/asn1/der_length_integer.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/asn1/der_length_object_identifier.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/asn1/der_length_octet_string.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/asn1/der_length_printable_string.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/asn1/der_length_sequence.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/asn1/der_length_utctime.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/asn1/der_sequence_free.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/asn1/der_length_utf8_string.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/asn1/der_length_short_integer.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/ecc/ltc_ecc_map.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/ecc/ltc_ecc_mul2add.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/ecc/ltc_ecc_mulmod.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/ecc/ltc_ecc_points.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/ecc/ltc_ecc_projective_add_point.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/ecc/ltc_ecc_projective_dbl_point.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/pkcs1/pkcs_1_mgf1.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/pkcs1/pkcs_1_oaep_decode.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/pkcs1/pkcs_1_pss_decode.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/pkcs1/pkcs_1_v1_5_decode.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/rsa/rsa_exptmod.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/rsa/rsa_free.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/rsa/rsa_import.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/rsa/rsa_make_key.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/rsa/rsa_verify_hash.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtomcrypt/src/pk/rsa/rsa_verify_simple.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bncore.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_fast_mp_invmod.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_fast_mp_montgomery_reduce.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_fast_s_mp_mul_digs.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_fast_s_mp_mul_high_digs.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_fast_s_mp_sqr.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_2expt.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_abs.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_add.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_addmod.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_add_d.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_and.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_clamp.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_clear.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_clear_multi.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_cmp.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_cmp_d.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_cmp_mag.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_cnt_lsb.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_copy.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_count_bits.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_div.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_div_2.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_div_2d.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_div_3.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_div_d.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_dr_is_modulus.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_dr_reduce.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_dr_setup.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_exch.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_exptmod.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_exptmod_fast.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_expt_d.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_exteuclid.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_fread.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_fwrite.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_gcd.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_get_int.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_grow.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_init.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_init_copy.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_init_multi.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_init_set.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_init_set_int.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_init_size.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_invmod.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_invmod_slow.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_is_square.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_jacobi.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_karatsuba_mul.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_karatsuba_sqr.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_lcm.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_lshd.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_mod.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_mod_2d.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_mod_d.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_montgomery_calc_normalization.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_montgomery_reduce.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_montgomery_setup.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_mul.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_mulmod.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_mul_2.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_mul_2d.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_mul_d.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_neg.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_n_root.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_or.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_prime_fermat.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_prime_is_divisible.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_prime_is_prime.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_prime_miller_rabin.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_prime_next_prime.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_prime_rabin_miller_trials.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_prime_random_ex.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_radix_size.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_radix_smap.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_rand.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_read_radix.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_read_signed_bin.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_read_unsigned_bin.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_reduce.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_reduce_2k.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_reduce_2k_l.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_reduce_2k_setup.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_reduce_2k_setup_l.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_reduce_is_2k.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_reduce_is_2k_l.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_reduce_setup.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_rshd.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_set.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_set_int.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_shrink.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_signed_bin_size.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_sqr.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_sqrmod.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_sqrt.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_sub.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_submod.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_sub_d.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_toom_mul.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_toom_sqr.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_toradix.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_toradix_n.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_to_signed_bin.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_to_signed_bin_n.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_to_unsigned_bin.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_to_unsigned_bin_n.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_unsigned_bin_size.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_xor.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_mp_zero.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_prime_tab.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_reverse.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_s_mp_add.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_s_mp_exptmod.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_s_mp_mul_digs.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_s_mp_mul_high_digs.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_s_mp_sqr.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/libtommath/bn_s_mp_sub.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/lzma/C/LzFind.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/lzma/C/LzmaDec.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/lzma/C/LzmaEnc.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/pklib/explode.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/pklib/implode.c
)

set(ZLIB_BZIP2_FILES
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/bzip2/blocksort.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/bzip2/bzlib.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/bzip2/compress.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/bzip2/crctable.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/bzip2/decompress.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/bzip2/huffman.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/bzip2/randtable.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/zlib/adler32.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/zlib/compress2.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/zlib/crc32.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/zlib/deflate.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/zlib/inffast.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/zlib/inflate.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/zlib/inftrees.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/zlib/trees.c
           ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/zlib/zutil.c
)

set(extractor_SRCS
	${CMAKE_CURRENT_SOURCE_DIR}/adt.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/adt.h
	${CMAKE_CURRENT_SOURCE_DIR}/dbc.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dbc.h
	${CMAKE_CURRENT_SOURCE_DIR}/DBCFile.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/DBCFile.h
	${CMAKE_CURRENT_SOURCE_DIR}/FileLoader.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/FileLoader.h
	${CMAKE_CURRENT_SOURCE_DIR}/headers.h
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/map.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/map.h
	${CMAKE_CURRENT_SOURCE_DIR}/misc.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/misc.h
	${CMAKE_CURRENT_SOURCE_DIR}/MPQ.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/MPQ.h
	${CMAKE_CURRENT_SOURCE_DIR}/MPQFile.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/MPQFile.h
	${CMAKE_CURRENT_SOURCE_DIR}/typedefs.h
	${CMAKE_CURRENT_SOURCE_DIR}/wdt.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/wdt.h
	
)

set(extractor_C_FLAGS "-D_7ZIP_ST -DBZ_STRICT_ANSI")

if(WIN32)
    if(MSVC)
        set(extractor_C_FLAGS "-D_7ZIP_ST -DWIN32")
    endif()
    set(extractor_SRC_ADDITIONAL_FILES ${ZLIB_BZIP2_FILES})
endif()

if(APPLE)
    set(extractor_LINK_FLAGS "-lz -lbz2 -framework Carbon")
    set(extractor_PUBLIC_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/StormLib.h ${CMAKE_CURRENT_SOURCE_DIR}/StormLib/src/StormPort.h)
endif()

if (${CMAKE_SYSTEM_NAME} STREQUAL Linux)
    set(extractor_LINK_FLAGS "-lz -lbz2")
endif()

add_executable(extractor ${StormLib_SRCS}  ${ZLIB_BZIP2_FILES} ${extractor_SRCS})

if(APPLE)
	set_target_properties(extractor PROPERTIES COMPILE_FLAGS "${extractor_C_FLAGS}" LINK_FLAGS "${extractor_LINK_FLAGS}" PUBLIC_HEADER "${PUBLIC_HEADERS}")
else()
	set_target_properties(extractor PROPERTIES COMPILE_FLAGS "${extractor_C_FLAGS}" LINK_FLAGS "${extractor_LINK_FLAGS}")
endif()

if( UNIX )
  install(TARGETS extractor DESTINATION bin)
elseif( WIN32 )
  install(TARGETS extractor DESTINATION "${CMAKE_INSTALL_PREFIX}")
endif()