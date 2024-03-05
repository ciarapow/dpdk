/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2016-2021 Intel Corporation
 */

#ifndef _PMD_ZUC_PRIV_H_
#define _PMD_ZUC_PRIV_H_

#include "ipsec_mb_private.h"

#define ZUC_IV_KEY_LENGTH 16
#define ZUC_DIGEST_LENGTH 4
#define ZUC_MAX_BURST 16

uint8_t pmd_driver_id_zuc;

static const struct rte_cryptodev_capabilities zuc_capabilities[] = {
	{	/* ZUC (EIA3) */
		.op = RTE_CRYPTO_OP_TYPE_SYMMETRIC,
		{.sym = {
			.xform_type = RTE_CRYPTO_SYM_XFORM_AUTH,
			{.auth = {
				.algo = RTE_CRYPTO_AUTH_ZUC_EIA3,
				.block_size = 16,
				.key_size = {
					.min = 16,
					.max = 16,
					.increment = 0
				},
				.digest_size = {
					.min = ZUC_DIGEST_LENGTH,
					.max = ZUC_DIGEST_LENGTH,
					.increment = 0
				},
				.iv_size = {
					.min = ZUC_IV_KEY_LENGTH,
					.max = ZUC_IV_KEY_LENGTH,
					.increment = 0
				}
			}, }
		}, }
	},
	{	/* ZUC (EEA3) */
		.op = RTE_CRYPTO_OP_TYPE_SYMMETRIC,
		{.sym = {
			.xform_type = RTE_CRYPTO_SYM_XFORM_CIPHER,
			{.cipher = {
				.algo = RTE_CRYPTO_CIPHER_ZUC_EEA3,
				.block_size = 16,
				.key_size = {
					.min = 16,
					.max = 16,
					.increment = 0
				},
				.iv_size = {
					.min = ZUC_IV_KEY_LENGTH,
					.max = ZUC_IV_KEY_LENGTH,
					.increment = 0
				},
			}, }
		}, }
	},
	RTE_CRYPTODEV_END_OF_CAPABILITIES_LIST()
};

#endif /* _PMD_ZUC_PRIV_H_ */
