#include <zephyr/kernel.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main, CONFIG_MAIN_LOG_LEVEL);

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/uuid.h>

#define SERVICE_UUID            0xfcd2      /* BTHome service UUID */

#define ADV_PARAM BT_LE_ADV_PARAM(BT_LE_ADV_OPT_USE_IDENTITY, \
				  BT_GAP_ADV_SLOW_INT_MIN, \
				  BT_GAP_ADV_SLOW_INT_MAX, NULL)

/* Static sample service data */
static uint8_t service_data[] = {
	BT_UUID_16_ENCODE(SERVICE_UUID),
	0x40,
	0x02,	/* Temperature */
	0xc4,	/* Low byte */
	0x00,   /* High byte */
	0x03,	/* Humidity */
	0xbf,	/* 50.55%  low byte*/
	0x13,   /* 50.55%  high byte*/
};

static struct bt_data ad_data[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR),
	BT_DATA(BT_DATA_NAME_COMPLETE, CONFIG_BT_DEVICE_NAME, sizeof(CONFIG_BT_DEVICE_NAME) - 1),
	BT_DATA(BT_DATA_SVC_DATA16, service_data, ARRAY_SIZE(service_data))
};

int main(void)
{
	int ret;

	LOG_INF("Initializing bluetooth.");

	ret = bt_enable(NULL);
	if (ret) {
		LOG_ERR("Bluetooth init failed: '%s'", strerror(ret));
		return 0;
	}

	LOG_INF("Starting to advertise.");

	ret = bt_le_adv_start(ADV_PARAM, ad_data, ARRAY_SIZE(ad_data), NULL, 0);
	if (ret) {
		LOG_ERR("Starting advertising failed: '%s'", strerror(ret));
		return 0;
	}

	for (;;) {
		LOG_INF("Sending update.");

		ret = bt_le_adv_update_data(ad_data, ARRAY_SIZE(ad_data), NULL, 0);

		if (ret) {
			LOG_ERR("Failed to update advertising data: '%s'", strerror(ret));
		}

		k_sleep(K_MSEC(BT_GAP_ADV_SLOW_INT_MIN));
	}

	return 0;
}
