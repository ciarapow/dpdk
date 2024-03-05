/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2016-2021 Intel Corporation
 */

#include "pmd_zuc_priv.h"
#include "pmd_aesni_mb_priv.h"

struct rte_cryptodev_ops zuc_pmd_ops = {
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

struct rte_cryptodev_ops *rte_zuc_pmd_ops = &zuc_pmd_ops;

static int
zuc_probe(struct rte_vdev_device *vdev)
{
	return ipsec_mb_create(vdev, IPSEC_MB_PMD_TYPE_ZUC);
}

static struct rte_vdev_driver cryptodev_zuc_pmd_drv = {
	.probe = zuc_probe,
	.remove = ipsec_mb_remove

};

static struct cryptodev_driver zuc_crypto_drv;

RTE_PMD_REGISTER_VDEV(CRYPTODEV_NAME_ZUC_PMD, cryptodev_zuc_pmd_drv);
RTE_PMD_REGISTER_ALIAS(CRYPTODEV_NAME_ZUC_PMD, cryptodev_zuc_pmd);
RTE_PMD_REGISTER_PARAM_STRING(CRYPTODEV_NAME_ZUC_PMD,
	"max_nb_queue_pairs=<int> socket_id=<int>");
RTE_PMD_REGISTER_CRYPTO_DRIVER(zuc_crypto_drv, cryptodev_zuc_pmd_drv.driver,
		pmd_driver_id_zuc);

/* Constructor function to register zuc PMD */
RTE_INIT(ipsec_mb_register_zuc)
{
	struct ipsec_mb_internals *zuc_data
	    = &ipsec_mb_pmds[IPSEC_MB_PMD_TYPE_ZUC];

	zuc_data->caps = zuc_capabilities;
	zuc_data->dequeue_burst = aesni_mb_dequeue_burst;
	zuc_data->feature_flags = RTE_CRYPTODEV_FF_SYMMETRIC_CRYPTO
			| RTE_CRYPTODEV_FF_SYM_OPERATION_CHAINING
			| RTE_CRYPTODEV_FF_NON_BYTE_ALIGNED_DATA
			| RTE_CRYPTODEV_FF_OOP_SGL_IN_LB_OUT
			| RTE_CRYPTODEV_FF_SYM_SESSIONLESS
			| RTE_CRYPTODEV_FF_OOP_LB_IN_LB_OUT;
	zuc_data->internals_priv_size = 0;
	zuc_data->ops = &zuc_pmd_ops;
	zuc_data->qp_priv_size = sizeof(struct aesni_mb_qp_data);
	zuc_data->session_configure = aesni_mb_session_configure;
	zuc_data->session_priv_size =
			sizeof(struct aesni_mb_session);
}
