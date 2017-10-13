#ifndef NFTABLES_GMPUTIL_H
#define NFTABLES_GMPUTIL_H

#include <config.h>

#ifdef HAVE_LIBGMP
#include <gmp.h>
#else
#include <mini-gmp.h>
/* mini-gmp doesn't come with gmp_printf, so we use our own minimal variant */
extern int mpz_printf(const char *format, const mpz_t value);
#define gmp_printf mpz_printf
#endif

#include <asm/byteorder.h>

enum mpz_word_order {
	MPZ_MSWF		= 1,
	MPZ_LSWF		= -1,
};

#ifdef __LITTLE_ENDIAN_BITFIELD
#define MPZ_HWO	MPZ_LSWF
#elif defined(__BIG_ENDIAN_BITFIELD)
#define MPZ_HWO MPZ_MSWF
#else
#error "byteorder undefined"
#endif

enum mpz_byte_order {
	MPZ_BIG_ENDIAN		= 1,
	MPZ_HOST_ENDIAN		= 0,
	MPZ_LITTLE_ENDIAN	= -1,
};

extern void mpz_bitmask(mpz_t rop, unsigned int width);
extern void mpz_init_bitmask(mpz_t rop, unsigned int width);
extern void mpz_prefixmask(mpz_t rop, unsigned int width, unsigned int prefix_len);

extern void mpz_lshift_ui(mpz_t rop, unsigned int n);
extern void mpz_rshift_ui(mpz_t rop, unsigned int n);

extern uint64_t mpz_get_uint64(const mpz_t op);
extern uint32_t mpz_get_uint32(const mpz_t op);
extern uint16_t mpz_get_uint16(const mpz_t op);
extern uint8_t mpz_get_uint8(const mpz_t op);

extern uint32_t mpz_get_be32(const mpz_t op);
extern uint16_t mpz_get_be16(const mpz_t op);

enum byteorder;
extern void *mpz_export_data(void *data, const mpz_t op,
			     enum byteorder byteorder,
			     unsigned int len);
extern void mpz_import_data(mpz_t rop, const void *data,
			    enum byteorder byteorder,
			    unsigned int len);
extern void mpz_switch_byteorder(mpz_t rop, unsigned int len);

#endif /* NFTABLES_GMPUTIL_H */
