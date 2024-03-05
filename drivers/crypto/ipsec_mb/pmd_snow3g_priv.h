/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2016-2021 Intel Corporation
 */

#ifndef _PMD_SNOW3G_PRIV_H_
#define _PMD_SNOW3G_PRIV_H_

#include "ipsec_mb_private.h"

#define SNOW3G_IV_LENGTH 16
#define SNOW3G_DIGEST_LENGTH 4

uint8_t pmd_driver_id_snow3g;

static const struct rte_cryptodev_capabilities snow3g_capabilities[] = {
	{	/* SNOW 3G (UIA2) */
		.op = RTE_CRYPTO_OP_TYPE_SYMMETRIC,
		{.sym = {
			.xform_type = RTE_CRYPTO_SYM_XFORM_AUTH,
			{.auth = {
				.algo = RTE_CRYPTO_AUTH_SNOW3G_UIA2,
				.block_size = 16,
				.key_size = {
					.min = 16,
					.max = 16,
					.increment = 0
				},
				.digest_size = {
					.min = SNOW3G_DIGEST_LENGTH,
					.max = SNOW3G_DIGEST_LENGTH,
					.increment = 0
				},
				.iv_size = {
					.min = SNOW3G_IV_LENGTH,
					.max = SNOW3G_IV_LENGTH,
					.increment = 0
				}
			}, }
		}, }
	},
	{	/* SNOW 3G (UEA2) */
		.op = RTE_CRYPTO_OP_TYPE_SYMMETRIC,
		{.sym = {
			.xform_type = RTE_CRYPTO_SYM_XFORM_CIPHER,
			{.cipher = {
				.algo = RTE_CRYPTO_CIPHER_SNOW3G_UEA2,
				.block_size = 16,
				.key_size = {
					.min = 16,
					.max = 16,
					.increment = 0
				},
				.iv_size = {
					.min = SNOW3G_IV_LENGTH,
					.max = SNOW3G_IV_LENGTH,
					.increment = 0
				}
			}, }
		}, }
	},
	RTE_CRYPTODEV_END_OF_CAPABILITIES_LIST()
};

#endif /* _PMD_SNOW3G_PRIV_H_ */
