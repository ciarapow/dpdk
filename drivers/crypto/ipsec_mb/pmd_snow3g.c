/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2016-2021 Intel Corporation
 */

#include "pmd_snow3g_priv.h"
#include "pmd_aesni_mb_priv.h"

struct rte_cryptodev_ops snow3g_pmd_ops = {
	.dev_configure = ipsec_mb_config,
	.dev_start = ipsec_mb_start,
	.dev_stop = ipsec_mb_stop,
	.dev_close = ipsec_mb_close,

	.stats_get = ipsec_mb_stats_get,
	.stats_reset = ipsec_mb_stats_reset,

	.dev_infos_get = ipsec_mb_info_get,

	.queue_pair_setup = ipsec_mb_qp_setup,
	.queue_pair_release = ipsec_mb_qp_release,

	.sym_session_get_size = ipsec_mb_sym_session_get_size,
	.sym_session_configure = ipsec_mb_sym_session_configure,
	.sym_session_clear = ipsec_mb_sym_session_clear
};

struct rte_cryptodev_ops *rte_snow3g_pmd_ops = &snow3g_pmd_ops;

static int
snow3g_probe(struct rte_vdev_device *vdev)
{
	return ipsec_mb_create(vdev, IPSEC_MB_PMD_TYPE_SNOW3G);
}

static struct rte_vdev_driver cryptodev_snow3g_pmd_drv = {
	.probe = snow3g_probe,
	.remove = ipsec_mb_remove
};

static struct cryptodev_driver snow3g_crypto_drv;

RTE_PMD_REGISTER_VDEV(CRYPTODEV_NAME_SNOW3G_PMD, cryptodev_snow3g_pmd_drv);
RTE_PMD_REGISTER_ALIAS(CRYPTODEV_NAME_SNOW3G_PMD, cryptodev_snow3g_pmd);
RTE_PMD_REGISTER_PARAM_STRING(CRYPTODEV_NAME_SNOW3G_PMD,
			       "max_nb_queue_pairs=<int> socket_id=<int>");
RTE_PMD_REGISTER_CRYPTO_DRIVER(snow3g_crypto_drv,
				cryptodev_snow3g_pmd_drv.driver,
				pmd_driver_id_snow3g);

/* Constructor function to register snow3g PMD */
RTE_INIT(ipsec_mb_register_snow3g)
{
	struct ipsec_mb_internals *snow3g_data
		= &ipsec_mb_pmds[IPSEC_MB_PMD_TYPE_SNOW3G];

	snow3g_data->caps = snow3g_capabilities;
	snow3g_data->dequeue_burst = aesni_mb_dequeue_burst;
	snow3g_data->feature_flags = RTE_CRYPTODEV_FF_SYMMETRIC_CRYPTO |
			RTE_CRYPTODEV_FF_SYM_OPERATION_CHAINING |
			RTE_CRYPTODEV_FF_NON_BYTE_ALIGNED_DATA |
			RTE_CRYPTODEV_FF_SYM_SESSIONLESS |
			RTE_CRYPTODEV_FF_OOP_LB_IN_LB_OUT |
			RTE_CRYPTODEV_FF_DIGEST_ENCRYPTED;
	snow3g_data->internals_priv_size = 0;
	snow3g_data->ops = &snow3g_pmd_ops;
	snow3g_data->qp_priv_size = sizeof(struct aesni_mb_qp_data);
	snow3g_data->session_configure = aesni_mb_session_configure;
	snow3g_data->session_priv_size =
			sizeof(struct aesni_mb_session);
}
